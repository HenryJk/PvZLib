#pragma once

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


#if VERSION == V_1_0_0_1051_EN // Original English
#include "pvz_reference/1_0_0_1051_en.h"
#endif