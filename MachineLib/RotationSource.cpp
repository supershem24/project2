/**
 * @file RotationSource.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include "RotationSource.h"

#include "IRotationSink.h"

/**
 * Constructor
 */
RotationSource::RotationSource()
{

}

/**
 * Adds sinks that this Rotation source will change the rotation of
 * @param sink The sink to add
 */
void RotationSource::AddSink(std::shared_ptr<IRotationSink> sink)
{
    mRotationSinks.push_back(sink);
}

/**
 * Sets the rotation of all sinks
 * @param rotation the rotation to set the sinks' rotation to
 */
void RotationSource::SetRotation(double rotation)
{
    for (auto sink : mRotationSinks)
    {
        sink->SetRotation(rotation);
    }
}
