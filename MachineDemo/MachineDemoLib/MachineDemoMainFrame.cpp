/**
 * @file MachineDemoMainFrame.cpp
 * @author Charles Owen
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

#include "MachineDemoMainFrame.h"
#include "ControlPanel.h"
#include "MachineView.h"
#include "AboutDialog.h"
#include "Controller.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 * @param machineIsolator The machine isolator that is used to create the images to use
 * @param controller The controller that controls the machine
 */
MachineDemoMainFrame::MachineDemoMainFrame(std::shared_ptr<IMachineSystemIsolator> machineIsolator,
        Controller* controller)
{
    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");
#ifdef WIN32
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif

    // Where do the images come from?
    auto standardPaths = wxStandardPaths::Get();
    auto imagesDir = standardPaths.GetResourcesDir().ToStdWstring() + ImagesDirectory;

    auto sizer = new wxBoxSizer( wxVERTICAL );

    mMachineView = new MachineView(this, machineIsolator, imagesDir);
    mControlPanel = new ControlPanel(this);

    sizer->Add(mMachineView, 1, wxEXPAND | wxALL);
    sizer->Add(mControlPanel, 0, wxEXPAND | wxALL);

    SetSizer( sizer );
    Layout();

    controller->SetWindows(this, mMachineView, mControlPanel);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MachineDemoMainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MachineDemoMainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MachineDemoMainFrame::OnClose, this);
}

/**
 * Exit menu option handlers
 * @param event Menu event
 */
void MachineDemoMainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Application about box menu handler
 * @param event Menu event
 */
void MachineDemoMainFrame::OnAbout(wxCommandEvent& event)
{
    AboutDialog aboutDlg(this);
    aboutDlg.ShowModal();
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MachineDemoMainFrame::OnClose(wxCloseEvent& event)
{
    mControlPanel->Stop();
    Destroy();
}





