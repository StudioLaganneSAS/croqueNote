//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef SHOW_CAPO_COMMAND_H
#define SHOW_CAPO_COMMAND_H

#include "PKUndoableCommand.h"

//
// ShowCapoCommand
//

class ChordableWindow;

class ShowCapoCommand : public PKUndoableCommand
{
public:
	ShowCapoCommand(ChordableWindow *window);
	~ShowCapoCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
};

#endif // SHOW_CAPO_COMMAND_H
