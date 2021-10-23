#pragma once

namespace pvz {
    struct Buffer {
        UNKNOWN_BYTES(4);
        IncompatibleVector mData;
        int32_t mDataBitSize;
        int32_t mReadBitPos;
        int32_t mWriteBitPos;
    };
} // namespace pvz
