#pragma once

#include "pvz.hpp"


namespace pvz {
    struct Event;

    typedef void (*EventHandler)(Event *);

    enum class EventType {
        // clang-format off
        // Event                            // Parameters
        kBoard_DrawGameObjects,             // Board *this
        kBoard_KillAllPlantsInRadius,       // Board *this, int32 x, int32 y
        kBoard_KillAllZombiesInRadius,      // Board *this, int32 row, int32 x, int32 y, int32 radius, int32 row_range, bool explosive, int32 damage_flags
        kBoard_UpdateGameObjects,           // Board *this
        kPlant_BlowAwayFliers,              // Plant *this
        kPlant_BurnRow,                     // Plant *this, int32 row
        kPlant_CobCannonFire,               // Plant *this, int32 x, int32 y
        kPlant_Die,                         // Plant *this
        kPlant_Fire,                        // Plant *this, Zombie *target, int32 row, PlantWeapon weapon
        kPlant_IceZombies,                  // Plant *this
        kPlant_KillAllPlantsNearDoom,       // Plant *this
        kPlant_PlantInitialize,             // Plant *this, int32 col, int32 row, SeedType type, SeedType imitater_type
        kPlant_Squish,                      // Plant *this
        kProjectile_DoImpact,               // Projectile *this, Zombie *primary_target
        kProjectile_DoSplashDamage,         // Projectile *this, Zombie *primary_target
        kProjectile_ProjectileInitialize,   // Projectile *this, int32 x, int32 y, int32 unknown, int32 row, ProjectileType type
        kZombie_BungeeStealTarget,          // Zombie *this
        kZombie_DieNoLoot,                  // Zombie *this
        kZombie_EatPlant,                   // Zombie *this, Plant *target
        kZombie_EatZombie,                  // Zombie *this, Zombie *target
        kZombie_TakeDamage,                 // Zombie *this, int32 damage, int32 damage_flags
        kZombie_SquishAllInSquare,          // Zombie *this, int32 col, int32 row, ZombieAttackType attack_type
        kZombie_ZombieInitialize,           // Zombie *this, int32 col, ZombieType type, bool hypnotized, Zombie *summoner, int32 from_wave
        // clang-format on
    };

    struct Event {
        int32_t mParams[8];

        static void InjectEventHandler(EventType type, EventHandler pre_event_handler, EventHandler post_event_handler);

        static void EjectEventHandler(EventType type);
    };
} // namespace pvz
