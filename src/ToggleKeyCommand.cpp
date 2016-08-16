//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ToggleKeyCommand.h"
#include "ChordableWindow.h"

//
// ShowTempoCommand
//

ToggleKeyCommand::ToggleKeyCommand(ChordableWindow *window, bool toggle)
{
	this->window = window;
	this->window->retain();
	this->toggle = toggle;

	if(toggle)
	{
		this->setDisplayName(PK_i18n(L"Show Key"));
	}
	else
	{
		this->setDisplayName(PK_i18n(L"Hide Key"));
	}
}

ToggleKeyCommand::~ToggleKeyCommand()
{
	this->window->release();
}

void ToggleKeyCommand::doCommand()
{
	if(this->window)
	{
        this->window->setControlEnabled("ID_INSPECTOR_KEY_COMBO", toggle);

        this->window->setControlHidden("ID_KEY_IMAGE",  !toggle);
        this->window->setControlHidden("ID_KEY_EDIT",   !toggle);
        this->window->setControlHidden("ID_KEY_SPACER", !toggle);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ToggleKeyCommand::undoCommand()
{
	if(this->window)
	{
		this->window->setCheckBoxChecked("ID_INSPECTOR_KEY_CHECKBOX", !toggle);
        this->window->setControlEnabled("ID_INSPECTOR_KEY_COMBO", !toggle);

        this->window->setControlHidden("ID_KEY_IMAGE",  toggle);
        this->window->setControlHidden("ID_KEY_EDIT",   toggle);
        this->window->setControlHidden("ID_KEY_SPACER", toggle);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ToggleKeyCommand::redoCommand()
{
	this->window->setCheckBoxChecked("ID_INSPECTOR_KEY_CHECKBOX", toggle);
	this->doCommand();
}
