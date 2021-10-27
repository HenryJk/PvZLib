#pragma once

namespace pvz {
    struct TodSmoothArray {
        int32_t mItem;
        float mWeight;
        float mLastPicked;
        float mSecondLastPicked;
    };
} // namespace pvz
