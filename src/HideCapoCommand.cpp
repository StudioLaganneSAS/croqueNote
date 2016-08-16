//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "HideCapoCommand.h"
#include "ChordableWindow.h"

//
// HideCapoCommand
//

HideCapoCommand::HideCapoCommand(ChordableWindow *window)
{
	this->window = window;
	this->window->retain();

	this->setDisplayName(PK_i18n(L"Hide Capo"));
}

HideCapoCommand::~HideCapoCommand()
{
	this->window->release();
}

void HideCapoCommand::doCommand()
{
	if(this->window)
	{
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

void HideCapoCommand::undoCommand()
{
	if(this->window)
	{
		this->window->setCheckBoxChecked("ID_INSPECTOR_CAPO_CHECKBOX", true);

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

void HideCapoCommand::redoCommand()
{
	this->window->setCheckBoxChecked("ID_INSPECTOR_CAPO_CHECKBOX", false);
	this->doCommand();
}
