//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ChangeKeyCommand.h"
#include "ChordableWindow.h"

//
// ShowTempoCommand
//

ChangeKeyCommand::ChangeKeyCommand(ChordableWindow *window, 
								   int32_t newSelection, 
								   int32_t oldSelection)
{
	this->window = window;
	this->window->retain();

	this->newSelection = newSelection;
	this->oldSelection = oldSelection;

	this->setDisplayName(PK_i18n(L"Change Key"));
}

ChangeKeyCommand::~ChangeKeyCommand()
{
	this->window->release();
}

void ChangeKeyCommand::doCommand()
{
	if(this->window)
	{
        std::wstring text = this->window->getComboBoxSelectedText("ID_INSPECTOR_KEY_COMBO");
		
		bool preferSharp = true; // TODO: setting
		int  pos = text.find_first_of(L'/');
		if(pos != std::wstring::npos)
		{
			if(preferSharp)
			{
				text = text.substr(0, pos);
			}
			else
			{
				text = text.substr(pos+1);				
			}
		}
		
		this->window->setEditableLabelText("ID_KEY_EDIT", text);
	}
}

void ChangeKeyCommand::undoCommand()
{
	if(this->window)
	{
		this->window->selectComboBoxItem("ID_INSPECTOR_KEY_COMBO", this->oldSelection);

        std::wstring text = this->window->getComboBoxSelectedText("ID_INSPECTOR_KEY_COMBO");
		
		bool preferSharp = true; // TODO: setting
		int  pos = text.find_first_of(L'/');
		if(pos != std::wstring::npos)
		{
			if(preferSharp)
			{
				text = text.substr(0, pos);
			}
			else
			{
				text = text.substr(pos+1);				
			}
		}
		
		this->window->setEditableLabelText("ID_KEY_EDIT", text);
	}
}

void ChangeKeyCommand::redoCommand()
{
	if(this->window)
	{
		this->window->selectComboBoxItem("ID_INSPECTOR_KEY_COMBO", this->newSelection);

        std::wstring text = this->window->getComboBoxSelectedText("ID_INSPECTOR_KEY_COMBO");
		
		bool preferSharp = true; // TODO: setting
		int  pos = text.find_first_of(L'/');
		if(pos != std::wstring::npos)
		{
			if(preferSharp)
			{
				text = text.substr(0, pos);
			}
			else
			{
				text = text.substr(pos+1);				
			}
		}
		
		this->window->setEditableLabelText("ID_KEY_EDIT", text);
	}
}
