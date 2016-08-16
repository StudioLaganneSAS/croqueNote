//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef BAR_SECTION_NUMBER_CHANGE_COMMAND_H
#define BAR_SECTION_NUMBER_CHANGE_COMMAND_H

#include "PKUndoableCommand.h"
#include "BarViewVectorControl.h"

//
// BarSectionNumberChangeCommand
//

class ChordableWindow;

class BarSectionNumberChangeCommand : public PKUndoableCommand
{
public:
	BarSectionNumberChangeCommand(ChordableWindow *window, 
 					 			  BarViewVectorControl *bar,
								  std::wstring oldValue, 
								  std::wstring newValue);

	~BarSectionNumberChangeCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	BarViewVectorControl *bar;
	std::wstring newValue;
	std::wstring oldValue;
};

#endif // BAR_SECTION_NUMBER_CHANGE_COMMAND_H
