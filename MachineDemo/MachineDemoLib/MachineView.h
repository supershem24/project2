/**
 * @file MachineView.h
 * @author Charles Owen
 *
 * The view for our machine
 */

#ifndef CANADIANEXPERIENCE_MACHINEVIEW_H
#define CANADIANEXPERIENCE_MACHINEVIEW_H

class MachineDemoMainFrame;
class IMachineSystemIsolator;

/**
 * The view for our machine
 */
class MachineView final : public wxScrolledCanvas {
private:
    void OnPaint(wxPaintEvent& event);

    /// First time we draw
    bool mFirstDraw = true;

    /// The machine we are displaying
    std::shared_ptr<IMachineSystemIsolator> mMachineIsolator;

    /// Current machine frame
    int mFrame = 0;

    /// Zoom factor
    double mZoom = 1.0;

    /// Frame rate
    int mFrameRate = 30;

    /// The background color to use
    wxColour mBackgroundColor = *wxWHITE;

public:
    explicit MachineView(MachineDemoMainFrame *mainFrame, std::shared_ptr<IMachineSystemIsolator> machineIsolator, std::wstring imagesDir);

    void DrawAxis(std::shared_ptr<wxGraphicsContext> graphics);

    double SetFrame(int frame);

    void SetZoom(double zoom);
    void SetFlag(int flag);

    /**
     * Get the machine system we are viewing, as
     * protected by the isolator.
     * @return IMachineSystem in an isolator object
     */
    auto GetMachineIsolator() {return mMachineIsolator;}

    double GetMachineTime();

    void SetupMachine();

    /**
     * Get the frame rate
     * @return Frame rate in frames per second
     */
    auto GetFrameRate() const {return mFrameRate;}

    /**
     * Set the view background color
     * @param color Color to set
     */
    void SetBackgroundColor(const wxColour& color) {mBackgroundColor = color;}

};

#endif //CANADIANEXPERIENCE_MACHINEVIEW_H
