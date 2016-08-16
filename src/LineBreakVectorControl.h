//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef LINEBREAK_VECTOR_CONTROL_H
#define LINEBREAK_VECTOR_CONTROL_H

#include "PKVectorControl.h"

//
// LineBreakVectorControl
//

class LineBreakVectorControl : public PKVectorControl
{
public:	
	LineBreakVectorControl();
	~LineBreakVectorControl();
	
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

private:
    bool hover;
	bool x_hit;
};

#endif // LINEBREAK_VECTOR_CONTROL_H
