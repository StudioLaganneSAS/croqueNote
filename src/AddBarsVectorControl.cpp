//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "AddBarsVectorControl.h"
#include "PKVectorEngine.h"
#include "PKDialog.h"

enum {

    PK_ABVC_MENU_ID_ADD_BARS  = 3345,
    PK_ABVC_MENU_ID_LINE_BREAK,
};

//
// AddBarsVectorControl
//

AddBarsVectorControl::AddBarsVectorControl()
{
    this->hoverPlus  = false;
    this->hoverArrow = false;

    this->downPlus  = false;
    this->downArrow = false;

    // Create popup menu

    this->menu = new PKPopupMenu();
    this->menu->setMenuCallback(this);

    this->menu->insertItem(PK_ABVC_MENU_ID_ADD_BARS,
                           PK_i18n(L"Add bars..."));
    this->menu->insertSeparator();
    this->menu->insertItem(PK_ABVC_MENU_ID_LINE_BREAK,
                           PK_i18n(L"Insert line break"));

    this->menuShown = false;
}

AddBarsVectorControl::~AddBarsVectorControl()
{
    this->menu->release();
}

void AddBarsVectorControl::updateUIStrings()
{
    this->menu->updateItem(PK_ABVC_MENU_ID_ADD_BARS,
                           PK_i18n(L"Add bars..."));

    this->menu->updateItem(PK_ABVC_MENU_ID_LINE_BREAK,
                           PK_i18n(L"Insert line break"));
}

bool AddBarsVectorControl::isPopupMenuShown()
{
    return this->menuShown;
}

void AddBarsVectorControl::drawVector(PKVectorEngine *engine,
									  int32_t x, int32_t y)
{
    int w = this->getW();
    int h = this->getH();
    
    double margin = (double)w/20.0;
    double offset = 2*(w-2*margin)/3;

    PKColor normalColor = PKColorCreate(230,230,230,255);
    PKColor hoverColor  = PKColorCreate(200,200,200,255);
    PKColor downColor   = PKColorCreate(170,170,170,255);
                                       
    double r = (double)w/20.0;
    
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

    engine->fillCircle(x+margin+r, y+margin+r, r, color1);
    engine->fillCircle(x+w-r-margin, y+margin+r, r, color2);
    
    engine->fillCircle(x+w-r-margin, y+h-r-margin, r, color2);
    engine->fillCircle(x+margin+r, y+h-r-margin, r, color1);
    
    engine->fillRect(x+margin, y+margin+r, 2*r, h-2*r-2*margin, color1);
    engine->fillRect(x+margin+r, y+margin, offset-r/4, h-2*margin, color1);    

    engine->fillRect(x+margin+r+offset+r/2, y+margin, w-2*margin-offset-2*r, h-2*margin, color2);    
    engine->fillRect(x+margin+w-2*margin-r, y+margin+r, r, h-2*r-2*margin, color2);
    
    PKColor white = PKColorCreate(255,255,255,255);

    engine->fillCircle(x+margin+offset/2+r/2, y+margin+(h-2*margin)/2, offset/3, white);
    engine->fillCircle(x+margin+offset/2+r/2, y+margin+(h-2*margin)/2, offset/3-r/2, color1);

    engine->fillRect(x+margin+offset/2, y+margin+(h-2*margin)/3, r, (h-2*margin)/3, white);
    engine->fillRect(x+margin+r/2+offset/3, y+margin+(h-2*margin)/2-r/2, offset/3, r, white);
    
    engine->fillTriangle(x+margin+offset+2*r+r/2, 
                         y+margin+(h-2*margin)/2-r/3, 
                         x+w-margin-r, 
                         y+margin+(h-2*margin)/2-r/3, 
                         x+margin+offset+2*r+r/2+((x+w-margin-r)-(x+margin+offset+2*r+r/2))/2, 
                         y+margin+(h-2*margin)/2+r, 
                         white);
}

void AddBarsVectorControl::mouseDown(PKButtonType button,
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

void AddBarsVectorControl::mouseUp(PKButtonType button,
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

void AddBarsVectorControl::mouseDblClick(PKButtonType button,
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

void AddBarsVectorControl::mouseMove(int x,
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

void AddBarsVectorControl::mouseLeave()
{
    this->hoverPlus  = false;
    this->hoverArrow = false;
    this->invalidate();
}

// From PKPopupMenuCallback

void AddBarsVectorControl::menuCancelled()
{
    this->menuShown = false;
}

void AddBarsVectorControl::menuCallback(unsigned int id)
{
	if(id == PK_ABVC_MENU_ID_ADD_BARS)
	{
        if(this->getDialog())
        {
            std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
            this->getDialog()->customControlClicked(PK_BUTTON_LEFT, sid, this, "ADD_BARS");
        }
	}

	if(id == PK_ABVC_MENU_ID_LINE_BREAK)
	{
        if(this->getDialog())
        {
            std::string sid = PKVALUE_STRING(this->get(PKControl::ID_STRING_PROPERTY));
            this->getDialog()->customControlClicked(PK_BUTTON_LEFT, sid, this, "LINE_BREAK");
        }
	}

	this->menuShown = false;
}

