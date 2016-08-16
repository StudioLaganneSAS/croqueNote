//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef TOGGLE_TUNING_COMMAND_H
#define TOGGLE_TUNING_COMMAND_H

#include "PKUndoableCommand.h"

//
// ShowTempoCommand
//

class ChordableWindow;

class ToggleTuningCommand : public PKUndoableCommand
{
public:
	ToggleTuningCommand(ChordableWindow *window, bool toggle);
	~ToggleTuningCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	bool toggle;
};

#endif // TOGGLE_TUNING_COMMAND_H
