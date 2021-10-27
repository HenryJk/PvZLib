#pragma once

namespace pvz {
    struct IncompatibleBasicString {
        UNKNOWN_BYTES(28);
    };

    struct IncompatibleVector {
        UNKNOWN_BYTES(16);
    };

    struct IncompatibleMap {
        UNKNOWN_BYTES(12);
    };

    struct IncompatibleList {
        UNKNOWN_BYTES(12);
    };

    struct IncompatibleSet {
        UNKNOWN_BYTES(12);
    };
} // namespace pvz
