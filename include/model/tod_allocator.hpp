#pragma once

namespace pvz {
    struct TodAllocator {
        void *mFreeList;
        void *mBlockList;
        int32_t mGrowCount;
        int32_t mTotalItems;
        int32_t mItemSize;
    };
} // namespace pvz
