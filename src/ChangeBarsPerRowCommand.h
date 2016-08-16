//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHANGE_BARS_PER_ROW_COMMAND_H
#define CHANGE_BARS_PER_ROW_COMMAND_H

#include "PKUndoableCommand.h"

//
// ChangeBarsPerRowCommand
//

class ChordableWindow;

class ChangeBarsPerRowCommand : public PKUndoableCommand
{
public:
	ChangeBarsPerRowCommand(ChordableWindow *window, uint32_t newSelection, uint32_t oldSelection);
	ChangeBarsPerRowCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	uint32_t newSelection;
	uint32_t oldSelection;
};

#endif // CHANGE_BARS_PER_ROW_COMMAND_H
