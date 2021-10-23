#pragma once

namespace pvz {
    struct XMLParser {
        UNKNOWN_BYTES(32);
        IncompatibleBasicString mFileName;
        IncompatibleBasicString mErrorText;
        int32_t mLineNum;
        bool mHasFailed;
        bool mAllowComments;
        IncompatibleBasicString mSection;
    };
} // namespace pvz
