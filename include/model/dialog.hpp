#pragma once

namespace pvz {
    struct DialogListener {
        UNKNOWN_BYTES(4);
    };

    struct Dialog {
        UNKNOWN_BYTES(140);
        DialogListener *mDialogListener;
        Image *mComponentImage;
        DialogButton *mYesButton;
        DialogButton *mNoButton;
        int32_t mNumButtons;
        IncompatibleBasicString mDialogHeader;
        IncompatibleBasicString mDialogFooter;
        IncompatibleBasicString mDialogLines;
        int32_t mButtonMode;
        Font *mHeaderFont;
        Font *mLinesFont;
        int32_t mTextAlign;
        int32_t mLineSpacingOffset;
        int32_t mButtonHeight;
        Insets mBackgroundInsets;
        Insets mContentInsets;
        int32_t mSpaceAfterHeader;
        bool mDragging;
        int32_t mDragMouseX;
        int32_t mDragMouseY;
        int32_t mId;
        bool mIsModal;
        int32_t mResult;
        int32_t mButtonHorzSpacing;
        int32_t mButtonSidePadding;
    };
} // namespace pvz
