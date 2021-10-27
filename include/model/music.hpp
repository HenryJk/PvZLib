#pragma once

namespace pvz {
    struct MusicInterface {
        UNKNOWN_BYTES(4);
    };

    struct Music {
        LawnApp *mApp;
        MusicInterface *mMusicInterface;
        MusicTune mCurMusicTune;
        MusicFile mCurMusicFileMain;
        MusicFile mCurMusicFileDrums;
        MusicFile mCurMusicFileHihats;
        int32_t mBurstOverride;
        int32_t mBaseBPM;
        int32_t mBaseModSpeed;
        MusicBurstState mMusicBurstState;
        int32_t mBurstStateCounter;
        MusicDrumsState mMusicDrumsState;
        int32_t mQueuedDrumTrackPackedOrder;
        int32_t mDrumsStateCounter;
        int32_t mPauseOffset;
        int32_t mPauseOffsetDrums;
        bool mPaused;
        bool mMusicDisabled;
        int32_t mFadeOutCounter;
        int32_t mFadeOutDuration;
    };
} // namespace pvz
