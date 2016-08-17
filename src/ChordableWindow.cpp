//
// ChordableWindow
//

#include "PKApp.h"
#include "ChordableWindow.h"
#include "ChordableWindow_XML.h"
#include "PKAboutDialog.h"
#include "PKStdDialog.h"
#include "PKSaveDialog.h"
#include "PKOpenDialog.h"
#include "PKDatabase.h"
#include "PKScrollView.h"
#include "PKPath.h"
#include "PKStr.h"
#include "PKEdit.h"
#include "PKEditableVectorLabel.h"
#include "PKCheckBox.h"
#include "PKComboBox.h"
#include "PKGridLayout.h"
#include "BarViewVectorControl.h"
#include "BarHeaderSpacer.h"
#include "LineBreakVectorControl.h"
#include "AddBarsVectorControl.h"
#include "PKLayout.h"
#include "PKVectorControlRoot.h"
#include "PKNumberInputDialog.h"
#include "PKSpacer.h"
#include "PKLittleArrows.h"
#include "PKChordDiagramVectorUI.h"
#include "ChordableVectorControlRoot.h"
#include "ExportDialog.h"
#include "PKVectorEngine.h"

//
// Commands
//

#include "HideCapoCommand.h"
#include "ShowCapoCommand.h"
#include "HideTempoCommand.h"
#include "ShowTempoCommand.h"
#include "ToggleKeyCommand.h"
#include "ToggleTuningCommand.h"
#include "ToggleSectionMarkerCommand.h"
#include "ChangeKeyCommand.h"
#include "ChangeTuningCommand.h"
#include "ChangeBarTypeCommand.h"
#include "ToggleRepeatCommand.h"
#include "GenericEditChangeCommand.h"
#include "GenericVectorEditChangeCommand.h"
#include "BarHeaderChangeCommand.h"
#include "BarSectionNumberChangeCommand.h"
#include "ToggleShowChordDiagramsCommand.h"
#include "ChangeBarsPerRowCommand.h"

static PKApp *app;

//
// Defines
//

#define CHORDABLE_DOCUMENT_TABLE_V1 "document_v1"
#define CHORDABLE_CONTENTS_TABLE_V1 "contents_v1"

//
// ChordableWindow
//

ChordableWindow::ChordableWindow(std::wstring icon, ChordableSettings *settings)
: PKDialog(L"CHORDABLE_MAIN_WINDOW", 
		   PK_WINDOW_STYLE_DEFAULT|PK_WINDOW_STYLE_DB_BUFFER|PK_WINDOW_STYLE_ACCEPT_DROP,
		   NULL,
		   icon)
{
    this->settings    = settings;
	this->selection.clear();
	
    if(this->settings == NULL)
    {
        return;
    }

    // Let's go

    this->ready = false;

	// Set caption

	PKVariantWStringI18N caption(L"PKI18N:Croque-Note - New Document");
	this->set(PKWindow::CAPTION_WSTRING_PROPERTY, &caption);

	// Load from XML

	this->addFactory(&this->factory);
	this->loadFromXML(chordableWindow_XML);

	// Create toolbar

	std::string toolbarXML = "<PKToolbar id=\"com.projectKetchup.croqueNote\">"
							 "  <PKToolbarItem id=\"TOOLBAR_ID_NEW\"  text=\"PKI18N:New\" help=\"PKI18N:Create a new Document\" icon=\"res|NEW\" />"
							 "  <PKToolbarItem id=\"TOOLBAR_ID_OPEN\" text=\"PKI18N:Open\" help=\"PKI18N:Open a Document\" icon=\"res|OPEN\" />"
							 "  <PKToolbarItem id=\"TOOLBAR_ID_SAVE\" text=\"PKI18N:Save\" help=\"PKI18N:Save the current Document\" icon=\"res|SAVE\" />"
						     "  <PKToolbarSeparator />"
							 "  <PKToolbarItem id=\"TOOLBAR_ID_PRINT\" text=\"PKI18N:Print\" help=\"PKI18N:Print the current Document\" icon=\"res|PRINT\" />"
							 "  <PKToolbarItem id=\"TOOLBAR_ID_EXPORT\" text=\"PKI18N:Export\" help=\"PKI18N:Export the current Document to various other formats\" icon=\"res|EXPORT\" />"
						     "  <PKToolbarFlexibleSpace />"
                             "  <PKToolbarSegmentedItem id=\"TOOLBAR_ID_NOTATION\" text=\"PKI18N:Notation\" help=\"PKI18N:Latin Notation (Do Re Mi...),US-UK Notation (C D E...)\" normalImage=\"res|NOTATION_NORMAL\" downImage=\"res|NOTATION_DOWN\" hoverImage=\"res|NOTATION_HOVER\" numButtons=\"2\" offsets=\"0,36,71\" selection=\"1\" />"
						     "  <PKToolbarSeparator />"
							 "  <PKToolbarItem id=\"TOOLBAR_ID_OPTIONS\" text=\"PKI18N:Options\" help=\"PKI18N:Tune the program settings\" icon=\"res|OPTIONS\" />"
							 "</PKToolbar>";

	this->toolbar = PKToolbar::loadToolbarFromXML(toolbarXML);
	this->setToolbar(this->toolbar);

    // Setup class pointers

    ChordableVectorControlRoot *root = dynamic_cast<ChordableVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

    if(root)
    {
        root->setWindow(this);
    }
	
	// Setup bindings
	
	PKControl *title1 = this->findControl("ID_TITLE_EDIT");
	PKControl *title2 = this->findControl("ID_INSPECTOR_TITLE_EDIT");
	
	if(title1 && title2)
    {
    	title1->bindToObject(PKEdit::TEXT_WSTRING_PROPERTY,
    						 title2,
    						 PKEditableVectorLabel::TEXT_WSTRING_PROPERTY);
    }

	PKControl *subtitle1 = this->findControl("ID_SUBTITLE_EDIT");
	PKControl *subtitle2 = this->findControl("ID_INSPECTOR_SUBTITLE_EDIT");
	
	if(subtitle1 && subtitle2)
    {
    	subtitle1->bindToObject(PKEdit::TEXT_WSTRING_PROPERTY,
    						    subtitle2,
    						    PKEditableVectorLabel::TEXT_WSTRING_PROPERTY);
    }

	PKControl *tempo1 = this->findControl("ID_TEMPO_EDIT");
	PKControl *tempo2 = this->findControl("ID_INSPECTOR_TEMPO_EDIT");
	
	if(tempo1 && tempo2)
    {
    	tempo1->bindToObject(PKEdit::TEXT_WSTRING_PROPERTY,
    						 tempo2,
    						 PKEditableVectorLabel::TEXT_WSTRING_PROPERTY);

        PKLittleArrows *arrows = dynamic_cast<PKLittleArrows*>(this->findControl("ID_TEMPO_ARROWS"));

        if(arrows)
        {
            arrows->setBuddyControl(tempo2);
        }
    }

	PKControl *capo1 = this->findControl("ID_CAPO_EDIT");
	PKControl *capo2 = this->findControl("ID_INSPECTOR_CAPO_EDIT");
	
	if(capo1 && capo2)
    {
    	capo1->bindToObject(PKEdit::TEXT_WSTRING_PROPERTY,
							capo2,
							PKEditableVectorLabel::TEXT_WSTRING_PROPERTY);
		
        PKLittleArrows *arrows = dynamic_cast<PKLittleArrows*>(this->findControl("ID_CAPO_ARROWS"));
		
        if(arrows)
        {
            arrows->setBuddyControl(capo2);
        }
    }

    PKControl *colEdit = this->findControl("ID_NUM_COL_EDIT");

    if(colEdit)
    {
        PKLittleArrows *arrows = dynamic_cast<PKLittleArrows*>(this->findControl("ID_COL_ARROWS"));

        if(arrows)
        {
            arrows->setBuddyControl(colEdit);
        }
    }

    PKControl *headerEdit = this->findControl("ID_BAR_SECTION_NUMBER_EDIT");

    if(headerEdit)
    {
        PKLittleArrows *arrows = dynamic_cast<PKLittleArrows*>(this->findControl("ID_BAR_SECTION_ARROWS"));

        if(arrows)
        {
            arrows->setBuddyControl(headerEdit);
        }
    }

	PKControl *keyCombo = this->findControl("ID_INSPECTOR_KEY_COMBO");

    // Setup defaults for controls

    this->disableControl("ID_INSPECTOR_CAPO_EDIT");
    this->disableControl("ID_INSPECTOR_TEMPO_EDIT");
    this->disableControl("ID_INSPECTOR_KEY_COMBO");

    this->disableControl("ID_CAPO_ARROWS");
    this->disableControl("ID_TEMPO_ARROWS");

    this->setControlHidden("ID_TEMPO_IMAGE", true);
    this->setControlHidden("ID_TEMPO_EDIT",  true);

    this->setControlHidden("ID_CAPO_LABEL", true);
    this->setControlHidden("ID_CAPO_EDIT",  true);

    this->setControlHidden("ID_TUNING_IMAGE",   true);
    this->setControlHidden("ID_TUNING_EDIT",    true);
    this->setControlHidden("ID_TUNING_SUBEDIT", true);

    this->setControlHidden("ID_KEY_IMAGE", true);
    this->setControlHidden("ID_KEY_EDIT",  true);

	this->setControlHidden("ID_CAPO_SPACER",  true);
	this->setControlHidden("ID_TEMPO_SPACER",  true);
	this->setControlHidden("ID_KEY_SPACER",    true);
    this->setControlHidden("ID_TUNING_SPACER", true);

	this->setControlHidden("ID_CHORDS_SPACER",  true);
	this->setControlHidden("ID_CHORDS_GRID",    true);

    // Create document and setup bindings

    this->currentDocument = new ChordableDocument();

    this->currentDocument->bindToObject(ChordableDocument::TITLE_WSTRING_PROPERTY,
                                        title2, PKEdit::TEXT_WSTRING_PROPERTY);
    this->currentDocument->bindToObject(ChordableDocument::SUBTITLE_WSTRING_PROPERTY,
                                        subtitle2, PKEdit::TEXT_WSTRING_PROPERTY);
    this->currentDocument->bindToObject(ChordableDocument::NOTES_WSTRING_PROPERTY,
                                        this->findControl("ID_INSPECTOR_NOTES_EDIT"),
                                        PKEdit::TEXT_WSTRING_PROPERTY);

	this->currentDocument->bindToObject(ChordableDocument::SHOW_CAPO_BOOL_PROPERTY,
										this->findControl("ID_INSPECTOR_CAPO_CHECKBOX"),
										PKCheckBox::CHECKED_BOOL_PROPERTY);
	this->currentDocument->bindToObject(ChordableDocument::SHOW_TEMPO_BOOL_PROPERTY,
										this->findControl("ID_INSPECTOR_TEMPO_CHECKBOX"),
										PKCheckBox::CHECKED_BOOL_PROPERTY);
	this->currentDocument->bindToObject(ChordableDocument::SHOW_KEY_BOOL_PROPERTY,
										this->findControl("ID_INSPECTOR_KEY_CHECKBOX"),
										PKCheckBox::CHECKED_BOOL_PROPERTY);
    this->currentDocument->bindToObject(ChordableDocument::TEMPO_WSTRING_PROPERTY,
                                        tempo2, PKEdit::TEXT_WSTRING_PROPERTY);
    this->currentDocument->bindToObject(ChordableDocument::CAPO_WSTRING_PROPERTY,
                                        capo2, PKEdit::TEXT_WSTRING_PROPERTY);
	this->currentDocument->bindToObject(ChordableDocument::SHOW_TUNING_BOOL_PROPERTY,
										this->findControl("ID_INSPECTOR_TUNING_CHECKBOX"),
										PKCheckBox::CHECKED_BOOL_PROPERTY);
    this->currentDocument->bindToObject(ChordableDocument::SHOW_CHORD_DIAGRAMS_BOOL_PROPERTY,
										this->findControl("ID_INSPECTOR_CHORDS_CHECKBOX"),
										PKCheckBox::CHECKED_BOOL_PROPERTY);

    this->currentDocument->bindToObject(ChordableDocument::KEY_INT32_PROPERTY,
                                        keyCombo, PKComboBox::CURRENTITEM_INT32_PROPERTY);	

    // Setup UI
    this->disableBarProperties();

	// Setup member variables
	this->needsSave   = false;
	this->currentFileName = L"";
    this->notation = (PKNotationName) PKVALUE_UINT32(this->settings->get(ChordableSettings::NOTATION_UINT32_PROPERTY));
    this->defaultZoom = PKVALUE_UINT32(this->settings->get(ChordableSettings::ZOOM_UINT32_PROPERTY));
    this->ignoreTuning = false;
    this->ignoreSetSave = false;
	this->barWidth  = 0;
	this->barHeight = 0;

    // Setup key combox box

    this->clearComboBoxItems("ID_INSPECTOR_KEY_COMBO");

    for(uint32_t n = PKNOTE_DO; n<PKNOTE_SI; n++)
    {
        PKNote note;

        note.note   = n;
        note.octave = 0;

        std::wstring noteName = PKNoteGetName(note, this->notation, true);
		this->addComboBoxItem("ID_INSPECTOR_KEY_COMBO", noteName);
    }

    this->selectComboBoxItem("ID_INSPECTOR_KEY_COMBO", 0);

	// Setup tuning combo box

	this->tunings = PKTuning::getAllGuitarTunings();

	this->clearComboBoxItems("ID_TUNING_COMBO");

	for(uint32_t i=0; i<this->tunings.size(); i++)
	{
		std::wstring tName = this->tunings[i]->getName();

		tName += L" (";

		for(uint32_t n=0; n<this->tunings[i]->getNumberOfStrings(); n++)
		{
			tName += PKNoteGetName(this->tunings[i]->getNoteForString(n),
								   this->notation, true);  

            if((this->notation == PKNOTATION_NAMES) && 
               (i != (this->tunings[i]->getNumberOfStrings() - 1)))
            {
                tName += L" ";
            }
		}

		tName += L")";

		this->addComboBoxItem("ID_TUNING_COMBO", tName);
	}

	this->selectComboBoxItem("ID_TUNING_COMBO", 0);

    // Create chord selection dialog
    this->chordDialog = new PKChordLibraryDialog(this->getWindowHandle(), icon);
    
    // Update its caption
    PKVariantWString c(PK_i18n(L"Croque-Note : Select a Chord"));
    this->chordDialog->set(PKWindow::CAPTION_WSTRING_PROPERTY, &c);

    // Setup the notation switch
    this->setToolbarSegmentedItemSelection("TOOLBAR_ID_NOTATION", (int32_t) this->notation);
}

ChordableWindow::~ChordableWindow()
{
	for(uint32_t i=0; i<this->tunings.size(); i++)
	{
		delete this->tunings[i];
	}
	this->tunings.clear();

	delete this->currentDocument;
}

void ChordableWindow::setReady()
{
    this->ready = true;
}

void ChordableWindow::layoutInitialDocument()
{
    // Setup document layouting
    this->setSliderValue("ID_ZOOM_SLIDER", this->defaultZoom);
	this->sliderChanged("ID_ZOOM_SLIDER", this->defaultZoom);
}

void ChordableWindow::processSafeEvent(std::string  eventName,
									   void        *payload)
{
	if(eventName == "ADD_LINE_BREAK")
	{
		AddBarsVectorControl *add = (AddBarsVectorControl *) payload;
		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
		PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

		if(add         != NULL && 
		   barGrid     != NULL && 
		   rootControl != NULL)
		{
			uint32_t numBars = PKVALUE_UINT32(barGrid->get(PKGridLayout::COLS_UINT32_PROPERTY));

			int32_t addButtonCol = barGrid->getColForChild(add);
			int32_t addButtonRow = barGrid->getRowForChild(add);
		
			int32_t numSpacers = (numBars - addButtonCol);

			// Insert spacers as needed

			for(int32_t i=0; i<numSpacers-1; i++)
			{
				PKSpacer *spacer = new PKSpacer();

		        PKVariantInt32 layoutx(1);
		        spacer->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
		        PKVariantInt32 layouty(1);
		        spacer->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

		        spacer->resize(this->barWidth, this->barHeight);

				barGrid->insertNewChildAt(addButtonCol, addButtonRow, spacer);

				spacer->build();
				spacer->initialize(this);
			}

			// Now insert line break control

			LineBreakVectorControl *lineBreak = new LineBreakVectorControl();

	        PKVariantInt32 layoutx(1);
	        lineBreak->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
	        PKVariantInt32 layouty(1);
	        lineBreak->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

			PKVariantBool shared(true);
			lineBreak->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

			lineBreak->resize(this->barWidth, this->barHeight);

			barGrid->insertNewChildAt(addButtonCol, addButtonRow, lineBreak);

			lineBreak->build();
			lineBreak->initialize(this);
			lineBreak->setControlRoot(rootControl);

			barGrid->relayout();
			this->invalidateControl("ID_VECTOR_CONTROL_ROOT");

            this->setNeedsSave();
        }
	}

	if(eventName == "REMOVE_LINEBREAK_ANIMATION")
	{
		LineBreakVectorControl *lb = (LineBreakVectorControl *) payload;
		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
		PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

		if(lb          != NULL && 
		   barGrid     != NULL && 
		   rootControl != NULL)
		{
			rootControl->clearInputState();

			this->removeAllOverheadSpacers();
			this->removeAllLineBreaksSpacers();
			
			this->removeLineBreak(lb);
			
			this->checkLineBreaksLayout();
			this->addOverheadSpacersWhereNeeded();

			barGrid->relayout();
			this->invalidateControl("ID_VECTOR_CONTROL_ROOT");

            // Flag we need to save the document
            this->setNeedsSave();
		}
	}

	if(eventName == "CLOSE_ANIMATION")
	{
		BarViewVectorControl *bar = (BarViewVectorControl *) payload;

		if(bar != NULL)
		{	
			// Remove from selction if needed
			this->selection.removeBar(bar);
			this->selectionChanged();
			
			// Remove this bar and redraw
			PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
			PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

			if(barGrid     != NULL && 
			   rootControl != NULL)
			{
				rootControl->clearInputState();

                // Remove the bar

				barGrid->removeChild(bar);
				this->removeAllOverheadSpacers();
				this->removeAllLineBreaksSpacers();

				this->checkLineBreaksLayout();
				this->addOverheadSpacersWhereNeeded();

				bar->release();
				barGrid->relayout();
				this->invalidateControl("ID_VECTOR_CONTROL_ROOT");

                // Update the chords grid
                this->refreshChordsGrid();

                // Flag we need to save the document
                this->setNeedsSave();
			}
		}
	}
}

void ChordableWindow::windowClosed()
{
    // Simulate a QUIT menu action
    this->menuItemClicked(NULL, NULL, "MENU_ID_QUIT");
}

void ChordableWindow::comboBoxChanged(std::string id, int32_t previousValue)
{
    if(id == "ID_INSPECTOR_KEY_COMBO" && this->ready)
	{
        if(this->ignoreTuning)
        {
            return;
        }

		int32_t newValue =  this->getComboBoxSelectedItem(id);
		ChangeKeyCommand *cmd = new ChangeKeyCommand(this, newValue, previousValue);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);

	    this->setNeedsSave();
	}

    if(id == "ID_TUNING_COMBO" && this->ready)
	{
        if(this->ignoreTuning)
        {
            return;
        }

		int32_t newValue = this->getComboBoxSelectedItem(id);

		ChangeTuningCommand *cmd = new ChangeTuningCommand(this, newValue, previousValue, this->notation);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);

        this->setNeedsSave();
	}
}


void ChordableWindow::checkBoxAction(std::string id, bool previousValue)
{
    if(id == "ID_INSPECTOR_CAPO_CHECKBOX")
    {
        bool checked = this->getCheckBoxChecked("ID_INSPECTOR_CAPO_CHECKBOX");

		if(checked)
		{
			ShowCapoCommand *cmd = new ShowCapoCommand(this);
			PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
		}
		else
		{
			HideCapoCommand *cmd = new HideCapoCommand(this);
			PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
		}
    }

    if(id == "ID_INSPECTOR_TEMPO_CHECKBOX")
    {
        bool checked = this->getCheckBoxChecked("ID_INSPECTOR_TEMPO_CHECKBOX");
		
		if(checked)
		{
			ShowTempoCommand *cmd = new ShowTempoCommand(this);
			PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
		}
		else
		{
			HideTempoCommand *cmd = new HideTempoCommand(this);
			PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
		}
    }

    if(id == "ID_INSPECTOR_KEY_CHECKBOX")
    {
        bool checked = this->getCheckBoxChecked("ID_INSPECTOR_KEY_CHECKBOX");

		ToggleKeyCommand *cmd = new ToggleKeyCommand(this, checked);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
    }

    if(id == "ID_INSPECTOR_TUNING_CHECKBOX")
    {
        bool checked = this->getCheckBoxChecked("ID_INSPECTOR_TUNING_CHECKBOX");

		ToggleTuningCommand *cmd = new ToggleTuningCommand(this, checked);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
    }

	if(id == "ID_BAR_SECTION_MARKUP_CHECK")
	{
        bool checked = this->getCheckBoxChecked("ID_BAR_SECTION_MARKUP_CHECK");

		ToggleSectionMarkerCommand *cmd = new ToggleSectionMarkerCommand(this, this->selection.getFirstBar(), checked);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
	}

    if(id == "ID_INSPECTOR_CHORDS_CHECKBOX")
    {
        bool checked = this->getCheckBoxChecked("ID_INSPECTOR_CHORDS_CHECKBOX");

        ToggleShowChordDiagramsCommand *cmd = new ToggleShowChordDiagramsCommand(this, checked);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
    }
}

void ChordableWindow::sliderChanged(std::string id, int32_t previousValue)
{
    if(id == "ID_ZOOM_SLIDER")
    {
        // Get new value

        int32_t value = this->getSliderValue("ID_ZOOM_SLIDER");

        // Save new choice

        PKVariantUInt32 new_zoom((uint32_t)value);
        this->settings->set(ChordableSettings::ZOOM_UINT32_PROPERTY, &new_zoom);
        this->settings->save();

        // Now get the viewport size
        // in order to calculate the extremes

        int margin = 10;

        PKControl *viewPort  = this->findControl("ID_VECTOR_CONTROL_ROOT");
        PKControl *page      = this->findControl("ID_PAGE_PANEL");
        PKControl *root      = this->findControl("ID_VECTOR_CONTROL_ROOT");

        PKScrollView *scroll = dynamic_cast<PKScrollView *>(this->findControl("ID_SCROLLVIEW"));

        if(viewPort && page && scroll && root)
        {
            // We'll keep this ratio constant
            double ratio = (double) 29.7 / (double) 21;

			// Update the page
			
            int maxWidth  = scroll->getViewportWidth() - 2*margin;
            int minHeight = scroll->getViewportHeight() - 2*margin;
    
            int minWidth  = (int) (minHeight / ratio);
            int maxHeight = (int) (maxWidth  * ratio);

            int newWidth  = minWidth  + (maxWidth  - minWidth)  * value / 100;
            int newHeight = minHeight + (maxHeight - minHeight) * value / 100;
        
			// Now update the page contents
			
			int pageHeight = newHeight - 32; // margins
			int pageWidth  = newWidth  - 32; // margins
			
			int page_margin = (uint32_t)(pageHeight/15.0);
		
			this->setControlHeight("ID_TITLE_EDIT", (uint32_t)(pageHeight/20.0));
			this->setControlHeight("ID_SUBTITLE_EDIT", (uint32_t)(pageHeight/40.0));

			this->setLayoutMargin("ID_PAGE_LAYOUT", page_margin);
			this->setLayoutSpacing("ID_PAGE_LAYOUT", (uint32_t)(pageHeight/120.0));
			this->setControlHeight("ID_SPACER_TOP", (uint32_t)(pageHeight/30.0));
			
			this->setControlHeight("ID_SUBTITLE_EDIT", (uint32_t)(pageHeight/28.0));
			
			this->setControlHeight("ID_SPACER_MIDDLE",  (uint32_t)(pageHeight/60.0));
			this->setControlHeight("ID_SPACER_MIDDLE2", (uint32_t)(pageHeight/60.0));
			this->setControlHeight("ID_CHORDS_SPACER", (uint32_t)(pageHeight/60.0));

			this->setControlHeight("ID_TUNING_IMAGE", (uint32_t)(pageHeight/30.0));
			this->setControlWidth("ID_TUNING_IMAGE", (uint32_t)(pageHeight/30.0));
			this->setControlHeight("ID_TUNING_EDIT", (uint32_t)(pageHeight/37.0));
			this->setControlWidth("ID_TUNING_EDIT", (uint32_t)(pageHeight/4.0));
			this->setControlHeight("ID_TUNING_SUBEDIT", (uint32_t)(pageHeight/50.0));
			this->setControlWidth("ID_TUNING_SUBEDIT", (uint32_t)(pageHeight/4.0));
			
            this->setControlHeight("ID_TEMPO_IMAGE", (uint32_t)(pageHeight/30.0));
			this->setControlWidth("ID_TEMPO_IMAGE", (uint32_t)(pageHeight/30.0));
			this->setControlHeight("ID_TEMPO_EDIT", (uint32_t)(pageHeight/37.0));
			this->setControlWidth("ID_TEMPO_EDIT", (uint32_t)(pageHeight/18.0));

			this->setControlHeight("ID_CAPO_LABEL", (uint32_t)(pageHeight/37.0));
			this->setControlWidth("ID_CAPO_LABEL", (uint32_t)(pageHeight/18.0));

            this->setControlHeight("ID_CAPO_EDIT", (uint32_t)(pageHeight/37.0));
			this->setControlWidth("ID_CAPO_EDIT", (uint32_t)(pageHeight/29.0));
			
			this->setControlWidth("ID_CAPO_SPACER", (uint32_t)(pageHeight/85.0));
			this->setControlWidth("ID_TEMPO_SPACER", (uint32_t)(pageHeight/85.0));
			this->setControlWidth("ID_KEY_SPACER", (uint32_t)(pageHeight/85.0));

			this->setControlHeight("ID_KEY_IMAGE", (uint32_t)(pageHeight/30.0));
			this->setControlWidth("ID_KEY_IMAGE", (uint32_t)(pageHeight/30.0));
			this->setControlHeight("ID_KEY_EDIT", (uint32_t)(pageHeight/37.0));
			this->setControlWidth("ID_KEY_EDIT",  (uint32_t)(pageHeight/18.0));

            // Layout the chord diagrams

            this->setLayoutSpacing("ID_CHORDS_GRID", (uint32_t)(pageHeight/400.0));
			PKGridLayout *chordGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_CHORDS_GRID"));

            if(chordGrid)
            {
				for(uint32_t i=0; i<chordGrid->getChildrenCount(); i++)
				{
					PKVLayout *lay = dynamic_cast<PKVLayout*>(chordGrid->getChildAt(i));

                    if(lay)
                    {
				        for(uint32_t n=0; n<lay->getChildrenCount(); n++)
				        {
						    PKEditableVectorLabel *l = dynamic_cast<PKEditableVectorLabel*>(lay->getChildAt(n));
    						
						    if(l)
						    {
							    l->resize(0, barHeight/4);
						    }

                            PKChordDiagramVectorUI *ui = dynamic_cast<PKChordDiagramVectorUI*>(lay->getChildAt(n));

                            if(ui)
                            {
                                PKVariantUInt32 mh(barHeight);
					            ui->set(PKChordDiagramVectorUI::MINHEIGTH_UINT32_PROPERTY, &mh);
                            }
                        }
                    }
                }
            }

            // Layout the bars
			
            // Uncomment this to place a space between bars
			// this->setLayoutSpacing("ID_BAR_GRID", (uint32_t)(pageHeight/300.0));
			
			PKLayout     *pageLay = dynamic_cast<PKLayout*>(this->findControl("ID_PAGE_LAYOUT"));
			PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
			
			if(barGrid)
			{
                int m = (PKVALUE_INT32(pageLay->get(PKLayout::MARGIN_INT32_PROPERTY)));
				int w = pageWidth - 2*m + 32; // margins
				int s = PKVALUE_INT32(barGrid->get(PKGridLayout::SPACING_INT32_PROPERTY));
				int n = PKVALUE_UINT32(barGrid->get(PKGridLayout::COLS_UINT32_PROPERTY));
				
				if(n > 1)
				{
					int barW = (w-(n-1)*s)/n;

					this->barWidth  = barW;
					this->barHeight = barW*2/3;
					int sph = this->barHeight/6;
					
					for(uint32_t i=0; i<barGrid->getChildrenCount(); i++)
					{
						BarViewVectorControl *bar = dynamic_cast<BarViewVectorControl*>(barGrid->getChildAt(i));
						
						if(bar)
						{
							bar->resize(barWidth, barHeight);
						}

						AddBarsVectorControl *add = dynamic_cast<AddBarsVectorControl*>(barGrid->getChildAt(i));
						
						if(add)
						{
							add->resize(barWidth, barHeight);
						}

						LineBreakVectorControl *lb = dynamic_cast<LineBreakVectorControl *>(barGrid->getChildAt(i));

						if(lb)
						{
							lb->resize(barWidth, barHeight);
						}

						BarHeaderSpacer *sp = dynamic_cast<BarHeaderSpacer *>(barGrid->getChildAt(i));

						if(sp)
						{
							sp->resize(10, sph);
						}
						else 
						{
							PKSpacer *spacer = dynamic_cast<PKSpacer *>(barGrid->getChildAt(i));
							
							if(spacer)
							{
								spacer->resize(barWidth, barHeight);
							}
						}

					}
				}
			}
			
			// Apply all the resizes

            page->resize(newWidth, newHeight);
			
            root->resize(pk_max(newWidth+2*margin, (int32_t) scroll->getViewportWidth()), 
                         newHeight+2*margin);
			
            this->relayoutControl("ID_VECTOR_CONTROL_ROOT");
            scroll->updateScrollbars();
		}
    }
}

void ChordableWindow::windowMoved()
{
    PKDialog::windowMoved();
}

void ChordableWindow::windowResized()
{
    // Call parent
    PKDialog::windowResized();

    if(this->ready)
    {
        // Force an update of the layout
        this->sliderChanged("ID_ZOOM_SLIDER", 0);
    }
}

void ChordableWindow::toolbarItemClicked(PKToolbar *toolbar,
										 PKToolbarItem *item,
										 std::string id)
{
	if(id == "TOOLBAR_ID_NEW")
	{
		this->newDocument();
	}		

	if(id == "TOOLBAR_ID_OPEN")
	{
		this->openDocument();
	}

	if(id == "TOOLBAR_ID_SAVE")
	{
		this->saveCurrentDocument();
	}

    if(id == "TOOLBAR_ID_EXPORT")
    {
        this->exportDocument();
    }

    if(id == "TOOLBAR_ID_OPTIONS")
    {
        ChordablePreferences prefs(L"CHORDABLE_PREFERENCES",
                                   this->getWindowHandle(),
                                   this->settings,
                                   L"ICON");

        std::string loc1 = PKVALUE_STRING(this->settings->get(ChordableSettings::LANGUAGE_STRING_PROPERTY));

        prefs.updateUIStrings();
        prefs.run();

        std::string loc2 = PKVALUE_STRING(this->settings->get(ChordableSettings::LANGUAGE_STRING_PROPERTY));

        if(loc1 != loc2)
        {
            PKi18n::getInstance()->setLocale(loc2);
            this->settings->save();

            int w = this->getWindowWidth();
            int h = this->getWindowHeight();

            this->updateUIStrings();
			app->updateUIStrings();
			
            this->resizeWindowAreaTo(w, h);
        }
    }
}

void ChordableWindow::toolbarSegmentedItemSwitched(PKToolbar *toolbar,
	   				                               PKToolbarSegmentedItem *item,
								                   std::string id, 
                                                   int32_t selection)
{
    if(id == "TOOLBAR_ID_NOTATION")
    {
        // Update the notation

        if(selection == 0)
        {
            this->notation = PKNOTATION_NAMES;
        }
        else if(selection == 1)
        {
            this->notation = PKNOTATION_LETTERS;
        }
        
        // Save the new choice

        PKVariantUInt32 new_notation((uint32_t)this->notation);
        this->settings->set(ChordableSettings::NOTATION_UINT32_PROPERTY, &new_notation);
        this->settings->save();

        // Update the tuning combo & key combo

        this->ignoreTuning = true;

        int32_t key = this->getComboBoxSelectedItem("ID_INSPECTOR_KEY_COMBO");
        this->clearComboBoxItems("ID_INSPECTOR_KEY_COMBO");

        for(uint32_t n = PKNOTE_DO; n<PKNOTE_SI; n++)
        {
            PKNote note;

            note.note   = n;
            note.octave = 0;

            std::wstring noteName = PKNoteGetName(note, this->notation, true);
		    this->addComboBoxItem("ID_INSPECTOR_KEY_COMBO", noteName);
        }

        int32_t sel = this->getComboBoxSelectedItem("ID_TUNING_COMBO");
	    this->clearComboBoxItems("ID_TUNING_COMBO");

	    for(uint32_t i=0; i<this->tunings.size(); i++)
	    {
		    std::wstring tName = this->tunings[i]->getName();

		    tName += L" (";

		    for(uint32_t n=0; n<this->tunings[i]->getNumberOfStrings(); n++)
		    {
			    tName += PKNoteGetName(this->tunings[i]->getNoteForString(n),
								       this->notation, true);  

                if((this->notation == PKNOTATION_NAMES) && 
                   (n != (this->tunings[i]->getNumberOfStrings() - 1)))
                {
                    tName += L" ";
                }
            }

		    tName += L")";

		    this->addComboBoxItem("ID_TUNING_COMBO", tName);
	    }

        this->ignoreTuning = false;
        this->ignoreSetSave = true;

        this->selectComboBoxItem("ID_INSPECTOR_KEY_COMBO", key);
	    this->selectComboBoxItem("ID_TUNING_COMBO", sel);

        // Update the key name on the document

        ChangeKeyCommand ckcmd(this, key, -1);
        ckcmd.doCommand();

        ChangeTuningCommand ctcmd(this, sel, -1, this->notation);
        ctcmd.doCommand();

        this->ignoreSetSave = false;

        // Update the chord names in the bars
        // and in the bar inspector if needed

		PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
        int numBars = grid->getChildrenCount();
		
		for(int32_t i=0; i<numBars; i++)
		{
			PKObject *child = grid->getChildAt(i);
			BarViewVectorControl *bar = dynamic_cast<BarViewVectorControl *>(child);

			if(bar)
			{
				for(uint32_t n=0; n<4; n++)
				{
					PKChordLibraryState *st = bar->getChordLibraryStateForIndex(n);

					if(st)
					{
						bar->setChordNameForIndex(n, this->chordDialog->getChordNameForLibraryState(st, this->notation));
						bar->invalidate();
					}
				}

				if(this->selection.getSize() == 1 && 
				   bar == this->selection.getFirstBar())
				{
					this->updateBarProperties(bar, false);
				}
			}
		}

        // TODO
    }
}

// Drag & Drop

void ChordableWindow::filesDropped(std::vector<std::wstring> files)
{
	if(files.size() > 0)
	{
		this->openDocument(files[0]);
	}
}

// Callbacks

void ChordableWindow::menuItemClicked(PKMenu *fromMenu,
                                      PKMenuItem *item,
                                      std::string id)
{
	// About
	
    if(id == "MENU_ID_ABOUT")
    {
        PKAboutDialog about(L"CHORDABLE_ABOUT_WINDOW",
                            this->getWindowHandle(),
                            PK_i18n(L"Croque-Note"),
                            PK_i18n(L"Version 1.0.0"),
                            PK_i18n(L"Copyright (c) 2010 - Ketchup Apps"),
                            L"ICON", L"res|ABOUT");
        about.run();
    }

	// Edit menu
	// TODO: make that automatic ??
	
    if(id == "MENU_ID_UNDO")
    {
		PKUndoManager::getInstance()->undo();
    }

    if(id == "MENU_ID_REDO")
    {
		PKUndoManager::getInstance()->redo();
    }

	if(id == "MENU_ID_CUT")
    {
        this->doCut();
    }

    if(id == "MENU_ID_COPY")
    {
        this->doCopy();
    }

    if(id == "MENU_ID_PASTE")
    {
        this->doPaste();
    }

    if(id == "MENU_ID_SELECT_ALL")
    {
        this->doSelectAll();
    }
	
	// File menu

	if(id == "MENU_ID_NEW")
	{
		this->newDocument();
	}

	if(id == "MENU_ID_OPEN")
	{
		this->openDocument();
	}

	if(id == "MENU_ID_SAVE")
	{
		this->saveCurrentDocument();
	}

    if(id == "MENU_ID_EXPORT")
    {
        this->exportDocument();
    }
	
    if(id == "MENU_ID_OPTIONS")
    {
        ChordablePreferences prefs(L"CHORDABLE_PREFERENCES",
                                   this->getWindowHandle(),
                                   this->settings,
                                   L"ICON");

        std::string loc1 = PKVALUE_STRING(this->settings->get(ChordableSettings::LANGUAGE_STRING_PROPERTY));

        prefs.updateUIStrings();
        prefs.run();

        std::string loc2 = PKVALUE_STRING(this->settings->get(ChordableSettings::LANGUAGE_STRING_PROPERTY));

        if(loc1 != loc2)
        {
            PKi18n::getInstance()->setLocale(loc2);
            this->settings->save();

            int w = this->getWindowWidth();
            int h = this->getWindowHeight();

            this->updateUIStrings();
            this->resizeWindowAreaTo(w, h);
        }
    }

    if(id == "MENU_ID_QUIT")
    {
        // Check if we need to save first

        if(this->currentDocument && this->needsSave)
	    {
		    // Ask for confirmation
    		
		    PKStdDialog dialog(L"CHORDABLE_QUIT_CONFIRM_DIALOG",
						       PK_STD_DIALOG_YES_NO_CANCEL,
						       this->getWindowHandle(),
						       PK_i18n(L"Croque-Note: Quit"),
						       L"ICON");
    		
		    PKVariantWString header(L"");
		    dialog.set(PKStdDialog::HEADER_WSTRING_PROPERTY, &header);
    		
		    PKVariantWString text(PK_i18n(L"There are unsaved changes in the current document. Do you want to save these changes before exiting?"));
		    dialog.set(PKStdDialog::TEXT_WSTRING_PROPERTY, &text);

		    PKVariantWString icon(PK_i18n(L"res|INFO"));
		    dialog.set(PKStdDialog::ICON_WSTRING_PROPERTY, &icon);

            dialog.updateUIStrings();
		    int32_t result = dialog.run();
    		
		    if(result == PK_STD_BUTTON_CANCEL)
		    {
			    // Abort
			    return;
		    }		
    		
		    if(result == PK_STD_BUTTON_YES)
		    {
			    if(!this->saveCurrentDocument())
                {
                    // Cancelled
                    return;
                }
		    }
	    }

        // Save window position

        int x = this->getWindowX();
        int y = this->getWindowY();
        int w = this->getWindowWidth();
        int h = this->getWindowHeight();

        PKVariantInt32 new_w(w);
        PKVariantInt32 new_h(h);

        this->settings->set(ChordableSettings::WINDOW_W_INT32_PROPERTY, &new_w);
        this->settings->set(ChordableSettings::WINDOW_H_INT32_PROPERTY, &new_h);

        PKVariantInt32 new_x(x);
        PKVariantInt32 new_y(y);

        this->settings->set(ChordableSettings::WINDOW_X_INT32_PROPERTY, &new_x);
        this->settings->set(ChordableSettings::WINDOW_Y_INT32_PROPERTY, &new_y);

        this->settings->save();

        // Let's quit
        app->quit();
    }

	// Recent files

	if(id.size() > 16 && id.substr(0, 16) == "ID_RECENT_FILES_")
	{
		std::string numStr = id.substr(16);
		uint32_t    num    = PKStr::stringToUInt32(numStr);

		if(num > 0)
		{
			std::wstring fileName = this->settings->getRecentFileAt(num-1);
			this->openDocument(fileName);
		}
	}
}

void ChordableWindow::editableVectorLabelTextChanged(std::string id)
{
    if(this->ready)
    {
		// Kind of a hack but oh well
	    this->editTextChanged(id, L"");
	}		
}

void ChordableWindow::editableVectorLabelEditEnded(std::string id, 
									               std::wstring oldValue, 
        							               std::wstring newValue)
{
	// We use this signal to add undoable commands
	// for actions involving a vector edit control as to
	// allow undo, but aggregate multiple keystrokes nicely

	if(id == "ID_TITLE_EDIT")
	{
		GenericVectorEditChangeCommand *cmd = new GenericVectorEditChangeCommand(this, id, PK_i18n(L"Change Title"), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}

	if(id == "ID_SUBTITLE_EDIT")
	{
		GenericVectorEditChangeCommand *cmd = new GenericVectorEditChangeCommand(this, id, PK_i18n(L"Change Subtitle"), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}

	if(id == "ID_TEMPO_EDIT")
	{
		GenericVectorEditChangeCommand *cmd = new GenericVectorEditChangeCommand(this, id, PK_i18n(L"Change Tempo"), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}

	if(id == "ID_CAPO_EDIT")
	{
		GenericVectorEditChangeCommand *cmd = new GenericVectorEditChangeCommand(this, id, PK_i18n(L"Change Capo"), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}
}

void ChordableWindow::selectorControlChanged(std::string id, int32_t oldValue)
{
    if(id == "ID_BAR_TYPE_SELECTOR")
    {
		int32_t newValue = this->getSelectorControlSelection(id);
		ChangeBarTypeCommand *cmd = new ChangeBarTypeCommand(this, this->selection.getFirstBar(), newValue, oldValue);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
    }
}

void ChordableWindow::editableVectorLabelEditStarted(std::string id)
{
    this->setArrowTabControlTab("ID_ICON_TAB", 0); // Document properties tab
}

void ChordableWindow::buttonClicked(std::string id)
{
    if((id == "ID_CHORD_BUTTON_1") ||
       (id == "ID_CHORD_BUTTON_2") ||
       (id == "ID_CHORD_BUTTON_3") ||
       (id == "ID_CHORD_BUTTON_4"))
    {
		if(this->chordDialog && this->selection.getSize() == 1)
        {
            // Setup chord dialog

			int32_t _index = 0;

			if(id == "ID_CHORD_BUTTON_2")
			{
				_index = 1;
			}

			if(id == "ID_CHORD_BUTTON_3")
			{
				_index = 2;
			}

			if(id == "ID_CHORD_BUTTON_4")
			{
				_index = 3;
			}

            // Select the right tuning

            int sel = this->getComboBoxSelectedItem("ID_TUNING_COMBO");
            this->chordDialog->selectTuningAtIndex(sel);

            // Update the notation on the chords picker
            this->chordDialog->setNotation(this->notation);

			// Select the right chord

			if(this->selection.getFirstBar()->getChordNameForIndex(_index) == L"")
			{
				this->chordDialog->reset();
			}
			else
			{
				// Make the chord dialog match
				// the current assigned chord...

				this->chordDialog->matchChordStateAndDiagram(this->selection.getFirstBar()->getChordDiagramForIndex(_index),
															 this->selection.getFirstBar()->getChordLibraryStateForIndex(_index));
			}

            // Let the user pick a chord
            this->chordDialog->updateUIStrings();
            int32_t result = this->chordDialog->run();

            // See what we got

            if(result == PK_STD_BUTTON_OK)
            {
                // Update current selected bar with chord

				PKChordDiagram *diagram = this->chordDialog->getSelectedChordDiagram();
				PKChordLibraryState *st = this->chordDialog->getCurrentLibraryState();
				std::wstring    name    = this->chordDialog->getChordNameForLibraryState(st, this->notation);

				int32_t index = 0;

				if(id == "ID_CHORD_BUTTON_1")
				{
					index = 0;
					this->setLabelText("ID_BAR_CHORD_1", name);
					this->setButtonText("ID_CHORD_BUTTON_1", PK_i18n(L"Change..."));
				}

				if(id == "ID_CHORD_BUTTON_2")
				{
					index = 1;
					this->setLabelText("ID_BAR_CHORD_2", name);
					this->setButtonText("ID_CHORD_BUTTON_2", PK_i18n(L"Change..."));
				}

				if(id == "ID_CHORD_BUTTON_3")
				{
					index = 2;
					this->setLabelText("ID_BAR_CHORD_3", name);
					this->setButtonText("ID_CHORD_BUTTON_3", PK_i18n(L"Change..."));
				}

				if(id == "ID_CHORD_BUTTON_4")
				{
					index = 3;
					this->setLabelText("ID_BAR_CHORD_4", name);
					this->setButtonText("ID_CHORD_BUTTON_4", PK_i18n(L"Change..."));
				}

				this->selection.getFirstBar()->setChordNameForIndex(index, name);
				this->selection.getFirstBar()->setChordLibraryStateForIndex(index, st);
				this->selection.getFirstBar()->setChordDiagramForIndex(index, diagram);

				this->selection.getFirstBar()->invalidate();

                // See if we need to update the chords diagram grid layout
                this->refreshChordsGrid();

                // And finally update the display & cleanup
                this->relayoutControl("ID_VECTOR_CONTROL_ROOT");
                this->invalidateControl("ID_VECTOR_CONTROL_ROOT");

                if(diagram) delete diagram;
				if(st) delete st;

				this->setNeedsSave();
			}
        }
    }
}

void ChordableWindow::toggleOverheadSpaceForBar(BarViewVectorControl *bar, bool onOff)
{
	if(bar == NULL)
	{
		return;
	}

	PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

	if(grid == NULL)
	{
		return;
	}

	uint32_t numBars = PKVALUE_UINT32(grid->get(PKGridLayout::COLS_UINT32_PROPERTY));
	int32_t  barCol  = grid->getColForChild(bar);		
	int32_t  barRow  = grid->getRowForChild(bar);
	int32_t  spacerh = bar->getH() / 6;

	if(onOff)
	{
		// Look at the row and see if there is 
		// already space allocated for headers

		bool found = false;

		for(uint32_t i=0; i<numBars; i++)
		{
			if(i != barCol)
			{
				PKObject *child = grid->getChildAtRowAndCol(barRow, i);
			
				if(child)
				{
					BarViewVectorControl *b = dynamic_cast<BarViewVectorControl *>(child);

					if(b)
					{
						bool hasSectionMarker = PKVALUE_BOOL(b->get(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY));
						bool hasHeader        = (PKVALUE_WSTRING(b->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY)) != L"");

						if(hasSectionMarker || hasHeader)
						{
							found = true;
							break;
						}
					}
				}
			}
		}

		if(found)
		{
			// Nothing to do
			return;
		}

		// Else we need to add a new row

		int offset = barRow*numBars;
		
		for(uint32_t i=0; i<numBars; i++)
		{
			BarHeaderSpacer *spacer = new BarHeaderSpacer();

			PKVariantInt32 ly(1);
			spacer->set(PKControl::LAYOUTY_INT32_PROPERTY, &ly);

			PKVariantRect fr(0, 0, 0, spacerh);
			spacer->set(PKControl::FRAME_RECT_PROPERTY, &fr);

			grid->insertChildAt(offset, spacer);
			spacer->build();
			spacer->initialize(this);
		}
	}
	else
	{
		// Look at the row and see if there 
		// are other bars that need the space

		bool found = false;

		for(uint32_t i=0; i<numBars; i++)
		{
			if(i != barCol)
			{
				PKObject *child = grid->getChildAtRowAndCol(barRow, i);
			
				if(child)
				{
					BarViewVectorControl *b = dynamic_cast<BarViewVectorControl *>(child);

					if(b)
					{
						bool hasSectionMarker = PKVALUE_BOOL(b->get(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY));
						bool hasHeader        = (PKVALUE_WSTRING(b->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY)) != L"");

						if(hasSectionMarker || hasHeader)
						{
							found = true;
							break;
						}
					}
				}
			}
		}

		if(found)
		{
			// Nothing to do
			return;
		}

		// Else we need to remove the whole row of spacers above

		if(barRow > 0)
		{
			int offset = (barRow-1)*numBars;
			
			for(uint32_t i=0; i<numBars; i++)
			{
				PKObject *child = grid->getChildAt(offset);
				grid->removeChild(child);
				child->release();
			}
		}
	}
}

void ChordableWindow::removeLineBreak(LineBreakVectorControl *lbreak)
{
	if(lbreak != NULL)
	{
		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
		PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

		if(barGrid != NULL && rootControl != NULL)
		{
			uint32_t numBars = PKVALUE_UINT32(barGrid->get(PKGridLayout::COLS_UINT32_PROPERTY));

			int32_t row = barGrid->getRowForChild(lbreak);
			int32_t col = barGrid->getColForChild(lbreak);

			// Remove the line break, and all the spacers after it

			barGrid->removeChild(lbreak);
			lbreak->release();

			for(uint32_t i=col; i<numBars; i++)
			{
				PKObject *child  = barGrid->getChildAtRowAndCol(row, col);
				PKSpacer *spacer = dynamic_cast<PKSpacer*>(child);

				if(spacer != NULL)
				{
					barGrid->removeChild(spacer);
					spacer->release();
				}
				else
				{
					break;
				}
			}
		}
	}
}

void ChordableWindowFindAllLineBreaks(PKObject *child, void *context)
{	
	LineBreakVectorControl *lb = dynamic_cast<LineBreakVectorControl*>(child);
	std::vector<LineBreakVectorControl *> *lineBreaks = (std::vector<LineBreakVectorControl *> *)context;

	if(lb != NULL && lineBreaks != NULL)
	{
		lineBreaks->push_back(lb);
	}
}

void ChordableWindow::removeAllLineBreaksSpacers()
{
	PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

	if(barGrid)
	{
		int32_t i=0;

		while(true)
		{
			if(i >= (int32_t)barGrid->getChildrenCount())
			{
				break;
			}

			PKObject *child = barGrid->getChildAt(i);

			PKSpacer *spacer = dynamic_cast<PKSpacer *>(child);
			BarHeaderSpacer *header = dynamic_cast<BarHeaderSpacer *>(child);

			if(spacer != NULL && header == NULL)
			{
				// Remove it
				barGrid->removeChild(child);
				spacer->release();
			}
			else
			{
				// Keep going
				i++;
			}
		}
	}
}

void ChordableWindow::checkLineBreaksLayout()
{
	PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

	if(barGrid)
	{
		uint32_t numBars = PKVALUE_UINT32(barGrid->get(PKGridLayout::COLS_UINT32_PROPERTY));

		// Gather all line breaks
		std::vector<LineBreakVectorControl *> lineBreaks;
		barGrid->walkChildren(ChordableWindowFindAllLineBreaks, (void *) &lineBreaks);

		// Now go through them and check layout
		for(uint32_t i=0; i<lineBreaks.size(); i++)
		{
			int32_t row = barGrid->getRowForChild(lineBreaks[i]);
			int32_t col = barGrid->getColForChild(lineBreaks[i]);

			int32_t count = 0;

			for(uint32_t n=col+1; n<numBars; n++)
			{
				PKObject *child  = barGrid->getChildAtRowAndCol(row, col);
				PKSpacer *spacer = dynamic_cast<PKSpacer*>(child);

				if(spacer != NULL)
				{
					count++;
				}
				else
				{
					break;
				}
			}

			// Add spacers if any are missing

			if(count < (int32_t)(numBars - col - 1))
			{
				int32_t diff = (numBars - col - 1) - count;

				for(int32_t k=0; k<diff; k++)
				{
					PKSpacer *spacer = new PKSpacer();

			        PKVariantInt32 layoutx(1);
			        spacer->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
			        PKVariantInt32 layouty(1);
			        spacer->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

			        spacer->resize(this->barWidth, this->barHeight);

					barGrid->insertNewChildAt(col+1, row, spacer);

					spacer->build();
					spacer->initialize(this);
				}
			}
		}
	}
}

void ChordableWindow::removeAllOverheadSpacers()
{
	PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

	if(barGrid)
	{
		int32_t i=0;

		while(true)
		{
			if(i >= (int32_t)barGrid->getChildrenCount())
			{
				break;
			}

			PKObject *child = barGrid->getChildAt(i);

			BarHeaderSpacer *header = dynamic_cast<BarHeaderSpacer *>(child);

			if(header != NULL)
			{
				// Remove it
				barGrid->removeChild(child);
				header->release();
			}
			else
			{
				// Keep going
				i++;
			}
		}
	}
}

void ChordableWindow::addOverheadSpacersWhereNeeded()
{
	PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

	if(barGrid)
	{
		uint32_t numBars = PKVALUE_UINT32(barGrid->get(PKGridLayout::COLS_UINT32_PROPERTY));

		std::vector<BarViewVectorControl *> bars_to_toggle;

		int skipRow = -1;

		for(uint32_t i=0; i<barGrid->getChildrenCount(); i++)
		{
			BarViewVectorControl *bar = dynamic_cast<BarViewVectorControl *>(barGrid->getChildAt(i));

			if(bar != NULL)
			{
				int32_t row = barGrid->getRowForChild(bar);

				if(row != skipRow)
				{
					std::wstring header = PKVALUE_WSTRING(bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));
					bool sectionHeader  = PKVALUE_BOOL(bar->get(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY));

					if(sectionHeader || (header != L""))
					{
						bars_to_toggle.push_back(bar);
						skipRow = row;
					}
				}
			}
		}

		// Now toggle for all these

		for(uint32_t n=0; n<bars_to_toggle.size(); n++)
		{
			this->toggleOverheadSpaceForBar(bars_to_toggle[n], true);
		}
	}
}

void ChordableWindow::addChordToChordsGrid(PKChordDiagram *diagram, 
                                           std::wstring name, 
                                           BarViewVectorControl *forBar)
{
    if(diagram == NULL)
    {
        return;
    }

    PKGridLayout *bars   = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
    PKGridLayout *chords = dynamic_cast<PKGridLayout*>(this->findControl("ID_CHORDS_GRID"));

    if(chords && bars)
    {
        bool found = false;

        // Look if we already have this exact chord diagram in the grid

        for(uint32_t i=0; i<bars->getChildrenCount(); i++)
        {
            BarViewVectorControl *bar = dynamic_cast<BarViewVectorControl*>(bars->getChildAt(i));

            if(bar && (bar != forBar))
            {
                if(PKChordDiagramEquivalent(bar->getChordDiagramForIndex(0), diagram) ||
                   PKChordDiagramEquivalent(bar->getChordDiagramForIndex(1), diagram) ||
                   PKChordDiagramEquivalent(bar->getChordDiagramForIndex(2), diagram) ||
                   PKChordDiagramEquivalent(bar->getChordDiagramForIndex(3), diagram))
                {
                    found = true;
                    break;
                }
            }
        }

        if(!found)
        {
            bool hidden = chords->getHidden();
		    PKVariantBool h(hidden);
		    PKVariantBool shared(true);

            // Make a copy
            PKChordDiagram *new_diagram = new PKChordDiagram(diagram);


            // First create a vertical layout
            PKVLayout *layout = new PKVLayout();
            layout->set(PKControl::HIDDEN_BOOL_PROPERTY, &h);

            PKVariantInt32 margin(0);
            layout->set(PKVLayout::MARGIN_INT32_PROPERTY, &margin);

            PKVariantInt32 spacing(0);
            layout->set(PKVLayout::SPACING_INT32_PROPERTY, &spacing);

            // And a label
            PKEditableVectorLabel *label = new PKEditableVectorLabel();

            PKVariantWString text(name);
            label->set(PKEditableVectorLabel::TEXT_WSTRING_PROPERTY, &text);

            PKVariantBool bold(true);
            label->set(PKEditableVectorLabel::BOLD_BOOL_PROPERTY, &bold);

            PKVariantBool editable(false);
            label->set(PKEditableVectorLabel::EDITABLE_BOOL_PROPERTY, &editable);

            PKVariantBool center(true);
            label->set(PKEditableVectorLabel::CENTER_BOOL_PROPERTY, &center);

            label->set(PKControl::HIDDEN_BOOL_PROPERTY, &h);
		    label->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

            PKVariantColor border(0, 0, 0, 0);
            label->set(PKEditableVectorLabel::BORDER_COLOR_COLOR_PROPERTY, &border);

            PKVariantInt32 lay_x(2);
            label->set(PKControl::LAYOUTX_INT32_PROPERTY, &lay_x);

            PKVariantInt32 lay_y(1);
            label->set(PKControl::LAYOUTY_INT32_PROPERTY, &lay_y);

            PKVariantRect frame(0, 0, 0, this->barHeight/4);
            label->set(PKControl::FRAME_RECT_PROPERTY, &frame);

            layout->addChild(label);

            // Then a diagram UI
            PKChordDiagramVectorUI *ui = new PKChordDiagramVectorUI();

		    ui->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);
            ui->set(PKControl::HIDDEN_BOOL_PROPERTY, &h);

            PKVariantUInt32 mh(barHeight);
		    ui->set(PKChordDiagramVectorUI::MINHEIGTH_UINT32_PROPERTY, &mh);

		    ui->setChordDiagram(new_diagram);
		    layout->addChild(ui);

            chords->addChild(layout);

            layout->build();
            label->build();
		    ui->build();

            layout->initialize(this);
            label->initialize(this);
		    ui->initialize(this);
        }
    }
}

void ChordableWindow::refreshChordsGrid()
{
    // First clear up all the diagrams

    PKGridLayout *bars   = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
    PKGridLayout *chords = dynamic_cast<PKGridLayout*>(this->findControl("ID_CHORDS_GRID"));

    if(chords && bars)
    {
        // Clear all
        chords->deleteAllChildControls();
        chords->clearChildren();

        // Now go through our bar list and add them all

        for(uint32_t i=0; i<bars->getChildrenCount(); i++)
        {
            BarViewVectorControl *bar = dynamic_cast<BarViewVectorControl*>(bars->getChildAt(i));

            if(bar)
            {
                this->addChordToChordsGrid(bar->getChordDiagramForIndex(0),
                                           bar->getChordNameForIndex(0), bar);
                this->addChordToChordsGrid(bar->getChordDiagramForIndex(1),
                                           bar->getChordNameForIndex(1), bar);
                this->addChordToChordsGrid(bar->getChordDiagramForIndex(2),
                                           bar->getChordNameForIndex(2), bar);
                this->addChordToChordsGrid(bar->getChordDiagramForIndex(3),
                                           bar->getChordNameForIndex(3), bar);
            }
        }

        // And finally update the display
        this->relayoutControl("ID_VECTOR_CONTROL_ROOT");
        this->invalidateControl("ID_VECTOR_CONTROL_ROOT");
    }
}

void ChordableWindow::updateBarProperties(BarViewVectorControl *bar, bool updateSelector)
{
    this->enableControl("ID_BAR_TYPE_SELECTOR");

    this->enableControl("ID_BAR_LABEL_1");
    this->enableControl("ID_BAR_LABEL_2");
    this->enableControl("ID_BAR_LABEL_3");
	this->enableControl("ID_BAR_LABEL_4");

    this->enableControl("ID_BAR_CHORD_1");
    this->enableControl("ID_BAR_CHORD_2");
    this->enableControl("ID_BAR_CHORD_3");
    this->enableControl("ID_BAR_CHORD_4");

    this->enableControl("ID_CHORD_BUTTON_1");
    this->enableControl("ID_CHORD_BUTTON_2");
    this->enableControl("ID_CHORD_BUTTON_3");
    this->enableControl("ID_CHORD_BUTTON_4");

    // Update the bar type selector

    uint8_t barType = PKVALUE_UINT8(bar->get(BarViewVectorControl::BARTYPE_UINT8_PROPERTY));

    if(updateSelector)
    {
        this->setSelectorControlSelection("ID_BAR_TYPE_SELECTOR", barType);
    }

    // Update the images and chord chooser buttons

    switch(barType)
    {
    case BAR_TYPE_SINGLE:
        {
            this->setControlHidden("ID_BAR_LAYOUT_1", false);
            this->setControlHidden("ID_BAR_IMAGE_1", false);
            this->setControlHidden("ID_BAR_CHORD_1", false);
            this->setControlHidden("ID_CHORD_BUTTON_1", false);

            this->loadImageFromResource("ID_BAR_IMAGE_1", L"CHORD_1BAR");

            this->setControlHidden("ID_BAR_LAYOUT_2", true);
            this->setControlHidden("ID_BAR_LAYOUT_3", true);
            this->setControlHidden("ID_BAR_LAYOUT_4", true);

            this->setControlHidden("ID_BAR_IMAGE_2", true);
            this->setControlHidden("ID_BAR_CHORD_2", true);
            this->setControlHidden("ID_CHORD_BUTTON_2", true);
            this->setControlHidden("ID_BAR_IMAGE_3", true);
            this->setControlHidden("ID_BAR_CHORD_3", true);
            this->setControlHidden("ID_CHORD_BUTTON_3", true);
            this->setControlHidden("ID_BAR_IMAGE_4", true);
            this->setControlHidden("ID_BAR_CHORD_4", true);
            this->setControlHidden("ID_CHORD_BUTTON_4", true);
        }
        break;
    case BAR_TYPE_DOUBLE:
        {
            this->setControlHidden("ID_BAR_LAYOUT_1", false);
            this->setControlHidden("ID_BAR_IMAGE_1", false);
            this->setControlHidden("ID_BAR_CHORD_1", false);
            this->setControlHidden("ID_CHORD_BUTTON_1", false);

            this->setControlHidden("ID_BAR_LAYOUT_2", false);
            this->setControlHidden("ID_BAR_IMAGE_2", false);
            this->setControlHidden("ID_BAR_CHORD_2", false);
            this->setControlHidden("ID_CHORD_BUTTON_2", false);

            this->loadImageFromResource("ID_BAR_IMAGE_1", L"CHORD_2BARS_1");
            this->loadImageFromResource("ID_BAR_IMAGE_2", L"CHORD_2BARS_2");

            this->setControlHidden("ID_BAR_LAYOUT_3", true);
            this->setControlHidden("ID_BAR_LAYOUT_4", true);

            this->setControlHidden("ID_BAR_IMAGE_3", true);
            this->setControlHidden("ID_BAR_CHORD_3", true);
            this->setControlHidden("ID_CHORD_BUTTON_3", true);
            this->setControlHidden("ID_BAR_IMAGE_4", true);
            this->setControlHidden("ID_BAR_CHORD_4", true);
            this->setControlHidden("ID_CHORD_BUTTON_4", true);
        }
        break;
    case BAR_TYPE_TRIPLE1:
        {
            this->setControlHidden("ID_BAR_LAYOUT_1", false);
            this->setControlHidden("ID_BAR_IMAGE_1", false);
            this->setControlHidden("ID_BAR_CHORD_1", false);
            this->setControlHidden("ID_CHORD_BUTTON_1", false);

            this->setControlHidden("ID_BAR_LAYOUT_2", false);
            this->setControlHidden("ID_BAR_IMAGE_2", false);
            this->setControlHidden("ID_BAR_CHORD_2", false);
            this->setControlHidden("ID_CHORD_BUTTON_2", false);

            this->setControlHidden("ID_BAR_LAYOUT_3", false);
            this->setControlHidden("ID_BAR_IMAGE_3", false);
            this->setControlHidden("ID_BAR_CHORD_3", false);
            this->setControlHidden("ID_CHORD_BUTTON_3", false);

            this->loadImageFromResource("ID_BAR_IMAGE_1", L"CHORD_3BARS1_1");
            this->loadImageFromResource("ID_BAR_IMAGE_2", L"CHORD_3BARS1_2");
            this->loadImageFromResource("ID_BAR_IMAGE_3", L"CHORD_3BARS1_3");

            this->setControlHidden("ID_BAR_LAYOUT_4", true);
            this->setControlHidden("ID_BAR_IMAGE_4", true);
            this->setControlHidden("ID_BAR_CHORD_4", true);
            this->setControlHidden("ID_CHORD_BUTTON_4", true);
        }
        break;
    case BAR_TYPE_TRIPLE2:
        {
            this->setControlHidden("ID_BAR_LAYOUT_1", false);
            this->setControlHidden("ID_BAR_IMAGE_1", false);
            this->setControlHidden("ID_BAR_CHORD_1", false);
            this->setControlHidden("ID_CHORD_BUTTON_1", false);

            this->setControlHidden("ID_BAR_LAYOUT_2", false);
            this->setControlHidden("ID_BAR_IMAGE_2", false);
            this->setControlHidden("ID_BAR_CHORD_2", false);
            this->setControlHidden("ID_CHORD_BUTTON_2", false);

            this->setControlHidden("ID_BAR_LAYOUT_3", false);
            this->setControlHidden("ID_BAR_IMAGE_3", false);
            this->setControlHidden("ID_BAR_CHORD_3", false);
            this->setControlHidden("ID_CHORD_BUTTON_3", false);

            this->loadImageFromResource("ID_BAR_IMAGE_1", L"CHORD_3BARS2_1");
            this->loadImageFromResource("ID_BAR_IMAGE_2", L"CHORD_3BARS2_2");
            this->loadImageFromResource("ID_BAR_IMAGE_3", L"CHORD_3BARS2_3");

            this->setControlHidden("ID_BAR_LAYOUT_4", true);
            this->setControlHidden("ID_BAR_IMAGE_4", true);
            this->setControlHidden("ID_BAR_CHORD_4", true);
            this->setControlHidden("ID_CHORD_BUTTON_4", true);
        }
        break;
    case BAR_TYPE_QUAD:
    default:
        {
            this->setControlHidden("ID_BAR_LAYOUT_1", false);
            this->setControlHidden("ID_BAR_IMAGE_1", false);
            this->setControlHidden("ID_BAR_CHORD_1", false);
            this->setControlHidden("ID_CHORD_BUTTON_1", false);

            this->setControlHidden("ID_BAR_LAYOUT_2", false);
            this->setControlHidden("ID_BAR_IMAGE_2", false);
            this->setControlHidden("ID_BAR_CHORD_2", false);
            this->setControlHidden("ID_CHORD_BUTTON_2", false);

            this->setControlHidden("ID_BAR_LAYOUT_3", false);
            this->setControlHidden("ID_BAR_IMAGE_3", false);
            this->setControlHidden("ID_BAR_CHORD_3", false);
            this->setControlHidden("ID_CHORD_BUTTON_3", false);

            this->setControlHidden("ID_BAR_LAYOUT_4", false);
            this->setControlHidden("ID_BAR_IMAGE_4", false);
            this->setControlHidden("ID_BAR_CHORD_4", false);
            this->setControlHidden("ID_CHORD_BUTTON_4", false);

            this->loadImageFromResource("ID_BAR_IMAGE_1", L"CHORD_4BARS_1");
            this->loadImageFromResource("ID_BAR_IMAGE_2", L"CHORD_4BARS_2");
            this->loadImageFromResource("ID_BAR_IMAGE_3", L"CHORD_4BARS_3");
            this->loadImageFromResource("ID_BAR_IMAGE_4", L"CHORD_4BARS_4");
        }
        break;
    }

	if(bar->getChordNameForIndex(0) != L"")
	{
		this->setLabelText("ID_BAR_CHORD_1", bar->getChordNameForIndex(0));
		this->setButtonText("ID_CHORD_BUTTON_1", PK_i18n(L"Change..."));
	}
	else
	{
		this->setLabelText("ID_BAR_CHORD_1", PK_i18n(L"Not Selected"));
		this->setButtonText("ID_CHORD_BUTTON_1", PK_i18n(L"Select..."));
	}

	if(bar->getChordNameForIndex(1) != L"")
	{
    	this->setLabelText("ID_BAR_CHORD_2", bar->getChordNameForIndex(1));
		this->setButtonText("ID_CHORD_BUTTON_2", PK_i18n(L"Change..."));
	}
	else
	{
		this->setLabelText("ID_BAR_CHORD_2", PK_i18n(L"Not Selected"));
		this->setButtonText("ID_CHORD_BUTTON_2", PK_i18n(L"Select..."));
	}

	if(bar->getChordNameForIndex(2) != L"")
	{
		this->setLabelText("ID_BAR_CHORD_3", bar->getChordNameForIndex(2));
		this->setButtonText("ID_CHORD_BUTTON_3", PK_i18n(L"Change..."));
	}
	else
	{
		this->setLabelText("ID_BAR_CHORD_3", PK_i18n(L"Not Selected"));
		this->setButtonText("ID_CHORD_BUTTON_3", PK_i18n(L"Select..."));
	}

	if(bar->getChordNameForIndex(3) != L"")
	{
		this->setLabelText("ID_BAR_CHORD_4", bar->getChordNameForIndex(3));
		this->setButtonText("ID_CHORD_BUTTON_4", PK_i18n(L"Change..."));
	}
	else
	{
		this->setLabelText("ID_BAR_CHORD_4", PK_i18n(L"Not Selected"));
		this->setButtonText("ID_CHORD_BUTTON_4", PK_i18n(L"Select..."));
	}

	// Update the markups and headers
	
	this->enableControl("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON");
	this->enableControl("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON");
	this->enableControl("ID_BAR_SECTION_MARKUP_CHECK");
	this->enableControl("ID_BAR_SECTION_NUMBER_EDIT");
	this->enableControl("ID_BAR_SECTION_ARROWS");
	this->enableControl("ID_BAR_HEADER_EDIT");

	PKVariant *repeatLeft = bar->get(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY);
	bool rl = PKVALUE_BOOL(repeatLeft);
	this->setBitmapToggleButtonToggled("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON", rl);

	PKVariant *repeatRight = bar->get(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY);
	bool rr = PKVALUE_BOOL(repeatRight);
	this->setBitmapToggleButtonToggled("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON", rr);

	PKVariant *section = bar->get(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY);
	bool hasSectionMarker = PKVALUE_BOOL(section);
	this->setCheckBoxChecked("ID_BAR_SECTION_MARKUP_CHECK", hasSectionMarker);

	this->setControlEnabled("ID_BAR_SECTION_NUMBER_EDIT", hasSectionMarker);
	this->setControlEnabled("ID_BAR_SECTION_ARROWS", hasSectionMarker);

	PKVariant *numv = bar->get(BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY);
	uint32_t   num  = PKVALUE_UINT32(numv);
	this->setEditText("ID_BAR_SECTION_NUMBER_EDIT", PKStr::uint32ToWstring(num));

	PKVariant *hv = bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY);
	std::wstring header  = PKVALUE_WSTRING(hv);
	this->setEditText("ID_BAR_HEADER_EDIT", header);	

	this->relayoutControl("ID_ICON_TAB");
    this->setArrowTabControlTab("ID_ICON_TAB", 1); // Bar properties tab
}       


void ChordableWindow::disableBarProperties()
{
    // Cleanup bar properties panel

    this->setControlHidden("ID_BAR_LAYOUT_1", false);
    this->setControlHidden("ID_BAR_IMAGE_1", false);
    this->setControlHidden("ID_BAR_CHORD_1", false);
    this->setControlHidden("ID_CHORD_BUTTON_1", false);

    this->loadImageFromResource("ID_BAR_IMAGE_1", L"CHORD_1BAR_DISABLED");

    this->setControlHidden("ID_BAR_LAYOUT_2", true);
    this->setControlHidden("ID_BAR_LAYOUT_3", true);
    this->setControlHidden("ID_BAR_LAYOUT_4", true);

    this->setControlHidden("ID_BAR_IMAGE_2", true);
    this->setControlHidden("ID_BAR_CHORD_2", true);
    this->setControlHidden("ID_CHORD_BUTTON_2", true);
    this->setControlHidden("ID_BAR_IMAGE_3", true);
    this->setControlHidden("ID_BAR_CHORD_3", true);
    this->setControlHidden("ID_CHORD_BUTTON_3", true);
    this->setControlHidden("ID_BAR_IMAGE_4", true);
    this->setControlHidden("ID_BAR_CHORD_4", true);
    this->setControlHidden("ID_CHORD_BUTTON_4", true);

	bool rl = false;
	this->setBitmapToggleButtonToggled("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON", rl);
	
	bool rr = false;
	this->setBitmapToggleButtonToggled("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON", rr);
	
	bool hasSectionMarker = false;
	this->setCheckBoxChecked("ID_BAR_SECTION_MARKUP_CHECK", hasSectionMarker);
	
	uint32_t   num  = 1;
	this->setEditText("ID_BAR_SECTION_NUMBER_EDIT", PKStr::uint32ToWstring(num));
	
	std::wstring header  = L"";
	this->setEditText("ID_BAR_HEADER_EDIT", header);	

    // Disable bar properties panel

    this->disableControl("ID_BAR_TYPE_SELECTOR");

    this->disableControl("ID_BAR_LABEL_1");
    this->disableControl("ID_BAR_LABEL_2");
    this->disableControl("ID_BAR_LABEL_3");
    this->disableControl("ID_BAR_LABEL_4");

    this->setLabelText("ID_BAR_CHORD_1", PK_i18n(L"Not Selected"));

    this->disableControl("ID_BAR_CHORD_1");
    this->disableControl("ID_BAR_CHORD_2");
    this->disableControl("ID_BAR_CHORD_3");
    this->disableControl("ID_BAR_CHORD_4");

    this->disableControl("ID_CHORD_BUTTON_1");
    this->disableControl("ID_CHORD_BUTTON_2");
    this->disableControl("ID_CHORD_BUTTON_3");
    this->disableControl("ID_CHORD_BUTTON_4");
	
	this->disableControl("ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON");
	this->disableControl("ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON");
	this->disableControl("ID_BAR_SECTION_MARKUP_CHECK");
	this->disableControl("ID_BAR_SECTION_NUMBER_EDIT");
	this->disableControl("ID_BAR_SECTION_ARROWS");
	this->disableControl("ID_BAR_HEADER_EDIT");


    if(this->getArrowTabControlTab("ID_ICON_TAB") == 1) // Force a refresh if it's currently showing
    {
        this->relayoutControl("ID_ICON_TAB");
        this->setArrowTabControlTab("ID_ICON_TAB", 1); // Bar properties tab
    }
}

void ChordableWindow::vectorControlRootMouseMove(std::string id,
                                                 int32_t x,
                                                 int32_t y)
{
    if(this->getControlHidden("ID_ADD_BARS"))
    {
        this->setControlHidden("ID_ADD_BARS", false);

		// We have to relayout the bargrid, since
		// the add bars control was just shown it is
		// possible that it wasn't taken into account
		// before for the row heights

		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

		if(barGrid)
		{
			barGrid->relayout();
		}

        PKControl *viewPort  = this->findControl("ID_VECTOR_CONTROL_ROOT");
        viewPort->invalidate();        
    }    
}

void ChordableWindow::vectorControlRootMouseLeave(std::string id)
{
    PKControl *addBars = this->findControl("ID_ADD_BARS");
    AddBarsVectorControl *add = dynamic_cast<AddBarsVectorControl *>(addBars);

    if(add && !add->isPopupMenuShown())
    {
        this->setControlHidden("ID_ADD_BARS", true);
        PKControl *viewPort  = this->findControl("ID_VECTOR_CONTROL_ROOT");
        viewPort->invalidate();
    }
}

void ChordableWindow::bitmapToggleButtonToggled(std::string id,
									            PKBitmapToggleButton *button,
												bool previousValue)
{
	if(id == "ID_BAR_REPEAT_LEFT_TOGGLE_BUTTON")
	{
		bool toggled = this->getBitmapToggleButtonToggled(id);
		ToggleRepeatCommand *cmd = new ToggleRepeatCommand(this, this->selection.getFirstBar(), true, toggled);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
	}

	if(id == "ID_BAR_REPEAT_RIGHT_TOGGLE_BUTTON")
	{
		bool toggled = this->getBitmapToggleButtonToggled(id);
		ToggleRepeatCommand *cmd = new ToggleRepeatCommand(this, this->selection.getFirstBar(), false, toggled);
		PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
	}
}

void ChordableWindow::customControlClicked(PKButtonType button,
                                           std::string id,
                                           PKCustomControl *control,
                                           std::string partCode)
{
    PKVectorControlRoot   *root = dynamic_cast<PKVectorControlRoot  *>(control);
    BarViewVectorControl   *bar = dynamic_cast<BarViewVectorControl *>(control);
    AddBarsVectorControl   *add = dynamic_cast<AddBarsVectorControl *>(control);
	LineBreakVectorControl *lb  = dynamic_cast<LineBreakVectorControl *>(control); 

	// Comit edit changes since they are losing focus
	this->commitEditControlChanges();

	if(lb != NULL)
	{
		if(partCode == "CLOSE")
		{
			PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

			// Remove that line break, but first animate a fade out

			PKVectorAnimation *anim = new PKVectorAnimation();

			PKVectorAnimationBlock *block1 = new PKVectorAnimationBlock(lb, 0, 0.3, 
											 new PKVectorAnimationDescriptorFade(1.0, 0.0));
			anim->addAnimationBlock(block1);
			anim->setCompletionHandler(this, "REMOVE_LINEBREAK_ANIMATION", lb);

			rootControl->queueVectorControlAnimation(anim);
		}
	}
    else if(bar != NULL)
    {
		if(partCode == "CLOSE")
		{
			PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

			// Remove that bar, first animate a fade out

			PKVectorAnimation *anim = new PKVectorAnimation();

			PKVectorAnimationBlock *block1 = new PKVectorAnimationBlock(bar, 0, 0.3, 
											 new PKVectorAnimationDescriptorFade(1.0, 0.0));
			anim->addAnimationBlock(block1);
			anim->setCompletionHandler(this, "CLOSE_ANIMATION", bar);

			rootControl->queueVectorControlAnimation(anim);
		}
		else if(partCode == "CTRL") // ctrl+clic or command+clic
		{
			PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
			int32_t barIndex = grid->getIndexForChild(bar);

			// Toggle bar selection
			if(this->selection.hasBar(bar))
			{
				this->selection.removeBar(bar);
				this->selectionChanged();
			}
			else 
			{
				this->selection.addBar(bar, barIndex);
				this->selectionChanged();
			}
		}
		else
		{
			// Unselect the last selected one if any
			this->selection.clear();
			
			PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
			int32_t barIndex = grid->getIndexForChild(bar);
			
			// We have a selection so let's record it
			// and then update the bar properties tab

			this->updateBarProperties(bar, true);
			this->selection.addBar(bar, barIndex);
			this->selectionChanged();
		}
    }
    else if(add != NULL)
    {
        if(partCode == "ADD_BARS")
        {
			PKNumberInputDialog d(L"CHORDABLE_ADD_BARS_ID", this->getWindowHandle(), 
                                  PK_i18n(L"Add Bars"), L"ICON");

			PKVariantWString icon(L"res|INFO");
			d.set(PKNumberInputDialog::ICON_WSTRING_PROPERTY, &icon);

            PKVariantWString text(PK_i18n(L"How many bars do you want to add?"));
			d.set(PKNumberInputDialog::TEXT_WSTRING_PROPERTY, &text);

            PKVariantWString dtext(L"4");
			d.set(PKNumberInputDialog::DEFAULT_TEXT_WSTRING_PROPERTY, &dtext);

			int32_t button = d.run();

			if(button == PK_STD_BUTTON_OK)
			{
				// Go

				int32_t numAdd = d.getInputNumber();

				if(numAdd > 0)
				{
					PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
					PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

					if(grid != NULL && rootControl != NULL)
					{
						uint32_t numBars = PKVALUE_UINT32(grid->get(PKGridLayout::COLS_UINT32_PROPERTY));

						int32_t addButtonCol = grid->getColForChild(add);
						int32_t addButtonRow = grid->getRowForChild(add);

						int32_t xAddButtonStart = add->getX();
						int32_t yAddButtonStart = add->getY();

						int32_t newButtonCol = addButtonCol;
						int32_t newButtonRow = addButtonRow;

						// Add the bars

						bool sameLine = true;
						std::vector<BarViewVectorControl *> new_bars;

						for(int32_t n=0; n<numAdd; n++)
						{
							// Decide where it should move, and where to add the new bar

							int32_t newBarCol = newButtonCol;
							int32_t newBarRow = newButtonRow;

							if(newButtonCol < (int32_t)(numBars - 1))
							{
								// There is room on that line
								newButtonCol = newButtonCol + 1;
								newButtonRow = newButtonRow;
							}
							else
							{
								sameLine = false;
								// Move to next line
								newButtonCol = 0;
								newButtonRow = newButtonRow+1;
							}

							// Figure out the new positions

							int32_t xNewBar = grid->getXForChildAtPos(newBarCol, newBarRow);
							int32_t yNewBar = grid->getYForChildAtPos(newBarCol, newBarRow);

							// Add the new bar control

							BarViewVectorControl *newBar = new BarViewVectorControl();

							PKVariantInt32 layoutx(1);
							newBar->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
							PKVariantInt32 layouty(1);
							newBar->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

							newBar->resize(this->barWidth, this->barHeight);
							newBar->move(xNewBar, yNewBar);

							PKVariantDouble alpha(0.0);
							newBar->set(PKVectorControl::ALPHA_DOUBLE_PROPERTY, &alpha);

							PKVariantBool shared(true);
							newBar->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

							grid->insertNewChildAt(newBarCol, newBarRow, newBar);
							newBar->build();
							newBar->initialize(this);
							newBar->setControlRoot(rootControl);
						
							new_bars.push_back(newBar);
						}

                        // Flag we need to save the document
                        this->setNeedsSave();

						int32_t xAddButtonEnd = grid->getXForChildAtPos(newButtonCol, newButtonRow);
						int32_t yAddButtonEnd = grid->getYForChildAtPos(newButtonCol, newButtonRow);

						// Animate the change

						PKVectorAnimation *anim = new PKVectorAnimation();

						if(sameLine)
						{
							PKVectorAnimationBlock *block1 = new PKVectorAnimationBlock(add, 0, 0.15*numAdd, 
															 new PKVectorAnimationDescriptorSlide(xAddButtonStart, yAddButtonStart, 
																								  xAddButtonEnd, yAddButtonEnd));
							anim->addAnimationBlock(block1);

							for(int32_t k=0; k<numAdd; k++)
							{
								PKVectorAnimationBlock *block2 = new PKVectorAnimationBlock(new_bars[k], 0.2*(k+1), 0.2*(k+1)+0.3, 
																 new PKVectorAnimationDescriptorFade(0.0, 1.0));

								anim->addAnimationBlock(block2);
							}
						}
						else
						{
							PKVectorAnimationBlock *block1 = new PKVectorAnimationBlock(add, 0, 0.3, 
															 new PKVectorAnimationDescriptorSlide(xAddButtonStart, yAddButtonStart, 
																								  xAddButtonStart, yAddButtonEnd));

							PKVectorAnimationBlock *block2 = new PKVectorAnimationBlock(add, 0.3, 0.7, 
															 new PKVectorAnimationDescriptorSlide(xAddButtonStart, yAddButtonEnd, 
																								  xAddButtonEnd, yAddButtonEnd));

							anim->addAnimationBlock(block1);
							anim->addAnimationBlock(block2);

							for(int32_t k=0; k<numAdd; k++)
							{
								PKVectorAnimationBlock *block3 = new PKVectorAnimationBlock(new_bars[k], 0.05*(k+1), 0.05*(k+1)+0.3, 
																 new PKVectorAnimationDescriptorFade(0.0, 1.0));

								anim->addAnimationBlock(block3);
							}
						}

						rootControl->queueVectorControlAnimation(anim);
					}
				}
			}
		}

        if(partCode == "LINE_BREAK")
        {
			PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
			PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

			if(grid != NULL && rootControl != NULL)
			{
				uint32_t numBars = PKVALUE_UINT32(grid->get(PKGridLayout::COLS_UINT32_PROPERTY));

				int32_t addButtonCol = grid->getColForChild(add);
				int32_t addButtonRow = grid->getRowForChild(add);
			
				int32_t newButtonCol = 0;
				int32_t newButtonRow = addButtonRow+1;

				int32_t xAddButtonStart = add->getX();
				int32_t yAddButtonStart = add->getY();

				// Animate the transition

				int32_t xAddButtonEnd = grid->getXForChildAtPos(newButtonCol, newButtonRow);
				int32_t yAddButtonEnd = grid->getYForChildAtPos(newButtonCol, newButtonRow);

				PKVectorAnimation *anim = new PKVectorAnimation();

				PKVectorAnimationBlock *block1 = new PKVectorAnimationBlock(add, 0, 0.2, 
												 new PKVectorAnimationDescriptorSlide(xAddButtonStart, yAddButtonStart, 
																					  xAddButtonStart, yAddButtonEnd));

				PKVectorAnimationBlock *block2 = new PKVectorAnimationBlock(add, 0.2, 0.8, 
												 new PKVectorAnimationDescriptorSlide(xAddButtonStart, yAddButtonEnd, 
																					  xAddButtonEnd, yAddButtonEnd));

				anim->addAnimationBlock(block1);
				anim->addAnimationBlock(block2);
				anim->setCompletionHandler(this, "ADD_LINE_BREAK", add);

                // Flag we need to save the document
                this->setNeedsSave();

                rootControl->queueVectorControlAnimation(anim);
			}			
		}

		if(partCode == "PLUS")
        {
            // Add one bar

			PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
			PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

			if(grid != NULL && rootControl != NULL)
			{
				uint32_t numBars = PKVALUE_UINT32(grid->get(PKGridLayout::COLS_UINT32_PROPERTY));

				int32_t addButtonCol = grid->getColForChild(add);
				int32_t addButtonRow = grid->getRowForChild(add);

				// Decide where it should move, and where to add the new bar

				bool sameLine = true;

				int32_t newButtonCol = -1;
				int32_t newButtonRow = -1;

				int32_t newBarCol = addButtonCol;
				int32_t newBarRow = addButtonRow;

				if(addButtonCol < (int32_t)(numBars - 1))
				{
					// There is room on that line
					newButtonCol = addButtonCol + 1;
					newButtonRow = addButtonRow;
				}
				else
				{
					sameLine = false;
					// Move to next line
					newButtonCol = 0;
					newButtonRow = addButtonRow+1;
				}

				// Figure out the new positions

				int32_t xAddButtonStart = add->getX();
				int32_t yAddButtonStart = add->getY();

				int32_t xAddButtonEnd = grid->getXForChildAtPos(newButtonCol, newButtonRow);
				int32_t yAddButtonEnd = grid->getYForChildAtPos(newButtonCol, newButtonRow);

				int32_t xNewBar = grid->getXForChildAtPos(newBarCol, newBarRow);
				int32_t yNewBar = grid->getYForChildAtPos(newBarCol, newBarRow);

				// Add the new bar control

				BarViewVectorControl *newBar = new BarViewVectorControl();

				PKVariantInt32 layoutx(1);
				newBar->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
				PKVariantInt32 layouty(1);
				newBar->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

				newBar->resize(this->barWidth, this->barHeight);
				newBar->move(xNewBar, yNewBar);

				PKVariantDouble alpha(0.0);
				newBar->set(PKVectorControl::ALPHA_DOUBLE_PROPERTY, &alpha);

				PKVariantBool shared(true);
				newBar->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

				grid->insertNewChildAt(newBarCol, newBarRow, newBar);
				newBar->build();
				newBar->initialize(this);
				newBar->setControlRoot(rootControl);

				// Animate the transition(s)
				
				PKVectorAnimation *anim = new PKVectorAnimation();

				if(sameLine)
				{
					PKVectorAnimationBlock *block1 = new PKVectorAnimationBlock(add, 0, 0.3, 
													 new PKVectorAnimationDescriptorSlide(xAddButtonStart, yAddButtonStart, 
																						  xAddButtonEnd, yAddButtonEnd));
					PKVectorAnimationBlock *block2 = new PKVectorAnimationBlock(newBar, 0.2, 0.6, 
													 new PKVectorAnimationDescriptorFade(0.0, 1.0));

					anim->addAnimationBlock(block1);
					anim->addAnimationBlock(block2);
				}
				else
				{
					PKVectorAnimationBlock *block1 = new PKVectorAnimationBlock(add, 0, 0.2, 
													 new PKVectorAnimationDescriptorSlide(xAddButtonStart, yAddButtonStart, 
																						  xAddButtonStart, yAddButtonEnd));

					PKVectorAnimationBlock *block2 = new PKVectorAnimationBlock(add, 0.2, 0.8, 
													 new PKVectorAnimationDescriptorSlide(xAddButtonStart, yAddButtonEnd, 
																						  xAddButtonEnd, yAddButtonEnd));

					PKVectorAnimationBlock *block3 = new PKVectorAnimationBlock(newBar, 0.3, 0.7, 
													 new PKVectorAnimationDescriptorFade(0.0, 1.0));

					anim->addAnimationBlock(block1);
					anim->addAnimationBlock(block2);
					anim->addAnimationBlock(block3);
				}

				rootControl->queueVectorControlAnimation(anim);

                // Flag we need to save the document
                this->setNeedsSave();
			}
        }
    }
    else if(root != NULL)
    {
        // Clear selection
		this->selection.clear();
    
        this->disableBarProperties();
        this->setArrowTabControlTab("ID_ICON_TAB", 0);
    }
}   

void ChordableWindow::customControlDoubleClicked(PKButtonType button,
												 std::string id,
												 PKCustomControl *control,
												 std::string partCode)
{
    BarViewVectorControl   *bar = dynamic_cast<BarViewVectorControl *>(control);

	if(bar != NULL)
	{
		uint8_t barType = PKVALUE_UINT8(bar->get(BarViewVectorControl::BARTYPE_UINT8_PROPERTY));
		
		switch(barType)
		{
			case BAR_TYPE_SINGLE:
			{
				// Clear selection
				this->selection.clear();

				// Select this bar
				PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
				int32_t barIndex = grid->getIndexForChild(bar);
				
				this->selection.addBar(bar, barIndex);
				
				// We have a selection so let's record it
				// and then update the bar properties tab
				
				this->updateBarProperties(bar, true);
				
				// Now trigger chord selection
				this->buttonClicked("ID_CHORD_BUTTON_1");
				
			}
				break;
				
			default:
				break;
		}
				
	}
}

void ChordableWindow::selectionChanged()
{
	if(this->selection.getSize() == 0)
	{
		this->setArrowTabControlTab("ID_ICON_TAB", 0);
	}
	else if(this->selection.getSize() == 1)
	{
		this->updateBarProperties(this->selection.getFirstBar(), true);
	}
	else 
	{
		this->disableBarProperties();
	}

}

void ChordableWindow::setNeedsSave()
{
    if(!this->ready)
    {
        return;
    }

    if(this->ignoreSetSave)
    {
        return;
    }

    if(this->currentFileName == L"")
    {
        std::wstring title = this->getEditableLabelText("ID_TITLE_EDIT");
        std::wstring sub   = this->getEditableLabelText("ID_SUBTITLE_EDIT");
    
		PKGridLayout *grid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

        int numBars = grid->getChildrenCount() - 1;

        if(title == L"" && sub == L"" && numBars == 0)
        {
            // No need to save an empty document
            return;
        }
    }

	this->needsSave = true;

	// Update visuals

	if(this->currentFileName == L"")
	{
		PKVariantWStringI18N caption(PK_i18n(L"Croque-Note - New Document *"));
		this->set(PKWindow::CAPTION_WSTRING_PROPERTY, &caption);
	}
	else
	{
		std::wstring docName = PKPath::getFileName(this->currentFileName);
		std::wstring c = PK_i18n(L"Croque-Note - ") + docName + L" *";		
		
		PKVariantWStringI18N caption(c);
		this->set(PKWindow::CAPTION_WSTRING_PROPERTY, &caption);
	}
}

void ChordableWindow::editTextChanged(std::string id, 
									  std::wstring text)
{
    if(!this->ready)
    {
        return;
    }

	this->setNeedsSave();

	if(id == "ID_BAR_SECTION_NUMBER_EDIT")
	{
		uint32_t num = PKStr::wstringToUInt32(text);

		if(num > 0 && this->selection.getSize() == 1)
		{
			PKVariantUInt32 numv(num);
			this->selection.getFirstBar()->set(BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY, &numv);
			this->invalidateControl("ID_VECTOR_CONTROL_ROOT");
		}
	}

	if(id == "ID_BAR_HEADER_EDIT")
	{
        PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

		if(this->selection.getSize() == 1 && barGrid)
		{
			PKVariant *ct = this->selection.getFirstBar()->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY);
			std::wstring currentHeader = PKVALUE_WSTRING(ct);

			PKVariantWString wtext(text);

			if(text != L"")
			{
				if(currentHeader == L"")
				{
					// We need to make sure there is space for the header

					this->toggleOverheadSpaceForBar(this->selection.getFirstBar(), true);
				}

				this->selection.getFirstBar()->set(BarViewVectorControl::HEADER_WSTRING_PROPERTY, &wtext);

				barGrid->relayout();
				this->invalidateControl("ID_VECTOR_CONTROL_ROOT"); // TODO: better ?
			}
			else
			{
				if(currentHeader != L"")
				{
					// We need to remove the space for the header
					// if the row is empty from bars that have headers

					this->toggleOverheadSpaceForBar(this->selection.getFirstBar(), false);
				}

				this->selection.getFirstBar()->set(BarViewVectorControl::HEADER_WSTRING_PROPERTY, &wtext);

				barGrid->relayout();
				this->invalidateControl("ID_VECTOR_CONTROL_ROOT"); // TODO: better ?
			}
		}
	}

    if(id == "ID_NUM_COL_EDIT")
    {
        uint32_t newNumCols = PKStr::wstringToUInt32(text);
		uint32_t oldNumCols = PKVALUE_UINT32(this->currentDocument->get(ChordableDocument::BARS_PER_ROW_UINT32_PROPERTY));
		
		if(newNumCols > 0 && newNumCols < 9 && newNumCols != oldNumCols)
		{
			ChangeBarsPerRowCommand *cmd = new ChangeBarsPerRowCommand(this, newNumCols, oldNumCols);
			PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
		}
    }
}

void ChordableWindow::editTextEditingEnded(std::string id, 
										   std::wstring oldValue, 
										   std::wstring newValue)
{
	// We use this signal to add undoable commands
	// for actions involving an edit control as to
	// allow undo, but aggregate multiple keystrokes nicely

	if(id == "ID_INSPECTOR_TITLE_EDIT")
	{
		GenericEditChangeCommand *cmd = new GenericEditChangeCommand(this, id, PK_i18n(L"Change Title"), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}

	if(id == "ID_INSPECTOR_SUBTITLE_EDIT")
	{
		GenericEditChangeCommand *cmd = new GenericEditChangeCommand(this, id, PK_i18n(L"Change Subtitle"), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}

	if(id == "ID_INSPECTOR_CAPO_EDIT")
	{
		GenericEditChangeCommand *cmd = new GenericEditChangeCommand(this, id, PK_i18n(L"Change Capo"), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}

	if(id == "ID_INSPECTOR_TEMPO_EDIT")
	{
		GenericEditChangeCommand *cmd = new GenericEditChangeCommand(this, id, PK_i18n(L"Change Tempo"), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}

	if(id == "ID_BAR_HEADER_EDIT")
	{	
		BarHeaderChangeCommand *cmd = new BarHeaderChangeCommand(this, this->selection.getFirstBar(), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}

	if(id == "ID_BAR_SECTION_NUMBER_EDIT")
	{
		BarSectionNumberChangeCommand *cmd = new BarSectionNumberChangeCommand(this, this->selection.getFirstBar(), oldValue, newValue);
		PKUndoManager::getInstance()->pushCommandButDontRunIt(cmd);
	}
}

void ChordableWindow::newDocument()
{
	// Check if we currently have a document
	
	if(this->currentDocument && this->needsSave)
	{
		// Ask for confirmation
		
		PKStdDialog dialog(L"CHORDABLE_NEW_DOCUMENT_CONFIRM_DIALOG",
						   PK_STD_DIALOG_YES_NO_CANCEL,
						   this->getWindowHandle(),
						   PK_i18n(L"Croque-Note: New Document"),
						   L"ICON");
		
		PKVariantWString header(L"");
		dialog.set(PKStdDialog::HEADER_WSTRING_PROPERTY, &header);
		
		PKVariantWString text(PK_i18n(L"There are unsaved changes in the current document. Do you want to save these changes first?"));
		dialog.set(PKStdDialog::TEXT_WSTRING_PROPERTY, &text);

		PKVariantWString icon(PK_i18n(L"res|INFO"));
		dialog.set(PKStdDialog::ICON_WSTRING_PROPERTY, &icon);

        dialog.updateUIStrings();
		int32_t result = dialog.run();
		
		if(result == PK_STD_BUTTON_CANCEL)
		{
			// Abort
			return;
		}		
		
		if(result == PK_STD_BUTTON_YES)
		{
			if(!this->saveCurrentDocument())
            {
                // Cancelled
                return;
            }
		}
	}
	
	// Setup new document
		
    this->currentDocument->revertAllPropertiesToDefaultValues();

    // We need to run commands for each document property 
    // to setup the display of the document page

    ToggleKeyCommand *keyCmd = new ToggleKeyCommand(this, PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_KEY_BOOL_PROPERTY)));
    PKUndoManager::getInstance()->pushCommandAndRunIt(keyCmd);

    if(PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_TEMPO_BOOL_PROPERTY)))
    {
        ShowTempoCommand *tempoCmd = new ShowTempoCommand(this);
        PKUndoManager::getInstance()->pushCommandAndRunIt(tempoCmd);
    }
    else
    {
        HideTempoCommand *tempoCmd = new HideTempoCommand(this);
        PKUndoManager::getInstance()->pushCommandAndRunIt(tempoCmd);
    }

    if(PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_CAPO_BOOL_PROPERTY)))
    {
        ShowCapoCommand *tempoCmd = new ShowCapoCommand(this);
        PKUndoManager::getInstance()->pushCommandAndRunIt(tempoCmd);
    }
    else
    {
        HideCapoCommand *tempoCmd = new HideCapoCommand(this);
        PKUndoManager::getInstance()->pushCommandAndRunIt(tempoCmd);
    }

    int32_t sel = this->getComboBoxSelectedItem("ID_INSPECTOR_KEY_CHECKBOX");
    ChangeKeyCommand *ckCmd = new ChangeKeyCommand(this, sel, -1);
    PKUndoManager::getInstance()->pushCommandAndRunIt(ckCmd);

    ToggleShowChordDiagramsCommand * tgCmd = new ToggleShowChordDiagramsCommand(this, PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_CHORD_DIAGRAMS_BOOL_PROPERTY)));
    PKUndoManager::getInstance()->pushCommandAndRunIt(tgCmd);

    ToggleTuningCommand *tgtCmd = new ToggleTuningCommand(this, PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_TUNING_BOOL_PROPERTY)));
    PKUndoManager::getInstance()->pushCommandAndRunIt(tgtCmd);

    sel = this->getComboBoxSelectedItem("ID_TUNING_COMBO");
    ChangeTuningCommand *tuCmd = new ChangeTuningCommand(this, sel, -1, this->notation);
    PKUndoManager::getInstance()->pushCommandAndRunIt(tuCmd);

    // Reset the undo/redo stack
    PKUndoManager::getInstance()->clearUndoAndRedoState();

    // Clear the contents of the document

	this->selection.clear();
	this->disableBarProperties();
    this->setArrowTabControlTab("ID_ICON_TAB", 0); // Document properties tab

	PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
	PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

	if(barGrid != NULL && rootControl != NULL)
	{
		// Clear all children
		barGrid->deleteAllChildControls();
        barGrid->clearChildren();

		// Add 4 new bars

		for(uint32_t i=0; i<4; i++)
		{
			BarViewVectorControl *newBar = new BarViewVectorControl();

			PKVariantInt32 layoutx(1);
			newBar->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
			PKVariantInt32 layouty(1);
			newBar->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

			newBar->resize(this->barWidth, this->barHeight);

			PKVariantBool shared(true);
			newBar->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

			barGrid->addChild(newBar);
			newBar->build();
			newBar->initialize(this);
			newBar->setControlRoot(rootControl);
		}

		// Add the AddBars control

		AddBarsVectorControl *add = new AddBarsVectorControl();

		PKVariantString id("ID_ADD_BARS");
		add->set(PKControl::ID_STRING_PROPERTY, &id);

		PKVariantBool hidden(true);
		add->set(PKControl::HIDDEN_BOOL_PROPERTY, &hidden);

		PKVariantInt32 layoutx(1);
		add->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
		PKVariantInt32 layouty(1);
		add->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

		add->resize(this->barWidth, this->barHeight);

		PKVariantBool shared(true);
		add->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

		barGrid->addChild(add);
		add->build();
		add->initialize(this);
		add->setControlRoot(rootControl);

		barGrid->relayout();
	}

	// Update the tuning
	
	PKVariant *t = this->currentDocument->get(ChordableDocument::TUNING_STRINGLIST_PROPERTY);
	std::vector<std::string> tuning = PKVALUE_STRINGLIST(t);

	for(uint32_t i=0; i<this->tunings.size(); i++)
	{
		PKTuning *current = this->tunings[i];

		if(current->getNumberOfStrings() != tuning.size())
		{
			continue;
		}

		bool allGood = true;

		for(uint32_t n=0; n<current->getNumberOfStrings(); n++)
		{
			if(PKStr::stringToInt32(tuning[n]) != current->getNoteForString(n).note)
			{
				allGood = false;
				break;
			}
		}

		if(allGood)
		{
			// Found it !
			this->selectComboBoxItem("ID_TUNING_COMBO", i);
			break;
		}
	}
	
	// Update the number of bars per row
	
	uint32_t numRows = PKVALUE_UINT32(this->currentDocument->get(ChordableDocument::BARS_PER_ROW_UINT32_PROPERTY));
	this->setEditText("ID_NUM_COL_EDIT", PKStr::uint32ToWstring(numRows));

    // Udate other properties

    this->setCheckBoxChecked("ID_INSPECTOR_CHORDS_CHECKBOX", false);
    this->setEditText("ID_INSPECTOR_NOTES_EDIT", L"");

    // Reset chords
    this->refreshChordsGrid();
	
    this->needsSave       = false;
	this->currentFileName = L"";

	PKVariantWStringI18N caption(PK_i18n(L"Croque-Note - New Document"));
	this->set(PKWindow::CAPTION_WSTRING_PROPERTY, &caption);
}

void ChordableWindow::openDocument(std::wstring fileName)
{
	// Do we need to save the
	// current document first ?
	
	if(this->currentDocument && this->needsSave)
	{
		// Ask for confirmation
		
		PKStdDialog dialog(L"CHORDABLE_NEW_DOCUMENT_CONFIRM_DIALOG",
						   PK_STD_DIALOG_YES_NO_CANCEL,
						   this->getWindowHandle(),
						   PK_i18n(L"Croque-Note: Open a Document"),
						   L"ICON");
		
		PKVariantWString header(L"");
		dialog.set(PKStdDialog::HEADER_WSTRING_PROPERTY, &header);
		
		PKVariantWString text(PK_i18n(L"There are unsaved changes in the current document. Do you want to save these changes first?"));
		dialog.set(PKStdDialog::TEXT_WSTRING_PROPERTY, &text);
		
		PKVariantWString icon(PK_i18n(L"res|INFO"));
		dialog.set(PKStdDialog::ICON_WSTRING_PROPERTY, &icon);
		
        dialog.updateUIStrings();
		int32_t result = dialog.run();
		
		if(result == PK_STD_BUTTON_CANCEL)
		{
			// Abort
			return;
		}		
		
		if(result == PK_STD_BUTTON_YES)
		{
			if(!this->saveCurrentDocument())
            {
                // Cancelled
                return;
            }
		}
	}
	
	// Now go ahead
	
	std::wstring result = L"";

	if(fileName == L"")
	{
		PKOpenDialog open;
		
		open.setTitle(PK_i18n(L"Croque-Note: Open a Document"));
		open.addFilterEntry(L"*.chd", PK_i18n(L"Croque-Note Documents"));
		open.addFilterEntry(L"*.*", PK_i18n(L"All Files"));
	
		result = open.askForOpenFilename(this->getWindowHandle());
	}
	else
	{
		result = fileName;
	}

	if(result != L"")
	{
		// Open the document
		
		if(this->openDocumentAtPath(result))
		{
			this->currentFileName = result;
			
			// Update recent files

			this->settings->addRecentFile(result);

			if(this->getMenu())
			{
				this->getMenu()->updateRecentFilesMenu();
			}

			// Setup the UI
			
			std::wstring docName = PKPath::getFileName(this->currentFileName);
			std::wstring c = L"PKI18N:Croque-Note - " + docName;		
			
			PKVariantWStringI18N caption(c);
			this->set(PKWindow::CAPTION_WSTRING_PROPERTY, &caption);

            this->needsSave = false;
		}
	}	
}

bool ChordableWindow::saveCurrentDocument()
{
	if(!this->needsSave)
	{
		return false;
	}
	
	if(this->currentFileName == L"")
	{
		// Need to ask for a save location
		
		PKSaveDialog save;
		
		save.setTitle(PK_i18n(L"Croque-Note: Save Document"));
		save.setInitialFilename(PK_i18n(L"Untitled.chd"));
		save.addFilterEntry(L"*.chd", PK_i18n(L"Croque-Note Documents"));
		
		std::wstring result = save.askForSaveFilename(this->getWindowHandle());
		
		if(result != L"")
		{
		    // Apend .chd if not present
		    
		    if(result.size() < 4 || PKStr::toLower(result.substr(result.size()-4, 4)) != L".chd")
		    {
		        result += L".chd";
		    }
		
			this->currentFileName = result;

			this->settings->addRecentFile(this->currentFileName);

			if(this->getMenu())
			{
				this->getMenu()->updateRecentFilesMenu();
			}
		}		
		else
		{
			return false;
		}
	}
	
	// Actually save to disk

    this->writeCurrentDocumentToFile(this->currentFileName);

	// Update variables
	
	this->needsSave = false;

	// Update visuals
	
	std::wstring docName = PKPath::getFileName(this->currentFileName);
	std::wstring c = L"PKI18N:Croque-Note - " + docName;		
		
	PKVariantWStringI18N caption(c);
	this->set(PKWindow::CAPTION_WSTRING_PROPERTY, &caption);

    return true;
}

void ChordableWindow::exportDocument()
{
    // Show export dialog
    ExportDialog dialog(this->getWindowHandle(), PK_i18n(L"Croque-Note: Export"), L"ICON");
    int32_t result = dialog.run();

    if(result == EXPORT_DIALOG_BUTTON_EXPORT)
    {
        // Ask for filename
        int32_t pngDim = 0;
        std::wstring ext = L"";
        std::wstring name = PK_i18n(L"Untitled");

        // use current file name if any
        if(this->currentFileName != L"")
        {
            name = this->currentFileName;
        }

        // remove extension if present
        if(name.size() > 4 && PKStr::toLower(PKPath::getExtension(this->currentFileName)) == L".chd")
        {
            name = name.substr(0, name.size() - 4);
        }

        PKSaveDialog save;
        save.setTitle(PK_i18n(L"Croque-Note: Export Document"));

        // Get parameters
        switch(dialog.getExportType())
        {
			case EXPORT_DIALOG_EXPORT_JPEG:
            {
                ext = L".jpg";
				
                // Get JPEG size
                pngDim = dialog.getJPEGSize();
				
                // Setup save dialog
                save.setInitialFilename(name + L".jpg");
                save.addFilterEntry(L"*.jpg", PK_i18n(L"JPEG Images"));
            }
				break;

			case EXPORT_DIALOG_EXPORT_PNG:
            {
                ext = L".png";

                // Get PNG size
                pngDim = dialog.getPNGSize();

                // Setup save dialog
                save.setInitialFilename(name + L".png");
                save.addFilterEntry(L"*.png", PK_i18n(L"PNG Images"));
            }
            break;

        case EXPORT_DIALOG_EXPORT_PDF:
            {
                ext = L".pdf";

                // Setup save dialog
                save.setInitialFilename(name + L".pdf");
                save.addFilterEntry(L"*.pdf", PK_i18n(L"PDF Documents"));
            }
            break;

        default:
            return;
            break;
        }

        // Ask for save location
        std::wstring result = save.askForSaveFilename(this->getWindowHandle());

        if(result != L"")
        {
            // Append extension if not present
            if(result.size() < 4 || PKStr::toLower(result.substr(result.size()-4, 4)) != ext)
            {
                result += ext;
            }

            // Proceed to export
			
			// Save current document to a temp file
			std::wstring tempDir  = PKPath::getTempPath();
			std::wstring tempFile = PKPath::getTempFileName(tempDir);
			
			this->writeCurrentDocumentToFile(tempFile);
			
			if(!PKPath::fileExists(tempFile) || PKPath::getFileSize(tempFile) == 0)
			{
				// TODO: error message
				return;
			}
			
			// Create a new ChordableWindow, and load the document in it
			ChordableWindow *newWindow = new ChordableWindow(L"ICON", this->settings);
			newWindow->updateUIStrings();

			// Load the document
			newWindow->openDocumentAtPath(tempFile);
						
			// Setup empty labels
			if(newWindow->getEditableLabelText("ID_TITLE_EDIT") == L"")
			{
				newWindow->setEditableLabelText("ID_TITLE_EDIT", L" ");
			}
			
			if(newWindow->getEditableLabelText("ID_SUBTITLE_EDIT") == L"")
			{
				newWindow->setEditableLabelText("ID_SUBTITLE_EDIT", L" ");
			}
 			
			// Export
			
			switch(dialog.getExportType())
			{
				case EXPORT_DIALOG_EXPORT_JPEG:
				{
					// Setup its size
					newWindow->resizeWindowAreaTo(3000, 2000) ;
					newWindow->layoutInitialDocument();
					newWindow->setSliderValue("ID_ZOOM_SLIDER", 0);
#ifdef MACOSX
					newWindow->sliderChanged("ID_ZOOM_SLIDER", 0);
#endif
					
					ChordableVectorControlRoot *root = dynamic_cast<ChordableVectorControlRoot*> (newWindow->findControl("ID_VECTOR_CONTROL_ROOT"));
					
					if(root != NULL)
					{
						int wh = newWindow->getWindowHeight();
						int ph = root->getH();
						
						int diff = wh - ph;
						int vh = pngDim + diff + 64; // margins
						
						newWindow->resizeWindowAreaTo(vh*3/2, vh) ;
						newWindow->setSliderValue("ID_ZOOM_SLIDER", 0);
#ifdef MACOSX
						newWindow->sliderChanged("ID_ZOOM_SLIDER", 0);
#endif
					}
					
					newWindow->exportToJPEGFile(result, dialog.getJPEGQuality()); // quality
				}
					break;

				case EXPORT_DIALOG_EXPORT_PNG:
				{
					// Setup its size
					newWindow->resizeWindowAreaTo(3000, 2000) ;
					newWindow->layoutInitialDocument();
					newWindow->setSliderValue("ID_ZOOM_SLIDER", 0);
#ifdef MACOSX
					newWindow->sliderChanged("ID_ZOOM_SLIDER", 0);
#endif
					
					ChordableVectorControlRoot *root = dynamic_cast<ChordableVectorControlRoot*> (newWindow->findControl("ID_VECTOR_CONTROL_ROOT"));
					
					if(root != NULL)
					{
						int wh = newWindow->getWindowHeight();
						int ph = root->getH();
						
						int diff = wh - ph;
						int vh = pngDim + diff + 64; // margins
					
						newWindow->resizeWindowAreaTo(vh*3/2, vh) ;
						newWindow->setSliderValue("ID_ZOOM_SLIDER", 0);
#ifdef MACOSX
						newWindow->sliderChanged("ID_ZOOM_SLIDER", 0);
#endif
					}
					
					newWindow->exportToPNGFile(result);
				}
					break;
					
				case EXPORT_DIALOG_EXPORT_PDF:
				{
					// Setup its size
					newWindow->resizeWindowAreaTo(3000, 2000) ;
					newWindow->layoutInitialDocument();
					newWindow->setSliderValue("ID_ZOOM_SLIDER", 0);
#ifdef MACOSX
					newWindow->sliderChanged("ID_ZOOM_SLIDER", 0);
#endif

					// Export
					newWindow->exportToPDFFile(result);
				}
					break;
					
				default:
					return;
					break;
			}
			
			// Cleanup			
			newWindow->release();
			PKPath::deleteFile(tempFile);
        }
    }
}

void ChordableWindow::exportToJPEGFile(std::wstring file, float quality)
{
	// Draw the current document into a PNG context
	
	ChordableVectorControlRoot *root = dynamic_cast<ChordableVectorControlRoot*> (this->findControl("ID_VECTOR_CONTROL_ROOT"));
	
	if(root != NULL)
	{
		root->exportToJPEGFile(file, quality);
	}	
}

void ChordableWindow::exportToPNGFile(std::wstring file)
{
	// Draw the current document into a PNG context

	ChordableVectorControlRoot *root = dynamic_cast<ChordableVectorControlRoot*> (this->findControl("ID_VECTOR_CONTROL_ROOT"));
	
	if(root != NULL)
	{
		root->exportToPNGFile(file);
	}
}

void ChordableWindow::exportToPDFFile(std::wstring file)
{
	// Draw the current document into a PDF context

	ChordableVectorControlRoot *root = dynamic_cast<ChordableVectorControlRoot*> (this->findControl("ID_VECTOR_CONTROL_ROOT"));
	
	if(root != NULL)
	{
		root->exportToPDFFile(file);
	}
}

// Object creation function for the database loading process

PKObject *_ChordableWindowCreateContentObject()
{	
	return new ChordableContentObject();
}

bool ChordableWindow::openDocumentAtPath(std::wstring filename)
{
    PKDatabase db;

    if(db.openDB(filename) == PKDB_OK)
    {
		db.readFirstObjectFromTable(CHORDABLE_DOCUMENT_TABLE_V1, this->currentDocument);

		// Update the tuning
		
		PKVariant *t = this->currentDocument->get(ChordableDocument::TUNING_STRINGLIST_PROPERTY);
		std::vector<std::string> tuning = PKVALUE_STRINGLIST(t);

		for(uint32_t i=0; i<this->tunings.size(); i++)
		{
			PKTuning *current = this->tunings[i];

			if(current->getNumberOfStrings() != tuning.size())
			{
				continue;
			}

			bool allGood = true;

			for(uint32_t n=0; n<current->getNumberOfStrings(); n++)
			{
				if(PKStr::stringToInt32(tuning[n]) != current->getNoteForString(n).note)
				{
					allGood = false;
					break;
				}
			}

			if(allGood)
			{
				// Found it !
				this->selectComboBoxItem("ID_TUNING_COMBO", i);
				break;
			}
		}

        // We need to run commands for each document property 
        // to setup the display of the document page

        ToggleKeyCommand *keyCmd = new ToggleKeyCommand(this, PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_KEY_BOOL_PROPERTY)));
        PKUndoManager::getInstance()->pushCommandAndRunIt(keyCmd);

        if(PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_TEMPO_BOOL_PROPERTY)))
        {
            ShowTempoCommand *tempoCmd = new ShowTempoCommand(this);
            PKUndoManager::getInstance()->pushCommandAndRunIt(tempoCmd);
        }
        else
        {
            HideTempoCommand *tempoCmd = new HideTempoCommand(this);
            PKUndoManager::getInstance()->pushCommandAndRunIt(tempoCmd);
        }

        if(PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_CAPO_BOOL_PROPERTY)))
        {
            ShowCapoCommand *tempoCmd = new ShowCapoCommand(this);
            PKUndoManager::getInstance()->pushCommandAndRunIt(tempoCmd);
        }
        else
        {
            HideCapoCommand *tempoCmd = new HideCapoCommand(this);
            PKUndoManager::getInstance()->pushCommandAndRunIt(tempoCmd);
        }
		
        int32_t sel = this->getComboBoxSelectedItem("ID_INSPECTOR_KEY_CHECKBOX");
        ChangeKeyCommand *ckCmd = new ChangeKeyCommand(this, sel, -1);
        PKUndoManager::getInstance()->pushCommandAndRunIt(ckCmd);

        ToggleShowChordDiagramsCommand * tgCmd = new ToggleShowChordDiagramsCommand(this, PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_CHORD_DIAGRAMS_BOOL_PROPERTY)));
        PKUndoManager::getInstance()->pushCommandAndRunIt(tgCmd);

        ToggleTuningCommand *tgtCmd = new ToggleTuningCommand(this, PKVALUE_BOOL(this->currentDocument->get(ChordableDocument::SHOW_TUNING_BOOL_PROPERTY)));
        PKUndoManager::getInstance()->pushCommandAndRunIt(tgtCmd);

        sel = this->getComboBoxSelectedItem("ID_TUNING_COMBO");
        ChangeTuningCommand *tuCmd = new ChangeTuningCommand(this, sel, -1, this->notation);
        PKUndoManager::getInstance()->pushCommandAndRunIt(tuCmd);
		
		// Update the current document

		this->selection.clear();
		this->disableBarProperties();
		this->setArrowTabControlTab("ID_ICON_TAB", 0); // Document properties tab

		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
		PKVectorControlRoot *rootControl = dynamic_cast<PKVectorControlRoot*>(this->findControl("ID_VECTOR_CONTROL_ROOT"));

		if(barGrid != NULL && rootControl != NULL)
		{
			// Clear all children
			barGrid->deleteAllChildControls();

			// Update the number of bars per row here
			// so that is recalculates the bar size
			
			uint32_t numRows = PKVALUE_UINT32(this->currentDocument->get(ChordableDocument::BARS_PER_ROW_UINT32_PROPERTY));
			
			this->setEditText("ID_NUM_COL_EDIT", PKStr::uint32ToWstring(numRows));
			ChangeBarsPerRowCommand *cmd = new ChangeBarsPerRowCommand(this, numRows, 6);
			PKUndoManager::getInstance()->pushCommandAndRunIt(cmd);
			
			// And then load the contents
			std::vector<PKObject *> contents;
			db.getObjectsFromTableWithCreateFunction(CHORDABLE_CONTENTS_TABLE_V1, &contents, _ChordableWindowCreateContentObject);

			// And see what we got

			for(uint32_t i=0; i<contents.size(); i++)
			{
				ChordableContentObject *object = dynamic_cast<ChordableContentObject*>(contents[i]);

				int type = PKVALUE_INT8(object->get(ChordableContentObject::OBJECT_TYPE_UINT8_PROPERTY));

				if(type == CHORDABLE_CONTENT_OBJECT_TYPE_BAR)
				{
					BarViewVectorControl *newBar = new BarViewVectorControl();

					// Set standard properties

					PKVariantInt32 layoutx(1);
					newBar->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
					PKVariantInt32 layouty(1);
					newBar->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

					newBar->resize(this->barWidth, this->barHeight);
		
					PKVariantBool shared(true);
					newBar->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

					// Set display properties
					newBar->set(BarViewVectorControl::BARTYPE_UINT8_PROPERTY, object->get(ChordableContentObject::BAR_TYPE_UINT8_PROPERTY));
					newBar->set(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY, object->get(ChordableContentObject::REPEAT_LEFT_BOOL_PROPERTY));
					newBar->set(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY, object->get(ChordableContentObject::REPEAT_RIGHT_BOOL_PROPERTY));
					newBar->set(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY, object->get(ChordableContentObject::SECTION_MARKER_BOOL_PROPERTY));
					newBar->set(BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY, object->get(ChordableContentObject::SECTION_NUMBER_UINT32_PROPERTY));
					newBar->set(BarViewVectorControl::HEADER_WSTRING_PROPERTY, object->get(ChordableContentObject::HEADER_WSTRING_PROPERTY));

					// Chord #1

					void *libraryStateBuffer1 = PKVALUE_BINARY_BUFFER(object->get(ChordableContentObject::LIBRARY_STATE_1_BINARY_PROPERTY));
					int   libraryStateSize1   = PKVALUE_BINARY_SIZE(object->get(ChordableContentObject::LIBRARY_STATE_1_BINARY_PROPERTY));

					void *chordDiagramBuffer1 = PKVALUE_BINARY_BUFFER(object->get(ChordableContentObject::CHORD_DIAGRAM_1_BINARY_PROPERTY));
					int   chordDiagramSize1   = PKVALUE_BINARY_SIZE(object->get(ChordableContentObject::CHORD_DIAGRAM_1_BINARY_PROPERTY));

					if(libraryStateSize1 > 0 &&
                       chordDiagramSize1 > 0 &&
				       libraryStateBuffer1 != NULL &&
                       chordDiagramBuffer1 != NULL)
					{
						// Library state

						if(libraryStateSize1 == sizeof(PKChordLibraryState))
						{
							PKChordLibraryState *state = (PKChordLibraryState *) libraryStateBuffer1;

							if(state->version == 1)
							{
								newBar->setChordLibraryStateForIndex(0, state);
								newBar->setChordNameForIndex(0, this->chordDialog->getChordNameForLibraryState(state, this->notation));
							}
						}

						// Chord diagram

						PKChordDiagram *diagram = new PKChordDiagram();

						if(diagram != NULL)
						{
							if(diagram->getBinaryRepresentationVersion(chordDiagramBuffer1, chordDiagramSize1) == 1)
							{
								if(diagram->loadFromBinaryRepresentationV1(chordDiagramBuffer1, chordDiagramSize1))
								{
									newBar->setChordDiagramForIndex(0, diagram);
								}
							}

							// It was copied by setChordDiagramForIndex
							delete diagram;
						}
					}

					// Chord #2

					void *libraryStateBuffer2 = PKVALUE_BINARY_BUFFER(object->get(ChordableContentObject::LIBRARY_STATE_2_BINARY_PROPERTY));
					int   libraryStateSize2   = PKVALUE_BINARY_SIZE(object->get(ChordableContentObject::LIBRARY_STATE_2_BINARY_PROPERTY));

					void *chordDiagramBuffer2 = PKVALUE_BINARY_BUFFER(object->get(ChordableContentObject::CHORD_DIAGRAM_2_BINARY_PROPERTY));
					int   chordDiagramSize2   = PKVALUE_BINARY_SIZE(object->get(ChordableContentObject::CHORD_DIAGRAM_2_BINARY_PROPERTY));

					if(libraryStateSize2 > 0 &&
                       chordDiagramSize2 > 0 &&
				       libraryStateBuffer2 != NULL &&
                       chordDiagramBuffer2 != NULL)
					{
						// Library state

						if(libraryStateSize2 == sizeof(PKChordLibraryState))
						{
							PKChordLibraryState *state = (PKChordLibraryState *) libraryStateBuffer2;

							if(state->version == 1)
							{
								newBar->setChordLibraryStateForIndex(1, state);
								newBar->setChordNameForIndex(1, this->chordDialog->getChordNameForLibraryState(state, this->notation));
							}
						}

						// Chord diagram

						PKChordDiagram *diagram = new PKChordDiagram();

						if(diagram != NULL)
						{
							if(diagram->getBinaryRepresentationVersion(chordDiagramBuffer2, chordDiagramSize2) == 1)
							{
								if(diagram->loadFromBinaryRepresentationV1(chordDiagramBuffer2, chordDiagramSize2))
								{
									newBar->setChordDiagramForIndex(1, diagram);
								}
							}

							// It was copied by setChordDiagramForIndex
							delete diagram;
						}
					}

					// Chord #3

					void *libraryStateBuffer3 = PKVALUE_BINARY_BUFFER(object->get(ChordableContentObject::LIBRARY_STATE_3_BINARY_PROPERTY));
					int   libraryStateSize3   = PKVALUE_BINARY_SIZE(object->get(ChordableContentObject::LIBRARY_STATE_3_BINARY_PROPERTY));

					void *chordDiagramBuffer3 = PKVALUE_BINARY_BUFFER(object->get(ChordableContentObject::CHORD_DIAGRAM_3_BINARY_PROPERTY));
					int   chordDiagramSize3   = PKVALUE_BINARY_SIZE(object->get(ChordableContentObject::CHORD_DIAGRAM_3_BINARY_PROPERTY));

					if(libraryStateSize3 > 0 &&
                       chordDiagramSize3 > 0 &&
				       libraryStateBuffer3 != NULL &&
                       chordDiagramBuffer3 != NULL)
					{
						// Library state

						if(libraryStateSize3 == sizeof(PKChordLibraryState))
						{
							PKChordLibraryState *state = (PKChordLibraryState *) libraryStateBuffer3;

							if(state->version == 1)
							{
								newBar->setChordLibraryStateForIndex(2, state);
								newBar->setChordNameForIndex(2, this->chordDialog->getChordNameForLibraryState(state, this->notation));
							}
						}

						// Chord diagram

						PKChordDiagram *diagram = new PKChordDiagram();

						if(diagram != NULL)
						{
							if(diagram->getBinaryRepresentationVersion(chordDiagramBuffer3, chordDiagramSize3) == 1)
							{
								if(diagram->loadFromBinaryRepresentationV1(chordDiagramBuffer3, chordDiagramSize3))
								{
									newBar->setChordDiagramForIndex(2, diagram);
								}
							}

							// It was copied by setChordDiagramForIndex
							delete diagram;
						}
					}

					// Chord #4

					void *libraryStateBuffer4 = PKVALUE_BINARY_BUFFER(object->get(ChordableContentObject::LIBRARY_STATE_4_BINARY_PROPERTY));
					int   libraryStateSize4   = PKVALUE_BINARY_SIZE(object->get(ChordableContentObject::LIBRARY_STATE_4_BINARY_PROPERTY));

					void *chordDiagramBuffer4 = PKVALUE_BINARY_BUFFER(object->get(ChordableContentObject::CHORD_DIAGRAM_4_BINARY_PROPERTY));
					int   chordDiagramSize4   = PKVALUE_BINARY_SIZE(object->get(ChordableContentObject::CHORD_DIAGRAM_4_BINARY_PROPERTY));

					if(libraryStateSize4 > 0 &&
                       chordDiagramSize4 > 0 &&
				       libraryStateBuffer4 != NULL &&
                       chordDiagramBuffer4 != NULL)
					{
						// Library state

						if(libraryStateSize4 == sizeof(PKChordLibraryState))
						{
							PKChordLibraryState *state = (PKChordLibraryState *) libraryStateBuffer4;

							if(state->version == 1)
							{
								newBar->setChordLibraryStateForIndex(3, state);
								newBar->setChordNameForIndex(3, this->chordDialog->getChordNameForLibraryState(state, this->notation));
							}
						}

						// Chord diagram

						PKChordDiagram *diagram = new PKChordDiagram();

						if(diagram != NULL)
						{
							if(diagram->getBinaryRepresentationVersion(chordDiagramBuffer4, chordDiagramSize4) == 1)
							{
								if(diagram->loadFromBinaryRepresentationV1(chordDiagramBuffer4, chordDiagramSize4))
								{
									newBar->setChordDiagramForIndex(3, diagram);
								}
							}

							// It was copied by setChordDiagramForIndex
							delete diagram;
						}
					}

					barGrid->addChild(newBar);
					newBar->build();
					newBar->initialize(this);
					newBar->setControlRoot(rootControl);
				}

				if(type == CHORDABLE_CONTENT_OBJECT_TYPE_LINE_BREAK)
				{
					LineBreakVectorControl *lb = new LineBreakVectorControl();

					PKVariantInt32 layoutx(1);
					lb->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
					PKVariantInt32 layouty(1);
					lb->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

					lb->resize(this->barWidth, this->barHeight);
		
					PKVariantBool shared(true);
					lb->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

					barGrid->addChild(lb);
					lb->build();
					lb->initialize(this);
					lb->setControlRoot(rootControl);
				}
			}

			// Add AddBars control

			AddBarsVectorControl *add = new AddBarsVectorControl();

			PKVariantString id("ID_ADD_BARS");
			add->set(PKControl::ID_STRING_PROPERTY, &id);

			PKVariantBool hidden(true);
			add->set(PKControl::HIDDEN_BOOL_PROPERTY, &hidden);

			PKVariantInt32 layoutx(1);
			add->set(PKControl::LAYOUTX_INT32_PROPERTY, &layoutx);
			PKVariantInt32 layouty(1);
			add->set(PKControl::LAYOUTY_INT32_PROPERTY, &layouty);

			add->resize(this->barWidth, this->barHeight);

			PKVariantBool shared(true);
			add->set(PKVectorControl::SHARED_VECTOR_ENGINE_BOOL_PROPERTY, &shared);

			barGrid->addChild(add);
			add->build();
			add->initialize(this);
			add->setControlRoot(rootControl);

			// Make sure the document is all good

			this->checkLineBreaksLayout();
			this->addOverheadSpacersWhereNeeded();
            this->refreshChordsGrid();

			// And relayout

			barGrid->relayout();
		}

		// And we're done
		
		db.closeDB();
		this->redraw();

        // Reset the undo/redo stack
        PKUndoManager::getInstance()->clearUndoAndRedoState();

		return true;
	}
	
	// Reset the undo/redo stack
	PKUndoManager::getInstance()->clearUndoAndRedoState();

	return false;
}

PKGridLayout *ChordableWindow::getBarGridLayout()
{
	PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));
	return barGrid;
}

BarViewVectorControl *ChordableWindow::getSelectedBar()
{
	if(this->selection.getSize() == 1)
	{
		return this->selection.getFirstBar();
	}
	
	return NULL;
}

ChordableDocument *ChordableWindow::getCurrentDocument()
{
	return this->currentDocument;
}

bool ChordableWindow::writeCurrentDocumentToFile(std::wstring filename)
{
    bool result = false;

    if(!this->currentDocument)
    {
        return result;
    }

    PKDatabase db;

    // Create a copy of the file first
    // in case the write fails for some reason

    PKPath::moveFile(filename, filename+L".bak");

    // Now save

    if(db.createDB(filename) == PKDB_OK)
    {
		PKDBErr err = PKDB_OK;

		// Save the document object

		err = db.createTableFromObjectProperties(CHORDABLE_DOCUMENT_TABLE_V1, this->currentDocument);
        
		if(err != PKDB_OK)
		{
			// TODO: Do something
		}
		
		err = db.insertObjectIntoTable(CHORDABLE_DOCUMENT_TABLE_V1, this->currentDocument);

		if(err != PKDB_OK)
		{
			// TODO: Do something
		}

		// Save the bars & line breaks
		ChordableContentObject contentObject;
		db.createTableFromObjectProperties(CHORDABLE_CONTENTS_TABLE_V1, &contentObject);

		PKGridLayout *barGrid = dynamic_cast<PKGridLayout*>(this->findControl("ID_BAR_GRID"));

		if(barGrid != NULL)
		{
			for(uint32_t i=0; i<barGrid->getChildrenCount(); i++)
			{
				PKObject *child = barGrid->getChildAt(i);

				if(child != NULL)
				{
					BarViewVectorControl *bar = dynamic_cast<BarViewVectorControl *>(child);

					if(bar != NULL) // Insert a bar
					{
						ChordableContentObject barObject;

						PKVariantUInt8 type(CHORDABLE_CONTENT_OBJECT_TYPE_BAR);
						barObject.set(ChordableContentObject::OBJECT_TYPE_UINT8_PROPERTY, &type);

						// Setup its properties

						barObject.set(ChordableContentObject::BAR_TYPE_UINT8_PROPERTY, bar->get(BarViewVectorControl::BARTYPE_UINT8_PROPERTY));
						barObject.set(ChordableContentObject::REPEAT_LEFT_BOOL_PROPERTY, bar->get(BarViewVectorControl::REPEAT_LEFT_BOOL_PROPERTY));
						barObject.set(ChordableContentObject::REPEAT_RIGHT_BOOL_PROPERTY, bar->get(BarViewVectorControl::REPEAT_RIGHT_BOOL_PROPERTY));
						barObject.set(ChordableContentObject::SECTION_MARKER_BOOL_PROPERTY, bar->get(BarViewVectorControl::SECTION_MARKER_BOOL_PROPERTY));
						barObject.set(ChordableContentObject::SECTION_NUMBER_UINT32_PROPERTY, bar->get(BarViewVectorControl::SECTION_NUMBER_UINT32_PROPERTY));
						barObject.set(ChordableContentObject::HEADER_WSTRING_PROPERTY, bar->get(BarViewVectorControl::HEADER_WSTRING_PROPERTY));

						// Chord #1

						PKChordLibraryState *state1 = bar->getChordLibraryStateForIndex(0);
						PKChordDiagram      *cdiag1 = bar->getChordDiagramForIndex(0);

						if(state1 != NULL && cdiag1 != NULL)
						{
							PKVariantBinary binaryState(sizeof(PKChordLibraryState), state1);
							barObject.set(ChordableContentObject::LIBRARY_STATE_1_BINARY_PROPERTY, &binaryState);

							uint32_t chordDiagramBufferSize = 0;
							void *chordDiagramBuffer = cdiag1->createBinaryRepresentationForDiagram(&chordDiagramBufferSize);

							if(chordDiagramBuffer != NULL && chordDiagramBufferSize > 0)
							{
								PKVariantBinary binaryDiagram(chordDiagramBufferSize, chordDiagramBuffer);
								barObject.set(ChordableContentObject::CHORD_DIAGRAM_1_BINARY_PROPERTY, &binaryDiagram);

								delete [] chordDiagramBuffer;
							}
						}

						// Chord #2

						PKChordLibraryState *state2 = bar->getChordLibraryStateForIndex(1);
						PKChordDiagram      *cdiag2 = bar->getChordDiagramForIndex(1);

						if(state2 != NULL && cdiag2 != NULL)
						{
							PKVariantBinary binaryState(sizeof(PKChordLibraryState), state2);
							barObject.set(ChordableContentObject::LIBRARY_STATE_2_BINARY_PROPERTY, &binaryState);

							uint32_t chordDiagramBufferSize = 0;
							void *chordDiagramBuffer = cdiag2->createBinaryRepresentationForDiagram(&chordDiagramBufferSize);

							if(chordDiagramBuffer != NULL && chordDiagramBufferSize > 0)
							{
								PKVariantBinary binaryDiagram(chordDiagramBufferSize, chordDiagramBuffer);
								barObject.set(ChordableContentObject::CHORD_DIAGRAM_2_BINARY_PROPERTY, &binaryDiagram);

								delete [] chordDiagramBuffer;
							}
						}

						// Chord #3

						PKChordLibraryState *state3 = bar->getChordLibraryStateForIndex(2);
						PKChordDiagram      *cdiag3 = bar->getChordDiagramForIndex(2);

						if(state3 != NULL && cdiag3 != NULL)
						{
							PKVariantBinary binaryState(sizeof(PKChordLibraryState), state3);
							barObject.set(ChordableContentObject::LIBRARY_STATE_3_BINARY_PROPERTY, &binaryState);

							uint32_t chordDiagramBufferSize = 0;
							void *chordDiagramBuffer = cdiag3->createBinaryRepresentationForDiagram(&chordDiagramBufferSize);

							if(chordDiagramBuffer != NULL && chordDiagramBufferSize > 0)
							{
								PKVariantBinary binaryDiagram(chordDiagramBufferSize, chordDiagramBuffer);
								barObject.set(ChordableContentObject::CHORD_DIAGRAM_3_BINARY_PROPERTY, &binaryDiagram);

								delete [] chordDiagramBuffer;
							}
						}

						// Chord #4

						PKChordLibraryState *state4 = bar->getChordLibraryStateForIndex(3);
						PKChordDiagram      *cdiag4 = bar->getChordDiagramForIndex(3);

						if(state4 != NULL && cdiag4 != NULL)
						{
							PKVariantBinary binaryState(sizeof(PKChordLibraryState), state4);
							barObject.set(ChordableContentObject::LIBRARY_STATE_4_BINARY_PROPERTY, &binaryState);

							uint32_t chordDiagramBufferSize = 0;
							void *chordDiagramBuffer = cdiag4->createBinaryRepresentationForDiagram(&chordDiagramBufferSize);

							if(chordDiagramBuffer != NULL && chordDiagramBufferSize > 0)
							{
								PKVariantBinary binaryDiagram(chordDiagramBufferSize, chordDiagramBuffer);
								barObject.set(ChordableContentObject::CHORD_DIAGRAM_4_BINARY_PROPERTY, &binaryDiagram);

								delete [] chordDiagramBuffer;
							}
						}

						// Write it to table

						db.insertObjectIntoTable(CHORDABLE_CONTENTS_TABLE_V1, &barObject);
					}

					LineBreakVectorControl *lb = dynamic_cast<LineBreakVectorControl *>(child);

					if(lb != NULL) // Insert a line break
					{
						ChordableContentObject lineBreakObject;

						// Just set the type

						PKVariantUInt8 type(CHORDABLE_CONTENT_OBJECT_TYPE_LINE_BREAK);
						lineBreakObject.set(ChordableContentObject::OBJECT_TYPE_UINT8_PROPERTY, &type);
						
						// Write it to table

						db.insertObjectIntoTable(CHORDABLE_CONTENTS_TABLE_V1, &lineBreakObject);
					}
				}
			}
		}

		db.closeDB();
        result = true;
    }
    
    // TODO: Try loading the file back
    // and verify it's all good, maybe ??

    // Cleanup the backup

    PKPath::deleteFile(filename+L".bak");

    return result;
}



