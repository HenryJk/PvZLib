#include "pvz.hpp"

#include <memoryapi.h>
#include <processthreadsapi.h>
#include <unordered_map>
#include <vector>

namespace {
    std::vector<pvz::Event *> events;
    std::unordered_map<uintptr_t, std::vector<uint8_t>> original_codes;
    std::vector<uint8_t *> trampolines;

    struct Trampoline {
        pvz::Event *mEvent;
        uint8_t *mCode;
        uint32_t mNext;

        Trampoline(pvz::Event *event) {
            mEvent = event;
            events.push_back(event);
            mCode = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
            trampolines.push_back(mCode);
            mCode[0] = 0x60; // pushad;
            mNext    = 1;
        }

        Trampoline &AddCustomInstructions(uint8_t *instructions, uint32_t length) {
            memcpy(&mCode[mNext], instructions, length);
            mNext += length;
            return *this;
        }

        Trampoline &AddCallHandler(uintptr_t handler) {
            mCode[mNext]                   = 0x68; // push mEvent
            (uintptr_t &) mCode[mNext + 1] = (uintptr_t) mEvent;
            mCode[mNext + 5]               = 0xE8;
            (uintptr_t &) mCode[mNext + 6] = handler - (uintptr_t) &mCode[mNext + 10];
            mCode[mNext + 10]              = 0x83; // add esp, 4
            mCode[mNext + 11]              = 0xC4;
            mCode[mNext + 12]              = 0x04;
            mCode[mNext + 13]              = 0x61; // popad;
            mNext += 14;
            return *this;
        }

        Trampoline &AddBackJump(uintptr_t injection_address, uint32_t code_length) {
            mCode[mNext]                   = 0xE9; // jmp injection_address+code_length;
            (uintptr_t &) mCode[mNext + 1] = injection_address + code_length - (uintptr_t) &mCode[mNext + 5];
            mNext += 5;
            return *this;
        }

        void Inject(uintptr_t injection_address) {
            for (int i = 0; i < 5; i++) original_codes[injection_address].push_back(((uint8_t *) injection_address)[i]);
            uint8_t patch[5];
            patch[0]               = 0xE9; // jmp trampoline;
            (uintptr_t &) patch[1] = (uintptr_t) mCode - (injection_address + 5);
            WriteProcessMemory(GetCurrentProcess(), (void *) injection_address, patch, sizeof(patch), nullptr);
        }
    };

    void InjectBoardDrawGameObjects(void (*handler)(pvz::Event *)) {
        auto event = new pvz::Event;
#ifdef VERSION_1_0_0_1051_EN
        auto injection_address = 0x417350;
        Trampoline(event)
                .AddCallHandler((uintptr_t) handler)
                .AddCustomInstructions((uint8_t *) injection_address, 6)
                .Inject(injection_address);
#endif
    }

    void InjectBoardUpdateGameObjects(void (*handler)(pvz::Event *)) {
        auto event = new pvz::Event;
#ifdef VERSION_1_0_0_1051_EN
        auto injection_address = 0x413210;
        Trampoline(event)
                .AddCallHandler((uintptr_t) handler)
                .AddCustomInstructions((uint8_t *) injection_address, 1)
                .Inject(injection_address);
#endif
    }

    void InjectPlantDraw(void (*handler)(pvz::Event *)) {
        auto event = new pvz::Event;
#ifdef VERSION_1_0_0_1051_EN
        auto injection_address = 0x4660A5;

        // mov eax, [esp + 24h];
        // mov &event->mPlant, eax;
        uint8_t event_builder[]        = {0x8B, 0x44, 0x24, 0x24, 0xA3, 0x00, 0x00, 0x00, 0x00};
        (uintptr_t &) event_builder[5] = (uintptr_t) &(event->mPlant);

        Trampoline(event)
                .AddCustomInstructions(event_builder, sizeof(event_builder))
                .AddCallHandler((uintptr_t) handler)
                .AddCustomInstructions((uint8_t *) injection_address, 5)
                .AddBackJump(injection_address, 5)
                .Inject(injection_address);
#endif
    }
} // namespace

namespace pvz {
    void Event::InjectEventHandler(EventType type, void (*handler)(Event *)) {
        switch (type) {
            case EventType::kBoard_DrawGameObjects:
                InjectBoardDrawGameObjects(handler);
                break;
            case EventType::kBoard_UpdateGameObjects:
                InjectBoardUpdateGameObjects(handler);
                break;
            case EventType::kPlant_Draw:
                InjectPlantDraw(handler);
                break;
            default:
                break;
        }
    }
} // namespace pvz
