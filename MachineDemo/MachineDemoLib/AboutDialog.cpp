/**
 * @file AboutDialog.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>
#include <sstream>
#include <iomanip>

#include "AboutDialog.h"
#include "Config.h"

using namespace std;

/**
 * Constructor
 * @param parent Parent window
 */
AboutDialog::AboutDialog(wxWindow* parent)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"AboutDialog");

    auto versionCtrl = XRCCTRL(*this, "MachineDemoVersion", wxStaticText);

    wstringstream str;
    str << L"Version " << MachineDemoVersionMajor << L"." <<
        setfill(L'0') << setw(2) << MachineDemoVersionMinor << L"." <<
        setfill(L'0') << setw(2) << MachineDemoVersionPatch;
    versionCtrl->SetLabel(str.str());
}
