#pragma once

#include "pvz_button.h"
#include "pvz_cardselectionui.h"
#include "pvz_cursor.h"
#include "pvz_enum.h"
#include "pvz_floatingitem.h"
#include "pvz_griditem.h"
#include "pvz_plant.h"
#include "pvz_projectile.h"
#include "pvz_reference.h"
#include "pvz_seedbank.h"
#include "pvz_zombie.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) Game {
        union {
            OF(Zombie *zombie_ptr, GAME_ZOMBIE_PTR_OFFSET);
            OF(uint32_t zombie_count, GAME_ZOMBIE_COUNT_OFFSET);
            OF(Plant *plant_ptr, GAME_PLANT_PTR_OFFSET);
            OF(uint32_t plant_count, GAME_PLANT_COUNT_OFFSET);
            OF(uint32_t next_plant_index, GAME_PLANT_NEXT_OFFSET);
            OF(Projectile *projectile_ptr, GAME_PROJECTILE_PTR_OFFSET);
            OF(uint32_t projectile_count, GAME_PROJECTILE_COUNT_OFFSET);
            OF(FloatingItem *floating_item_ptr, GAME_FLOATING_ITEM_PTR_OFFSET);
            OF(uint32_t floating_item_count, GAME_FLOATING_ITEM_COUNT_OFFSET);
            OF(void *lawnmower_ptr, GAME_LAWNMOWER_PTR_OFFSET);
            OF(uint32_t lawnmower_count, GAME_LAWNMOWER_COUNT_OFFSET);
            OF(GridItem *grid_item_ptr, GAME_GRID_ITEM_PTR_OFFSET);
            OF(uint32_t grid_item_count, GAME_GRID_ITEM_COUNT_OFFSET);
            OF(Cursor *cursor_ptr, GAME_CURSOR_PTR_OFFSET);
            OF(SeedBank *seed_bank_ptr, GAME_SEED_BANK_PTR_OFFSET);
            OF(Button *menu_button_ptr, GAME_MENU_BUTTON_PTR_OFFSET);
            OF(Button *last_stand_button_ptr, GAME_LAST_STAND_BUTTON_PTR_OFFSET);
            OF(CardSelectionUI *card_selection_ui_ptr, GAME_CARD_SELECTION_UI_PTR_OFFSET);
            OF(bool is_paused, GAME_IS_PAUSED_OFFSET);
            OF(TerrainType terrain_type_array[54], GAME_TERRAIN_TYPE_ARRAY_OFFSET);
            OF(uint32_t ice_trail_coord_array[6], GAME_ICE_TRAIL_COORD_ARRAY_OFFSET);
            OF(uint32_t ice_trail_countdown_array[6], GAME_ICE_TRAIL_COUNTDOWN_ARRAY_OFFSET);
            OF(ZombieType spawn_list[1000], GAME_SPAWN_LIST_OFFSET);
            OF(bool spawn_flags[33], GAME_SPAWN_FLAGS_OFFSET);
            OF(uint32_t falling_sun_countdown, GAME_FALLING_SUN_COUNTDOWN_OFFSET);
            OF(BattlefieldType battlefield_type, GAME_BATTLEFIELD_TYPE_OFFSET);
            OF(uint32_t sun_value, GAME_SUN_VALUE_OFFSET);
            OF(uint32_t total_wave_count, GAME_TOTAL_WAVE_COUNT_OFFSET);
            OF(uint32_t spawned_wave_count, GAME_SPAWNED_WAVE_COUNT_OFFSET);
            OF(uint32_t spawn_wave_hp_threshold, GAME_SPAWN_WAVE_HP_THRESHOLD_OFFSET);
            OF(uint32_t current_wave_total_hp, GAME_CURRENT_WAVE_TOTAL_HP_OFFSET);
            OF(uint32_t next_wave_countdown, GAME_NEXT_WAVE_COUNTDOWN_OFFSET);
            OF(uint32_t next_wave_initial_countdown, GAME_NEXT_WAVE_INITIAL_COUNTDOWN_OFFSET);
            OF(uint32_t huge_wave_countdown, GAME_HUGE_WAVE_COUNTDOWN_OFFSET);
            OF(uint32_t cannon_debounce_countdown, GAME_CANNON_DEBOUNCE_COUNTDOWN_OFFSET);
            OF(uint32_t cannon_debounce_xpos, GAME_CANNON_DEBOUNCE_XPOS_OFFSET);
            OF(uint32_t cannon_debounce_ypos, GAME_CANNON_DEBOUNCE_YPOS_OFFSET);
        };

        inline void Click(uint32_t x, uint32_t y, int32_t key) {
            asm volatile("pushal;"
                         "pushl %0;"
                         "pushl %1;"
                         "pushl %2;"
                         "movl %3, %%ecx;"
                         "movl %4, %%eax;"
                         "calll *%%eax;"
                         "popal;"
                         :
                         : "g"(key), "g"(y), "g"(x), "g"(this), "i"(CLICK_BATTLEFIELD_FUNC_ADDRESS)
                         : "eax", "ecx", "esp");
        }
    };
} // namespace pvz
