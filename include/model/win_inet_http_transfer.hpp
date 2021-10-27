#pragma once

#include <cstdio>

namespace pvz {
    struct WinInetHTTPTransfer {
        UNKNOWN_BYTES(4);
        IncompatibleBasicString mSpecifiedBaseURL;
        IncompatibleBasicString mSpecifiedRelURL;
        IncompatibleBasicString mURL;
        IncompatibleBasicString mProto;
        IncompatibleBasicString mUserName;
        IncompatibleBasicString mUserPass;
        IncompatibleBasicString mHost;
        int32_t mPort;
        IncompatibleBasicString mPath;
        IncompatibleBasicString mAction;
        IncompatibleBasicString mUserAgent;
        IncompatibleBasicString mPostContentType;
        IncompatibleBasicString mPostData;
        _iobuf *mFP;
        bool mUsingFile;
        IncompatibleBasicString mContent;
        int32_t mContentLength;
        int32_t mCurContentLength;
        bool mTransferPending;
        bool mThreadRunning;
        bool mExiting;
        bool mAborted;
        EResult mResult;
        _RTL_CRITICAL_SECTION mFileCritSection;
    };
} // namespace pvz
