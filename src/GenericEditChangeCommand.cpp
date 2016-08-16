//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "GenericEditChangeCommand.h"
#include "ChordableWindow.h"

//
// GenericEditChangeCommand
//

GenericEditChangeCommand::GenericEditChangeCommand(ChordableWindow *window, 
												   std::string editID,
												   std::wstring name,
												   std::wstring oldValue,
												   std::wstring newValue)
{
	this->window = window;
	this->window->retain();

	this->id = editID;
	this->name = name;
	this->oldValue = oldValue;
	this->newValue = newValue;

	this->setDisplayName(name);
}

GenericEditChangeCommand::~GenericEditChangeCommand()
{
	this->window->release();
}

void GenericEditChangeCommand::doCommand()
{
	// Nothing to do
}

void GenericEditChangeCommand::undoCommand()
{
	if(this->window)
	{
		this->window->setEditText(this->id, this->oldValue);
		this->window->resetEditChanges(this->id); // So the change we made isn't recorded when commitChanges is called
	}
}

void GenericEditChangeCommand::redoCommand()
{
	if(this->window)
	{
		this->window->setEditText(this->id, this->newValue);
		this->window->resetEditChanges(this->id); // So the change we made isn't recorded when commitChanges is called
	}
}
