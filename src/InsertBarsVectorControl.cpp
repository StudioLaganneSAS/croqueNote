//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "InsertBarsVectorControl.h"
#include "PKVectorEngine.h"
#include "PKDialog.h"

enum {

    PK_ABVC_MENU_ID_INSERT_BARS  = 3375,
    PK_ABVC_MENU_ID_INSERT_PASTE,
    PK_ABVC_MENU_ID_INSERT_LINE_BREAK,
};

//
// InsertBarsVectorControl
//

InsertBarsVectorControl::InsertBarsVectorControl()
{
    this->hoverPlus  = false;
    this->hoverArrow = false;

    this->downPlus  = false;
    this->downArrow = false;

    // Create popup menu

    this->menu = new PKPopupMenu();
    this->menu->setMenuCallback(this);

    this->menu->insertItem(PK_ABVC_MENU_ID_INSERT_BARS,
                           PK_i18n(L"Insert bars..."));
    this->menu->insertSeparator();
    this->menu->insertItem(PK_ABVC_MENU_ID_INSERT_PASTE,
                           PK_i18n(L"Paste"));
    this->menu->insertSeparator();
    this->menu->insertItem(PK_ABVC_MENU_ID_INSERT_LINE_BREAK,
                           PK_i18n(L"Insert line break"));

    this->menuShown = false;
}

InsertBarsVectorControl::~InsertBarsVectorControl()
{
    this->menu->release();
}

void InsertBarsVectorControl::updateUIStrings()
{
    this->menu->updateItem(PK_ABVC_MENU_ID_INSERT_BARS,
                           PK_i18n(L"Insert bars..."));

    this->menu->updateItem(PK_ABVC_MENU_ID_INSERT_PASTE,
                           PK_i18n(L"Paste"));

    this->menu->updateItem(PK_ABVC_MENU_ID_INSERT_LINE_BREAK,
                           PK_i18n(L"Insert line break"));
}

bool InsertBarsVectorControl::isPopupMenuShown()
{
    return this->menuShown;
}

void InsertBarsVectorControl::drawVector(PKVectorEngine *engine,
									     int32_t x, int32_t y)
{
    int w = this->getW();
    
    double margin = (double)w/20.0;
    double offset = 2*(w-2*margin)/3;
    double r  = (double)w/20.0;
    double rr = 3*(double)w/20.0/2;
    double a_y = 2*margin;

    int h = this->getH()-a_y;

    // Draw background

    PKColor bkgColor = PKColorCreate(120,170,210,255);

	engine->fillCircle(x+rr, y+a_y+rr, rr, bkgColor);
    engine->fillCircle(x+w-rr, y+a_y+rr, rr, bkgColor);
    engine->fillCircle(x+w-rr, y+a_y+h-rr, rr, bkgColor);
    engine->fillCircle(x+rr, y+a_y+h-rr, rr, bkgColor);

	engine->fillTriangle(x+w/2-2.5*margin, y+a_y+1,
		                 x+w/2+2.5*margin, y+a_y+1,
						 x+w/2, y+1,
						 bkgColor);

	engine->fillRect(x, y+a_y+rr, w, h-2*rr, bkgColor);
	engine->fillRect(x+rr, y+a_y, w-2*rr, h, bkgColor);

	// Draw buttons

	PKColor normalColor = PKColorCreate(230,240,245,255);
    PKColor hoverColor  = PKColorCreate(245,255,255,255);
    PKColor downColor   = PKColorCreate(210,220,225,255);
                                           
    PKColor color1 = normalColor;
    
    if(this->downPlus)
    {
        color1 = downColor;
    }
    else if(this->hoverPlus)
    {
        color1 = hoverColor;
    }
    
    PKColor color2 = normalColor;
    
    if(this->downArrow)
    {
        color2 = downColor;
    }
    else if(this->hoverArrow)
    {
        color2 = hoverColor;
    }

    engine->fillCircle(x+margin+r, y+a_y+margin+r, r, color1);
    engine->fillCircle(x+w-r-margin, y+a_y+margin+r, r, color2);
    
    engine->fillCircle(x+w-r-margin, y+a_y+h-r-margin, r, color2);
    engine->fillCircle(x+margin+r, y+a_y+h-r-margin, r, color1);
    
    engine->fillRect(x+margin, y+a_y+margin+r, 2*r, h-2*r-2*margin, color1);
    engine->fillRect(x+margin+r, y+a_y+margin, offset-r/2, h-2*margin, color1);    

    engine->fillRect(x+margin+r+offset+r/2, y+a_y+margin, w-2*margin-offset-2*r, h-2*margin, color2);    
    engine->fillRect(x+margin+w-2*margin-r, y+a_y+margin+r, r, h-2*r-2*margin, color2);
    
	// Symbols

    engine->fillCircle(x+margin+offset/2, y+a_y+margin+(h-2*margin)/2, offset/3, bkgColor);
    engine->fillCircle(x+margin+offset/2, y+a_y+margin+(h-2*margin)/2, offset/3-r, color1);

    engine->fillRect(x+margin+offset/2-r/2, y+a_y+margin+(h-2*margin)/3, r, (h-2*margin)/3, bkgColor);
    engine->fillRect(x+margin+r/2+offset/3-r/2, y+a_y+margin+(h-2*margin)/2-r/2, offset/3, r, bkgColor);
    
    engine->fillTriangle(x+margin+offset+2*r+r/2, 
                         y+a_y+margin+(h-2*margin)/2-r/3-r/2, 
                         x+w-margin-r, 
                         y+a_y+margin+(h-2*margin)/2-r/3-r/2, 
                         x+margin+offset+2*r+r/2+((x+w-margin-r)-(x+margin+offset+2*r+r/2))/2, 
                         y+a_y+margin+(h-2*margin)/2+r, 
                         bkgColor);
}

void InsertBarsVectorControl::mouseDown(PKButtonType button,
										 int x,
										 int y,
										 unsigned int mod)
{
    if(button == PK_BUTTON_LEFT)
    {
        int w = this->getW();    
        double margin = (double)w/20.0;
        double offset = 2*(w-2*margin)/3;

        if(x <= 2*margin+offset)
        {
            this->downPlus = true;
            this->invalidate();
        }
        else
        {
            this->downArrow = true;
            this->invalidate();
        }
    }
}

void InsertBarsVectorControl::mouseUp(PKButtonType button,
				                   int x,
				                   int y,
                                   unsigned int mod)
{
    if(button == PK_BUTTON_LEFT)
    {
        int w = this->getW();    
        double margin = (double)w/20.0;
        double offset = 2*(w-2*margin)/3;

        if(x <= 2*margin+offset)
        {
            if(this->downPlus)
            {
                // It's a hit

                if(this->getDialog())
                {
                    std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
                    this->getDialog()->customControlClicked(button, sid, this, "PLUS");
                }

                this->downPlus  = false;
                this->downArrow = false;

                this->invalidate();
                return;
            }
        }
        else
        {
            if(this->downArrow)
            {
                // It's a hit, show the popup menu

                PKWindowHandle window = NULL;
                if(this->controlRoot)
                {
                    window = controlRoot->getWindowHandle();
                }

                this->menuShown = true;
                this->menu->popup(window);

                this->downPlus  = false;
                this->downArrow = false;

				// No need to invalidate here
				// it will trigger an animation

                return;
            }
        }

        this->downPlus  = false;
        this->downArrow = false;
        this->invalidate();
    }
}

void InsertBarsVectorControl::mouseDblClick(PKButtonType button,
						                 int x,
					                     int y,
					                     unsigned int mod)
{
    if(button == PK_BUTTON_LEFT)
    {
        int w = this->getW();    
        double margin = (double)w/20.0;
        double offset = 2*(w-2*margin)/3;

        if(x <= 2*margin+offset)
        {
            if(this->downPlus)
            {
                // It's a hit

                if(this->getDialog())
                {
                    std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
                    this->getDialog()->customControlClicked(button, sid, this, "PLUS");
                }

                this->downPlus  = false;
                this->downArrow = false;

                this->invalidate();
                return;
            }
        }
        else
        {
            if(this->downArrow)
            {
                // It's a hit, show the popup menu
                // TODO

                this->downPlus  = false;
                this->downArrow = false;

                this->invalidate();
                return;
            }
        }
    }

    this->downPlus  = false;
    this->downArrow = false;
    this->invalidate();
}

void InsertBarsVectorControl::mouseMove(int x,
			                         int y,
			                         unsigned int mod)
{
    int w = this->getW();    
    double margin = (double)w/20.0;
    double offset = 2*(w-2*margin)/3;

    if(x <= 2*margin+offset)
    { 
        if(this->hoverPlus == false)
        {
            this->hoverPlus = true;
            this->hoverArrow = false;
            this->invalidate();
        }
    }
    else
    {
        if(this->hoverArrow == false)
        {
            this->hoverArrow = true;
            this->hoverPlus = false;
            this->invalidate();
        }
    }
}

void InsertBarsVectorControl::mouseLeave()
{
    this->hoverPlus  = false;
    this->hoverArrow = false;
    this->invalidate();
}

// From PKPopupMenuCallback

void InsertBarsVectorControl::menuCancelled()
{
    this->menuShown = false;
}

void InsertBarsVectorControl::menuCallback(unsigned int id)
{
	if(id == PK_ABVC_MENU_ID_INSERT_BARS)
	{
        if(this->getDialog())
        {
            std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
            this->getDialog()->customControlClicked(PK_BUTTON_LEFT, sid, this, "INSERT_BARS");
        }
	}

	if(id == PK_ABVC_MENU_ID_INSERT_BARS)
	{
        if(this->getDialog())
        {
            std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
            this->getDialog()->customControlClicked(PK_BUTTON_LEFT, sid, this, "INSERT_PASTE");
        }
	}

    if(id == PK_ABVC_MENU_ID_INSERT_LINE_BREAK)
	{
        if(this->getDialog())
        {
            std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
            this->getDialog()->customControlClicked(PK_BUTTON_LEFT, sid, this, "INSERT_LINE_BREAK");
        }
	}

	this->menuShown = false;
}

