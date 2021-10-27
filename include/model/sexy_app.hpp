#pragma once

#include "beta_support.hpp"
#include "internet_manager.hpp"
#include "sexy_app_base.hpp"

namespace pvz {
    struct SexyApp : SexyAppBase {
        InternetManager *mInternetManager;
        BetaSupport *mBetaSupport;
        IncompatibleBasicString mBetaSupportSiteOverride;
        IncompatibleBasicString mBetaSupportProdNameOverride;
        IncompatibleBasicString mReferId;
        IncompatibleBasicString mVariation;
        uint32_t mDownloadId;
        IncompatibleBasicString mRegSource;
        uint32_t mLastVerCheckQueryTime;
        bool mSkipAd;
        bool mDontUpdate;
        int32_t mBuildNum;
        IncompatibleBasicString mBuildDate;
        IncompatibleBasicString mUserName;
        IncompatibleBasicString mRegUserName;
        IncompatibleBasicString mRegCode;
        bool mIsRegistered;
        bool mBuildUnlocked;
        int32_t mTimesPlayed;
        int32_t mTimesExecuted;
        bool mTimedOut;
        UNKNOWN_BYTES(7);
    };
} // namespace pvz
