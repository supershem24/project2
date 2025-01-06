/**
 * @file Box.h
 * @author Shawn_Porto
 *
 * The box component of the machine
 */
 
#ifndef BOX_H
#define BOX_H
#include "Component.h"
#include "IOpenable.h"
#include "Polygon.h"

/**
 * The box component of the machine
 */
class Box : public Component, public IOpenable
{
private:
    /// tells if the box is open
    bool mIsOpen = false;
    /// lid polygon
    cse335::Polygon mLid;
    /// multiplier of the lid's height
    double mLidAngle;
    /// Lid's height
    double mLidHeight;
    /// foreground polygon
    cse335::Polygon mForeground;
    /// box background polygon
    cse335::Polygon mBackground;
    /// box size
    double mBoxSize;
public:
    Box(std::wstring imagesDir, int boxSize, int lidSize);

    ///Disable constructor
    Box() = delete;
    /** Copy constructor disabled */
    Box(const Box &) = delete;
    /** Assignment operator disabled */
    void operator=(const Box &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;
    void DrawLast(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;
    void Open() override;
    void Advance(double delta) override;
    //void Update(double time) override;
    void Reset() override;
};



#endif //BOX_H
