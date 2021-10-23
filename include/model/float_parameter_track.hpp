#pragma once

namespace pvz {
    struct FloatParameterTrackNode {
        float mTime;
        float mLowValue;
        float mHighValue;
        TodCurves mCurveType;
        TodCurves mDistribution;
    };

    struct FloatParameterTrack {
        FloatParameterTrackNode *mNodes;
        int32_t mCountNodes;
    };
} // namespace pvz
