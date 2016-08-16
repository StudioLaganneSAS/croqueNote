//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef BAR_HEADER_CHANGE_COMMAND_H
#define BAR_HEADER_CHANGE_COMMAND_H

#include "PKUndoableCommand.h"
#include "BarViewVectorControl.h"

//
// BarHeaderChangeCommand
//

class ChordableWindow;

class BarHeaderChangeCommand : public PKUndoableCommand
{
public:
	BarHeaderChangeCommand(ChordableWindow *window, 
 					 	   BarViewVectorControl *bar,
						   std::wstring oldValue, 
						   std::wstring newValue);

	~BarHeaderChangeCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	BarViewVectorControl *bar;
	std::wstring newValue;
	std::wstring oldValue;
};

#endif // BAR_HEADER_CHANGE_COMMAND_H
