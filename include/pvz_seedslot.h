#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) SeedSlot {
        union {
            EXACT_SIZE(SEED_SLOT_STRUCT_SIZE);
            OF(uint32_t xpos, SEED_SLOT_XPOS_OFFSET);
            OF(uint32_t ypos, SEED_SLOT_YPOS_OFFSET);
            OF(uint32_t width, SEED_SLOT_WIDTH_OFFSET);
            OF(uint32_t height, SEED_SLOT_HEIGHT_OFFSET);
            OF(bool is_visible, SEED_SLOT_IS_VISIBLE_OFFSET);
            OF(uint32_t recharge_progress, SEED_SLOT_RECHARGE_PROGRESS_OFFSET);
            OF(uint32_t refresh_threshold, SEED_SLOT_REFRESH_THRESHOLD_OFFSET);
            OF(uint32_t index, SEED_SLOT_INDEX_OFFSET);
            OF(PlantType type, SEED_SLOT_TYPE_OFFSET);
            OF(PlantType imitater_type, SEED_SLOT_IMITATER_TYPE_OFFSET);
            OF(bool is_available, SEED_SLOT_IS_AVAILABLE_OFFSET);
            OF(uint32_t usage_counter, SEED_SLOT_USAGE_COUNTER_OFFSET);
        };
    };
} // namespace pvz
