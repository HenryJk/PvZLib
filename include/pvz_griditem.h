#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) GridItem {
        union {
            EXACT_SIZE(GRID_ITEM_STRUCT_SIZE);
            OF(GridItemType type, GRID_ITEM_TYPE_OFFSET);
            OF(uint32_t column_index, GRID_ITEM_COLUMN_INDEX_OFFSET);
            OF(uint32_t row_index, GRID_ITEM_ROW_INDEX_OFFSET);
            OF(uint32_t crater_countdown, GRID_ITEM_CRATER_COUNTDOWN_OFFSET);
            OF(uint32_t id, GRID_ITEM_ID_OFFSET);
        };
    };
}