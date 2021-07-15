#pragma once

#include "pvz_game.h"

#include <d3d.h>

namespace pvz {
    void RegisterOnTickHook(void (*handler)());
    void RegisterOnZombieCreatedHook(void (*handler)(Zombie *));
    void RegisterOnPlantBittenHook(void (*handler)(Plant *, Zombie *));
    void RegisterOnPlantCrushedHook(void (*handler)(Plant *, Zombie *));
    void RegisterOnSpikerockDamaged(void (*handler)(Plant *, Zombie *));
    void RegisterOnSpikeplantRanOver(void (*handler)(Plant *, Zombie *));
    void RegisterOnProjectileCollideHook(void (*handler)(Projectile *, Zombie *));
    void RegisterOnBasketballCollideHook(void (*handler)(Projectile *, Plant *));
    void RegisterOnFrameRenderedHook(void (*handler)(IDirect3DDevice7 *));
    void DisableAllHooks();
} // namespace pvz
