#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) FloatingItem {
        union {
            EXACT_SIZE(FLOATING_ITEM_STRUCT_SIZE);
            OF(uint32_t width, FLOATING_ITEM_WIDTH_OFFSET);
            OF(uint32_t height, FLOATING_ITEM_HEIGHT_OFFSET);
            OF(bool is_visible, FLOATING_ITEM_IS_VISIBLE_OFFSET);
            OF(uint32_t xpos, FLOATING_ITEM_XPOS_OFFSET);
            OF(uint32_t ypos, FLOATING_ITEM_YPOS_OFFSET);
            OF(bool is_collected, FLOATING_ITEM_IS_COLLECTED_OFFSET);
            OF(uint32_t disappear_countdown, FLOATING_ITEM_DISAPPEAR_COUNTDOWN_OFFSET);
            OF(FloatingItemType type, FLOATING_ITEM_TYPE_OFFSET);
            OF(bool has_halo, FLOATING_ITEM_HAS_HALO_OFFSET);
            OF(uint32_t id, FLOATING_ITEM_ID_OFFSET);
        };
    };
}