//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ChangeTuningCommand.h"
#include "ChordableWindow.h"
#include "PKStr.h"

//
// ShowTempoCommand
//

ChangeTuningCommand::ChangeTuningCommand(ChordableWindow *window, 
										 int32_t newSelection, 
										 int32_t oldSelection,
									     PKNotationName notation)
{
	this->window = window;
	this->window->retain();

	this->newSelection = newSelection;
	this->oldSelection = oldSelection;
	this->notation     = notation;

	this->setDisplayName(PK_i18n(L"Change Tuning"));

	this->tunings = PKTuning::getAllGuitarTunings();
}

ChangeTuningCommand::~ChangeTuningCommand()
{
	this->window->release();

	for(uint32_t i=0; i<this->tunings.size(); i++)
	{
		delete this->tunings[i];
	}
	this->tunings.clear();
}

void ChangeTuningCommand::doCommand()
{
	if(this->window)
	{
		// Record the change in the document

		int tuningIndex = this->window->getComboBoxSelectedItem("ID_TUNING_COMBO");

		if(tuningIndex >= 0 && 
		   tuningIndex < (int) this->tunings.size())
		{
			PKTuning *t = this->tunings[tuningIndex];

            // Save it to ChordableDocument

            std::wstring             notes = L"";
			std::vector<std::string> list;
			
			for(uint32_t n=0; n<t->getNumberOfStrings(); n++)
			{
				PKNote note = t->getNoteForString(n);
				list.push_back(PKStr::int32ToString(note.note));

                notes += PKNoteGetName(note, this->notation, true);

                if((this->notation == PKNOTATION_NAMES) && 
                   (n != (t->getNumberOfStrings() - 1)))
                {
                    notes += L" ";
                }
			}

			PKVariantStringList l(list);
			this->window->getCurrentDocument()->set(ChordableDocument::TUNING_STRINGLIST_PROPERTY, &l);

            // Update the display

            this->window->setEditableLabelText("ID_TUNING_EDIT", notes);
            this->window->setEditableLabelText("ID_TUNING_SUBEDIT", L"(" + t->getName() + L")");
		}
	}
}

void ChangeTuningCommand::undoCommand()
{
	if(this->window)
	{
		this->window->selectComboBoxItem("ID_TUNING_COMBO", this->oldSelection);

		// Record the change in the document

		int tuningIndex = this->window->getComboBoxSelectedItem("ID_TUNING_COMBO");

		if(tuningIndex >= 0 && 
		   tuningIndex < (int) this->tunings.size())
		{
			PKTuning *t = this->tunings[tuningIndex];

            // Save it to ChordableDocument

            std::wstring             notes = L"";
			std::vector<std::string> list;
			
			for(uint32_t n=0; n<t->getNumberOfStrings(); n++)
			{
				PKNote note = t->getNoteForString(n);
				list.push_back(PKStr::int32ToString(note.note));

                notes += PKNoteGetName(note, this->notation, true);

                if((this->notation == PKNOTATION_NAMES) && 
                   (n != (t->getNumberOfStrings() - 1)))
                {
                    notes += L" ";
                }
			}

			PKVariantStringList l(list);
			this->window->getCurrentDocument()->set(ChordableDocument::TUNING_STRINGLIST_PROPERTY, &l);

            // Update the display

            this->window->setEditableLabelText("ID_TUNING_EDIT", notes);
            this->window->setEditableLabelText("ID_TUNING_SUBEDIT", L"(" + t->getName() + L")");
		}
	}
}

void ChangeTuningCommand::redoCommand()
{
	if(this->window)
	{
		this->window->selectComboBoxItem("ID_TUNING_COMBO", this->newSelection);

		// Record the change in the document

		int tuningIndex = this->window->getComboBoxSelectedItem("ID_TUNING_COMBO");

		if(tuningIndex >= 0 && 
		   tuningIndex < (int) this->tunings.size())
		{
			PKTuning *t = this->tunings[tuningIndex];

            // Save it to ChordableDocument

            std::wstring             notes = L"";
			std::vector<std::string> list;
			
			for(uint32_t n=0; n<t->getNumberOfStrings(); n++)
			{
				PKNote note = t->getNoteForString(n);
				list.push_back(PKStr::int32ToString(note.note));

                notes += PKNoteGetName(note, this->notation, true);

                if((this->notation == PKNOTATION_NAMES) && 
                   (n != (t->getNumberOfStrings() - 1)))
                {
                    notes += L" ";
                }
			}

			PKVariantStringList l(list);
			this->window->getCurrentDocument()->set(ChordableDocument::TUNING_STRINGLIST_PROPERTY, &l);

            // Update the display

            this->window->setEditableLabelText("ID_TUNING_EDIT", notes);
            this->window->setEditableLabelText("ID_TUNING_SUBEDIT", L"(" + t->getName() + L")");
		}
	}
}
