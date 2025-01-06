/**
 * @file IRotationSink.h
 * @author Shawn_Porto
 *
 * The rotation sink class for the rotation sinks
 */
 
#ifndef IROTATIONSINK_H
#define IROTATIONSINK_H

/**
 * The rotation sink class for the rotation sinks
 */
class IRotationSink
{
    public:
    /**
     * Rotate this object to the rotation
     * @param rotation the rotation to set the object's rotation to
     */
    virtual void SetRotation(double rotation) = 0;
};

#endif //IROTATIONSINK_H
