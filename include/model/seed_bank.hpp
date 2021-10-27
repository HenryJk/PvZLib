#pragma once

#include "seed_packet.hpp"

namespace pvz {
    struct SeedBank : GameObject {
        int32_t mNumPackets;
        SeedPacket mSeedPackets[10];
        int32_t mCutSceneDarken;
        int32_t mConveyorBeltCounter;
    };
} // namespace pvz
