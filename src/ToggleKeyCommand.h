//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef TOGGLE_KEY_COMMAND_H
#define TOGGLE_KEY_COMMAND_H

#include "PKUndoableCommand.h"

//
// ShowTempoCommand
//

class ChordableWindow;

class ToggleKeyCommand : public PKUndoableCommand
{
public:
	ToggleKeyCommand(ChordableWindow *window, bool toggle);
	~ToggleKeyCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	bool toggle;
};

#endif // TOGGLE_KEY_COMMAND_H
