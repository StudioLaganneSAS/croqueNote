//
//
//

#include "ChordablePreferences.h"
#include "ChordablesPreferences_XML.h"
#include "PKLabel.h"
#include "PKButton.h"
#include "PKStr.h"

//
// ChordablePreferences
//
 
ChordablePreferences::ChordablePreferences(std::wstring    id,
              						       PKWindowHandle  parent,
                                           ChordableSettings *settings,
                                           std::wstring    icon)

:PKModalDialog(id, PK_WINDOW_STYLE_DEFAULT | 
			       PK_WINDOW_STYLE_NO_MAX  | 
			       PK_WINDOW_STYLE_NO_RESIZE,
		           parent, icon)
{
	PKVariantWString cpt(PK_i18n(L"Croque-Note"));
	this->set(PKWindow::CAPTION_WSTRING_PROPERTY, &cpt);

    this->ready = false;
    this->settings = settings;

	std::string xml = ChordablesPreferencesXML;
	this->loadFromXML(xml);

    // Setup the languages

    PKi18n *i18n = PKi18n::getInstance();
    this->clearComboBoxItems("ID_LANGUAGE_COMBO");

    for(uint32_t i=0; i<i18n->getNumberOfAvailableLocales(); i++)
    {
        std::string loc = i18n->getAvailableLocaleAt(i);
        this->addComboBoxItem("ID_LANGUAGE_COMBO", i18n->getLocalizedNameForLocale(loc));

        if(loc == PKVALUE_STRING(this->settings->get(ChordableSettings::LANGUAGE_STRING_PROPERTY)))
        {
            this->selectComboBoxItem("ID_LANGUAGE_COMBO", i);
        }
    }

    this->ready = true;
}

ChordablePreferences::~ChordablePreferences()
{
}

int32_t ChordablePreferences::run()
{	
	// Resize
	this->resizeToFit();
    return PKModalDialog::run();
}

void ChordablePreferences::windowClosed()
{
    this->terminateDialog(PK_STD_BUTTON_OK);
}

void ChordablePreferences::buttonClicked(std::string id)
{
    this->terminateDialog(PK_STD_BUTTON_OK);
}

void ChordablePreferences::keyUp(unsigned int modifier,
			                     PKKey        keyCode,
			                     unsigned int virtualCode)
{
    if(keyCode == PK_KEY_ESCAPE)
    {
        this->terminateDialog(PK_STD_BUTTON_OK);
    }
}

void ChordablePreferences::comboBoxChanged(std::string id, int32_t previousValue)
{
    if(id == "ID_LANGUAGE_COMBO" && this->ready)
    {
        int index = this->getComboBoxSelectedItem("ID_LANGUAGE_COMBO");
        std::string locale = PKi18n::getInstance()->getAvailableLocaleAt(index);

        if(this->settings)
        {
            PKVariantString new_loc(locale);
            this->settings->set(ChordableSettings::LANGUAGE_STRING_PROPERTY, &new_loc);
        }
    }
}

