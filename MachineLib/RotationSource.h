/**
 * @file RotationSource.h
 * @author Shawn_Porto
 *
 * Rotation source that connects to all the rotation sinks
 */
 
#ifndef ROTATIONSOURCE_H
#define ROTATIONSOURCE_H

class IRotationSink;

/**
 * Rotation source that connects to all the rotation sinks
 */
class RotationSource
{
private:
    /// Vector of rotation sinks that this source controls
    std::vector<std::shared_ptr<IRotationSink>> mRotationSinks;
public:
    RotationSource();

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;
    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    void AddSink(std::shared_ptr<IRotationSink> sink);
    void SetRotation(double rotation);
};



#endif //ROTATIONSOURCE_H
