#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) Card {
        union {
            EXACT_SIZE(CARD_STRUCT_SIZE);
            OF(uint32_t xpos, CARD_XPOS_OFFSET);
            OF(uint32_t ypos, CARD_YPOS_OFFSET);
            OF(PlantType type, CARD_TYPE_OFFSET);
            OF(CardState state, CARD_STATE_OFFSET);
            OF(uint32_t slot_index, CARD_SLOT_INDEX_OFFSET);
            OF(PlantType imitater_type, CARD_IMITATER_TYPE_OFFSET);
            OF(bool is_enforced, CARD_IS_ENFORCED_OFFSET);
        };
    };
} // namespace pvz
