#pragma once

#include "flags_mod.hpp"
#include "insets.hpp"

namespace pvz {
    struct WidgetManager;

    struct WidgetContainer {
        UNKNOWN_BYTES(4);
        IncompatibleList mWidgets;
        WidgetManager *mWidgetManager;
        WidgetContainer *mParent;
        bool mUpdateIteratorModified;
        UNDECIPHERABLE mUpdateIterator[8];
        uint32_t mLastWMUpdateCount;
        int32_t mUpdateCnt;
        bool mDirty;
        int mX;
        int mY;
        int mWidth;
        int mHeight;
        bool hasAlpha;
        bool mClip;
        FlagsMod mWidgetFlagsMod;
        int32_t mPriority;
        int32_t mZOrder;
    };

    struct Widget : WidgetContainer {
        bool mVisible;
        bool mMouseVisible;
        bool mDisabled;
        bool mHasFocus;
        bool mIsDown;
        bool mIsOver;
        bool mHasTransparencies;
        IncompatibleVector mColors;
        Insets mMouseInsets;
        bool mDoFinger;
        bool mWantsFocus;
        Widget *mTabPrev;
        Widget *mTabNext;
    };
} // namespace pvz
