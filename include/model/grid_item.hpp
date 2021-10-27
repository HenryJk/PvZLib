#pragma once

#include "motion_trail_frame.hpp"

namespace pvz {
    struct GridItem {
        LawnApp *mApp;
        Board *mBoard;
        GridItemType mGridItemType;
        GridItemState mGridItemState;
        int32_t mGridX;
        int32_t mGridY;
        int32_t mGridItemCounter;
        int32_t mRenderOrder;
        bool mDead;
        float mPosX;
        float mPosY;
        float mGoalX;
        float mGoalY;
        int32_t mGridItemReanimID;
        int32_t mGridItemParticleID;
        ZombieType mZombieType;
        SeedType mSeedType;
        ScaryPotType mScaryPotType;
        bool mHighlighted;
        int32_t mTransparentCounter;
        int32_t mSunCount;
        MotionTrailFrame mMotionTrailFrames[12];
        int32_t mMotionTrailCount;
    };
} // namespace pvz
