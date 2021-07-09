#pragma once

#include "pvz_reference.h"

namespace pvz {
    struct __attribute__((packed)) CardSelectionUI {
        union {
            OF(bool is_active, CARD_SELECTION_UI_IS_ACTIVE_OFFSET);
            OF(bool is_zombie_generated, CARD_SELECTION_UI_IS_ZOMBIE_GENERATED_OFFSET);
        };
    };
} // namespace pvz
