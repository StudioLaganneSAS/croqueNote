//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "BarViewVectorControl.h"
#include "PKVectorEngine.h"
#include "PKDialog.h"
#include "PKStr.h"
#include "PKCursorTools.h"

//
// Properties
//

std::string BarViewVectorControl::SELECTED_BOOL_PROPERTY       = "selected";
std::string BarViewVectorControl::LINECOLOR_COLOR_PROPERTY     = "lineColor";
std::string BarViewVectorControl::HOVERCOLOR_COLOR_PROPERTY    = "hoverColor";
std::string BarViewVectorControl::SELECTEDCOLOR_COLOR_PROPERTY = "selectedColor";
std::string BarViewVectorControl::BARTYPE_UINT8_PROPERTY       = "barType";

std::string BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY      = "repeatLeft";
std::string BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY     = "repeatRight";
std::string BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY   = "sectionMarker";
std::string BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY = "sectionNumber";
std::string BarViewVectorControl::HEADER_WSTRING_PROPERTY        = "header";

//
// BarViewVectorControl
//

BarViewVectorControl::BarViewVectorControl()
{
    this->hover = false;
    this->hit   = false;
	this->x_hit = false;

    PKColor lineColor1     = PKColorCreate(0, 0, 0, 255);
    PKColor hoverColor1    = PKColorCreate(160, 200, 230, 255);
    PKColor selectedColor1 = PKColorCreate(130, 180, 220, 255);

    PKOBJECT_ADD_BOOL_PROPERTY(selected, false);
    PKOBJECT_ADD_COLOR_PROPERTY(lineColor, lineColor1);
    PKOBJECT_ADD_COLOR_PROPERTY(hoverColor, hoverColor1);
    PKOBJECT_ADD_COLOR_PROPERTY(selectedColor, selectedColor1);
    PKOBJECT_ADD_UINT8_PROPERTY(barType, 0);

	PKOBJECT_ADD_BOOL_PROPERTY(repeatLeft, false);
	PKOBJECT_ADD_BOOL_PROPERTY(repeatRight, false);
	PKOBJECT_ADD_BOOL_PROPERTY(sectionMarker, false);
	PKOBJECT_ADD_UINT32_PROPERTY(sectionNumber, 1);
	PKOBJECT_ADD_WSTRING_PROPERTY(header, L"");

	this->chordNames.push_back(L"");
	this->chordNames.push_back(L"");
	this->chordNames.push_back(L"");
	this->chordNames.push_back(L"");

	this->diagrams.push_back(NULL);
	this->diagrams.push_back(NULL);
	this->diagrams.push_back(NULL);
	this->diagrams.push_back(NULL);

	this->states.push_back(NULL);
	this->states.push_back(NULL);
	this->states.push_back(NULL);
	this->states.push_back(NULL);
}

BarViewVectorControl::~BarViewVectorControl()
{
}

void BarViewVectorControl::setChordNameForIndex(int32_t index, std::wstring name)
{
	if(index > 3)
	{
		return;
	}

	this->chordNames[index] = name;
}

std::wstring BarViewVectorControl::getChordNameForIndex(int32_t index)
{
	if(index > 3)
	{
		return L"";
	}

	return this->chordNames[index];
}

PKChordLibraryState *BarViewVectorControl::getChordLibraryStateForIndex(int32_t index)
{
	if(index > 3)
	{
		return NULL;
	}

	return this->states[index];
}

PKChordDiagram *BarViewVectorControl::getChordDiagramForIndex(int32_t index)
{
	if(index > 3)
	{
		return NULL;
	}

	return this->diagrams[index];
}

void BarViewVectorControl::setChordLibraryStateForIndex(int32_t index, PKChordLibraryState *state)
{
	if(index > 3)
	{
		return;
	}

	if(state == NULL)
	{
		return;
	}

	if(this->states[index] != NULL)
	{
		delete this->states[index];
		this->states[index] = NULL;
	}

	PKChordLibraryState *newState = new PKChordLibraryState;

	if(newState == NULL)
	{
		return;
	}

	newState->version          = state->version;
	newState->allowOpenStrings = state->allowOpenStrings;
	newState->bassNote         = state->bassNote;
	newState->rootNote         = state->rootNote;

	memcpy(newState->chordType_intervals, 
		   state->chordType_intervals, 
		   PKCHORD_MAX_INTERVALS*sizeof(uint8_t));

	newState->fiveMinus = state->fiveMinus;
	newState->fivePlus  = state->fivePlus;
	newState->flat      = state->flat;
	newState->nineMinus = state->nineMinus;
	newState->ninePlus  = state->ninePlus;
	newState->noteIndex = state->noteIndex;
	newState->sharp     = state->sharp;

	newState->thirteenMinus = state->thirteenMinus;
	newState->thirteenPlus  = state->thirteenPlus;

	this->states[index] = newState;
}

void BarViewVectorControl::setChordDiagramForIndex(int32_t index, PKChordDiagram *diagram)
{
	if(index > 3)
	{
		return;
	}

	if(diagram == NULL)
	{
		return;
	}

	if(this->diagrams[index] != NULL)
	{
		delete this->diagrams[index];
		this->diagrams[index] = NULL;
	}

	PKChordDiagram *newDiagram = new PKChordDiagram(diagram);

	if(newDiagram == NULL)
	{
		return;
	}

	this->diagrams[index] = newDiagram;
}

void BarViewVectorControl::drawVector(PKVectorEngine *engine,
									  int32_t x, int32_t y)
{
    int w = this->getW();
    int h = this->getH();

    double margin    = (double)w/20.0;
    double lineWidth = (double)w/100.0;

    int ww = w - 2*margin;
    int hh = h - 2*margin;

    PKColor lineColor = PKVALUE_COLOR(this->get(BarViewVectorControl::LINECOLOR_COLOR_PROPERTY));

	// Draw header if any

	bool sectionMarker  = PKVALUE_BOOL(this->get(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY));
	std::wstring header = PKVALUE_WSTRING(this->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));

	if(sectionMarker)
	{
		std::wstring numStr = PKStr::uint32ToWstring(PKVALUE_UINT32(this->get(BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY)));

		if(numStr != L"")
		{
			double fh = (double)hh/5;

			// Draw the lines

			engine->drawLine(x+margin, y-hh/20,
							 x+margin, y-hh/15-fh, 
							 lineColor, lineWidth);

			engine->drawLine(x+margin, y-hh/15-fh,
							 x+margin+ww, y-hh/15-fh, 
							 lineColor, lineWidth);

			// Draw the number

			engine->drawString(L"Arial", fh, PKV_FONT_STYLE_BOLD, lineColor, x+margin+ww/25, y-fh-hh/20, numStr+L".");
		}
	}
	else
	{
		if(header != L"")
		{
			// TODO: check allowed length
			double fh = (double)hh/4;
			engine->drawString(L"Arial", fh, PKV_FONT_STYLE_NORMAL, lineColor, x+margin, y-fh-hh/20, header);
		}
	}

    // Draw border if selected or hover

    if(this->hover)
    {
        PKColor hoverColor = PKVALUE_COLOR(this->get(BarViewVectorControl::HOVERCOLOR_COLOR_PROPERTY));

        double r = margin/2;
        
        engine->fillCircle(x+r, y+r, r, hoverColor);
        engine->fillCircle(x+w-r, y+r, r, hoverColor);
        engine->fillCircle(x+w-r, y+h-r, r, hoverColor);
        engine->fillCircle(x+r, y+h-r, r, hoverColor);

        engine->fillRect(x, y+r, w, h-2*r, hoverColor);
        engine->fillRect(x+r, y, w-2*r, h, hoverColor);
    }
    else
    {
        if(PKVALUE_BOOL(this->get(BarViewVectorControl::SELECTED_BOOL_PROPERTY)))
        {
            PKColor selectionColor = PKVALUE_COLOR(this->get(BarViewVectorControl::SELECTEDCOLOR_COLOR_PROPERTY));

            double r = margin/2;
            
            engine->fillCircle(x+r, y+r, r, selectionColor);
            engine->fillCircle(x+w-r, y+r, r, selectionColor);
            engine->fillCircle(x+w-r, y+h-r, r, selectionColor);
            engine->fillCircle(x+r, y+h-r, r, selectionColor);

            engine->fillRect(x, y+r, w, h-2*r, selectionColor);
            engine->fillRect(x+r, y, w-2*r, h, selectionColor);

        }
    }

    // Draw white fill
    PKColor white = PKColorCreate(255, 255, 255, 255);
    engine->fillRect(x+margin, y+margin, ww, hh, white); 

	// Draw repeat lines

	PKVariant *rl   = this->get(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY);
	bool repeatLeft = PKVALUE_BOOL(rl);
	int offsetRL    = 0;

	if(repeatLeft)
	{
		engine->fillRect(x+margin, y+margin,
						 3*lineWidth, hh, 
						 lineColor);

		engine->drawLine(x+margin+5*lineWidth, y+margin,
						 x+margin+5*lineWidth, y+margin+hh, 
						 lineColor, lineWidth);

		engine->fillCircle(x+margin+7*lineWidth+hh/20, y+margin+hh/2-hh/12, hh/20, lineColor);
		engine->fillCircle(x+margin+7*lineWidth+hh/20, y+margin+hh/2+hh/12, hh/20, lineColor);
	
		offsetRL = 7*lineWidth+hh/20;
	}

	PKVariant *rr    = this->get(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY);
	bool repeatRight = PKVALUE_BOOL(rr);
	int offsetRR     = 0;

	if(repeatRight)
	{
		engine->fillRect(x+margin+ww-3*lineWidth, y+margin,
						 3*lineWidth, hh, 
						 lineColor);

		engine->drawLine(x+margin+ww-5*lineWidth, y+margin,
						 x+margin+ww-5*lineWidth, y+margin+hh, 
						 lineColor, lineWidth);

		engine->fillCircle(x+margin+ww-7*lineWidth-hh/20, y+margin+hh/2-hh/12, hh/20, lineColor);
		engine->fillCircle(x+margin+ww-7*lineWidth-hh/20, y+margin+hh/2+hh/12, hh/20, lineColor);
	
		offsetRR = 7*lineWidth+hh/20;
	}

	// Draw lines

    engine->drawRect(x+margin, y+margin, ww, hh, lineColor, lineWidth);

    int32_t type = PKVALUE_UINT8(this->get(BarViewVectorControl::BARTYPE_UINT8_PROPERTY));

    switch(type)
    {
    case BAR_TYPE_DOUBLE:
        {
            engine->drawLine(x+margin, y+h-margin, x+w-margin, y+margin, lineColor, lineWidth);

            // Draw two chord names

            double maxSize = ww/2 + ww/10;

            if(this->chordNames[0] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[0])) > (maxSize - offsetRL)) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + offsetRL + (maxSize - offsetRL - size)/2;
                int yy = margin + (hh - fontHeight)/6;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[0]);
            }

            if(this->chordNames[1] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[1])) > (maxSize - offsetRR)) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + (ww - maxSize) + (maxSize - offsetRR - size)/2;
                int yy = margin + 5*(hh - fontHeight)/6;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[1]);
            }
        }
        break;
    case BAR_TYPE_TRIPLE1:
        {
            engine->drawLine(x+margin, y+h-margin, x+w-margin, y+margin, lineColor, lineWidth);
            engine->drawLine(x+margin, y+margin, x+margin+ww/2+1, y+margin+hh/2+1, lineColor, lineWidth);

            // Draw three chord names

            double maxSizeTop    = ww/3 + ww/20;
            double maxSizeBottom = ww/2 + ww/10;

            if(this->chordNames[0] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[0])) > (maxSizeTop - offsetRL)) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + hh/30 + offsetRL - (maxSizeTop - offsetRL - size)/2;
                int yy = margin + (hh - fontHeight)/2;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[0]);
            }

            if(this->chordNames[1] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[1])) > maxSizeTop) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + ww/2 - (maxSizeTop - size)/2;
                int yy = margin + (hh - fontHeight)/10;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[1]);
            }

            if(this->chordNames[2] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[2])) > (maxSizeBottom - offsetRR)) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + (ww - maxSizeBottom) + (maxSizeBottom - offsetRR - size)/2;
                int yy = margin + 5*(hh - fontHeight)/6;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[2]);
            }
        }
        break;
    case BAR_TYPE_TRIPLE2:
        {
            engine->drawLine(x+margin, y+h-margin, x+w-margin, y+margin, lineColor, lineWidth);
            engine->drawLine(x+margin+ww/2, y+margin+hh/2, x+w-margin, y+h-margin, lineColor, lineWidth);

            // Draw three chord names

            double maxSizeBottom = ww/3 + ww/20;
            double maxSizeTop    = ww/2 + ww/10;

            if(this->chordNames[0] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[0])) > (maxSizeTop - offsetRL)) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + offsetRL + (maxSizeTop - offsetRL - size)/2;
                int yy = margin + (hh - fontHeight)/6;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[0]);
            }

            if(this->chordNames[1] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[1])) > maxSizeBottom) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + ww/2 - (maxSizeBottom - size)/2;
                int yy = margin + hh - fontHeight - (hh - fontHeight)/20;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[1]);
            }

            if(this->chordNames[2] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[2])) > (maxSizeBottom - offsetRR)) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + 2*ww/3 - offsetRR/3 + (maxSizeBottom - offsetRR - size)/2;
                int yy = margin + (hh - fontHeight)/2;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[2]);
            }
        }
        break;
    case BAR_TYPE_QUAD:
        {
            engine->drawLine(x+margin, y+h-margin, x+w-margin, y+margin, lineColor, lineWidth);
            engine->drawLine(x+margin, y+margin, x+w-margin, y+h-margin, lineColor, lineWidth);
        
            // Draw four chords

            double maxSize = ww/3 + ww/20;

            if(this->chordNames[0] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[0])) > (maxSize - offsetRL)) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + offsetRL + (maxSize - offsetRL - size)/2;
                int yy = margin + (hh - fontHeight)/2;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[0]);
            }

            if(this->chordNames[1] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[1])) > maxSize) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + ww/2 - (maxSize - size)/2 - ww/20;
                int yy = margin + (hh - fontHeight)/10;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[1]);
            }

            if(this->chordNames[2] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[2])) > maxSize) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + ww/2 - (maxSize - size)/2 - ww/20;
                int yy = margin + hh - fontHeight - (hh - fontHeight)/20;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[2]);
            }

            if(this->chordNames[3] != L"")
            {
                int fontHeight = h / 3;
                int size;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[3])) > (maxSize - offsetRR)) && 
                      fontHeight > 4)
                {
                    fontHeight -= 1;
                }

                int xx = margin + 2*ww/3 - offsetRR/3 + (maxSize - offsetRR - size)/2;
                int yy = margin + (hh - fontHeight)/2;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[3]);
            }
        }
        break;
    case BAR_TYPE_SINGLE:
    default:
        {
            // Draw one chord name

            if(this->chordNames[0] != L"")
            {
                int fontHeight = h / 3;
                int size;

				int allowed_w = ww - offsetRL - offsetRR;

                while(((size = engine->getStringWidth(L"Arial", 
                                                      fontHeight, 
                                                      PKV_FONT_STYLE_NORMAL, 
                                                      this->chordNames[0])) > allowed_w) && fontHeight > 5)
                {
                    fontHeight -= 1;
                }

                int xx = margin + offsetRL + (allowed_w - size)/2;
                int yy = margin + (hh - fontHeight)/2;

                engine->drawString(L"Arial", fontHeight, PKV_FONT_STYLE_NORMAL, lineColor, x+xx, y+yy, this->chordNames[0]);
            }
        }
        break;
    }

	if(this->hover)
	{
		// Draw the "X" to delete the bar

        PKColor hoverColor = PKVALUE_COLOR(this->get(BarViewVectorControl::HOVERCOLOR_COLOR_PROPERTY));

		// Draw background

        double r = margin/2;
        engine->fillCircle(x+margin+ww-ww/4, y+margin+hh/4, r, hoverColor);

        engine->fillRect(x+margin+ww-ww/4-r, y+margin-lineWidth, ww/4+r+lineWidth, hh/4+lineWidth, hoverColor);
        engine->fillRect(x+margin+ww-ww/4, y+margin+hh/4-lineWidth, ww/4+lineWidth, r+lineWidth, hoverColor);

		// Draw the "X"

		PKColor white = PKColorCreate(255, 255, 255, 255);

		int fh = hh/4;
		int size = engine->getStringWidth(L"Helvetica", fh, PKV_FONT_STYLE_BOLD, L"X");
        engine->drawString(L"Helvetica", fh, PKV_FONT_STYLE_BOLD, white, x+margin+ww-ww/4+(ww/4-size)/2+r/2, y+margin-hh/20, L"X");
	}
}

void BarViewVectorControl::mouseDown(PKButtonType button,
				                     int x,
				                     int y,
				                     unsigned int mod)
{
	int w = this->getW();
	int h = this->getH();

	double margin = (double)w/20.0;
	double r      = margin/2;

	int ww = w - 2*margin;
	int hh = h - 2*margin;
	
	if(button == PK_BUTTON_LEFT)
    {
		if((x >= (margin + ww - ww/4 - r)) && (x <= (margin + ww)) &&
		   (y <= margin+hh/4+r) && (y >= margin))
		{
			this->x_hit = true;
			PKCursorTools::setCursor(PK_CURSOR_HAND);
		}
		else
		{
            if(x >= margin && x <= (margin + ww) &&
               y >= margin && y <= (margin + hh))
            {
    			this->hit = true;
            }
		}
	}
}

void BarViewVectorControl::mouseUp(PKButtonType button,
				                   int x,
				                   int y,
                                   unsigned int mod)
{
    if(button == PK_BUTTON_LEFT)
    {
		int w = this->getW();
		int h = this->getH();

		double margin = (double)w/20.0;
		double r      = margin/2;

		int ww = w - 2*margin;
		int hh = h - 2*margin;

		if((x >= (margin + ww - ww/4 - r)) && (x <= (margin + ww)) &&
		   (y <= margin+hh/4+r) && (y >= margin))
		{
			if(this->x_hit)
			{
				if(this->getDialog())
				{
					std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
					this->getDialog()->customControlClicked(button, sid, this, "CLOSE");
				}
			}
		}
		else
		{
            if(x >= margin && x <= (margin + ww) &&
               y >= margin && y <= (margin + hh))
            {
			    if(this->hit)
			    {
				    if(this->getDialog())
				    {
						std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));

						if(mod & PK_MOD_CONTROL || mod & PK_MOD_COMMAND)
						{
							this->getDialog()->customControlClicked(button, sid, this, "CTRL");
						}
						else 
						{
							this->getDialog()->customControlClicked(button, sid, this, "");
						}
					}
			    }
            }
		}
    }

	this->x_hit = false;
    this->hit   = false;
}

void BarViewVectorControl::mouseMove(int x,
			                         int y,
			                         unsigned int mod)
{
	int w = this->getW();
	int h = this->getH();

	double margin = (double)w/20.0;
	double r      = margin/2;

	int ww = w - 2*margin;
	int hh = h - 2*margin;
	
	if((x >= (margin + ww - ww/4 - r)) && (x <= (w-margin)) &&
	   (y <= margin+hh/4+r) && (y >= margin))
	{
        // We're over the X area

        if(!this->hover)
        {
            this->hover = true;
            this->invalidate();
        }

        PKCursorTools::setCursor(PK_CURSOR_HAND);
	}
	else
	{
        if((x >= margin) && (x <= (w-margin)) &&
           (y >= margin) && (y <= (h-margin)))
        {
            if(!this->hover)
            {
                this->hover = true;
                this->invalidate();
            }
        }
        else
        {
            if(this->hover)
            {
                this->hover = false;
                this->invalidate();
            }
        }

		PKCursorTools::setCursor(PK_CURSOR_ARROW);
	}
}

void BarViewVectorControl::mouseLeave()
{
	PKCursorTools::setCursor(PK_CURSOR_ARROW);

	this->hit = false;

    if(this->hover)
    {
        this->hover = false;
        this->invalidate();
    }
}


void BarViewVectorControl::mouseDblClick(PKButtonType button,
										 int x,
										 int y,
										 unsigned int mod)
{
	std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
	this->getDialog()->customControlDoubleClicked(button, sid, this, "");
}


void BarViewVectorControl::selfPropertyChanged(PKProperty *prop, PKVariant *oldValue)
{
    if(prop->getName() == BarViewVectorControl::SELECTED_BOOL_PROPERTY)
    {
        this->invalidate();
    }

    if(prop->getName() == BarViewVectorControl::BARTYPE_UINT8_PROPERTY)
    {
        this->invalidate();
    }

	if(prop->getName() == BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY)
    {
        this->invalidate();
    }

	if(prop->getName() == BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY)
    {
        this->invalidate();
    }

	if(prop->getName() == BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY)
    {
        this->invalidate();
    }

	if(prop->getName() == BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY)
    {
        this->invalidate();
    }

	if(prop->getName() == BarViewVectorControl::HEADER_WSTRING_PROPERTY)
    {
        this->invalidate();
    }

	PKVectorControl::selfPropertyChanged(prop, oldValue);
}
