//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHORDABLE_SETTINGS_H
#define CHORDABLE_SETTINGS_H

#include "PKSettings.h"

//
// ChordableSettings
//

class ChordableSettings : public PKSettings
{
public:

    // PROPERTIES

    static std::string NOTATION_UINT32_PROPERTY;
    static std::string ZOOM_UINT32_PROPERTY;

    static std::string WINDOW_X_INT32_PROPERTY;
    static std::string WINDOW_Y_INT32_PROPERTY;
    static std::string WINDOW_W_INT32_PROPERTY;
    static std::string WINDOW_H_INT32_PROPERTY;

    static std::string LANGUAGE_STRING_PROPERTY;

public:

    ChordableSettings();
    ~ChordableSettings();


};

#endif // CHORDABLE_SETTINGS_H
