#pragma once

#include "pvz_game.h"

namespace pvz {
    void RegisterTickEventHook(void (*handler)(Game *));
    void RegisterZombieCreatedHook(void (*handler)(pvz::Zombie *));
}
