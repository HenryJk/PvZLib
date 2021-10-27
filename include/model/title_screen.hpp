#pragma once

#include "hyperlink_widget.hpp"

namespace pvz {
    struct TitleScreen : EMRPLGBLT {
        HyperlinkWidget *mStartButton;
        float mCurBarWidth;
        float mTotalBarWidth;
        float mBarVel;
        bool mRegisterClicked;
        bool mLoadingThreadComplete;
        int32_t mTitleAge;
        KeyCode mQuickLoadKey;
        bool mNeedRegister;
        bool mNeedShowRegisterBox;
        bool mDrawnYet;
        bool mNeedToInit;
        float mPrevLoadingPercent;
        LawnApp *mApp;
    };
} // namespace pvz
