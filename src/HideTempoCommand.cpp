//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "HideTempoCommand.h"
#include "ChordableWindow.h"

//
// HideTempoCommand
//

HideTempoCommand::HideTempoCommand(ChordableWindow *window)
{
	this->window = window;
	this->window->retain();

	this->setDisplayName(PK_i18n(L"Hide Tempo"));
}

HideTempoCommand::~HideTempoCommand()
{
	this->window->release();
}

void HideTempoCommand::doCommand()
{
	if(this->window)
	{
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

void HideTempoCommand::undoCommand()
{
	if(this->window)
	{
		this->window->setCheckBoxChecked("ID_INSPECTOR_TEMPO_CHECKBOX", true);

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

void HideTempoCommand::redoCommand()
{
	this->window->setCheckBoxChecked("ID_INSPECTOR_TEMPO_CHECKBOX", false);
	this->doCommand();
}
