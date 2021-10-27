#pragma once

#include "flags_mod.hpp"
#include "graphics.hpp"

namespace pvz {
    struct WidgetManager {
        UNKNOWN_BYTES(84);
        Widget *mDefaultTab;
        Graphics *mCurG;
        SexyAppBase *mApp;
        MemoryImage *mImage;
        MemoryImage *mTransientImage;
        bool mLastHadTransients;
        Widget *mPopupCommandWidget;
        IncompatibleVector mDeferredOverlayWidgets;
        int32_t mMinDeferredOverlayPriority;
        bool mHasFocus;
        Widget *mFocusWidget;
        Widget *mLastDownWidget;
        Widget *mOverWidget;
        Widget *mBaseModalWidget;
        FlagsMod mLostFocusFlagsMod;
        FlagsMod mBelowModalFlagsMod;
        FlagsMod mDefaultBelowModalFlagsMod;
        IncompatibleList mPreModalInfoList;
        TRect<int32_t> mMouseDestRect;
        TRect<int32_t> mMouseSourceRect;
        bool mMouseIn;
        int32_t mLastMouseX;
        int32_t mLastMouseY;
        int32_t mDownButtons;
        int32_t mActualDownButtons;
        int32_t mLastInputUpdateCnt;
        bool mKeyDown[255];
        int32_t mLastDownButtonId;
        int32_t mWidgetFlags;
    };
} // namespace pvz
