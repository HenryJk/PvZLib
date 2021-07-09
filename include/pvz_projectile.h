#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) Projectile {
        union {
            EXACT_SIZE(PROJECTILE_STRUCT_SIZE);
            OF(bool is_visible, PROJECTILE_IS_VISIBLE_OFFSET);
            OF(uint32_t row_index, PROJECTILE_ROW_INDEX_OFFSET);
            OF(uint32_t xpos, PROJECTILE_XPOS_OFFSET);
            OF(uint32_t ypos, PROJECTILE_YPOS_OFFSET);
            OF(bool is_colliding, PROJECTILE_IS_COLLIDING_OFFSET);
            OF(uint32_t cattail_target_id, PROJECTILE_CATTAIL_TARGET_ID_OFFSET);
            OF(uint32_t id, PROJECTILE_ID_OFFSET);
        };
    };
}