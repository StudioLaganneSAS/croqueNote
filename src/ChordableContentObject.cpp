//
//
//

#include "ChordableContentObject.h"

//
// PROPERTIES
//

std::string ChordableContentObject::OBJECT_TYPE_UINT8_PROPERTY      = "object_type";
std::string ChordableContentObject::BAR_TYPE_UINT8_PROPERTY         = "bar_type";
std::string ChordableContentObject::REPEAT_LEFT_BOOL_PROPERTY       = "repeat_left";
std::string ChordableContentObject::REPEAT_RIGHT_BOOL_PROPERTY      = "repeat_right";
std::string ChordableContentObject::SECTION_MARKER_BOOL_PROPERTY    = "section_marker";
std::string ChordableContentObject::SECTION_NUMBER_UINT32_PROPERTY  = "section_number";
std::string ChordableContentObject::HEADER_WSTRING_PROPERTY         = "header";
std::string ChordableContentObject::LIBRARY_STATE_1_BINARY_PROPERTY = "library_state_1";
std::string ChordableContentObject::CHORD_DIAGRAM_1_BINARY_PROPERTY = "chord_diagram_1";
std::string ChordableContentObject::LIBRARY_STATE_2_BINARY_PROPERTY = "library_state_2";
std::string ChordableContentObject::CHORD_DIAGRAM_2_BINARY_PROPERTY = "chord_diagram_2";
std::string ChordableContentObject::LIBRARY_STATE_3_BINARY_PROPERTY = "library_state_3";
std::string ChordableContentObject::CHORD_DIAGRAM_3_BINARY_PROPERTY = "chord_diagram_3";
std::string ChordableContentObject::LIBRARY_STATE_4_BINARY_PROPERTY = "library_state_4";
std::string ChordableContentObject::CHORD_DIAGRAM_4_BINARY_PROPERTY = "chord_diagram_4";

//
// ChordableContentObject
// 

ChordableContentObject::ChordableContentObject()
{
	PKOBJECT_ADD_UINT8_PROPERTY(object_type, 0);
	PKOBJECT_ADD_UINT8_PROPERTY(bar_type,    0);

	PKOBJECT_ADD_BOOL_PROPERTY(repeat_left,    false);
	PKOBJECT_ADD_BOOL_PROPERTY(repeat_right,   false);
	PKOBJECT_ADD_BOOL_PROPERTY(section_marker, false);

	PKOBJECT_ADD_UINT32_PROPERTY(section_number, 1);

	PKOBJECT_ADD_WSTRING_PROPERTY(header, L"");

	PKOBJECT_ADD_BINARY_PROPERTY(library_state_1, 0, NULL);
	PKOBJECT_ADD_BINARY_PROPERTY(chord_diagram_1, 0, NULL);

	PKOBJECT_ADD_BINARY_PROPERTY(library_state_2, 0, NULL);
	PKOBJECT_ADD_BINARY_PROPERTY(chord_diagram_2, 0, NULL);

	PKOBJECT_ADD_BINARY_PROPERTY(library_state_3, 0, NULL);
	PKOBJECT_ADD_BINARY_PROPERTY(chord_diagram_3, 0, NULL);

	PKOBJECT_ADD_BINARY_PROPERTY(library_state_4, 0, NULL);
	PKOBJECT_ADD_BINARY_PROPERTY(chord_diagram_4, 0, NULL);
}

ChordableContentObject::~ChordableContentObject()
{
}

