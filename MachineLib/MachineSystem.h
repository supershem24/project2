/**
 * @file MachineSystem.h
 * @author Shawn_Porto
 *
 * The System that will handle changing machines and setting framedata
 */
 
#ifndef MACHINESYSTEM_H
#define MACHINESYSTEM_H
#include "IMachineSystem.h"
#include "Machine.h"

/**
 * The System that will handle changing machines and setting framedata
 */
class MachineSystem : public IMachineSystem
{
private:
    ///Images directory
    std::wstring mResourcesDir;
    ///Current Machine number
    int mNumber = 1;
    /// Location of the machine
    wxPoint mLocation = wxPoint(200, 500);
    /// Amount of frames moved per second
    double mFrameRate = 30;
    /// Current frame the machine system is on
    int mFrame = 0;
    /// Current time the machine system is on
    double mTime = 0;
    /// Current machine in the system
    std::shared_ptr<Machine> mMachine;
public:
    ///Constructor
    MachineSystem(std::wstring mResourcesDir);
    ///Disable constructor
    MachineSystem() = delete;
    /** Copy constructor disabled */
    MachineSystem(const MachineSystem &) = delete;
    /** Assignment operator disabled */
    void operator=(const MachineSystem &) = delete;

    /**
    * Set the position for the root of the machine
    * @param location The x,y location to place the machine
    */
    void SetLocation(wxPoint location) override
    {
        mLocation = location;
        if (mMachine != nullptr)
            mMachine->SetLocation(location);
    }

    /**
     * Get the location of the machine
     * @return Location x,y in pixels as a point
     */
    wxPoint GetLocation() override {return mLocation;}

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetMachineFrame(int frame) override;

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) override {mFrameRate = rate;}

    void ChooseMachine(int machine) override;

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    int GetMachineNumber() override {return mNumber;}

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetMachineTime() override {return mTime;}


    void SetFlag(int flag) override;

};



#endif //MACHINESYSTEM_H
