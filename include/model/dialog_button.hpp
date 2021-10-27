#pragma once

#include "button_widget.hpp"

namespace pvz {
    struct DialogButton : ButtonWidget {
        Image *mComponentImage;
        int32_t mTranslateX;
        int32_t mTranslateY;
        int32_t mTextOffsetX;
        int32_t mTextOffsetY;
        UNKNOWN_BYTES(4);
    };
} // namespace pvz
