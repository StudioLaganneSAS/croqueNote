//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef GENERIC_EDIT_CHANGE_COMMAND_H
#define GENERIC_EDIT_CHANGE_COMMAND_H

#include "PKUndoableCommand.h"

//
// GenericEditChangeCommand
//

class ChordableWindow;

class GenericEditChangeCommand : public PKUndoableCommand
{
public:
	GenericEditChangeCommand(ChordableWindow *window, 
							 std::string editID,
							 std::wstring name,
							 std::wstring oldValue,
							 std::wstring newValue);
	~GenericEditChangeCommand();

	void doCommand();
	void undoCommand();
	void redoCommand();

private:
	ChordableWindow *window;
	std::string id;
	std::wstring name;
	std::wstring oldValue;
	std::wstring newValue;
};

#endif // GENERIC_EDIT_CHANGE_COMMAND_H
