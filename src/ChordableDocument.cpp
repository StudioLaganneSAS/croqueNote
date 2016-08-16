//
//
//

#include "ChordableDocument.h"
#include "PKNotes.h"
#include "PKStr.h"

//
//
//

std::string ChordableDocument::TITLE_WSTRING_PROPERTY            = "title";
std::string ChordableDocument::SUBTITLE_WSTRING_PROPERTY         = "subtitle";
std::string ChordableDocument::SHOW_TEMPO_BOOL_PROPERTY          = "showTempo";
std::string ChordableDocument::TEMPO_WSTRING_PROPERTY            = "tempo";
std::string ChordableDocument::SHOW_KEY_BOOL_PROPERTY            = "showKey";
std::string ChordableDocument::KEY_INT32_PROPERTY                = "key";
std::string ChordableDocument::TUNING_STRINGLIST_PROPERTY        = "tuning";
std::string ChordableDocument::SHOW_TUNING_BOOL_PROPERTY         = "showTuning";
std::string ChordableDocument::BARS_PER_ROW_UINT32_PROPERTY      = "barsPerRow";
std::string ChordableDocument::NOTES_WSTRING_PROPERTY            = "notes";
std::string ChordableDocument::SHOW_CHORD_DIAGRAMS_BOOL_PROPERTY = "showChords";
std::string ChordableDocument::SHOW_CAPO_BOOL_PROPERTY           = "showCapo";
std::string ChordableDocument::CAPO_WSTRING_PROPERTY             = "capo";


ChordableDocument::ChordableDocument()
{
	std::vector<std::string> t;

    PKOBJECT_ADD_WSTRING_PROPERTY(title,    L"");
    PKOBJECT_ADD_WSTRING_PROPERTY(subtitle, L"");
    PKOBJECT_ADD_WSTRING_PROPERTY(capo,     L"1");
    PKOBJECT_ADD_WSTRING_PROPERTY(tempo,    L"120");
    PKOBJECT_ADD_WSTRING_PROPERTY(notes,    L"");
	
	PKOBJECT_ADD_BOOL_PROPERTY(showTempo,  false);
	PKOBJECT_ADD_BOOL_PROPERTY(showKey,    false);
	PKOBJECT_ADD_BOOL_PROPERTY(showChords, false);
	PKOBJECT_ADD_BOOL_PROPERTY(showCapo,   false);

    PKOBJECT_ADD_INT32_PROPERTY(key,  0);

	t.push_back(PKStr::int32ToString(PKNOTE_E));
	t.push_back(PKStr::int32ToString(PKNOTE_A));
	t.push_back(PKStr::int32ToString(PKNOTE_D));
	t.push_back(PKStr::int32ToString(PKNOTE_G));
	t.push_back(PKStr::int32ToString(PKNOTE_B));
	t.push_back(PKStr::int32ToString(PKNOTE_E));

	PKOBJECT_ADD_STRINGLIST_PROPERTY(tuning, t);
	PKOBJECT_ADD_BOOL_PROPERTY(showTuning, false);
	
	PKOBJECT_ADD_UINT32_PROPERTY(barsPerRow, 6);
}

ChordableDocument::~ChordableDocument()
{
}

