/**
 * @file ControlPanel.h
 * @author Charles Owen
 *
 * The machine demonstrator control panel
 */

#ifndef CANADIANEXPERIENCE_CONTROLPANEL_H
#define CANADIANEXPERIENCE_CONTROLPANEL_H

class MachineDemoMainFrame;
class MachineView;


/**
 * The machine demonstrator control panel
 */
class ControlPanel final : public wxPanel {
private:
    void OnFrameSliderChanged(wxCommandEvent& event);
    void OnZoomSliderChanged(wxCommandEvent& event);
    void OnSelectMachine(wxCommandEvent& event);
    void OnRewind(wxCommandEvent& event);
    void OnPlay(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnFlagCheckboxChanged(wxCommandEvent &event);

    void SetFlag();

    void SetMachineFrame(int frame);

    /// Pointer to the machine view
    MachineView *mMachineView;

    /// The frame choice slider
    wxSlider *mFrameSlider;

    /// The static control that displays the current frame
    wxStaticText *mFrameNumberCtrl;

    /// The zoom slider
    wxSlider *mZoomSlider;

    /// The static control that displays the machine number
    wxStaticText *mMachineNumberCtrl;

    /// Machine time control
    wxStaticText *mMachineTimeCtrl;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// Are we playing?
    bool mPlaying = false;

    /// The 8 flag checkboxes
    wxCheckBox* mFlags[8];

public:
    ControlPanel(MachineDemoMainFrame *mainFrame);

    void Stop();

    void SetFrame(int frame);
    void SetMachineNumber(int machine);
};

#endif //CANADIANEXPERIENCE_CONTROLPANEL_H
