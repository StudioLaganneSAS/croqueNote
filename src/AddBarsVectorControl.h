//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef ADDBARS_VECTOR_CONTROL_H
#define ADDBARS_VECTOR_CONTROL_H

#include "PKVectorControl.h"
#include "PKChordLibraryDialog.h"
#include "PKPopupMenu.h"

//
// AddBarsVectorControl
//

class AddBarsVectorControl : public PKVectorControl, public PKPopupMenuCallback
{
public:	
	AddBarsVectorControl();
	~AddBarsVectorControl();
	
    bool isPopupMenuShown();

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

	virtual void mouseDblClick(PKButtonType button,
							   int x,
							   int y,
							   unsigned int mod);

    virtual void mouseMove(int x,
						   int y,
						   unsigned int mod);

	virtual void mouseLeave();

    // PKControl

    void updateUIStrings();

    // From PKPopupMenuCallback

    virtual void menuCancelled();
	virtual void menuCallback(unsigned int id);

private:

    bool hoverPlus;
    bool hoverArrow;

    bool downPlus;
    bool downArrow;

    PKPopupMenu *menu;
    bool menuShown;
};

#endif // ADDBARS_VECTOR_CONTROL_H
