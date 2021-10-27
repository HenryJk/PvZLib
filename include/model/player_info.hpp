#pragma once

namespace pvz {
    struct PlayerInfo {
        IncompatibleBasicString mName;
        uint32_t mUseSeq;
        uint32_t mId;
        int32_t mLevel;
        int32_t mCoins;
        int32_t mFinishedAdventure;
        int32_t mChallengeRecords[100];
        int32_t mPurchases[80];
        int32_t mPlayTimeActivePlayer;
        int32_t mPlayTimeInactivePlayer;
        int32_t mHasUsedCheatKeys;
        int32_t mHasWokenStinky;
        int32_t mDidntPurchasePacketUpgrade;
        int32_t mLastStinkyChocolateTime;
        int32_t mStinkyPosX;
        int32_t mStinkyPosY;
        int32_t mHasUnlockedMinigames;
        int32_t mHasUnlockedPuzzleMode;
        int32_t mHasNewMiniGame;
        int32_t mHasNewVasebreaker;
        int32_t mHasNewIZombie;
        int32_t mHasNewSurvival;
        int32_t mPlaceHolderPlayerStats[6];
        int32_t mNumPottedPlants;
        UNKNOWN_BYTES(4);
        PottedPlant mPottedPlant[200];
    };
} // namespace pvz
