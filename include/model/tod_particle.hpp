#pragma once

#include "float_parameter_track.hpp"
#include "particle_field.hpp"
#include "sexy_vector2.hpp"

namespace pvz {
    struct TodEmitterDefinition {
        Image *mImage;
        int32_t mImageCol;
        int32_t mImageRow;
        int32_t mImageFrames;
        int32_t mAnimated;
        int32_t mParticleFlags;
        EmitterType mEmitterType;
        char *mName;
        char *mOnDuration;
        FloatParameterTrack mSystemDuration;
        FloatParameterTrack mCrossFadeDuration;
        FloatParameterTrack mSpawnRate;
        FloatParameterTrack mSpawnMinActive;
        FloatParameterTrack mSpawnMaxActive;
        FloatParameterTrack mSpawnMaxLaunched;
        FloatParameterTrack mEmitterRadius;
        FloatParameterTrack mEmitterOffsetX;
        FloatParameterTrack mEmitterOffsetY;
        FloatParameterTrack mEmitterBoxX;
        FloatParameterTrack mEmitterBoxY;
        FloatParameterTrack mEmitterSkewX;
        FloatParameterTrack mEmitterSkewY;
        FloatParameterTrack mEmitterPath;
        FloatParameterTrack mParticleDuration;
        FloatParameterTrack mLaunchSpeed;
        FloatParameterTrack mLaunchAngle;
        FloatParameterTrack mSystemRed;
        FloatParameterTrack mSystemGreen;
        FloatParameterTrack mSystemBlue;
        FloatParameterTrack mSystemAlpha;
        FloatParameterTrack mSystemBrightness;
        ParticleField *mParticleFields;
        int32_t mParticleFieldCount;
        ParticleField *mSystemFields;
        int32_t mSystemFieldCount;
        FloatParameterTrack mParticleRed;
        FloatParameterTrack mParticleGreen;
        FloatParameterTrack mParticleBlue;
        FloatParameterTrack mParticleAlpha;
        FloatParameterTrack mParticleBrightness;
        FloatParameterTrack mParticleSpinAngle;
        FloatParameterTrack mParticleSpinSpeed;
        FloatParameterTrack mParticleScale;
        FloatParameterTrack mParticleStretch;
        FloatParameterTrack mCollisionReflect;
        FloatParameterTrack mCollisionSpin;
        FloatParameterTrack mClipTop;
        FloatParameterTrack mClipBottom;
        FloatParameterTrack mClipLeft;
        FloatParameterTrack mClipRight;
        FloatParameterTrack mAnimationRate;
    };

    struct TodParticleDefinition {
        TodEmitterDefinition *mEmitterDefs;
        int32_t mEmitterDefCount;
    };

    struct TodParticleHolder;

    struct TodParticleSystem {
        ParticleEffect mEffectType;
        TodParticleDefinition *mParticleDef;
        TodParticleHolder *mParticleHolder;
        TodList<int32_t> mEmitterList;
        bool mDead;
        bool mIsAttachment;
        int32_t mRenderOrder;
        bool mDontUpdate;
    };

    struct TodParticleEmitter {
        TodEmitterDefinition *mEmitterDef;
        TodParticleSystem *mParticleSystem;
        TodList<int32_t> mParticleList;
        float mSpawnAccum;
        SexyVector2 mSystemCenter;
        int32_t mParticlesSpawned;
        int32_t mSystemAge;
        int32_t mSystemDuration;
        float mSystemTimeValue;
        float mSystemLastTimeValue;
        bool mDead;
        Color mColorOverride;
        bool mExtraAdditiveDrawOverride;
        float mScaleOverride;
        Image *mImageOverride;
        int32_t mCrossFadeEmitterID;
        int32_t mEmitterCrossFadeCountDown;
        int32_t mFrameOverride;
        float mTrackInterp[10];
        float mSystemFieldInterp[4][2];
    };

    struct TodParticle {
        TodParticleEmitter *mParticleEmitter;
        int32_t mParticleDuration;
        int32_t mParticleAge;
        float mParticleTimeValue;
        float mParticleLastTimeValue;
        float mAnimationTimeValue;
        SexyVector2 mVelocity;
        SexyVector2 mPosition;
        int32_t mImageFrame;
        float mSpinPosition;
        float mSpinVelocity;
        int32_t mCrossFadeParticleID;
        int32_t mCrossFadeDuration;
        float mParticleInterp[16];
        float mParticleFieldInterp[4][2];
    };

    struct TodParticleHolder {
        DataArray<TodParticleSystem> mParticleSystems;
        DataArray<TodParticleEmitter> mEmitters;
        DataArray<TodParticle> mParticles;
        TodAllocator mParticleListNodeAllocator;
        TodAllocator mEmitterListNodeAllocator;
    };
} // namespace pvz
