#pragma once

#include "sexy_transform_2d.hpp"

namespace pvz {
    struct AttachEffect {
        uint32_t mEffectID;
        EffectType mEffectType;
        SexyTransform2D mOffset;
        bool mDontDrawIfParentHidden;
        bool mDontPropogateColor;
    };

    struct Attachment {
        AttachEffect mEffectArray[16];
        int32_t mNumEffects;
        bool mDead;
    };

    struct AttachmentHolder {
        DataArray<Attachment> mAttachments;
    };
} // namespace pvz
