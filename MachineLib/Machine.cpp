/**
 * @file Machine.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include "Machine.h"

/**
 * Constructor
 * @param location the location of the machine
 */
Machine::Machine(wxPoint location) : mLocation(location)
{

}

/**
 * Adds a component to the machine
 * @param component the component to add
 */
void Machine::AddComponent(const std::shared_ptr<Component>& component)
{
    mComponents.push_back(component);
}

/**
 * Draws the machine and all it's components
 * @param graphics the graphics component
 */
void Machine::Draw(const std::shared_ptr<wxGraphicsContext>& graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    for(auto component : mComponents)
    {
        component->Draw(graphics, component->GetPosition().x, component->GetPosition().y);
    }
    for(auto component : mComponents)
    {
        component->DrawLast(graphics, component->GetPosition().x, component->GetPosition().y);
    }
    graphics->PopState();
}

/**
 * Updates each machine with the new time
 */
void Machine::Update()
{
    for (const auto& component : mComponents)
    {
        component->Update(mTime);
    }
}
/**
 * Advances the machine by delta
 * @param delta the amount of time to advance the machine by
 */
void Machine::Advance(double delta)
{
    for (const auto& component : mComponents)
    {
        component->Advance(delta);
    }
}

/**
 * Resets the machine to where time = 0
 */
void Machine::Reset()
{
    mTime = 0;
    for (const auto& component : mComponents)
    {
        component->Reset();
    }
}



