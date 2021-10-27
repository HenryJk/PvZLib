#pragma once



namespace pvz {
    struct Font {
        UNKNOWN_BYTES(4);
        int32_t mAscent;
        int32_t mAscentPadding;
        int32_t mHeight;
        int32_t mLineSpacingOffset;
    };
} // namespace pvz
