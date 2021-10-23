#pragma once

namespace pvz {
    template<typename T>
    struct DataArrayItem {
        T mItem;
        uint32_t mID;
    };

    template<typename T>
    struct DataArray {
        DataArrayItem<T> *mBlock;
        uint32_t mMaxUsedCount;
        uint32_t mMaxSize;
        uint32_t mFreeListHead;
        uint32_t mSize;
        uint32_t mNextKey;
        char *mName;
    };
} // namespace pvz
