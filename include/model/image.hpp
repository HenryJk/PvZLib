#pragma once

#include "anim_info.hpp"
#include "incompatible_stdlib.hpp"

namespace pvz {
    struct Image {
        UNKNOWN_BYTES(4);
        bool mDrawn;
        IncompatibleBasicString mFilePath;
        int32_t mWidth;
        int32_t mHeight;
        int32_t mNumRows;
        int32_t mNumCols;
        AnimInfo *mAnimInfo;
    };
} // namespace pvz
