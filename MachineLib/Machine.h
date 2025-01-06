/**
 * @file Machine.h
 * @author Shawn_Porto
 *
 * Physical machine that has all the components in it
 */
 
#ifndef MACHINE_H
#define MACHINE_H

#include <vector>

#include "Component.h"

/**
 * Physical machine that has all the components in it
 */
class Machine
{
private:
    ///Time that the machine is currently on
    double mTime = 0;
    ///Position of the machine
    wxPoint mLocation;
    /// Components that this machine has
    std::vector<std::shared_ptr<Component>> mComponents;
public:
    Machine(wxPoint location);

    ///Disable constructor
    Machine() = delete;
    /** Copy constructor disabled */
    Machine(const Machine &) = delete;
    /** Assignment operator disabled */
    void operator=(const Machine &) = delete;

    void AddComponent(const std::shared_ptr<Component>& component);
    void Draw(const std::shared_ptr<wxGraphicsContext>& graphics);

    /**
    * Set the current machine time
    * @param time Time the machine is at
    */
    void SetTime(double time) { mTime = time; }
    /**
     * Get the current machine time
     * @return time that the machine is at
     */
    double GetTime() { return mTime; }

    /**
    * Set the current machine location
    * @param location location the machine is at
    */
    void SetLocation(wxPoint location) { mLocation = location; }
    /**
     * Get the current machine location
     * @return location that the machine is at
     */
    wxPoint GetLocation() { return mLocation; }

    void Update();

    void Reset();
    void Advance(double delta);
};



#endif //MACHINE_H
