#include "pvz.hpp"


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

    class EventInjector {
    public:
        Event *mEvent = nullptr;
        pair<uintptr_t, uint32_t> mEntryPoint;
        vector<int32_t> mParamLocations;
        vector<pair<uintptr_t, uint32_t>> mExitPoints;
        EventHandler mPreEventHandler  = nullptr;
        EventHandler mPostEventHandler = nullptr;

        void Inject() {
            vector<uint8_t> event_builder;
            for (int i = 0; i < mParamLocations.size(); i++) {
                event_builder.push_back(0x8B); // mov eax, [esp + 0x20 + mParameterOffsets[i]];
                event_builder.push_back(0x44);
                event_builder.push_back(0x24);
                event_builder.push_back(0x20 + mParamLocations[i]);
                event_builder.push_back(0xA3); // mov [&mEvent->mParams[i]], eax;
                event_builder.push_back(((uint32_t) &mEvent->mParams[i] >> 0) & 0xFF);
                event_builder.push_back(((uint32_t) &mEvent->mParams[i] >> 8) & 0xFF);
                event_builder.push_back(((uint32_t) &mEvent->mParams[i] >> 16) & 0xFF);
                event_builder.push_back(((uint32_t) &mEvent->mParams[i] >> 24) & 0xFF);
            }
            auto &[entry_address, entry_num_bytes] = mEntryPoint;
            Trampoline()
                    .Pushad()
                    .AddCustom(&event_builder[0], event_builder.size())
                    .Call(mPreEventHandler, mEvent)
                    .Popad()
                    .AddCustom((uint8_t *) entry_address, entry_num_bytes)
                    .Jump(entry_address + entry_num_bytes)
                    .Inject(entry_address);

            for (auto &[exit_address, exit_num_bytes] : mExitPoints) {
                Trampoline()
                        .Pushad()
                        .Call(mPostEventHandler, mEvent)
                        .Popad()
                        .AddCustom((uint8_t *) exit_address, exit_num_bytes)
                        .Inject(exit_address);
            }
        }
    };
} // namespace

namespace pvz {
    void Event::InjectEventHandler(EventType type, EventHandler pre_event_handler, EventHandler post_event_handler) {
        EventInjector injector;
        injector.mEvent = new Event;
        injector.mPreEventHandler = pre_event_handler;
        injector.mPostEventHandler = post_event_handler;
        switch (type) {
#ifdef VERSION_1_0_0_1051_EN
            case EventType::kBoard_DrawGameObjects:
                injector.mEntryPoint     = {0x416880, 6};
                injector.mParamLocations = {0x04};
                injector.mExitPoints     = {{0x417350, 6}};
                break;
            case EventType::kBoard_KillAllPlantsInRadius:
                injector.mEntryPoint     = {0x41CBF0, 8};
                injector.mParamLocations = {EDX, 0x04, EBX};
                injector.mExitPoints     = {{0x41CC4F, 6}};
                break;
            case EventType::kBoard_KillAllZombiesInRadius:
                injector.mEntryPoint     = {0x41D8A0, 6};
                injector.mParamLocations = {0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20};
                injector.mExitPoints     = {{0x41DA09, 3}};
                break;
            case EventType::kBoard_UpdateGameObjects:
                injector.mEntryPoint     = {0x4130D0, 5};
                injector.mParamLocations = {0x04};
                injector.mExitPoints     = {{0x413210, 1}};
                break;
            case EventType::kPlant_BlowAwayFliers:
                injector.mEntryPoint     = {0x4665B0, 5};
                injector.mParamLocations = {0x04};
                injector.mExitPoints     = {{0x466649, 6}};
                break;
            case EventType::kPlant_BurnRow:
                injector.mEntryPoint     = {0x4664B0, 5};
                injector.mParamLocations = {EDI, 0x04};
                injector.mExitPoints     = {{0x4665A6, 6}};
                break;
            case EventType::kPlant_CobCannonFire:
                injector.mEntryPoint     = {0x466D50, 7};
                injector.mParamLocations = {EAX, 0x04, 0x08};
                injector.mExitPoints     = {{0x466DFB, 4}};
                break;
            case EventType::kPlant_Die:
                injector.mEntryPoint     = {0x4679B0, 5};
                injector.mParamLocations = {0x04};
                injector.mExitPoints     = {{0x467AF9, 3}};
                break;
            case EventType::kPlant_Fire:
                injector.mEntryPoint     = {0x466E00, 8};
                injector.mParamLocations = {0x04, 0x08, 0x0C, 0x10};
                injector.mExitPoints     = {
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
                injector.mEntryPoint     = {0x466420, 6};
                injector.mParamLocations = {EDI};
                injector.mExitPoints     = {{0x4664A9, 1}};
                break;
            case EventType::kPlant_KillAllPlantsNearDoom:
                injector.mEntryPoint     = {0x466650, 6};
                injector.mParamLocations = {EDI};
                injector.mExitPoints     = {{0x46669B, 4}};
                break;
            case EventType::kPlant_PlantInitialize:
                injector.mEntryPoint     = {0x45DB60, 6};
                injector.mParamLocations = {0x04, ECX, EAX, 0x08, 0x0C};
                injector.mExitPoints     = {{0x45E7B0, 3}};
                break;
            case EventType::kPlant_Squish:
                injector.mEntryPoint     = {0x462B80, 6};
                injector.mParamLocations = {0x04};
                injector.mExitPoints     = {{0x462C05, 5}, {0x462CD0, 3}};
                break;
            case EventType::kProjectile_DoImpact:
                injector.mEntryPoint     = {0x46E000, 6};
                injector.mParamLocations = {ECX, EDX};
                injector.mExitPoints     = {{0x46EBB9, 1}};
                { // custom trampoline
                    auto custom_point = 0x46EB39;
                    Trampoline()
                            .AddCustom((uint8_t *) custom_point, 5)
                            .Pushad()
                            .Call((void *)post_event_handler, injector.mEvent)
                            .Popad()
                            .Jump(custom_point + 5)
                            .Inject(custom_point);
                }
                break;
            case EventType::kProjectile_DoSplashDamage:
                injector.mEntryPoint     = {0x46D390, 5};
                injector.mParamLocations = {EAX, 0x04};
                injector.mExitPoints     = {{0x46d484, 3}};
                break;
            case EventType::kProjectile_ProjectileInitialize:
                injector.mEntryPoint     = {0x46C730, 6};
                injector.mParamLocations = {0x04, 0x08, 0x0C, 0x10, EAX, 0x14};
                injector.mExitPoints     = {{0x46CA8F, 3}};
                break;
            case EventType::kZombie_BungeeStealTarget:
                injector.mEntryPoint     = {0x524C70, 6};
                injector.mParamLocations = {EAX};
                injector.mExitPoints     = {{0x524D63, 1}};
                break;
            case EventType::kZombie_DieNoLoot:
                injector.mEntryPoint     = {0x530510, 6};
                injector.mParamLocations = {ECX};
                injector.mExitPoints     = {{0x530637, 1}};
                break;
            case EventType::kZombie_EatPlant:
                injector.mEntryPoint     = {0x52FB40, 7};
                injector.mParamLocations = {0x04, ECX};
                injector.mExitPoints     = {{0x52FB7E, 6}, {0x52FC75, 6}, {0x52FBE4, 6}, {0x52FE00, 3}};
                break;
            case EventType::kZombie_EatZombie:
                injector.mEntryPoint     = {0x52FE10, 5};
                injector.mParamLocations = {EDI, EAX};
                injector.mExitPoints     = {{0x52FE43, 1}};
                break;
            case EventType::kZombie_TakeDamage:
                injector.mEntryPoint     = {0x5317C0, 7};
                injector.mParamLocations = {ESI, 0x04, EAX};
                injector.mExitPoints     = {{0x53187B, 3}};
                break;
            case EventType::kZombie_SquishAllInSquare:
                injector.mEntryPoint     = {0x52E920, 6};
                injector.mParamLocations = {0x10, 0x04, 0x08, 0x0C};
                injector.mExitPoints     = {{0x52E995, 3}};
                break;
            case EventType::kZombie_ZombieInitialize:
                injector.mEntryPoint     = {0x522580, 6};
                injector.mParamLocations = {0x04, 0x08, EAX, 0x0C, 0x10, 0x14};
                injector.mExitPoints     = {{0x52403B, 3}};
                break;
            default:
                break;
#endif
        }
        injector.Inject();
    }
} // namespace pvz
