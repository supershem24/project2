/**
 * @file StartFrameDlg.h
 * @author Shawn_Porto
 *
 * Start frame dialog box
 */
 
#ifndef STARTFRAMEDLG_H
#define STARTFRAMEDLG_H


class AdapterMachineDrawable;

/**
 * Start frame dialog box
 */
class StartFrameDlg final : public wxDialog {
private:
    void OnOK(wxCommandEvent& event);

    /// The pointer to the Machine Adapter
    AdapterMachineDrawable* mMachineAdapter;

    /// Starting frame for the machine
    int mStartFrame;

public:
    StartFrameDlg(wxWindow* parent, AdapterMachineDrawable* machineAdapter);
};



#endif //STARTFRAMEDLG_H
