#pragma once

#include "win_inet_http_transfer.hpp"

namespace pvz {
    struct SexyApp;
    struct BetaSupport {
        UNKNOWN_BYTES(4);
        SexyApp *mApp;
        HFONT__ *mDialogFont;
        HFONT__ *mItalicsFont;
        HFONT__ *mBoldFont;
        int32_t mPeriodCount;
        HWND__ *mHWnd;
        HWND__ *mTextHWnd;
        HWND__ *mNameHWnd;
        HWND__ *mPasswordHWnd;
        WinInetHTTPTransfer mWinInetHTTPTransfer;
        bool mAborted;
        bool mDialogClosed;
        IncompatibleBasicString mBetaCommentURL;
        IncompatibleBasicString mDemoUploadFile;
        IncompatibleBasicString mName;
        IncompatibleBasicString mPassword;
        bool mValidated;
        IncompatibleMap mDataLogs;
    };
} // namespace pvz
