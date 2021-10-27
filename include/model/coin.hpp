#pragma once

#include "game_object.hpp"
#include "potted_plant.hpp"

namespace pvz {
    struct Coin : GameObject {
        float mPosX;
        float mPosY;
        float mVelX;
        float mVelY;
        float mScale;
        bool mDead;
        int32_t mFadeCount;
        float mCollectX;
        float mCollectY;
        int32_t mGroundY;
        int32_t mCoinAge;
        bool mIsBeingCollected;
        int32_t mDisappearCounter;
        CoinType mType;
        CoinMotion mCoinMotion;
        int32_t mAttachmentID;
        float mCollectionDistance;
        SeedType mUsableSeedType;
        UNKNOWN_BYTES(4);
        PottedPlant mPottedPlantSpec;
        bool mNeedsBouncyArrow;
        bool mHasBouncyArrow;
        bool mHitGround;
        int32_t mTimesDropped;
    };
} // namespace pvz
