#include "pvz.hpp"

#include <memoryapi.h>
#include <processthreadsapi.h>
#include <unordered_map>
#include <vector>

namespace {
    using namespace std;
    using namespace pvz;

    enum Register {
        EAX = -0x04,
        ECX = -0x08,
        EDX = -0x0C,
        EBX = -0x10,
        ESP = -0x14,
        EBP = -0x18,
        ESI = -0x1C,
        EDI = -0x20,
    };

    vector<Event *> events;
    unordered_map<uintptr_t, vector<uint8_t>> original_codes;
    vector<uint8_t *> trampolines;

    struct Trampoline {
        Event *mEvent;
        uint8_t *mCode;
        uint32_t mNext = 0;

        explicit Trampoline(pvz::Event *event) {
            mEvent = event;
            events.push_back(event);
            mCode = (uint8_t *) VirtualAlloc(nullptr, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
            trampolines.push_back(mCode);
        }

        Trampoline &AddRegisterPreservation() {
            mCode[mNext] = 0x60; // pushad;
            mNext        = mNext + 1;
            return *this;
        }

        Trampoline &AddRegisterRestoration() {
            mCode[mNext] = 0x61; // popad;
            mNext        = mNext + 1;
            return *this;
        }

        Trampoline &AddCustomInstructions(uint8_t *instructions, uint32_t length) {
            memcpy(&mCode[mNext], instructions, length);
            mNext += length;
            return *this;
        }

        Trampoline &AddCallHandler(void (*handler)(pvz::Event *)) {
            if (handler == nullptr) return *this;
            mCode[mNext]                   = 0x68; // push mEvent
            (uintptr_t &) mCode[mNext + 1] = (uintptr_t) mEvent;
            mCode[mNext + 5]               = 0xE8;
            (uintptr_t &) mCode[mNext + 6] = (uintptr_t) handler - (uintptr_t) &mCode[mNext + 10];
            mCode[mNext + 10]              = 0x83; // add esp, 4
            mCode[mNext + 11]              = 0xC4;
            mCode[mNext + 12]              = 0x04;
            mNext += 13;
            return *this;
        }

        Trampoline &AddBackJump(uintptr_t back_address) {
            mCode[mNext]                   = 0xE9; // jmp back_address;
            (uintptr_t &) mCode[mNext + 1] = back_address - (uintptr_t) &mCode[mNext + 5];
            mNext += 5;
            return *this;
        }

        void Inject(uintptr_t injection_address) const {
            for (int i = 0; i < 5; i++) original_codes[injection_address].push_back(((uint8_t *) injection_address)[i]);
            uint8_t patch[5];
            patch[0]               = 0xE9; // jmp trampoline;
            (uintptr_t &) patch[1] = (uintptr_t) mCode - (injection_address + 5);
            WriteProcessMemory(GetCurrentProcess(), (void *) injection_address, patch, sizeof(patch), nullptr);
        }
    };

    struct Injector {
        Event *mEvent = new Event;
        pair<uintptr_t, uint32_t> mEntryPoint;
        vector<pair<uintptr_t, uint32_t>> mExitPoints;
        vector<int32_t> mParamOffsets;
        EventHandler mPreEventHandler  = nullptr;
        EventHandler mPostEventHandler = nullptr;

        Injector() = default;

        Injector &EntryPoint(pair<uintptr_t, uint32_t> entry_point) {
            mEntryPoint = entry_point;
            return *this;
        }

        Injector &ExitPoints(vector<pair<uintptr_t, uint32_t>> &exit_points) {
            mExitPoints = exit_points;
            return *this;
        }

        Injector &ParamOffsets(vector<int32_t> &parameter_offsets) {
            mParamOffsets = parameter_offsets;
            return *this;
        }

        Injector &PreEventHandler(EventHandler pre_event_handler) {
            mPreEventHandler = pre_event_handler;
            return *this;
        }

        Injector &PostEventHandler(EventHandler post_event_handler) {
            mPostEventHandler = post_event_handler;
            return *this;
        }

        void Inject() {
            vector<uint8_t> event_builder;
            for (int i = 0; i < mParamOffsets.size(); i++) {
                event_builder.push_back(0x8B); // mov eax, [esp + 0x20 + mParameterOffsets[i]];
                event_builder.push_back(0x44);
                event_builder.push_back(0x24);
                event_builder.push_back(0x20 + mParamOffsets[i]);
                event_builder.push_back(0xA3); // mov [&mEvent->mParams[i]], eax;
                event_builder.push_back(((uint32_t) &mEvent->mParams[i] >> 0) & 0xFF);
                event_builder.push_back(((uint32_t) &mEvent->mParams[i] >> 8) & 0xFF);
                event_builder.push_back(((uint32_t) &mEvent->mParams[i] >> 16) & 0xFF);
                event_builder.push_back(((uint32_t) &mEvent->mParams[i] >> 24) & 0xFF);
            }
            Trampoline(mEvent)
                    .AddRegisterPreservation()
                    .AddCustomInstructions(&event_builder[0], event_builder.size())
                    .AddCallHandler(mPreEventHandler)
                    .AddRegisterRestoration()
                    .AddCustomInstructions((uint8_t *) mEntryPoint.first, mEntryPoint.second)
                    .AddBackJump(mEntryPoint.first + mEntryPoint.second)
                    .Inject(mEntryPoint.first);

            for (auto &[address, num_bytes] : mExitPoints) {
                Trampoline(mEvent)
                        .AddRegisterPreservation()
                        .AddCallHandler(mPostEventHandler)
                        .AddRegisterRestoration()
                        .AddCustomInstructions((uint8_t *) address, num_bytes)
                        .Inject(address);
            }
        }
    };
} // namespace

namespace pvz {
    void Event::InjectEventHandler(EventType type, EventHandler pre_event_handler, EventHandler post_event_handler) {
        pair<uintptr_t, uint32_t> entry_point;
        vector<pair<uintptr_t, uint32_t>> exit_points;
        vector<int32_t> param_offsets;
        switch (type) {
#ifdef VERSION_1_0_0_1051_EN
            case EventType::kBoard_DrawGameObjects:
                entry_point   = {0x416880, 6};
                exit_points   = {{0x417350, 6}};
                param_offsets = {0x04};
                break;
            case EventType::kBoard_KillAllPlantsInRadius:
                entry_point   = {0x41CBF0, 8};
                exit_points   = {{0x41CC4F, 6}};
                param_offsets = {EDX, 0x04, EBX};
                break;
            case EventType::kBoard_UpdateGameObjects:
                entry_point   = {0x4130D0, 5};
                exit_points   = {{0x413210, 1}};
                param_offsets = {0x04};
                break;
            case EventType::kPlant_BlowAwayFliers:
                entry_point   = {0x4665B0, 5};
                exit_points   = {{0x466649, 6}};
                param_offsets = {0x04};
                break;
            case EventType::kPlant_BurnRow:
                entry_point   = {0x4664B0, 5};
                exit_points   = {{0x466649, 6}};
                param_offsets = {0x08, 0x04};
                break;
            case EventType::kPlant_CobCannonFire:
                entry_point   = {0x466D50, 7};
                exit_points   = {{0x466DFB, 4}};
                param_offsets = {EAX, ECX, ESI};
                break;
            case EventType::kPlant_Die:
                entry_point   = {0x4679B0, 5};
                exit_points   = {{0x467AF9, 3}};
                param_offsets = {0x04};
                break;
            case EventType::kPlant_Fire:
                entry_point = {0x466E00, 8};
                exit_points = {
                        {0x467553, 3},
                        {0x466E7C, 6},
                        {0x466E93, 6},
                        {0x467349, 6},
                        {0x467430, 6},
                        {0x46737B, 6},
                        {0x4673AA, 6},
                        {0x46741f, 6},
                };
                param_offsets = {0x04, 0x08, 0x0C, 0x10};
                break;
            default:
                break;
#endif
        }
        Injector()
                .EntryPoint(entry_point)
                .ExitPoints(exit_points)
                .ParamOffsets(param_offsets)
                .PreEventHandler(pre_event_handler)
                .PostEventHandler(post_event_handler)
                .Inject();
    }
} // namespace pvz
