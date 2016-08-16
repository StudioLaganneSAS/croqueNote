//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef TOGGLE_SECTION_MARKER_COMMAND_H
#define TOGGLE_SECTION_MARKER_COMMAND_H

#include "PKUndoableCommand.h"

//
// ShowTempoCommand
//

class ChordableWindow;
class BarViewVectorControl;

class ToggleSectionMarkerCommand : public PKUndoableCommand
{
public:
	ToggleSectionMarkerCommand(ChordableWindow *window, 
							   BarViewVectorControl *bar,
							   bool toggle);
	~ToggleSectionMarkerCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	BarViewVectorControl *bar;
	bool toggle;
};

#endif // TOGGLE_SECTION_MARKER_COMMAND_H
