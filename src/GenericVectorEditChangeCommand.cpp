//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "GenericVectorEditChangeCommand.h"
#include "ChordableWindow.h"

//
// GenericVectorEditChangeCommand
//

GenericVectorEditChangeCommand::GenericVectorEditChangeCommand(ChordableWindow *window, 
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

GenericVectorEditChangeCommand::~GenericVectorEditChangeCommand()
{
	this->window->release();
}

void GenericVectorEditChangeCommand::doCommand()
{
	// Nothing to do
}

void GenericVectorEditChangeCommand::undoCommand()
{
	if(this->window)
	{
        this->window->setEditableLabelText(this->id, this->oldValue);
		this->window->resetEditableLabelChanges(this->id); // So the change we made isn't recorded when commitChanges is called
	}
}

void GenericVectorEditChangeCommand::redoCommand()
{
	if(this->window)
	{
		this->window->setEditableLabelText(this->id, this->newValue);
		this->window->resetEditableLabelChanges(this->id); // So the change we made isn't recorded when commitChanges is called
	}
}
