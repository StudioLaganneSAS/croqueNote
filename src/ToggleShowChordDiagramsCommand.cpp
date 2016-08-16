//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ToggleShowChordDiagramsCommand.h"
#include "ChordableWindow.h"

//
// ShowTempoCommand
//

ToggleShowChordDiagramsCommand::ToggleShowChordDiagramsCommand(ChordableWindow *window, bool toggle)
{
	this->window = window;
	this->window->retain();

	this->toggle = toggle;

	if(toggle)
	{
		this->setDisplayName(PK_i18n(L"Show Chord Diagrams"));
	}
	else
	{
		this->setDisplayName(PK_i18n(L"Hide Chord Diagrams"));
	}
}

ToggleShowChordDiagramsCommand::~ToggleShowChordDiagramsCommand()
{
	this->window->release();
}

void ToggleShowChordDiagramsCommand::doCommand()
{
	if(this->window)
	{
        this->window->setControlHidden("ID_CHORDS_SPACER", !toggle);
        this->window->setControlTreeHidden("ID_CHORDS_GRID", !toggle);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ToggleShowChordDiagramsCommand::undoCommand()
{
	if(this->window)
	{
		this->window->setCheckBoxChecked("ID_INSPECTOR_CHORDS_CHECKBOX", !toggle);

        this->window->setControlHidden("ID_CHORDS_SPACER", toggle);
        this->window->setControlTreeHidden("ID_CHORDS_GRID", toggle);

        this->window->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");

		this->window->setNeedsSave();
	}
}

void ToggleShowChordDiagramsCommand::redoCommand()
{
	this->window->setCheckBoxChecked("ID_INSPECTOR_CHORDS_CHECKBOX", toggle);
	this->doCommand();
}
