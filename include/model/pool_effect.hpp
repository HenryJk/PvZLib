#pragma once



namespace pvz {
    struct PoolEffect {
        unsigned char *mCausticGrayscaleImage;
        MemoryImage *mCausticImage;
        LawnApp *mApp;
        int32_t mPoolCounter;
    };
} // namespace pvz
