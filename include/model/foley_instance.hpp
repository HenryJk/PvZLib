#pragma once

#include "sound_instance.hpp"

namespace pvz {
    struct FoleyInstance {
        SoundInstance *mInstance;
        int32_t mRefCount;
        bool mPaused;
        int32_t mStartTime;
        int32_t mPauseOffset;
    };
} // namespace pvz
