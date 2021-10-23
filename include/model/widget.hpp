#pragma once


#include "insets.hpp"

namespace pvz {
    struct Widget {
        UNKNOWN_BYTES(84);
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
