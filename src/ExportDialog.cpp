//
//
//

#include "ExportDialog.h"
#include "ExportDialog_XML.h"
#include "PKLabel.h"
#include "PKButton.h"
#include "PKLittleArrows.h"
#include "PKStr.h"

//
// ExportDialog
//

ExportDialog::ExportDialog(PKWindowHandle  parent,
                           std::wstring    caption,
                           std::wstring    icon)
:PKModalDialog(L"CHORDABLE_EXPORT_DIALOG", 
               PK_WINDOW_STYLE_DEFAULT | 
               PK_WINDOW_STYLE_NO_MAX  | 
               PK_WINDOW_STYLE_NO_RESIZE|
			   PK_WINDOW_STYLE_SHEET,
               parent, icon)
{
    PKVariantWString c(caption);
    this->set(PKWindow::CAPTION_WSTRING_PROPERTY, &c);
}

ExportDialog::~ExportDialog()
{
}

int32_t ExportDialog::run()
{
    // Load
    std::string xml = exportDialogXML;
    this->loadFromXML(xml);

    // Setup
	
    PKControl *pngEdit = this->findControl("ID_PNG_EDIT");

    if(pngEdit)
    {
        PKLittleArrows *arrows = dynamic_cast<PKLittleArrows*>(this->findControl("ID_PNG_ARROWS"));

        if(arrows)
        {
            arrows->setBuddyControl(pngEdit);
        }
    }


    PKControl *jpegEdit = this->findControl("ID_JPEG_EDIT");
	
    if(jpegEdit)
    {
        PKLittleArrows *arrows = dynamic_cast<PKLittleArrows*>(this->findControl("ID_JPEG_ARROWS"));
		
        if(arrows)
        {
            arrows->setBuddyControl(jpegEdit);
        }
    }

    // Update UI
    this->updateUIStrings();

    // Resize
    this->resizeToFit();

    // Run
    return PKModalDialog::run();
}

ExportDialogExportType ExportDialog::getExportType()
{
    // Check what tab is selected
    int32_t tab = this->getArrowTabControlTab("ID_TAB_CONTROL");

    if(tab == 0)
    {
        return EXPORT_DIALOG_EXPORT_JPEG;
    }

    if(tab == 1)
    {
        return EXPORT_DIALOG_EXPORT_PNG;
    }
 
    return EXPORT_DIALOG_EXPORT_PDF;
}

int32_t ExportDialog::getPNGSize()
{
    std::wstring text = this->getEditText("ID_PNG_EDIT");
    return PKStr::wstringToInt32(text);
}

int32_t ExportDialog::getJPEGSize()
{
    std::wstring text = this->getEditText("ID_JPEG_EDIT");
    return PKStr::wstringToInt32(text);
}

float ExportDialog::getJPEGQuality()
{
	int32_t val = this->getSliderValue("ID_JPEG_SLIDER");
    return (float) val / 100.0;
}

void ExportDialog::windowClosed()
{
    this->terminateDialog(EXPORT_DIALOG_BUTTON_CANCEL);
}

void ExportDialog::buttonClicked(std::string id)
{
    if(id == "ID_BUTTON_EXPORT")
    {
        this->terminateDialog(EXPORT_DIALOG_BUTTON_EXPORT);
    }

    if(id == "ID_BUTTON_CANCEL")
    {
        this->terminateDialog(EXPORT_DIALOG_BUTTON_CANCEL);
    }
}


