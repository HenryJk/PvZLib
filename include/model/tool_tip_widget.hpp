#pragma once

namespace pvz {
    struct ToolTipWidget {
        IncompatibleBasicString mTitle;
        IncompatibleBasicString mLabel;
        IncompatibleBasicString mWarningText;
        int32_t mX;
        int32_t mY;
        int32_t mWidth;
        int32_t mHeight;
        bool mVisible;
        bool mCenter;
        int32_t mMinLeft;
        int32_t mMaxBottom;
        int32_t mGetsLinesWidth;
        int32_t mWarningFlashCounter;
    };
} // namespace pvz
