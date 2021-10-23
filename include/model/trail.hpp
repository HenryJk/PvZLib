#pragma once

namespace pvz {
    struct TrailPoint {
        SexyVector2 aPos;
    };

    struct TrailDefinition {
        Image *mImage;
        int32_t mMaxPoints;
        float mMinPointDistance;
        int32_t mTrailFlags;
        FloatParameterTrack mTrailDuration;
        FloatParameterTrack mWidthOverLength;
        FloatParameterTrack mWidthOverTime;
        FloatParameterTrack mAlphaOverLength;
        FloatParameterTrack mAlphaOverTime;
    };

    struct TrailHolder;

    struct Trail {
        TrailPoint mTrailPoints[20];
        int32_t mNumTrailPoints;
        bool mDead;
        int32_t mRenderOrder;
        int32_t mTrailAge;
        int32_t mTrailDuration;
        TrailDefinition *mDefinition;
        TrailHolder *mTrailHolder;
        float mTrailInterp[4];
        SexyVector2 mTrailCenter;
        bool mIsAttachment;
        Color mColorOverride;
    };

    struct TrailHolder {
        DataArray<Trail> mTrails;
    };
} // namespace pvz
