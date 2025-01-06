/**
 * @file AdapterMachineDrawable.h
 * @author Shawn_Porto
 *
 * Creates the Adapter for the Machines to a drawable
 */
 
#ifndef ADAPTERMACHINEDRAWABLE_H
#define ADAPTERMACHINEDRAWABLE_H
#include "Drawable.h"
#include "Timeline.h"
#include "../MachineLib/MachineSystem.h"

/**
 * Creates the Adapter for the Machines to a drawable
 */
class AdapterMachineDrawable : public Drawable
{
private:
    /// what frame does the machine start the timer
    int mFrameStart = 0;
    /// the machine system in question
    std::shared_ptr<IMachineSystem> mSystem;
    /// The timeline this machine is on
    Timeline* mTimeline;
public:
    AdapterMachineDrawable(const std::wstring& name, const std::wstring& resourcesDir);

    /// Default constructor (disabled)
    AdapterMachineDrawable() = delete;
    /// Copy constructor (disabled)
    AdapterMachineDrawable(const AdapterMachineDrawable &) = delete;
    /// Assignment operator
    void operator=(const AdapterMachineDrawable &) = delete;

    bool SetMachineNumber(wxWindow* frame);
    bool SetMachineStart(wxWindow* frame);

    /**
     * Sets when the machine animation starts
     * @param frameStart the frame the machine starts
     */
    void SetFrameStart(int frameStart) { mFrameStart = frameStart; }

    /**
     * Gets the frame the machine starts
     * @return the frame that the machine starts
     */
    int GetFrameStart() { return mFrameStart; }

    /**
     * Sets the machine number
     * @param machineNumber the frame the machine starts
     */
    void SetMachineNumberInt(int machineNumber) { mSystem->ChooseMachine(machineNumber); }

    /**
     * Gets the machineNumber
     * @return the machineNumber
     */
    int GetMachineNumber() { return mSystem->GetMachineNumber(); }



    /**
     * Sets the timeline
     * @param timeline the timeline the machine is on
     */
    void SetTimeline(Timeline* timeline) override
    {
        Drawable::SetTimeline(timeline);
        mTimeline = timeline;
        mSystem->SetFrameRate(mTimeline->GetFrameRate());
    }

    /**
     * Gets the timeline
     * @return the timeline
     */
    Timeline* GetTimeline() { return mTimeline; }

    /**
     * Sets the position of the drawable
     * @param pos the position to set the drawable to
     */
    void SetPosition(wxPoint pos) override
    {
        Drawable::SetPosition(pos);
        if (mSystem != nullptr)
        {
            mSystem->SetLocation(pos);
        }
    }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(wxPoint pos) override;
};



#endif //ADAPTERMACHINEDRAWABLE_H
