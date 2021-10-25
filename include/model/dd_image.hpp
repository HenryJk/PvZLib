#pragma once

namespace pvz {
    struct DDInterface;
    struct DDImage : MemoryImage {
        DDInterface *mDDInterface;
        IDirectDrawSurface *mSurface;
        bool mSurfaceSet;
        bool mNoLock;
        bool mVideoMemory;
        bool mFirstPixelTrans;
        bool mWantDDSurface;
        bool mDrawToBits;
        int32_t mLockCount;
        _DDSURFACEDESC mLockedSurfaceDesc;
    };
} // namespace pvz
