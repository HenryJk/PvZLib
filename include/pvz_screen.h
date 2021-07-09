#pragma once

#include "pvz_reference.h"

#include <cstdint>

namespace pvz {
    struct __attribute__((packed)) Screen {
        inline void Click(uint32_t x, uint32_t y, int32_t key) {
            asm volatile("pushl %0;"
                         "movl %1, %%ebx;"
                         "movl %2, %%eax;"
                         "movl %3, %%ecx;"
                         "movl %4, %%edx;"
                         "calll *%%edx;"
                         :
                         : "g"(x), "g"(key), "g"(y), "g"(this), "i"(CLICK_SCREEN_FUNC_ADDRESS)
                         : "eax", "ebx", "ecx", "edx", "esp");
        }
    };
} // namespace pvz