//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHANGE_BAR_TYPE_COMMAND_H
#define CHANGE_BAR_TYPE_COMMAND_H

#include "PKUndoableCommand.h"
#include "BarViewVectorControl.h"

//
// ChangeBarTypeCommand
//

class ChordableWindow;

class ChangeBarTypeCommand : public PKUndoableCommand
{
public:
	ChangeBarTypeCommand(ChordableWindow *window, 
 					 	 BarViewVectorControl *bar,
						 int32_t newSelection, 
						 int32_t oldSelection);

	~ChangeBarTypeCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	BarViewVectorControl *bar;
	int32_t newSelection;
	int32_t oldSelection;
};

#endif // CHANGE_BAR_TYPE_COMMAND_H
