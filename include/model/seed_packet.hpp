#pragma once

namespace pvz {
    struct SeedPacket : GameObject {
        int32_t mRefreshCounter;
        int32_t mRefreshTime;
        int32_t mIndex;
        int32_t mOffsetX;
        SeedType mPacketType;
        SeedType mImitaterType;
        int32_t mSlotMachineCountDown;
        SeedType mSlotMachiningNextSeed;
        float mSlotMachiningPosition;
        bool mActive;
        bool mRefreshing;
        int32_t mTimesUsed;
    };
} // namespace pvz
