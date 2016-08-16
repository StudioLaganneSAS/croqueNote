//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef ChordableVectorControlRoot_H
#define ChordableVectorControlRoot_H

#include "PKVectorControlRoot.h"
#include "PKSafeEvents.h"
#include "InsertBarsVectorControl.h"

class BarViewVectorControl;
class PKGridLayout;
class ChordableWindow;

//
// ChordableVectorControlRoot
//

class ChordableVectorControlRoot : public PKVectorControlRoot
{
public:

    ChordableVectorControlRoot();
    ~ChordableVectorControlRoot();

    void setWindow(ChordableWindow *window);

	// Export Utils

	void exportToJPEGFile(std::wstring file, float quality /* 0-1 */);
	void exportToPNGFile(std::wstring file);
	void exportToPDFFile(std::wstring file);
		
	// PKSafeEvents

	void processSafeEvent(std::string  eventName,
						  void        *payload);

    // Input events, overriden for special behavior

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

protected:

	virtual void drawVectorInternal(PKVectorEngine *engine);

protected:

    BarViewVectorControl *moving_bar;
    int mouse_x_original;
    int mouse_y_original;
    int bar_x_original;
    int bar_y_original;

    int min_x_move_bar;
    int min_y_move_bar;
    int max_x_move_bar;
    int max_y_move_bar;

    int original_bar_col;
    int original_bar_row;
    int current_bar_col;
    int current_bar_row;

    PKGridLayout *grid;
    ChordableWindow *window;

	InsertBarsVectorControl *insertBars;
    bool eventSent;

    int i_x;
    int i_y;

    bool showMarker;
    double  x_marker;
    double  y_marker;
    double  w_marker;
    double  h_marker;
};

#endif // ChordableVectorControlRoot_H
