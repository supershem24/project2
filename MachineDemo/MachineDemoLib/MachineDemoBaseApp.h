/**
 * @file MachineDemoBaseApp.h
 * @author Charles Owen
 *
 * Base class for the MachineDemo application class
 */

#ifndef CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H
#define CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H

#include "Controller.h"

class IMachineSystemIsolator;

/**
 * Base class for the MachineDemo application class
 * This ia an abstract class.
 */
class MachineDemoBaseApp : public wxApp {
private:
    /// The application command-line-based controller
    Controller mController;

    /// The program main frame
    MachineDemoMainFrame* mMainFrame = nullptr;

public:
    bool OnInit() override;
    int OnExit() override;

    /**
     * Create the machine isolator, which contains the machine we are displaying.
     * @param resourcesDir Directory containing the resources for the program
     * @return MachineSystemIsolator object
     */
    virtual std::shared_ptr<IMachineSystemIsolator> CreateMachineIsolator(std::wstring resourcesDir) = 0;

    bool OnCmdLineParsed(wxCmdLineParser & 	parser) override;

    void OnInitCmdLine(wxCmdLineParser& parser) override;

    void SetBackgroundColor(const wxColour& color);
};

#endif //CANADIANEXPERIENCE_MACHINEDEMOBASEAPP_H
