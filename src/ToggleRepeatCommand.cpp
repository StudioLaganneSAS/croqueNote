//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ToggleRepeatCommand.h"
#include "ChordableWindow.h"
#include "PKStr.h"

//
// ShowTempoCommand
//

ToggleRepeatCommand::ToggleRepeatCommand(ChordableWindow *window, 
									     BarViewVectorControl *bar,
										 bool left,
									     bool toggle)
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
	
	this->toggled = toggle;
	this->left    = left;

	this->removedOther = false;

	if(toggle)
	{
		this->setDisplayName(PK_i18n(L"Add Repeat Marker"));
	}
	else
	{
		this->setDisplayName(PK_i18n(L"Remove Repeat Marker"));
	}
}

ToggleRepeatCommand::~ToggleRepeatCommand()
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

void ToggleRepeatCommand::doCommand()
{
	this->removedOther = false;

	if(this->window && this->bar)
	{
		if(this->left) // left repeat
		{
			PKVariantBool on(toggled);
			this->bar->set(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY, &on);

			if(toggled)
			{
				this->removedOther = PKVALUE_BOOL(this->bar->get(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY));
				PKVariantBool off(false);
				this->bar->set(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY, &off);
				this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON", false);
			}
		}
		else // right repeat
		{
			PKVariantBool on(toggled);
			this->bar->set(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY, &on);

			if(toggled)
			{
				this->removedOther = PKVALUE_BOOL(this->bar->get(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY));
				PKVariantBool off(false);
				this->bar->set(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY, &off);
				this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON", false);
			}
		}
	}
}

void ToggleRepeatCommand::undoCommand()
{
	if(this->window && this->bar)
	{
		BarViewVectorControl *selectedBar = this->window->getSelectedBar();

		if(this->left)
		{
			// We just update the bar
			PKVariantBool val(!toggled);
			this->bar->set(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY, &val);

			// See if we need to restore the other one
			if(this->removedOther)
			{
				// Set the other repeat back
				PKVariantBool val(true);
				this->bar->set(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY, &val);
			}

			if(selectedBar == this->bar)
			{
				// We also toggle again
				this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON", !toggled);

				if(this->removedOther)
				{
					this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON", true);
				}
			}
		}
		else
		{
			// We just update the bar
			PKVariantBool val(!toggled);
			this->bar->set(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY, &val);

			// See if we need to restore the other one
			if(this->removedOther)
			{
				// Set the other repeat back
				PKVariantBool val(true);
				this->bar->set(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY, &val);
			}

			if(selectedBar == this->bar)
			{
				// We just toggle again
				this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON", !toggled);

				if(this->removedOther)
				{
					this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON", true);
				}
			}
		}
	}
}

void ToggleRepeatCommand::redoCommand()
{
	if(this->window && this->bar)
	{
		BarViewVectorControl *selectedBar = this->window->getSelectedBar();

		if(this->left)
		{
			PKVariantBool on(toggled);
			this->bar->set(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY, &on);

			if(toggled)
			{
				this->removedOther = PKVALUE_BOOL(this->bar->get(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY));
				PKVariantBool off(false);
				this->bar->set(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY, &off);

				if(selectedBar == this->bar)
				{
					this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON", false);
				}
			}

			if(selectedBar == this->bar)
			{
				// We just toggle again
				this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON", toggled);
			}
		}
		else
		{
			PKVariantBool on(toggled);
			this->bar->set(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY, &on);

			if(toggled)
			{
				this->removedOther = PKVALUE_BOOL(this->bar->get(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY));
				PKVariantBool off(false);
				this->bar->set(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY, &off);

				if(selectedBar == this->bar)
				{
					this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON", false);
				}
			}

			if(selectedBar == this->bar)
			{
				// We just toggle again
				this->window->setBitmapToggleButtonToggled("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON", toggled);
			}
		}
	}
}
