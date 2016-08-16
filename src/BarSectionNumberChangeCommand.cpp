//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "BarSectionNumberChangeCommand.h"
#include "ChordableWindow.h"
#include "PKStr.h"

//
// BarHeaderChangeCommand
//

BarSectionNumberChangeCommand::BarSectionNumberChangeCommand(ChordableWindow *window, 
															 BarViewVectorControl *bar,
															 std::wstring oldValue, 
															 std::wstring newValue)
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

	this->newValue = newValue;
	this->oldValue = oldValue;

	this->setDisplayName(PK_i18n(L"Change Bar Section Number"));
}

BarSectionNumberChangeCommand::~BarSectionNumberChangeCommand()
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

void BarSectionNumberChangeCommand::doCommand()
{
	// Nothing to do
}

void BarSectionNumberChangeCommand::undoCommand()
{
	if(this->window)
	{
		if(this->bar == this->window->getSelectedBar())
		{
			this->window->setEditText("ID_BAR_SECTION_NUMBER_EDIT", oldValue);
			this->window->resetEditChanges("ID_BAR_SECTION_NUMBER_EDIT"); // So the change we made isn't recorded when commitChanges is called
		}

		PKVariantUInt32 oldv(PKStr::wstringToUInt32(oldValue));
		this->bar->set(BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY, &oldv);

        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");
	}
}

void BarSectionNumberChangeCommand::redoCommand()
{
	if(this->window)
	{
		if(this->bar == this->window->getSelectedBar())
		{
			this->window->setEditText("ID_BAR_SECTION_NUMBER_EDIT", newValue);
			this->window->resetEditChanges("ID_BAR_SECTION_NUMBER_EDIT"); // So the change we made isn't recorded when commitChanges is called
		}

		PKVariantUInt32 newv(PKStr::wstringToUInt32(newValue));
		this->bar->set(BarViewVectorControl::HEADER_WSTRING_PROPERTY, &newv);

        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");
	}
}
