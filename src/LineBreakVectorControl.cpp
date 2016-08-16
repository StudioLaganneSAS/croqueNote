//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "LineBreakVectorControl.h"
#include "PKVectorEngine.h"
#include "PKDialog.h"
#include "PKStr.h"
#include "PKCursorTools.h"

//
// LineBreakVectorControl
//

LineBreakVectorControl::LineBreakVectorControl()
{
    this->hover = false;
	this->x_hit = false;
}

LineBreakVectorControl::~LineBreakVectorControl()
{
}


void LineBreakVectorControl::drawVector(PKVectorEngine *engine,
									    int32_t x, int32_t y)
{
	if(this->hover)
	{
		int w = this->getW();
		int h = this->getH();

		double margin = (double)w/20.0;

		int ww = w/2 - 2*margin;
		int hh = h - 2*margin;

		PKColor normalColor  = PKColorCreate(220,220,220,255);
		PKColor downColor    = PKColorCreate(190,190,190,255);
	                                       
		double r = (double)w/20.0;
	    
		PKColor color1 = normalColor;

		engine->fillCircle(x+margin+r, y+margin+r, r, color1);
		engine->fillCircle(x+w/2-r-margin, y+margin+r, r, color1);
	    
		engine->fillCircle(x+w/2-r-margin, y+h-r-margin, r, color1);
		engine->fillCircle(x+margin+r, y+h-r-margin, r, color1);
	    
		engine->fillRect(x+margin, y+margin+r, 2*r, h-2*r-2*margin, color1);
		engine->fillRect(x+margin+r, y+margin, w/2-2*margin-2*r+1, h-2*margin, color1);    
		engine->fillRect(x+margin+w/2-2*margin-r, y+margin+r, r, h-2*r-2*margin, color1);

		PKColor white  = PKColorCreate(255,255,255,255);

		// Draw separator
		engine->fillRect(x, y+margin+h/3, w, h/17, white);

		// Draw close button
		int fh = h/5;
		int size = engine->getStringWidth(L"Helvetica", fh, PKV_FONT_STYLE_BOLD, L"X");
        engine->drawString(L"Helvetica", fh, PKV_FONT_STYLE_BOLD, white, x+margin+(w/2-2*margin-size)/2, y+margin+h/15, L"X");

		// Draw the line break symbol

		double tr = hh/5;

		engine->fillTriangle(x+margin+ww/2, 
							 y+margin+2*hh/3+tr/3, 
							 x+margin+ww/2, 
							 y+margin+2*hh/3+tr+tr/3, 
							 x+margin+ww/2-2*tr/3, 
							 y+margin+2*hh/3+tr/2+tr/3, 
							 white);

		engine->fillRect(x+margin+ww/2, y+margin+2*hh/3+tr/2-ww/30+tr/3, ww/5, ww/15, white);
		engine->fillRect(x+margin+ww/2+ww/5-ww/15, y+margin+2*hh/3+tr/2-hh/4+tr/3, ww/15, hh/4, white);
	}
}

void LineBreakVectorControl::mouseDown(PKButtonType button,
				                       int x,
				                       int y,
				                       unsigned int mod)
{
	int w = this->getW();
	int h = this->getH();

	double margin = (double)w/20.0;

	if(y <= margin+h/3)
	{
		PKCursorTools::setCursor(PK_CURSOR_HAND);
		this->x_hit = true;
	}
}

void LineBreakVectorControl::mouseUp(PKButtonType button,
				                     int x,
				                     int y,
                                     unsigned int mod)
{
	int w = this->getW();
	int h = this->getH();

	double margin = (double)w/20.0;

	if(y <= margin+h/3)
	{
		if(this->x_hit)
		{
			// It's a hit
            if(this->getDialog())
            {
                std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
                this->getDialog()->customControlClicked(button, sid, this, "CLOSE");
            }
		}
	}

	this->x_hit = false;
}

void LineBreakVectorControl::mouseMove(int x,
			                           int y,
			                           unsigned int mod)
{
	int w = this->getW();
	int h = this->getH();

	double margin = (double)w/20.0;

	if(y <= margin+h/3)
	{
		PKCursorTools::setCursor(PK_CURSOR_HAND);
	}
	else
	{
		PKCursorTools::setCursor(PK_CURSOR_ARROW);
	}

	if(!this->hover)
    {
        this->hover = true;
        this->invalidate();
    }
}

void LineBreakVectorControl::mouseLeave()
{
	PKCursorTools::setCursor(PK_CURSOR_ARROW);

	this->x_hit = false;

    if(this->hover)
    {
        this->hover = false;
        this->invalidate();
    }
}