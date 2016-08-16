//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef BARVIEW_VECTOR_CONTROL_H
#define BARVIEW_VECTOR_CONTROL_H

#include "PKVectorControl.h"
#include "PKChordLibraryDialog.h"

//
// Types
//

typedef enum 
{
    BAR_TYPE_SINGLE,
    BAR_TYPE_DOUBLE,
    BAR_TYPE_TRIPLE1,
    BAR_TYPE_TRIPLE2,
    BAR_TYPE_QUAD,

} BarControlType;

//
// BarViewVectorControl
//

class BarViewVectorControl : public PKVectorControl
{
public:	

    static std::string SELECTED_BOOL_PROPERTY;
    static std::string LINECOLOR_COLOR_PROPERTY;
    static std::string HOVERCOLOR_COLOR_PROPERTY;
    static std::string SELECTEDCOLOR_COLOR_PROPERTY;
    static std::string BARTYPE_UINT8_PROPERTY;

	static std::string REPEAT_LEFT_BOOL_PROPERTY;
	static std::string REPEAT_RIGHT_BOOL_PROPERTY;
	static std::string SECTION_MARKER_BOOL_PROPERTY;
	static std::string SECTION_NUMBER_UINT32_PROPERTY;
	static std::string HEADER_WSTRING_PROPERTY;

public:	
	BarViewVectorControl();
	~BarViewVectorControl();
	
	// Setup

	void setChordNameForIndex(int32_t index, std::wstring name);
	void setChordLibraryStateForIndex(int32_t index, PKChordLibraryState *state);
	void setChordDiagramForIndex(int32_t index, PKChordDiagram *diagram);

	std::wstring         getChordNameForIndex(int32_t index);
	PKChordLibraryState *getChordLibraryStateForIndex(int32_t index);
	PKChordDiagram      *getChordDiagramForIndex(int32_t index);

    // PKVectorControl

	void drawVector(PKVectorEngine *engine,
					int32_t x, int32_t y);	

    // PKCustomControl

    virtual void mouseDown(PKButtonType button,
					            int x,
					            int y,
					            unsigned int mod);

    virtual void mouseUp(PKButtonType button,
					          int x,
					          int y,
                              unsigned int mod);

    virtual void mouseMove(int x,
						   int y,
						   unsigned int mod);

	virtual void mouseLeave();

	virtual void mouseDblClick(PKButtonType button,
							   int x,
							   int y,
							   unsigned int mod);

    // PKObject

	virtual void selfPropertyChanged(PKProperty *prop, PKVariant *oldValue);

private:
    bool hover;
    bool hit;
	bool x_hit;

	std::vector<PKChordDiagram *>      diagrams;
	std::vector<std::wstring>          chordNames;
	std::vector<PKChordLibraryState *> states;
};

#endif // BARVIEW_VECTOR_CONTROL_H
