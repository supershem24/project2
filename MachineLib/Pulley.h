/**
 * @file Pulley.h
 * @author Shawn_Porto
 *
 * Pulley connects to another pulley and changes how fast the rotation it is porpotional to the divisor of radiuses
 */
 
#ifndef PULLEY_H
#define PULLEY_H
#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "RotationSource.h"

/**
 * Pulley connects to another pulley and changes how fast the rotation it is porpotional to the divisor of radiuses
 */
class Pulley : public Component, public IRotationSink
{
private:
    ///Left cylinder of the pulley
    cse335::Cylinder mCylinderL;
    /// Right cylinder of the pulley
    cse335::Cylinder mCylinderR;
    /// Rotation of the pulley
    double mRotation = 0;
    /// Radius of the pulley
    double mRadius;
    /// Pulley connceted by belt
    std::shared_ptr<Pulley> mBeltPulley;
    /// Rotation source of this pulley
    RotationSource mSource;
public:
    Pulley(double radius);

    /// Default Constructor disabled
    Pulley() = delete;
    /** Copy constructor disabled */
    Pulley(const Pulley &) = delete;
    /** Assignment operator disabled */
    void operator=(const Pulley &) = delete;

    /// Get a pointer to the source object
    /// @return Pointer to RotationSource object
    RotationSource *GetSource() { return &mSource; }

    /// Get the radius of this pulley
    /// @return the radius of the pulley
    double GetRadius() {  return mRadius; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;
    void ConnectTo(const std::shared_ptr<Pulley>& other);
    void SetRotation(double rotation) override;


};



#endif //PULLEY_H
