//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ShowTempoCommand.h"
#include "ChordableWindow.h"

//
// ShowTempoCommand
//

ShowTempoCommand::ShowTempoCommand(ChordableWindow *window)
{
	this->window = window;
	this->window->retain();

	this->setDisplayName(PK_i18n(L"Show Tempo"));
}

ShowTempoCommand::~ShowTempoCommand()
{
	this->window->release();
}

void ShowTempoCommand::doCommand()
{
	if(this->window)
	{
        this->window->setControlEnabled("ID_INSPECTOR_TEMPO_EDIT", true);
        this->window->setControlEnabled("ID_TEMPO_ARROWS", true);

        this->window->setControlHidden("ID_TEMPO_IMAGE",  false);
        this->window->setControlHidden("ID_TEMPO_EDIT",   false);
        this->window->setControlHidden("ID_TEMPO_SPACER", false);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ShowTempoCommand::undoCommand()
{
	if(this->window)
	{
		this->window->setCheckBoxChecked("ID_INSPECTOR_TEMPO_CHECKBOX", false);

		this->window->setControlEnabled("ID_INSPECTOR_TEMPO_EDIT", false);
        this->window->setControlEnabled("ID_TEMPO_ARROWS", false);

        this->window->setControlHidden("ID_TEMPO_IMAGE",  true);
        this->window->setControlHidden("ID_TEMPO_EDIT",   true);
        this->window->setControlHidden("ID_TEMPO_SPACER", true);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ShowTempoCommand::redoCommand()
{
	this->window->setCheckBoxChecked("ID_INSPECTOR_TEMPO_CHECKBOX", true);
	this->doCommand();
}
