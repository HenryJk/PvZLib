#pragma once

namespace pvz {
    struct NewLawnButton {
        UNKNOWN_BYTES(312);
        Font *mHiliteFont;
        int32_t mTextDownOffsetX;
        int32_t mTextDownOffsetY;
        UNKNOWN_BYTES(4);
    };
} // namespace pvz
