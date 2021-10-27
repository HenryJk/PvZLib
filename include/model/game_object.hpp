#pragma once

namespace pvz {
    struct GameObject {
        LawnApp *mApp;
        Board *mBoard;
        int32_t mX;
        int32_t mY;
        int32_t mWidth;
        int32_t mHeight;
        bool mVisible;
        int32_t mRow;
        int32_t mRenderOrder;
    };
} // namespace pvz
