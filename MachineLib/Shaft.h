/**
 * @file Shaft.h
 * @author Shawn_Porto
 *
 * Shafts that will be rotated and rotate other components
 */
 
#ifndef SHAFT_H
#define SHAFT_H
#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "RotationSource.h"

/**
 * Shafts that will be rotated and rotate other components
 */
class Shaft : public Component, public IRotationSink
{
private:
    /// The cylinder that makes up the visible shaft
    cse335::Cylinder mShaft;
    /// The current rotation of the shaft
    double mRotation = 0;
    /// Rotation source for this component
    RotationSource mSource;
public:
    Shaft(int diameter, int length);

    ///Default constructor disabled
    Shaft() = delete;
    /** Copy constructor disabled */
    Shaft(const Shaft &) = delete;
    /** Assignment operator disabled */
    void operator=(const Shaft &) = delete;

    /// Get a pointer to the source object
    /// @return Pointer to RotationSource object
    RotationSource *GetSource() { return &mSource; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;
    void SetRotation(double rotation) override;

};



#endif //SHAFT_H
