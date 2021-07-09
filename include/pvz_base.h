#pragma once

#include "pvz_game.h"
#include "pvz_pregameui.h"
#include "pvz_reference.h"
#include "pvz_screen.h"

namespace pvz {
    struct __attribute__((packed)) Base {
        union {
            OF(double music_volume, BASE_MUSIC_VOLUME_OFFSET);
            OF(double sfx_volume, BASE_SFX_VOLUME_OFFSET);
            OF(Screen *screen_ptr, BASE_SCREEN_PTR_OFFSET);
            OF(uint32_t ms_per_tick, BASE_MS_PER_TICK_OFFSET);
            OF(Game *game_ptr, BASE_GAME_PTR_OFFSET);
            OF(PreGameUI *pregame_ui_ptr, BASE_PREGAME_UI_PTR_OFFSET);
            OF(uint32_t game_type, BASE_GAME_TYPE_OFFSET);
            OF(uint32_t game_status, BASE_GAME_STATUS_OFFSET);
            OF(bool free_planting_mode, BASE_FREE_PLANTING_MODE_OFFSET);
        };

        static Base &GetInstance();
    };
} // namespace pvz
