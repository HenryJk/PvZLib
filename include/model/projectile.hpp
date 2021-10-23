#pragma once

namespace pvz {
    struct Projectile : GameObject {
        int32_t mFrame;
        int32_t mNumFrames;
        int32_t mAnimCounter;
        float mPosX;
        float mPosY;
        float mPosZ;
        float mVelX;
        float mVelY;
        float mVelZ;
        float mAccZ;
        float mShadowY;
        bool mDead;
        int32_t mAnimTicksPerFrame;
        ProjectileMotion mMotionType;
        ProjectileType mProjectileType;
        int32_t mProjectileAge;
        int32_t mClickBackoffCounter;
        float mRotation;
        float mRotationSpeed;
        bool mOnHighGround;
        int32_t mDamageRangeFlags;
        int32_t mHitTorchwoodGridX;
        int32_t mAttachmentID;
        float mCobTargetX;
        int32_t mCobTargetRow;
        int32_t mTargetZombieID;
        int32_t mLastPortalX;
    };
} // namespace pvz
