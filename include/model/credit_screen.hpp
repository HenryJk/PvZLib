#pragma once


#include "lawn_stone_button.hpp"
#include "perf_timer.hpp"

namespace pvz {
    struct CreditScreen {
        UNKNOWN_BYTES(140);
        GameButton *mCloseButton;
        LawnApp *mApp;
        CreditsPhase mCreditsPhase;
        int32_t mCreditsPhaseCounter;
        int32_t mCreditsReanimID;
        int32_t mFogParticleID;
        int32_t mBlinkCountdown;
        LawnStoneButton *mMainMenuButton;
        NewLawnButton *mReplayButton;
        Widget *mOverlayWidget;
        bool mDrawBrain;
        float mBrainPosX;
        float mBrainPosY;
        int32_t mUpdateCount;
        int32_t mDrawCount;
        PerfTimer mTimerSinceStart;
        bool mDontSync;
        bool mCreditsPaused;
        UNKNOWN_BYTES(6);
        double mOriginalMusicVolume;
        bool mPreloaded;
        UNKNOWN_BYTES(7);
    };
} // namespace pvz
