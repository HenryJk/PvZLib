#pragma once



namespace pvz {
    struct MessageWidget {
        LawnApp *mApp;
        char mLabel[128];
        int32_t mDisplayTime;
        int32_t mDuration;
        MessageStyle mMessageStyle;
        ReanimationType mReanimType;
        int32_t mSlideOffTime;
        char mLabelNext[128];
        MessageStyle mMessageStyleNext;
    };
} // namespace pvz
