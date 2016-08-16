//
//
//

#ifndef CHORDABLE_CONTENT_OBJECT_H
#define CHORDABLE_CONTENT_OBJECT_H

#include "PKObject.h"

//
// Defines
//

#define CHORDABLE_CONTENT_OBJECT_TYPE_BAR        1
#define CHORDABLE_CONTENT_OBJECT_TYPE_LINE_BREAK 2

//
// ChordableContentObject
//

class ChordableContentObject : public PKObject
{
public:

    static std::string OBJECT_TYPE_UINT8_PROPERTY;

    static std::string BAR_TYPE_UINT8_PROPERTY;
    static std::string REPEAT_LEFT_BOOL_PROPERTY;
    static std::string REPEAT_RIGHT_BOOL_PROPERTY;
    static std::string SECTION_MARKER_BOOL_PROPERTY;
    static std::string SECTION_NUMBER_UINT32_PROPERTY;
    static std::string HEADER_WSTRING_PROPERTY;

    static std::string LIBRARY_STATE_1_BINARY_PROPERTY;
    static std::string CHORD_DIAGRAM_1_BINARY_PROPERTY;

    static std::string LIBRARY_STATE_2_BINARY_PROPERTY;
    static std::string CHORD_DIAGRAM_2_BINARY_PROPERTY;

    static std::string LIBRARY_STATE_3_BINARY_PROPERTY;
    static std::string CHORD_DIAGRAM_3_BINARY_PROPERTY;

    static std::string LIBRARY_STATE_4_BINARY_PROPERTY;
    static std::string CHORD_DIAGRAM_4_BINARY_PROPERTY;

public:

    ChordableContentObject();
    ~ChordableContentObject();

private:
};

#endif // CHORDABLE_CONTENT_OBJECT_H