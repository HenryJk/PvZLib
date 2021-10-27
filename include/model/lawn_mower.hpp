#pragma once



namespace pvz {
    struct LawnMower {
        LawnApp *mApp;
        Board *mBoard;
        float mPosX;
        float mPosY;
        int32_t mRenderOrder;
        int32_t mRow;
        int32_t mAnimTicksPerFrame;
        int32_t mReanimID;
        int32_t mChompCounter;
        int32_t mRollingInCounter;
        int32_t mSquishedCounter;
        LawnMowerState mMowerState;
        bool mDead;
        bool mVisible;
        LawnMowerType mMowerType;
        float mAltitude;
        MowerHeight mMowerHeight;
        int32_t mLastPortalX;
    };
} // namespace pvz
