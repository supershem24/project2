/**
 * @file StartFrameDlg.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include <machine-api.h>

#include "StartFrameDlg.h"
#include "AdapterMachineDrawable.h"

/**
 * Constructor
 * @param parent The parent window we will center in
 * @param machineAdapter Pointer to the Machine Adapter we are editing
 */
StartFrameDlg::StartFrameDlg(wxWindow* parent, AdapterMachineDrawable* machineAdapter) : mMachineAdapter(machineAdapter)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"MachineStartFrameDlg");

    mStartFrame = mMachineAdapter->GetFrameStart();

    Bind(wxEVT_BUTTON, &StartFrameDlg::OnOK, this, wxID_OK);

    auto startFrameCtrl = XRCCTRL(*this, "StartFrameDlgStartFrame", wxTextCtrl);
    wxIntegerValidator<int> startFrameValidator(&mStartFrame);
    startFrameValidator.SetRange(0, 10000);
    startFrameCtrl->SetValidator(startFrameValidator);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void StartFrameDlg::OnOK(wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        // Success! Set values in the class
        mMachineAdapter->SetFrameStart(mStartFrame);

        EndModal(wxID_OK);
    }
}