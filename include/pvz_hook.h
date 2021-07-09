#pragma once

#include "pvz_game.h"

namespace pvz {
    void RegisterOnTickHook(void (*handler)(Game *));
    void RegisterOnZombieCreatedHook(void (*handler)(pvz::Zombie *));
    void DisableAllHooks();
}
