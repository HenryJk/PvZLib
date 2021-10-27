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
        Event *mEvent;
        pair<uintptr_t, uint32_t> mEntryPoint;
        vector<int32_t> mParamOffsets;
        vector<pair<uintptr_t, uint32_t>> mExitPoints;
        EventHandler mPreEventHandler  = nullptr;
        EventHandler mPostEventHandler = nullptr;

        Injector(Event *event) { mEvent = event; }

        Injector &EntryPoint(pair<uintptr_t, uint32_t> entry_point) {
            mEntryPoint = entry_point;
            return *this;
        }

        Injector &ParamOffsets(vector<int32_t> &parameter_offsets) {
            mParamOffsets = parameter_offsets;
            return *this;
        }

        Injector &ExitPoints(vector<pair<uintptr_t, uint32_t>> &exit_points) {
            mExitPoints = exit_points;
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
        auto event = new Event;
        pair<uintptr_t, uint32_t> entry_point;
        vector<int32_t> param_offsets;
        vector<pair<uintptr_t, uint32_t>> exit_points;
        switch (type) {
#ifdef VERSION_1_0_0_1051_EN
            case EventType::kBoard_DrawGameObjects:
                entry_point   = {0x416880, 6};
                param_offsets = {0x04};
                exit_points   = {{0x417350, 6}};
                break;
            case EventType::kBoard_KillAllPlantsInRadius:
                entry_point   = {0x41CBF0, 8};
                param_offsets = {EDX, 0x04, EBX};
                exit_points   = {{0x41CC4F, 6}};
                break;
            case EventType::kBoard_KillAllZombiesInRadius:
                entry_point   = {0x41D8A0, 6};
                param_offsets = {0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20};
                exit_points   = {{0x41DA09, 3}};
                break;
            case EventType::kBoard_UpdateGameObjects:
                entry_point   = {0x4130D0, 5};
                param_offsets = {0x04};
                exit_points   = {{0x413210, 1}};
                break;
            case EventType::kPlant_BlowAwayFliers:
                entry_point   = {0x4665B0, 5};
                param_offsets = {0x04};
                exit_points   = {{0x466649, 6}};
                break;
            case EventType::kPlant_BurnRow:
                entry_point   = {0x4664B0, 5};
                param_offsets = {0x08, 0x04};
                exit_points   = {{0x466649, 6}};
                break;
            case EventType::kPlant_CobCannonFire:
                entry_point   = {0x466D50, 7};
                param_offsets = {EAX, ECX, ESI};
                exit_points   = {{0x466DFB, 4}};
                break;
            case EventType::kPlant_Die:
                entry_point   = {0x4679B0, 5};
                param_offsets = {0x04};
                exit_points   = {{0x467AF9, 3}};
                break;
            case EventType::kPlant_Fire:
                entry_point   = {0x466E00, 8};
                param_offsets = {0x04, 0x08, 0x0C, 0x10};
                exit_points   = {
                        {0x467553, 3},
                        {0x466E7C, 6},
                        {0x466E93, 6},
                        {0x467349, 6},
                        {0x467430, 6},
                        {0x46737B, 6},
                        {0x4673AA, 6},
                        {0x46741f, 6},
                };
                break;
            case EventType::kPlant_IceZombies:
                entry_point   = {0x466420, 6};
                param_offsets = {0x04};
                exit_points   = {{0x4664A9, 1}};
                break;
            case EventType::kPlant_KillAllPlantsNearDoom:
                entry_point   = {0x466650, 6};
                param_offsets = {0x04};
                exit_points   = {{0x46669B, 4}};
                break;
            case EventType::kPlant_PlantInitialize:
                entry_point   = {0x45DB60, 6};
                param_offsets = {0x04, 0x10, EAX, 0x08, 0x0C};
                exit_points   = {{0x45e7b0, 3}};
                break;
            case EventType::kPlant_Squish:
                entry_point   = {0x462B80, 6};
                param_offsets = {0x04};
                exit_points   = {{0x462C05, 5}, {0x462CD0, 3}};
                break;
            case EventType::kProjectile_DoImpact:
                entry_point   = {0x46E000, 6};
                param_offsets = {0x08, EAX};
                exit_points   = {{0x46EBB9, 1}};
                { // custom trampoline
                    auto custom_point = 0x46EB39;
                    Trampoline(event)
                            .AddCustomInstructions((uint8_t *) custom_point, 5)
                            .AddRegisterPreservation()
                            .AddCallHandler(post_event_handler)
                            .AddRegisterRestoration()
                            .AddBackJump(custom_point + 5)
                            .Inject(custom_point);
                }
                break;
            case EventType::kProjectile_DoSplashDamage:
                entry_point   = {0x468380, 5};
                param_offsets = {0x08, EAX};
                exit_points   = {{0x46d484, 3}};
                break;
            case EventType::kProjectile_ProjectileInitialize:
                entry_point   = {0x46C730, 6};
                param_offsets = {0x04, 0x08, 0x0C, 0x10, EAX, 0x14};
                exit_points   = {{0x46CA8F, 3}};
                break;
            case EventType::kZombie_BungeeStealTarget:
                entry_point   = {0x524C70, 6};
                param_offsets = {0x04};
                exit_points   = {{0x524D63, 1}};
                break;
            case EventType::kZombie_DieNoLoot:
                entry_point   = {0x530510, 6};
                param_offsets = {0x04};
                exit_points   = {{0x530637, 1}};
                break;
            case EventType::kZombie_EatPlant:
                entry_point   = {0x52FB40, 7};
                param_offsets = {0x04, ECX};
                exit_points   = {{0x52FB7E, 6}, {0x52FC75, 6}, {0x52FBE4, 6}, {0x52FE00, 3}};
                break;
            case EventType::kZombie_EatZombie:
                entry_point   = {0x52FE10, 5};
                param_offsets = {0x04, EAX};
                exit_points   = {{0x52FE43, 1}};
                break;
            case EventType::kZombie_TakeDamage:
                entry_point   = {0x5317C0, 7};
                param_offsets = {ESI, 0x04, 0x08};
                exit_points   = {{0x53187B, 3}};
                break;
            case EventType::kZombie_SquishAllInSquare:
                entry_point   = {0x52E920, 6};
                param_offsets = {0x10, 0x04, 0x08, 0x0C};
                exit_points   = {{0x52E995, 3}};
                break;
            case EventType::kZombie_ZombieInitialize:
                entry_point   = {0x522580, 6};
                param_offsets = {0x04, 0x08, EAX, 0x0C, 0x10};
                exit_points   = {{0x52403B, 3}};
                break;
            default:
                break;
#endif
        }
        Injector(event)
                .EntryPoint(entry_point)
                .ExitPoints(exit_points)
                .ParamOffsets(param_offsets)
                .PreEventHandler(pre_event_handler)
                .PostEventHandler(post_event_handler)
                .Inject();
    }
} // namespace pvz
