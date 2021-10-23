#pragma once

namespace pvz {
    struct ProfileMgr {
        UNKNOWN_BYTES(4);
        IncompatibleMap mProfileMap;
        uint32_t mNextProfileId;
        uint32_t mNextProfileUseSeq;
    };
} // namespace pvz
