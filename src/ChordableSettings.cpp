//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ChordableSettings.h"

//
// ChordableSettings
//

std::string ChordableSettings::NOTATION_UINT32_PROPERTY = "notation";
std::string ChordableSettings::ZOOM_UINT32_PROPERTY     = "zoom";
std::string ChordableSettings::WINDOW_X_INT32_PROPERTY  = "window_x";
std::string ChordableSettings::WINDOW_Y_INT32_PROPERTY  = "window_y";
std::string ChordableSettings::WINDOW_W_INT32_PROPERTY  = "window_w";
std::string ChordableSettings::WINDOW_H_INT32_PROPERTY  = "window_h";
std::string ChordableSettings::LANGUAGE_STRING_PROPERTY = "language";

ChordableSettings::ChordableSettings()
{
    this->setAppName("Croque-Note");

    PKOBJECT_ADD_UINT32_PROPERTY(notation, 1);
    PKOBJECT_ADD_UINT32_PROPERTY(zoom, 50);

    PKOBJECT_ADD_INT32_PROPERTY(window_x, -1);
    PKOBJECT_ADD_INT32_PROPERTY(window_y, -1);
    PKOBJECT_ADD_INT32_PROPERTY(window_w, -1);
    PKOBJECT_ADD_INT32_PROPERTY(window_h, -1);

    PKOBJECT_ADD_STRING_PROPERTY(language, "en_US");
}

ChordableSettings::~ChordableSettings()
{

}

