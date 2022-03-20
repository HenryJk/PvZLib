#![allow(non_snake_case)]

use crate::{DialogButton, LawnApp, SelectorAnimState, ToolTipWidget, Widget};

#[repr(C)]
pub struct GameSelector {
    pub base: Widget,
    unknown: u32,
    pub mApp: *mut LawnApp,
    pub mAdventureButton: *mut DialogButton,
    pub mMinigameButton: *mut DialogButton,
    pub mPuzzleButton: *mut DialogButton,
    pub mOptionsButton: *mut DialogButton,
    pub mQuitButton: *mut DialogButton,
    pub mHelpButton: *mut DialogButton,
    pub mStoreButton: *mut DialogButton,
    pub mAlmanacButton: *mut DialogButton,
    pub mZenGardenButton: *mut DialogButton,
    pub mSurvivalButton: *mut DialogButton,
    pub mChangeUserButton: *mut DialogButton,
    pub mOverlayWidget: *mut Widget,
    pub mStartingGame: bool,
    pub mStartingGameCounter: i32,
    pub mMinigamesLocked: bool,
    pub mPuzzleLocked: bool,
    pub mSurvivalLocked: bool,
    pub mShowStartButton: bool,
    pub mTrophyParticleID: i32,
    pub mSelectorReanimID: i32,
    pub mCloudReanimID: [i32; 6],
    pub mCloudCounter: [i32; 6],
    pub mFlowerReanimID: [i32; 3],
    pub mLeafReanimID: i32,
    pub mHandReanimID: i32,
    pub mLeafCounter: i32,
    pub mSelectorState: SelectorAnimState,
    pub mLevel: i32,
    pub mLoading: bool,
    pub mToolTip: *mut ToolTipWidget,
}