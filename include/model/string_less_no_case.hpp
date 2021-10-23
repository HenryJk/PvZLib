#pragma once

namespace pvz {
    struct StringLessNoCase {
        bool operator()(IncompatibleBasicString a, IncompatibleBasicString b) const;
    };
} // namespace pvz
