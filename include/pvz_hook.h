#pragma once

#include "pvz_game.h"

namespace pvz {
    void RegisterOnTickHook(void (*handler)(Game *));
    void RegisterOnZombieCreatedHook(void (*handler)(Zombie *));
    void RegisterOnProjectileCollideHook(void (*handler)(Projectile *, Zombie *));
    void DisableAllHooks();
}
