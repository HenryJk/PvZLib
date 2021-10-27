#pragma once

namespace pvz {
    struct PreModalInfo {
        Widget *mBaseModalWidget;
        Widget *mPrevBaseModalWidget;
        Widget *mPrevFocusWidget;
        FlagsMod mPrevBelowModalFlagsMod;
    };
} // namespace pvz
