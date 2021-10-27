#pragma once

namespace pvz {
    struct SharedImage {
        DDImage *mImage;
        int32_t mRefCount;
    };
} // namespace pvz
