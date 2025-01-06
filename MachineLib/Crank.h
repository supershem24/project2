/**
 * @file Crank.h
 * @author Shawn_Porto
 *
 * The crank component in the machine starts the rotation of the other parts
 */
 
#ifndef CRANK_H
#define CRANK_H
#include "Component.h"
#include "Cylinder.h"
#include "RotationSource.h"

/**
 * The crank component in the machine starts the rotation of the other parts
 */
class Crank : public Component
{
private:
    /// Cylinder that makes up the cranks handle
    cse335::Cylinder mHandle;
    /// Current rotation value of the crank (in turns)
    double mRotation = 0;
    /// Speed the crank will be rotating
    double mSpeed;
    /// Rotation source for this component
    RotationSource mSource;
public:
    Crank(double speed);

    ///Default Constructor disabled
    Crank() = delete;
    /** Copy constructor disabled */
    Crank(const Crank &) = delete;
    /** Assignment operator disabled */
    void operator=(const Crank &) = delete;

    /// Get a pointer to the source object
    /// @return Pointer to RotationSource object
    RotationSource *GetSource() { return &mSource; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;
    void Update(double time) override;
    void Advance(double delta) override;
    //void Reset() override;
    /**
     * Set the speed of the crank (and thus the machine)
     * @param speed the speed to set the crank to in turns per second
     */
    void SetSpeed(double speed) {mSpeed = speed;}

};



#endif //CRANK_H
