/**
 * @file Cam.h
 * @author Shawn_Porto
 *
 * The cam component of the machine
 */
 
#ifndef CAM_H
#define CAM_H
#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "Polygon.h"

class IOpenable;

/**
 * The cam component of the machine
 */
class Cam : public Component, public IRotationSink
{
private:
    /// the cam's cylinder
    cse335::Cylinder mCylinder;
    /// the cam's key
    cse335::Polygon mKey;
    /// if the key is in the hole or not
    bool mIsKeyed = false;
    /// the cam's current rotation
    double mRotation = 0;
    /// the openables in the scene
    std::vector<std::shared_ptr<IOpenable>> mOpenables;
public:
    Cam(std::wstring imagesDir);

    /// Default constructor disabled
    Cam() = delete;
    /** Copy constructor disabled */
    Cam(const Cam &) = delete;
    /** Assignment operator disabled */
    void operator=(const Cam &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;
    void OpenOpenables();
    void AddOpenable(std::shared_ptr<IOpenable> openable);
    void SetRotation(double rotation) override;
};



#endif //CAM_H
