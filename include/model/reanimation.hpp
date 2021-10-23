#pragma once

#include "memory_image.hpp"
#include "tod_list.hpp"

namespace pvz {
    struct ReanimatorTransform {
        float mTransX;
        float mTransY;
        float mSkewX;
        float mSkewY;
        float mScaleX;
        float mScaleY;
        float mFrame;
        float mAlpha;
        Image *mImage;
        Font *mFont;
        char *mText;
    };

    struct ReanimAtlasImage {
        int32_t mX;
        int32_t mY;
        int32_t mWidth;
        int32_t mHeight;
        Image *mOriginalImage;
    };

    struct ReanimatorTrack {
        char *mName;
        ReanimatorTransform *mTransforms;
        int32_t mTransformCount;
    };

    struct ReanimAtlas {
        ReanimAtlasImage mImageArray[64];
        int32_t mImageCount;
        MemoryImage *mMemoryImage;
    };

    struct ReanimatorDefinition {
        ReanimatorTrack *mTracks;
        int32_t mTrackCount;
        float mFPS;
        ReanimAtlas *mReanimAtlas;
    };

    struct ReanimatorTrackInstance {
        int32_t mBlendCounter;
        int32_t mBlendTime;
        ReanimatorTransform mBlendTransform;
        float mShakeOverride;
        float mShakeX;
        float mShakeY;
        int32_t mAttachmentID;
        Image *mImageOverride;
        int32_t mRenderGroup;
        Color mTrackColor;
        bool mIgnoreClipRect;
        bool mTruncateDisappearingFrames;
    };

    struct ReanimationHolder;

    struct Reanimation {
        ReanimationType mReanimationType;
        float mAnimTime;
        float mAnimRate;
        ReanimatorDefinition *mDefinition;
        ReanimLoopType mLoopType;
        bool mDead;
        int32_t mFrameStart;
        int32_t mFrameCount;
        int32_t mFrameBasePose;
        SexyTransform2D mOverlayMatrix;
        Color mColorOverride;
        ReanimatorTrackInstance *mTrackInstances;
        int32_t mLoopCount;
        ReanimationHolder *mReanimationHolder;
        bool mIsAttachment;
        int32_t mRenderOrder;
        Color mExtraAdditiveColor;
        bool mEnableExtraAdditiveDraw;
        Color mExtraOverlayColor;
        bool mEnableExtraOverlayDraw;
        float mLastFrameTime;
        FilterEffect mFilterEffect;
    };

    struct ReanimationHolder {
        DataArray<Reanimation> mReanimations;
    };

    struct ReanimCacheImageVariation {
        SeedType mSeedType;
        DrawVariation mDrawVariation;
        MemoryImage *mImage;
    };

    struct ReanimatorCache {
        unsigned char mPlantImages[212];
        TodList<ReanimCacheImageVariation> mImageVariationList;
        unsigned char mLawnMowers[16];
        unsigned char mZombieImages[132];
        LawnApp *mApp;
    };
} // namespace pvz
