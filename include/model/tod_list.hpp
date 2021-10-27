#pragma once

#include "tod_allocator.hpp"

namespace pvz {
    template<typename T>
    struct TodListNode {
        T mValue;
        TodListNode<T> *mNext;
        TodListNode<T> *mPrev;
    };

    template<typename T>
    struct TodList {
        TodListNode<T> *mHead;
        TodListNode<T> *mTail;
        int32_t mSize;
        TodAllocator *mpAllocator;
    };
} // namespace pvz
