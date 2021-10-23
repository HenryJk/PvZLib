#pragma once


namespace pvz {
    struct ChosenSeed {
        int32_t mX;
        int32_t mY;
        int32_t mTimeStartMotion;
        int32_t mTimeEndMotion;
        int32_t mStartX;
        int32_t mStartY;
        int32_t mEndX;
        int32_t mEndY;
        SeedType mSeedType;
        ChosenSeedState mSeedState;
        int32_t mSeedIndexInBank;
        bool mRefreshing;
        int32_t mRefreshCounter;
        SeedType mImitaterType;
        bool mCrazyDavePicked;
    };
} // namespace pvz
