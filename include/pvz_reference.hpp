#pragma once

#define CONCAT(a, b)       CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b

#define UNUSED_NAME(base)  CONCAT(base, __COUNTER__)

#define OFFSET_FIELD(name, offset)                                                                                     \
    struct __attribute__((__packed__)) {                                                                               \
        char __unused_##offset[offset];                                                                                \
        name;                                                                                                          \
    }

#define OF OFFSET_FIELD

#define EXACT_SIZE(size)                                                                                               \
    struct __attribute__((__packed__)) {                                                                               \
        char __full_##size[size];                                                                                      \
    }

#define UNKNOWN_BYTES(size) char UNUSED_NAME(__unknown)[size]

#define UNDECIPHERABLE      char

#if defined VERSION_1_0_0_1051_EN // Original English
#include "pvz_reference/1_0_0_1051_en.h"
#elif defined VERSION_1_2_0_1096_EN // Steam English
#include "pvz_reference/1_2_0_1096_en.h"
#endif

namespace pvz {
    template<typename T>
    struct TRect {
        T mX;
        T mY;
        T mWidth;
        T mHeight;
    };
} // namespace pvz
