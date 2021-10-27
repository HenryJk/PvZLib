#pragma once

#include "game_button.hpp"

namespace pvz {
    struct LawnApp;
    struct AwardScreen {
        UNKNOWN_BYTES(136);
        GameButton *mStartButton;
        GameButton *mMenuButton;
        LawnApp *mApp;
        int32_t mFadeInCounter;
        AwardType mAwardType;
    };
} // namespace pvz
