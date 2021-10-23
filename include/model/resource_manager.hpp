#pragma once

#include "xml_parser.hpp"

namespace pvz {
    struct ResourceManager {
        struct BaseRes {};
        UNKNOWN_BYTES(4);
        IncompatibleSet mLoadedGroups;
        IncompatibleMap mImageMap;
        IncompatibleMap mSoundMap;
        IncompatibleMap mFontMap;
        XMLParser *mXMLParser;
        IncompatibleBasicString mError;
        bool mHasFailed;
        SexyAppBase *mApp;
        IncompatibleBasicString mCurResGroup;
        IncompatibleBasicString mDefaultPath;
        IncompatibleBasicString mDefaultIdPrefix;
        bool mAllowMissingProgramResources;
        bool mAllowAlreadyDefinedResources;
        bool mHadAlreadyDefinedError;
        IncompatibleMap mResGroupMap;
        IncompatibleList *mCurResGroupList;
        UNDECIPHERABLE mCurResGroupListItr[8];
    };
} // namespace pvz
