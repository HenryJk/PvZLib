#pragma once

#include "dialog_button.hpp"

namespace pvz {
    struct GameSelector : EMRPLGBLT {
        LawnApp *mApp;
        DialogButton *mAdventureButton;
        DialogButton *mMinigameButton;
        DialogButton *mPuzzleButton;
        DialogButton *mOptionsButton;
        DialogButton *mQuitButton;
        DialogButton *mHelpButton;
        DialogButton *mStoreButton;
        DialogButton *mAlmanacButton;
        DialogButton *mZenGardenButton;
        DialogButton *mSurvivalButton;
        DialogButton *mChangeUserButton;
        Widget *mOverlayWidget;
        bool mStartingGame;
        int32_t mStartingGameCounter;
        bool mMinigamesLocked;
        bool mPuzzleLocked;
        bool mSurvivalLocked;
        bool mShowStartButton;
        int32_t mTrophyParticleID;
        int32_t mSelectorReanimID;
        int32_t mCloudReanimID[6];
        int32_t mCloudCounter[6];
        int32_t mFlowerReanimID[3];
        int32_t mLeafReanimID;
        int32_t mHandReanimID;
        int32_t mLeafCounter;
        SelectorAnimState mSelectorState;
        int32_t mLevel;
        bool mLoading;
        ToolTipWidget *mToolTip;
    };
} // namespace pvz
