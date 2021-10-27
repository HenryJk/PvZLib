#pragma once

namespace pvz {
    struct SexyAppBase;
    struct MemoryImage : Image {
        uint32_t *mBits;
        int32_t mBitsChangedCount;
        void *mD3DData;
        uint32_t mD3DFlags;
        uint32_t *mColorTable;
        unsigned char *mColorIndices;
        bool mForcedMode;
        bool mHasTrans;
        bool mHasAlpha;
        bool mIsVolatile;
        bool mPurgeBits;
        bool mWantPal;
        uint32_t *mNativeAlphaData;
        unsigned char *mRLAlphaData;
        unsigned char *mRLAdditiveData;
        bool mBitsChanged;
        SexyAppBase *mApp;
    };
} // namespace pvz
