#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"

namespace pvz {
    struct __attribute__((packed)) Cursor {
        union {
            OF(uint32_t xpos, CURSOR_XPOS_OFFSET);
            OF(uint32_t ypos, CURSOR_YPOS_OFFSET);
            OF(uint32_t seed_index, CURSOR_SEED_INDEX_OFFSET);
            OF(PlantType plant_type, CURSOR_PLANT_TYPE_OFFSET);
            OF(PlantType imitater_type, CURSOR_IMITATER_TYPE_OFFSET);
            OF(CursorItem held_item, CURSOR_HELD_ITEM_OFFSET);
        };
    };
} // namespace pvz
