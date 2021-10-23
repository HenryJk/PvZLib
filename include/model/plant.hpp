#pragma once

#include "magnet_item.hpp"
namespace pvz {
    struct Plant;

    typedef void(__thiscall *fun)(Plant *, int, int);

    struct Plant : GameObject {
        SeedType mSeedType;
        int32_t mPlantCol;
        int32_t mAnGameObject;
        bool mAnimPing;
        int32_t mFrame;
        int32_t mFrameLength;
        int32_t mNumFrames;
        PlantState mState;
        bool mDead;
        bool mSquished;
        int32_t mPlantHealth;
        int32_t mPlantMaxHealth;
        int32_t mSubclass;
        int32_t mDisappearCountdown;
        int32_t mDoSpecialCountdown;
        int32_t mStateCountdown;
        int32_t mLaunchCounter;
        int32_t mLaunchRate;
        TRect<int32_t> mPlantRect;
        TRect<int32_t> mPlantAttackRect;
        int32_t mTargetX;
        int32_t mTargetY;
        int32_t mStartRow;
        int32_t mParticleID;
        int32_t mShootingCounter;
        int32_t mBodyReanimID;
        int32_t mHeadReanimID;
        int32_t mHeadReanimID2;
        int32_t mHeadReanimID3;
        int32_t mBlinkReanimID;
        int32_t mLightReanimID;
        int32_t mSleepingReanimID;
        int32_t mBlinkCountdown;
        int32_t mRecentlyEatenCountdown;
        int32_t mEatenFlashCountdown;
        int32_t mBeghouledFlashCountdown;
        float mShakeOffsetX;
        float mShakeOffsetY;
        MagnetItem mMagnetItems[5];
        int32_t mTargetZombieID;
        int32_t mWakeUpCounter;
        bool mIsAsleep;
        bool mIsOnBoard;
        bool mIsOnBungee;
        bool mHighlighted;
        SeedType mImitaterType;
        int32_t mPottedPlantIndex;

        void CobCannonFire(int32_t x, int32_t y);
    };
} // namespace pvz
