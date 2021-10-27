#pragma once

#include "attachment.hpp"
#include "reanimation.hpp"
#include "tod_particle.hpp"
#include "trail.hpp"

namespace pvz {
    struct EffectSystem {
        TodParticleHolder *mParticleHolder;
        TrailHolder *mTrailHolder;
        ReanimationHolder *mReanimationHolder;
        AttachmentHolder *mAttachmentHolder;
    };
} // namespace pvz
