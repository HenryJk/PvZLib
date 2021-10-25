#pragma once

#include "pvz.hpp"


namespace pvz {
    enum class EventType {
        kBoard_DrawGameObjects,
        kBoard_KillAllPlantsInRadius,
        kBoard_UpdateGameObjects,
        kPlant_BlowAwayFliers,
        kPlant_BurnRow,
        kPlant_CobCannonFire,
        kPlant_Die,
        kPlant_Draw,
        kPlant_Fire,
        kPlant_IceZombies,
        kPlant_Initialize,
        kPlant_KillAllPlantsNearDoom,
        kPlant_Squish,
        kProjectile_DoImpact,
        kProjectile_DoSplashDamage,
        kProjectile_ProjectileInitialize,
        kZombie_BungeeStealTarget,
        kZombie_Die,
        kZombie_Draw,
        kZombie_EatPlant,
        kZombie_EatZombie,
        kZombie_TakeDamage,
        kZombie_SquishAllInSquare,
        kZombie_ZombieInitialize,
    };

    struct Event {
        Coin *mCoin = nullptr;
        GridItem *mGridItem = nullptr;
        LawnMower *mLawnMower = nullptr;
        Plant *mPlant = nullptr;
        Projectile *mProjectile = nullptr;
        Zombie *mZombie = nullptr;
        int32_t mCol = 0;
        int32_t mRow = 0;

        static void InjectEventHandler(EventType type, void (*handler)(Event *));

        static void EjectEventHandler(EventType type);
    };
} // namespace pvz
