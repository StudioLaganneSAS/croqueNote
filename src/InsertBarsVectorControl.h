//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef INSERTBARS_VECTOR_CONTROL_H
#define INSERTBARS_VECTOR_CONTROL_H

#include "PKVectorControl.h"
#include "PKChordLibraryDialog.h"
#include "PKPopupMenu.h"

//
// InsertBarsVectorControl
//

class InsertBarsVectorControl : public PKVectorControl, public PKPopupMenuCallback
{
public:	
	InsertBarsVectorControl();
	~InsertBarsVectorControl();
	
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

#endif // INSERTBARS_VECTOR_CONTROL_H
