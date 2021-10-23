#pragma once

#include "foley_instance.hpp"

namespace pvz {
    struct FoleyTypeData {
        FoleyInstance mFoleyInstances[8];
        int32_t mLastVariationPlayed;
    };
} // namespace pvz
