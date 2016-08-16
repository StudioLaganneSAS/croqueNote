//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ChangeBarsPerRowCommand.h"
#include "ChordableWindow.h"

//
// ChangeBarsPerRowCommand
//

ChangeBarsPerRowCommand::ChangeBarsPerRowCommand(ChordableWindow *window, 
								   uint32_t newSelection, 
								   uint32_t oldSelection)
{
	this->window = window;
	this->window->retain();

	this->newSelection = newSelection;
	this->oldSelection = oldSelection;

	this->setDisplayName(PK_i18n(L"Change Bars Per Row"));
}

ChangeBarsPerRowCommand::ChangeBarsPerRowCommand()
{
	this->window->release();
}

void ChangeBarsPerRowCommand::doCommand()
{
	if(this->window)
	{
		if(this->window->getCurrentDocument())
		{
			PKVariantUInt32 bars(this->newSelection);
			this->window->getCurrentDocument()->set(ChordableDocument::BARS_PER_ROW_UINT32_PROPERTY, &bars);
		}
		
		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->window->findControl("ID_BAR_GRID"));
		
		if(barGrid)
		{
			this->window->removeAllOverheadSpacers();
			this->window->removeAllLineBreaksSpacers();
			
			PKVariantUInt32 cols(this->newSelection);
			barGrid->set(PKGridLayout::COLS_UINT32_PROPERTY, &cols);
			
			this->window->checkLineBreaksLayout();
			this->window->addOverheadSpacersWhereNeeded();
			
			// Force an update of the layout
			this->window->sliderChanged("ID_ZOOM_SLIDER", 0);
			this->window->redraw();
		}			
	}
}

void ChangeBarsPerRowCommand::undoCommand()
{
	if(this->window)
	{
		if(this->window->getCurrentDocument())
		{
			PKVariantUInt32 bars(this->oldSelection);
			this->window->getCurrentDocument()->set(ChordableDocument::BARS_PER_ROW_UINT32_PROPERTY, &bars);
		}
		
		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->window->findControl("ID_BAR_GRID"));
		
		if(barGrid)
		{
			this->window->removeAllOverheadSpacers();
			this->window->removeAllLineBreaksSpacers();
			
			PKVariantUInt32 cols(this->oldSelection);
			barGrid->set(PKGridLayout::COLS_UINT32_PROPERTY, &cols);
			
			this->window->checkLineBreaksLayout();
			this->window->addOverheadSpacersWhereNeeded();
			
			// Force an update of the layout
			this->window->sliderChanged("ID_ZOOM_SLIDER", 0);
			this->window->redraw();
		}			
	}
}

void ChangeBarsPerRowCommand::redoCommand()
{
	if(this->window)
	{
		if(this->window->getCurrentDocument())
		{
			PKVariantUInt32 bars(this->newSelection);
			this->window->getCurrentDocument()->set(ChordableDocument::BARS_PER_ROW_UINT32_PROPERTY, &bars);
		}
		
		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->window->findControl("ID_BAR_GRID"));
		
		if(barGrid)
		{
			this->window->removeAllOverheadSpacers();
			this->window->removeAllLineBreaksSpacers();
			
			PKVariantUInt32 cols(this->newSelection);
			barGrid->set(PKGridLayout::COLS_UINT32_PROPERTY, &cols);
			
			this->window->checkLineBreaksLayout();
			this->window->addOverheadSpacersWhereNeeded();
			
			// Force an update of the layout
			this->window->sliderChanged("ID_ZOOM_SLIDER", 0);
			this->window->redraw();
		}			
	}
}
