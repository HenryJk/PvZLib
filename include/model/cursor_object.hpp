#pragma once



namespace pvz {
    struct CursorObject : GameObject {
        int32_t mSeedBankIndex;
        SeedType mType;
        SeedType mImitaterType;
        CursorType mCursorType;
        int32_t mCoinID;
        int32_t mGlovePlantID;
        int32_t mDuplicatorPlantID;
        int32_t mCobCannonPlantID;
        int32_t mHammerDownCounter;
        int32_t mReanimCursorID;
    };
} // namespace pvz
