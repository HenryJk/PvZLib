#pragma once



namespace pvz {
    struct PottedPlant {
        SeedType mSeedType;
        GardenType mWhichZenGarden;
        int32_t mX;
        int32_t mY;
        int32_t mFacing;
        UNKNOWN_BYTES(4);
        int32_t mLastWateredTime;
        DrawVariation mDrawVariation;
        PottedPlantAge mPlantAge;
        int32_t mTimesFed;
        int32_t mFeedingsPerGrow;
        PottedPlantNeed mPlantNeed;
        UNKNOWN_BYTES(4);
        int32_t mLastNeedFulfilledTime;
        int32_t mLastFertilizedTime;
        int32_t mLastChocolateTime;
        int32_t mFutureAttribute[1];
        UNKNOWN_BYTES(4);
    };
} // namespace pvz
