//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#include "ToggleSectionMarkerCommand.h"
#include "ChordableWindow.h"
#include "PKStr.h"

//
// ShowTempoCommand
//

ToggleSectionMarkerCommand::ToggleSectionMarkerCommand(ChordableWindow *window, 
													   BarViewVectorControl *bar,
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
	
	this->toggle = toggle;

	if(toggle)
	{
		this->setDisplayName(PK_i18n(L"Add Section Marker"));
	}
	else
	{
		this->setDisplayName(PK_i18n(L"Remove Section Marker"));
	}
}

ToggleSectionMarkerCommand::~ToggleSectionMarkerCommand()
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

void ToggleSectionMarkerCommand::doCommand()
{
	if(this->window && this->bar)
	{
		this->window->setControlEnabled("ID_BAR_SECTION_NUMBER_EDIT", toggle);
		this->window->setControlEnabled("ID_BAR_SECTION_ARROWS", toggle);

		this->window->setControlEnabled("ID_BAR_HEADER_EDIT", !toggle);

		PKGridLayout *barGrid = this->window->getBarGridLayout();

		if(this->bar && barGrid)
		{
			PKVariantBool s(toggle);
			this->bar->set(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY, &s);

			if(toggle)
			{
				std::wstring numStr = this->window->getEditText("ID_BAR_SECTION_NUMBER_EDIT");
				uint32_t     num    = PKStr::wstringToUInt32(numStr);

				if(num > 0)
				{
					PKVariantUInt32 numv(num);
					this->bar->set(BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY, &numv);
				}

				std::wstring header = PKVALUE_WSTRING(this->bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));

				if(header == L"")
				{
					this->window->toggleOverheadSpaceForBar(this->bar, true);
				}

				barGrid->relayout();
				this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT"); // TODO: better ?
			}
			else
			{
				std::wstring header = PKVALUE_WSTRING(this->bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));

				if(header == L"")
				{
					this->window->toggleOverheadSpaceForBar(this->bar, false);
				}
	
				barGrid->relayout();
				this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT"); // TODO: better ?
			}
		}
	}
}

void ToggleSectionMarkerCommand::undoCommand()
{
	if(this->window && this->bar)
	{
		BarViewVectorControl *selectedBar = this->window->getSelectedBar();

		if(selectedBar == this->bar)
		{
			this->window->setControlEnabled("ID_BAR_SECTION_NUMBER_EDIT", !toggle);
			this->window->setControlEnabled("ID_BAR_SECTION_ARROWS", !toggle);

			this->window->setControlEnabled("ID_BAR_HEADER_EDIT", toggle);
			this->window->setCheckBoxChecked("ID_BAR_SECTION_MARKUP_CHECK", !toggle);
		}

		PKGridLayout *barGrid = this->window->getBarGridLayout();

		if(this->bar && barGrid)
		{
			PKVariantBool s(!toggle);
			this->bar->set(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY, &s);

			if(toggle)
			{
				std::wstring header = PKVALUE_WSTRING(this->bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));

				if(header == L"")
				{
					this->window->toggleOverheadSpaceForBar(this->bar, false);
				}

				barGrid->relayout();
				this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT"); // TODO: better ?
			}
			else
			{
				std::wstring header = PKVALUE_WSTRING(this->bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));

				if(header == L"")
				{
					this->window->toggleOverheadSpaceForBar(this->bar, true);
				}
	
				barGrid->relayout();
				this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT"); // TODO: better ?
			}
		}
	}
}

void ToggleSectionMarkerCommand::redoCommand()
{
	if(this->window && this->bar)
	{
		BarViewVectorControl *selectedBar = this->window->getSelectedBar();

		if(selectedBar == this->bar)
		{
			this->window->setControlEnabled("ID_BAR_SECTION_NUMBER_EDIT", toggle);
			this->window->setControlEnabled("ID_BAR_SECTION_ARROWS", toggle);

			this->window->setControlEnabled("ID_BAR_HEADER_EDIT", !toggle);
			this->window->setCheckBoxChecked("ID_BAR_SECTION_MARKUP_CHECK", toggle);
		}

		PKGridLayout *barGrid = this->window->getBarGridLayout();

		if(this->bar && barGrid)
		{
			PKVariantBool s(toggle);
			this->bar->set(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY, &s);

			if(toggle)
			{
				std::wstring header = PKVALUE_WSTRING(this->bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));

				if(header == L"")
				{
					this->window->toggleOverheadSpaceForBar(this->bar, true);
				}

				barGrid->relayout();
				this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT"); // TODO: better ?
			}
			else
			{
				std::wstring header = PKVALUE_WSTRING(this->bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));

				if(header == L"")
				{
					this->window->toggleOverheadSpaceForBar(this->bar, false);
				}
	
				barGrid->relayout();
				this->window->invalidateControl("ID_VECTOR_CONTROL_ROOT"); // TODO: better ?
			}
		}
	}
}
