//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHORDABLE_WINDOW_H
#define CHORDABLE_WINDOW_H

// PK Includes

#include "PKDialog.h"
#include "PKMenu.h"
#include "PKToolbar.h"
#include "PKSafeEvents.h"
#include "PKGridLayout.h"

// Chordables includes

#include "ChordableDocument.h"
#include "ChordableFactory.h"
#include "BarViewVectorControl.h"
#include "PKChordLibraryDialog.h"
#include "ChordableSettings.h"
#include "ChordablePreferences.h"
#include "LineBreakVectorControl.h"
#include "ChordableContentObject.h"
#include "ChordableSelection.h"

//
// ChordableWindow
//

class ChordableWindow : public PKDialog, public IPKSafeEventHandler
{
public:
	
    ChordableWindow(std::wstring icon, 
                    ChordableSettings *settings);

	~ChordableWindow();

    void setReady();
	void layoutInitialDocument();

	// App methods
	
	void newDocument();
	void openDocument(std::wstring fileName = L"");
	bool saveCurrentDocument();
    void exportDocument();
	
	// PKSafeEvents

	void processSafeEvent(std::string  eventName,
						  void        *payload);

	// Callbacks

	void windowClosed();

	void filesDropped(std::vector<std::wstring> files);

	void menuItemClicked(PKMenu *fromMenu,
                         PKMenuItem *item,
                         std::string id);
	
	void toolbarItemClicked(PKToolbar *toolbar,
	   		  	 		    PKToolbarItem *item,
							std::string id);

    void toolbarSegmentedItemSwitched(PKToolbar *toolbar,
		   				              PKToolbarSegmentedItem *item,
									  std::string id, 
                                      int32_t selection);
   
	void checkBoxAction(std::string id, bool previousValue);
	void comboBoxChanged(std::string id, int32_t previousValue);
	
	void sliderChanged(std::string id, int32_t previousValue);

    void editTextChanged(std::string id, 
                         std::wstring text);	

	void editTextEditingEnded(std::string id, 
							  std::wstring oldValue, 
							  std::wstring newValue);

	void editableVectorLabelTextChanged(std::string id);

    virtual void editableVectorLabelEditEnded(std::string id, 
        									  std::wstring oldValue, 
		        							  std::wstring newValue);
    
    void bitmapToggleButtonToggled(std::string id,
								   PKBitmapToggleButton *button,
								   bool previousValue);

	void customControlClicked(PKButtonType button,
                              std::string id,
                              PKCustomControl *control,
                              std::string partCode);

    void customControlDoubleClicked(PKButtonType button,
									std::string id,
									PKCustomControl *control,
									std::string partCode);
	
    void vectorControlRootMouseMove(std::string id,
                                    int32_t x,
                                    int32_t y);
    
    void vectorControlRootMouseLeave(std::string id);

    void selectorControlChanged(std::string id, int32_t oldValue);

    void editableVectorLabelEditStarted(std::string id);

    void buttonClicked(std::string id);

	void windowMoved();
    void windowResized();

public:

	PKGridLayout *getBarGridLayout();
	BarViewVectorControl *getSelectedBar();
	ChordableDocument *getCurrentDocument();

    bool writeCurrentDocumentToFile(std::wstring filename);
    bool openDocumentAtPath(std::wstring filename);

    void updateBarProperties(BarViewVectorControl *bar, bool updateSelector);
    void disableBarProperties();

	void toggleOverheadSpaceForBar(BarViewVectorControl *bar, bool onOff);
	void removeLineBreak(LineBreakVectorControl *lbreak);
	
	void removeAllLineBreaksSpacers();
	void checkLineBreaksLayout();

	void removeAllOverheadSpacers();
	void addOverheadSpacersWhereNeeded();

    void addChordToChordsGrid(PKChordDiagram *diagram, 
                              std::wstring name, 
                              BarViewVectorControl *forBar,
                              int forIndex);
    void refreshChordsGrid();

	void setNeedsSave();
	void selectionChanged();

	void exportToJPEGFile(std::wstring file, float quality);
	void exportToPNGFile(std::wstring file);
	void exportToPDFFile(std::wstring file);
	
private:
	PKToolbar *toolbar;
    bool ready;
	bool needsSave;
    bool ignoreTuning;
    bool ignoreSetSave;
	ChordableDocument *currentDocument;
	std::wstring       currentFileName;
	ChordableFactory   factory;
    PKChordLibraryDialog *chordDialog;
	std::vector<PKTuning*> tunings;
    PKNotationName notation; 
    ChordableSettings *settings;
    int defaultZoom;
	int barWidth;
	int barHeight;
	ChordableSelection selection;
};

#endif // CHORDABLE_WINDOW_H

