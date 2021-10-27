#pragma once

#include "pvz.hpp"


namespace pvz {
    struct Event;

    typedef void (*EventHandler)(Event *);

    enum class EventType {
        // Event                      // Parameters
        kBoard_DrawGameObjects,       // Board *this
        kBoard_KillAllPlantsInRadius, // Board *this, int32_t x, int32_t y
        kBoard_UpdateGameObjects,     // Board *this
        kPlant_BlowAwayFliers,        // Plant *this
        kPlant_BurnRow,               // Plant *this, int32_t row
        kPlant_CobCannonFire,         // Plant *this, int32_t x, int32_t y
        kPlant_Die,                   // Plant *this
        kPlant_Fire,                  // Plant *this, Zombie *target, int32_t row, PlantWeapon weapon
        kPlant_IceZombies,
        kPlant_PlantInitialize,
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
        int32_t mParams[6];

        static void InjectEventHandler(EventType type, EventHandler pre_event_handler, EventHandler post_event_handler);

        static void EjectEventHandler(EventType type);
    };
} // namespace pvz
