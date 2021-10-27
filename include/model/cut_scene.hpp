#pragma once

namespace pvz {
    struct CutScene {
        LawnApp *mApp;
        Board *mBoard;
        int32_t mCutsceneTime;
        int32_t mSodTime;
        int32_t mGraveStoneTime;
        int32_t mReadySetPlantTime;
        int32_t mFogTime;
        int32_t mBossTime;
        int32_t mCrazyDaveTime;
        int32_t mLawnMowerTime;
        int32_t mCrazyDaveDialogStart;
        bool mSeedChoosing;
        int32_t mZombiesWonReanimID;
        bool mPreloaded;
        bool mPlacedZombies;
        bool mPlacedLawnItems;
    };
} // namespace pvz
