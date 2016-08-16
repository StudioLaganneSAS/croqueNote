//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ShowCapoCommand.h"
#include "ChordableWindow.h"

//
// ShowCapoCommand
//

ShowCapoCommand::ShowCapoCommand(ChordableWindow *window)
{
	this->window = window;
	this->window->retain();

	this->setDisplayName(PK_i18n(L"Show Capo"));
}

ShowCapoCommand::~ShowCapoCommand()
{
	this->window->release();
}

void ShowCapoCommand::doCommand()
{
	if(this->window)
	{
        this->window->setControlEnabled("ID_INSPECTOR_CAPO_EDIT", true);
        this->window->setControlEnabled("ID_CAPO_ARROWS", true);

        this->window->setControlHidden("ID_CAPO_LABEL",  false);
        this->window->setControlHidden("ID_CAPO_EDIT",   false);
        this->window->setControlHidden("ID_CAPO_SPACER", false);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ShowCapoCommand::undoCommand()
{
	if(this->window)
	{
		this->window->setCheckBoxChecked("ID_INSPECTOR_CAPO_CHECKBOX", false);

		this->window->setControlEnabled("ID_INSPECTOR_CAPO_EDIT", false);
        this->window->setControlEnabled("ID_CAPO_ARROWS", false);

        this->window->setControlHidden("ID_CAPO_LABEL",  true);
        this->window->setControlHidden("ID_CAPO_EDIT",   true);
        this->window->setControlHidden("ID_CAPO_SPACER", true);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ShowCapoCommand::redoCommand()
{
	this->window->setCheckBoxChecked("ID_INSPECTOR_CAPO_CHECKBOX", true);
	this->doCommand();
}
