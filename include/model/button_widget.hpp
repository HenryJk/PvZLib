#pragma once

#include "button_listener.hpp"
namespace pvz {
    struct ButtonWidget : Widget {
        int32_t mId;
        IncompatibleBasicString mLabel;
        int32_t mLabelJustify;
        Font *mFont;
        Image *mButtonImage;
        Image *mOverImage;
        Image *mDownImage;
        Image *mDisabledImage;
        TRect<int32_t> mNormalRect;
        TRect<int32_t> mOverRect;
        TRect<int32_t> mDownRect;
        TRect<int32_t> mDisabledRect;
        bool mInverted;
        bool mBtnNoDraw;
        bool mFrameNoDraw;
        ButtonListener *mButtonListener;
        double mOverAlpha;
        double mOverAlphaSpeed;
        double mOverAlphaFadeInSpeed;
    };
} // namespace pvz
