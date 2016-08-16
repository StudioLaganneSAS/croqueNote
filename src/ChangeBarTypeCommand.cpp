//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ChangeBarTypeCommand.h"
#include "ChordableWindow.h"

//
// ChangeBarTypeCommand
//

ChangeBarTypeCommand::ChangeBarTypeCommand(ChordableWindow *window, 
										   BarViewVectorControl *bar,
										   int32_t newSelection, 
										   int32_t oldSelection)
{
	this->window = NULL;
	this->bar    = NULL;

	if(window == NULL || bar == NULL)
	{
		return;
	}

	this->window = window;
	this->window->retain();

	this->bar = bar;
	this->bar->retain();

	this->newSelection = newSelection;
	this->oldSelection = oldSelection;

	this->setDisplayName(PK_i18n(L"Change Bar Type"));
}

ChangeBarTypeCommand::~ChangeBarTypeCommand()
{
	if(this->window != NULL)
	{
		this->window->release();
	}

	if(this->bar != NULL)
	{
		this->bar->release();
	}
}

void ChangeBarTypeCommand::doCommand()
{
	if(this->window)
	{
        // Update the selected bar

        if(this->bar)
        {
			PKVariantUInt8 type((uint8_t)this->newSelection);
            this->bar->set(BarViewVectorControl::BARTYPE_UINT8_PROPERTY, &type);
        }

        // Update the bar panel UI

        this->window->updateBarProperties(this->bar, false);
	}
}

void ChangeBarTypeCommand::undoCommand()
{
	if(this->window)
	{
		BarViewVectorControl *selectedBar = this->window->getSelectedBar();

		PKVariantUInt8 type((uint8_t)this->oldSelection);
        this->bar->set(BarViewVectorControl::BARTYPE_UINT8_PROPERTY, &type);

		if(selectedBar == this->bar)
		{
			this->window->setSelectorControlSelection("ID_BAR_TYPE_SELECTOR", this->oldSelection);
		}

        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");
	}
}

void ChangeBarTypeCommand::redoCommand()
{
	if(this->window)
	{
		BarViewVectorControl *selectedBar = this->window->getSelectedBar();

		PKVariantUInt8 type((uint8_t)this->newSelection);
        this->bar->set(BarViewVectorControl::BARTYPE_UINT8_PROPERTY, &type);

		if(selectedBar == this->bar)
		{
			this->window->setSelectorControlSelection("ID_BAR_TYPE_SELECTOR", this->newSelection);
		}

        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");
	}
}
