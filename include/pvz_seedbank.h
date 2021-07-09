#pragma once

#include "pvz_enum.h"
#include "pvz_reference.h"
#include "pvz_seedslot.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) SeedBank {
        union {
            OF(bool is_visible, SEED_BANK_IS_VISIBLE_OFFSET);
            OF(uint32_t slot_count, SEED_BANK_SLOT_COUNT_OFFSET);
            OF(SeedSlot slot[10], SEED_BANK_SLOT_ARRAY_OFFSET);
        };
    };
} // namespace pvz