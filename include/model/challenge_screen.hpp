#pragma once

#include "new_lawn_button.hpp"

namespace pvz {
    struct ChallengeScreen {
        UNKNOWN_BYTES(140);
        NewLawnButton *mBackButton;
        char mPageButton[16];
        char mChallengeButton[280];
        LawnApp *mApp;
        ToolTipWidget *mToolTip;
        ChallengePage mPageIndex;
        bool mCheatEnableChallenges;
        UnlockingState mUnlockState;
        int32_t mUnlockStateCounter;
        int32_t mUnlockChallengeIndex;
        float mLockShakeX;
        float mLockShakeY;
    };
} // namespace pvz
