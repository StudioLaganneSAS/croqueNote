//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ToggleTuningCommand.h"
#include "ChordableWindow.h"

//
// ShowTempoCommand
//

ToggleTuningCommand::ToggleTuningCommand(ChordableWindow *window, bool toggle)
{
	this->window = window;
	this->window->retain();
	this->toggle = toggle;

	if(toggle)
	{
		this->setDisplayName(PK_i18n(L"Show Tuning"));
	}
	else
	{
		this->setDisplayName(PK_i18n(L"Hide Tuning"));
	}
}

ToggleTuningCommand::~ToggleTuningCommand()
{
	this->window->release();
}

void ToggleTuningCommand::doCommand()
{
	if(this->window)
	{
        this->window->setControlHidden("ID_TUNING_IMAGE",   !toggle);
        this->window->setControlHidden("ID_TUNING_EDIT",    !toggle);
        this->window->setControlHidden("ID_TUNING_SUBEDIT", !toggle);
        this->window->setControlHidden("ID_TUNING_SPACER",  !toggle);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ToggleTuningCommand::undoCommand()
{
	if(this->window)
	{
		this->window->setCheckBoxChecked("ID_INSPECTOR_TUNING_CHECKBOX", !toggle);

		this->window->setControlHidden("ID_TUNING_IMAGE",   toggle);
        this->window->setControlHidden("ID_TUNING_EDIT",    toggle);
        this->window->setControlHidden("ID_TUNING_SUBEDIT", toggle);
        this->window->setControlHidden("ID_TUNING_SPACER",  toggle);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ToggleTuningCommand::redoCommand()
{
	this->window->setCheckBoxChecked("ID_INSPECTOR_TUNING_CHECKBOX", toggle);
	this->doCommand();
}
