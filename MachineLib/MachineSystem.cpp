/**
 * @file MachineSystem.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include "MachineSystem.h"
#include "MachineFactories.h"

/**
 * Constructs a machine system
 * @param resourcesDir the resources directory used for resources
 */
MachineSystem::MachineSystem(std::wstring resourcesDir)
{
    mResourcesDir = resourcesDir;
    ChooseMachine(mNumber);
}

/**
 * Draw the machine at the currently specified location
 * @param graphics Graphics object to render to
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    mMachine->Draw(graphics);
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
    if (frame < mFrame)
    {
        mFrame = 0;
        mMachine->SetTime(mTime);
        mMachine->Reset();
        mMachine->Update();
    }

    while (mFrame < frame) {
        mFrame++;
        mTime = mFrame / mFrameRate;
        mMachine->Advance(1.0/mFrameRate);
        mMachine->SetTime(mTime);
        mMachine->Update();
    }
}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystem::ChooseMachine(int machine)
{
    mNumber = machine;
    switch (mNumber)
    {
        case 1:
            {
                Machine1Factory machine1Factory = Machine1Factory(mResourcesDir);
                mMachine = machine1Factory.CreateMachine(mLocation);
                break;
            }
        case 2:
            {
                Machine2Factory machine2Factory = Machine2Factory(mResourcesDir);
                mMachine = machine2Factory.CreateMachine(mLocation);
                break;
            }
        default:
            {
                Machine1Factory machineFactory = Machine1Factory(mResourcesDir);
                mMachine = machineFactory.CreateMachine(mLocation);
                break;
            }
    }
}

/**
 * Set the flag from the control panel
 * @param flag Flag to set
 */
void MachineSystem::SetFlag(int flag)
{
}

