#pragma once

namespace pvz {
    struct Edge {
        double mX;
        double mDX;
        int32_t i;
        UNKNOWN_BYTES(4);
        double b;
    };

    struct GraphicsState {
        Image *mDestImage;
        float mTransX;
        float mTransY;
        float mScaleX;
        float mScaleY;
        float mScaleOrigX;
        float mScaleOrigY;
        TRect<int> mClipRect;
        Color mColor;
        Font *mFont;
        int32_t mDrawMode;
        bool mColorizeImages;
        bool mFastStretch;
        bool mWriteColoredString;
        bool mLinearBlend;
        bool mIs3D;
    };

    struct Graphics {
        UNKNOWN_BYTES(80);
        Edge *mPFActiveEdgeList;
        int32_t mPFNumActiveEdges;
        int32_t mPFNumVertices;
        IncompatibleList mStateStack;
    };
} // namespace pvz
