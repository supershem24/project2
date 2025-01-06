/**
 * @file MachineDemoMainFrame.h
 * @author Charles Owen
 *
 * The top-level (main) frame of the application
 */

#ifndef CANADIANEXPERIENCE_MACHINEDEMOMAINFRAME_H
#define CANADIANEXPERIENCE_MACHINEDEMOMAINFRAME_H

class MachineView;
class ControlPanel;
class IMachineSystemIsolator;
class Controller;

/**
 * The top-level (main) frame of the application
 */
class MachineDemoMainFrame final : public wxFrame {
private:
    /// Pointer to the machine view window
    MachineView* mMachineView;

    /// Pointer to the control panel window
    ControlPanel* mControlPanel;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

public:
    MachineDemoMainFrame(std::shared_ptr<IMachineSystemIsolator> machineIsolator, Controller* controller);

    /// Default constructor (disabled)
    MachineDemoMainFrame() = delete;

    /// Copy constructor (disabled)
    MachineDemoMainFrame(const MachineDemoMainFrame &) = delete;

    /// Assignment operator
    void operator=(const MachineDemoMainFrame &) = delete;

    /**
     * Get a pointer to the machine view
     * @return MachineView pointer
     */
    MachineView *GetMachineView() {return mMachineView;}
};

#endif //CANADIANEXPERIENCE_MACHINEDEMOMAINFRAME_H
