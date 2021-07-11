#pragma once

#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) Button {
        union {
            OF(uint32_t xpos, BUTTON_XPOS_OFFSET);
            OF(uint32_t ypos, BUTTON_YPOS_OFFSET);
            OF(uint32_t width, BUTTON_WIDTH_OFFSET);
            OF(uint32_t height, BUTTON_HEIGHT_OFFSET);
            OF(bool is_disabled, BUTTON_IS_DISABLED_OFFSET);
            OF(bool is_hidden, BUTTON_IS_HIDDEN_OFFSET);
        };
    };
} // namespace pvz
