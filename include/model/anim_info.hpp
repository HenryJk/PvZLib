#pragma once

#include "incompatible_stdlib.hpp"

namespace pvz {
    struct AnimInfo {
        AnimType mAnimType;
        int32_t mFrameDelay;
        int32_t mNumCels;
        IncompatibleVector mPerFrameDelay;
        IncompatibleVector mFrameMap;
        int32_t mTotalAnimTime;
    };
} // namespace pvz
