#pragma once

#include "color.hpp"
#include "font.hpp"
#include "image.hpp"
#include "widget.hpp"

namespace pvz {
    struct LawnApp;
    struct GameButton {
        LawnApp *mApp;
        Widget *mParentWidget;
        int32_t mX;
        int32_t mY;
        int32_t mWidth;
        int32_t mHeight;
        bool mIsOver;
        bool mIsDown;
        bool mDisabled;
        Color mColors[6];
        int32_t mId;
        char mLabel[28];
        int32_t mLabelJustify;
        Font *mFont;
        Image *mButtonImage;
        Image *mOverImage;
        Image *mDownImage;
        Image *mDisabledImage;
        Image *mOverOverlayImage;
        TRect<int32_t> mNormalRect;
        TRect<int32_t> mOverRect;
        TRect<int32_t> mDownRect;
        TRect<int32_t> mDisabledRect;
        bool mInverted;
        bool mBtnNoDraw;
        bool mFrameNoDraw;
        UNKNOWN_BYTES(4);
        double mOverAlpha;
        double mOverAlphaSpeed;
        double mOverAlphaFadeInSpeed;
        bool mDrawStoneButton;
        int32_t mTextOffsetX;
        int32_t mTextOffsetY;
        int32_t mButtonOffsetX;
        int32_t mButtonOffsetY;
        UNKNOWN_BYTES(4);
    };
} // namespace pvz
