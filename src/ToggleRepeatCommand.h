//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef TOGGLE_REPEAT_COMMAND_H
#define TOGGLE_REPEAT_COMMAND_H

#include "PKUndoableCommand.h"

//
// ShowTempoCommand
//

class ChordableWindow;
class BarViewVectorControl;

class ToggleRepeatCommand : public PKUndoableCommand
{
public:
	ToggleRepeatCommand(ChordableWindow *window, 
				        BarViewVectorControl *bar,
						bool left,
				        bool toggle);

	~ToggleRepeatCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	BarViewVectorControl *bar;
	bool toggled;
	bool left;
	bool removedOther;
};

#endif // TOGGLE_REPEAT_COMMAND_H
