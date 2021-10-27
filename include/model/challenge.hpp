#pragma once

#include "enum.hpp"

namespace pvz {
    struct LawnApp;
    struct Board;
    struct Challenge {
        LawnApp *mApp;
        Board *mBoard;
        bool mBeghouledMouseCapture;
        int32_t mBeghouledMouseDownX;
        int32_t mBeghouledMouseDownY;
        bool mBeghouledEated[9][6];
        bool mBeghouledPurcasedUpgrade[3];
        int32_t mBeghouledMatchesThisMove;
        ChallengeState mChallengeState;
        int32_t mChallengeStateCounter;
        int32_t mConveyorBeltCounter;
        int32_t mChallengeScore;
        bool mShowBowlingLine;
        SeedType mLastConveyorSeedType;
        int32_t mSurvivalStage;
        int32_t mSlotMachineRollCount;
        int32_t mReanimChallenge;
        int32_t mReanimCloud[6];
        int32_t mCloudCounter[6];
        int32_t mChallengeGridX;
        int32_t mChallengeGridY;
        int32_t mScaryPotterPots;
        int32_t mRainCounter;
        int32_t mTreeOfWisdomTalkIndex;
    };
} // namespace pvz
