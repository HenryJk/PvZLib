#pragma once


#include "chosen_seed.hpp"
namespace pvz {
    struct SeedChooserScreen : Widget {
        GameButton *mStartButton;
        GameButton *mRandomButton;
        GameButton *mViewLawnButton;
        GameButton *mStoreButton;
        GameButton *mAlmanacButton;
        GameButton *mMenuButton;
        GameButton *mImitaterButton;
        ChosenSeed mChosenSeeds[53];
        LawnApp *mApp;
        Board *mBoard;
        int32_t mNumSeedsToChoose;
        int32_t mSeedChooserAge;
        int32_t mSeedsInFlight;
        int32_t mSeedsInBank;
        ToolTipWidget *mToolTip;
        int32_t mToolTipSeed;
        int32_t mLastMouseX;
        int32_t mLastMouseY;
        SeedChooserState mChooseState;
        int32_t mViewLawnTime;
    };
} // namespace pvz
