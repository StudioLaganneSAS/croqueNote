//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef HIDE_CAPO_COMMAND_H
#define HIDE_CAPO_COMMAND_H

#include "PKUndoableCommand.h"

//
// HideCapoCommand
//

class ChordableWindow;

class HideCapoCommand : public PKUndoableCommand
{
public:
	HideCapoCommand(ChordableWindow *window);
	~HideCapoCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
};

#endif // HIDE_CAPO_COMMAND_H
