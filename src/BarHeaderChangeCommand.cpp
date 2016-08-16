//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "BarHeaderChangeCommand.h"
#include "ChordableWindow.h"

//
// BarHeaderChangeCommand
//

BarHeaderChangeCommand::BarHeaderChangeCommand(ChordableWindow *window, 
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

	this->setDisplayName(PK_i18n(L"Change Bar Header"));
}

BarHeaderChangeCommand::~BarHeaderChangeCommand()
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

void BarHeaderChangeCommand::doCommand()
{
	// Nothing to do
}

void BarHeaderChangeCommand::undoCommand()
{
	if(this->window)
	{
        PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->window->findControl("ID_BAR_GRID"));

		if(this->bar == this->window->getSelectedBar())
		{
			this->window->setEditText("ID_BAR_HEADER_EDIT", oldValue);
			this->window->resetEditChanges("ID_BAR_HEADER_EDIT"); // So the change we made isn't recorded when commitChanges is called
		}

		if(barGrid)
		{
			if(oldValue != L"")
			{
				if(newValue == L"")
				{
					// We need to make sure there is space for the header

					this->window->toggleOverheadSpaceForBar(this->bar, true);
				}

				PKVariantWString oldv(oldValue);
				this->bar->set(BarViewVectorControl::HEADER_WSTRING_PROPERTY, &oldv);
				barGrid->relayout();
			}
			else
			{
				if(newValue != L"")
				{
					// We need to remove the space for the header
					// if the row is empty from bars that have headers

					this->window->toggleOverheadSpaceForBar(this->bar, false);
				}

				PKVariantWString oldv(oldValue);
				this->bar->set(BarViewVectorControl::HEADER_WSTRING_PROPERTY, &oldv);
				barGrid->relayout();
			}
		}

        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");
	}
}

void BarHeaderChangeCommand::redoCommand()
{
	if(this->window)
	{
        PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->window->findControl("ID_BAR_GRID"));

		if(this->bar == this->window->getSelectedBar())
		{
			this->window->setEditText("ID_BAR_HEADER_EDIT", newValue);
			this->window->resetEditChanges("ID_BAR_HEADER_EDIT"); // So the change we made isn't recorded when commitChanges is called
		}

		if(barGrid)
		{
			if(newValue != L"")
			{
				if(oldValue == L"")
				{
					// We need to make sure there is space for the header

					this->window->toggleOverheadSpaceForBar(this->bar, true);
				}

				PKVariantWString newv(newValue);
				this->bar->set(BarViewVectorControl::HEADER_WSTRING_PROPERTY, &newv);
				barGrid->relayout();
			}
			else
			{
				if(oldValue != L"")
				{
					// We need to remove the space for the header
					// if the row is empty from bars that have headers

					this->window->toggleOverheadSpaceForBar(this->bar, false);
				}

				PKVariantWString newv(newValue);
				this->bar->set(BarViewVectorControl::HEADER_WSTRING_PROPERTY, &newv);
				barGrid->relayout();
			}
		}

        this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT");
	}
}
