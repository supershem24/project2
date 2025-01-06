/**
 * @file AdapterMachineDrawable.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include "AdapterMachineDrawable.h"
#include <machine-api.h>

#include "StartFrameDlg.h"
#include "Timeline.h"

/**
 * Constructor
 * @param name name of the drawable
 * @param resourcesDir resources directory for the factories
 */
AdapterMachineDrawable::AdapterMachineDrawable(const std::wstring& name, const std::wstring& resourcesDir) : Drawable(name)
{
    MachineSystemFactory factory(resourcesDir);
    mSystem = factory.CreateMachineSystem();

}

/**
 * Sets the machine number using the dialog box
 * @param frame the frame the dialog box will pop out of
 * @return if ok was pressed
 */
bool AdapterMachineDrawable::SetMachineNumber(wxWindow* frame)
{
    MachineDialog dialog(frame, mSystem);
    if (dialog.ShowModal() == wxID_OK)
    {

        return true;
    }
    return false;
}

/**
 * Sets the first animated machine frame using a dialog box
 * @param frame the frame the dialog box will pop out of
 * @return if ok was pressed
 */
bool AdapterMachineDrawable::SetMachineStart(wxWindow* frame)
{
    StartFrameDlg dialog(frame, this);
    return dialog.ShowModal() == wxID_OK;
}

/**
 * Calls draw on the machine
 * @param graphics graphics component
 */
void AdapterMachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = 0.75f;

    graphics->PushState();
    graphics->Scale(scale, scale);
    mSystem->SetMachineFrame(mTimeline->GetCurrentFrame() - mFrameStart);
    mSystem->DrawMachine(graphics);
    graphics->PopState();
}

/**
 * Hit test for the machine
 * @param pos the position the mouse is at
 * @return if the machine was hit
 */
bool AdapterMachineDrawable::HitTest(wxPoint pos)
{
    return false;
}

