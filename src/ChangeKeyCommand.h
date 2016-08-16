//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHANGE_KEY_COMMAND_H
#define CHANGE_KEY_COMMAND_H

#include "PKUndoableCommand.h"

//
// ShowTempoCommand
//

class ChordableWindow;

class ChangeKeyCommand : public PKUndoableCommand
{
public:
	ChangeKeyCommand(ChordableWindow *window, int32_t newSelection, int32_t oldSelection);
	~ChangeKeyCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	int32_t newSelection;
	int32_t oldSelection;
};

#endif // CHANGE_KEY_COMMAND_H
