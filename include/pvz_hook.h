#pragma once

#include "pvz_game.h"

#include <d3d.h>

namespace pvz {
    void RegisterOnTickHook(void (*handler)(Game *));
    void RegisterOnZombieCreatedHook(void (*handler)(Zombie *));
    void RegisterOnProjectileCollidedHook(void (*handler)(Projectile *, Zombie *));
    void RegisterOnFrameRenderedHook(void (*handler)(IDirect3DDevice7 *));
    void DisableAllHooks();
} // namespace pvz
