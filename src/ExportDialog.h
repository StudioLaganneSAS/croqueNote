//
//
//

#ifndef EXPORT_DIALOG_H
#define EXPORT_DIALOG_H

#include "PKModalDialog.h"

//
// ExportDialogButtonId
//

typedef enum {

    EXPORT_DIALOG_BUTTON_EXPORT,
    EXPORT_DIALOG_BUTTON_CANCEL,

} ExportDialogButtonId;

//
// ExportDialogExportType
//

typedef enum {

    EXPORT_DIALOG_EXPORT_JPEG,
    EXPORT_DIALOG_EXPORT_PNG,
    EXPORT_DIALOG_EXPORT_PDF,

} ExportDialogExportType;


//
// PKStdDialog
//

class ExportDialog : public PKModalDialog
{
public:

    ExportDialog(PKWindowHandle  parent,
                 std::wstring    caption,
                 std::wstring    icon = L"");

    ~ExportDialog();

    int32_t run();

    ExportDialogExportType getExportType();
    int32_t                getPNGSize();

    int32_t                getJPEGSize();
    float                  getJPEGQuality();

protected:

    // From PKWindow/PKDialog

    void windowClosed();
    void buttonClicked(std::string id);

private:

};

#endif // EXPORT_DIALOG_H
