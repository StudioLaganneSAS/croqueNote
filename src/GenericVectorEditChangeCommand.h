//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef GENERIC_VECTOR_EDIT_CHANGE_COMMAND_H
#define GENERIC_VECTOR_EDIT_CHANGE_COMMAND_H

#include "PKUndoableCommand.h"

//
// GenericVectorEditChangeCommand
//

class ChordableWindow;

class GenericVectorEditChangeCommand : public PKUndoableCommand
{
public:
	GenericVectorEditChangeCommand(ChordableWindow *window, 
						           std::string editID,
						           std::wstring name,
						           std::wstring oldValue,
						           std::wstring newValue);
	~GenericVectorEditChangeCommand();

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

#endif // GENERIC_VECTOR_EDIT_CHANGE_COMMAND_H
