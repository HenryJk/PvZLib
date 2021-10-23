#pragma once

#include "d3d_interface.hpp"
#include "d3d_tester.hpp"
#include "dd_image.hpp"
#include "ratio.hpp"

namespace pvz {
    struct DDInterface {
        UNKNOWN_BYTES(44);
        SexyAppBase *mApp;
        D3DInterface *mD3DInterface;
        D3DTester *mD3DTester;
        bool mIs3D;
        CritSect mCritSect;
        bool mInRedraw;
        IDirectDraw *mDD;
        IDirectDraw7 *mDD7;
        IDirectDrawSurface *mPrimarySurface;
        IDirectDrawSurface *mSecondarySurface;
        IDirectDrawSurface *mDrawSurface;
        unsigned char mWindowScaleBuffers[16];
        int32_t mWidth;
        int32_t mHeight;
        Ratio mAspect;
        int32_t mDesktopWidth;
        int32_t mDesktopHeight;
        Ratio mDesktopAspect;
        bool mIsWidescreen;
        int32_t mDisplayWidth;
        int32_t mDisplayHeight;
        Ratio mDisplayAspect;
        TRect<int> mPresentationRect;
        int32_t mFullscreenBits;
        uint32_t mRefreshRate;
        uint32_t mMillisecondsPerFrame;
        int32_t mScanLineFailCount;
        int *mRedAddTable;
        int *mGreenAddTable;
        int *mBlueAddTable;
        uint32_t mRedConvTable[256];
        uint32_t mGreenConvTable[256];
        uint32_t mBlueConvTable[256];
        bool mInitialized;
        HWND__ *mHWnd;
        bool mIsWindowed;
        DDImage *mScreenImage;
        DDImage *mSecondarySurfaceImage;
        IncompatibleSet mDDImageSet;
        bool mVideoOnlyDraw;
        uint32_t mInitCount;
        int32_t mCursorWidth;
        int32_t mCursorHeight;
        int32_t mNextCursorX;
        int32_t mNextCursorY;
        int32_t mCursorX;
        int32_t mCursorY;
        Image *mCursorImage;
        bool mHasOldCursorArea;
        IDirectDrawSurface *mOldCursorArea;
        IDirectDrawSurface *mNewCursorArea;
        DDImage *mOldCursorAreaImage;
        DDImage *mNewCursorAreaImage;
        IncompatibleBasicString mErrorString;
    };
} // namespace pvz
