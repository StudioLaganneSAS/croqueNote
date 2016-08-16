//
// ProjectKetchup:
// ---------------
//
// Copyright (c) 2008 Damien Chavarria
//

#ifndef CHORDABLE_PREFERENCES_H
#define CHORDABLE_PREFERENCES_H

#include "PKModalDialog.h"
#include "PKStdDialog.h"
#include "ChordableSettings.h"

class ChordablePreferences : public PKModalDialog
{
public:

	ChordablePreferences(std::wstring    id,
      				     PKWindowHandle  parent,
                         ChordableSettings *settings,
                         std::wstring    icon = L"");

	~ChordablePreferences();

    // Run

    int32_t run();

protected:
        
    // From PKWindow/PKDialog

	void keyUp(unsigned int modifier,
			   PKKey        keyCode,
			   unsigned int virtualCode);

    void windowClosed();
    void buttonClicked(std::string id);

	void comboBoxChanged(std::string id, int32_t previousValue);

private:

    bool ready;
    ChordableSettings *settings;
};

#endif // CHORDABLE_PREFERENCES_H
