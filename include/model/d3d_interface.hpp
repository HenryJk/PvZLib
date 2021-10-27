#pragma once

#include <d3d.h>
#include <ddraw.h>

namespace pvz {
    struct D3DInterface {
        UNKNOWN_BYTES(4);
        HWND__ *mHWnd;
        int32_t mWidth;
        int32_t mHeight;
        IDirectDraw7 *mDD;
        IDirectDrawSurface7 *mDDSDrawSurface;
        IDirectDrawSurface7 *mZBuffer;
        IDirect3D7 *mD3D;
        IDirect3DDevice7 *mD3DDevice;
        _D3DVIEWPORT7 mD3DViewport;
        bool mSceneBegun;
        bool mIsWindowed;
        IncompatibleSet mImageSet;
        IncompatibleList mTransformStack;
    };
} // namespace pvz
