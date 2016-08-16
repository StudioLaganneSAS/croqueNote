//
//
//

#ifndef CHORDABLE_DOCUMENT_H
#define CHORDABLE_DOCUMENT_H

#include "PKObject.h"

//
// ChordableDocument
//

class ChordableDocument : public PKObject
{
public:

    static std::string TITLE_WSTRING_PROPERTY;
    static std::string SUBTITLE_WSTRING_PROPERTY;
	static std::string SHOW_TEMPO_BOOL_PROPERTY;
	static std::string TEMPO_WSTRING_PROPERTY;
	static std::string SHOW_KEY_BOOL_PROPERTY;
	static std::string KEY_INT32_PROPERTY;
	static std::string TUNING_STRINGLIST_PROPERTY;
	static std::string SHOW_TUNING_BOOL_PROPERTY;
	static std::string BARS_PER_ROW_UINT32_PROPERTY;
	static std::string NOTES_WSTRING_PROPERTY;
	static std::string SHOW_CHORD_DIAGRAMS_BOOL_PROPERTY;
	static std::string SHOW_CAPO_BOOL_PROPERTY;
	static std::string CAPO_WSTRING_PROPERTY;

public:

    ChordableDocument();
    ~ChordableDocument();

private:
};

#endif // CHORDABLE_DOCUMENT_H