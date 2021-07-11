#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) Plant {
        union {
            EXACT_SIZE(PLANT_STRUCT_SIZE);
            OF(uint32_t xpos, PLANT_XPOS_OFFSET);
            OF(uint32_t ypos, PLANT_YPOS_OFFSET);
            OF(bool is_visible, PLANT_IS_VISIBLE_OFFSET);
            OF(uint32_t row_index, PLANT_ROW_INDEX_OFFSET);
            OF(PlantType type, PLANT_TYPE_OFFSET);
            OF(uint32_t column_index, PLANT_COLUMN_INDEX_OFFSET);
            OF(uint32_t state, PlANT_STATE_OFFSET);
            OF(uint32_t hp, PLANT_HP_OFFSET);
            OF(uint32_t max_hp, PLANT_MAX_HP_OFFSET);
            OF(bool is_shooter, PLANT_IS_SHOOTER_OFFSET);
            OF(uint32_t explosion_countdown, PLANT_EXPLOSION_COUNTDOWN_OFFSET);
            OF(uint32_t ability_countdown, PLANT_ABILITY_COUNTDOWN_OFFSET);
            OF(uint32_t work_countdown, PLANT_WORK_COUNTDOWN_OFFSET);
            OF(uint32_t work_interval, PLANT_WORK_INTERVAL_OFFSET);
            OF(uint32_t cob_target_xpos, PLANT_COB_TARGET_XPOS_OFFSET);
            OF(uint32_t cob_target_ypos, PLANT_COB_TARGET_YPOS_OFFSET);
            OF(uint32_t particle_id, PLANT_PARTICLE_ID_OFFSET);
            OF(uint32_t projectile_countdown, PLANT_PROJECTILE_COUNTDOWN_OFFSET);
            OF(uint32_t wakeup_countdown, PLANT_WAKEUP_COUNTDOWN_OFFSET);
            OF(PlantType imitater_type, PLANT_IMITATER_TYPE_OFFSET);
            OF(bool is_disappearing, PLANT_IS_DISAPPEARING_OFFSET);
            OF(bool is_squashed, PLANT_IS_SQUASHED_OFFSET);
            OF(bool is_sleeping, PLANT_IS_SLEEPING_OFFSET);
            OF(uint32_t id, PLANT_ID_OFFSET);
        };

        inline void LaunchCob(uint32_t x, uint32_t y) {
            asm volatile("pushal;"
                         "pushl %0;"
                         "pushl %1;"
                         "movl %2, %%eax;"
                         "movl %3, %%ebx;"
                         "calll *%%ebx;"
                         "popal;"
                         :
                         : "g"(y), "g"(x), "g"(this), "i"(LAUNCH_COB_FUNC_ADDRESS)
                         : "eax", "ebx", "esp");
        };
    };
} // namespace pvz
