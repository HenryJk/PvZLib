#pragma once

namespace pvz {
    struct PerfTimer {
        _LARGE_INTEGER mStart;
        double mDuration;
        bool mRunning;
        UNKNOWN_BYTES(7);
    };
} // namespace pvz
