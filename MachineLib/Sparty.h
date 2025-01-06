/**
 * @file Sparty.h
 * @author Shawn_Porto
 *
 * Sparty that will pop out of the box
 */
 
#ifndef SPARTY_H
#define SPARTY_H
#include "Component.h"
#include "IOpenable.h"
#include "Polygon.h"

/**
 * Sparty that will pop out of the box
 */
class Sparty : public Component, public IOpenable
{
private:
    ///whether sparty is compressed or not
    bool mCompressed = true;
    ///Sparty polygon
    cse335::Polygon mSparty;
    /// Sparty Width
    double mSpartyWidth;
    /// Spring Length
    double mSpringLength;
    /// Initial spring length
    double mCompressedLength;
public:
    Sparty(std::wstring imageDir, double size, double compressedLength);

    ///Disable constructor
    Sparty() = delete;
    /** Copy constructor disabled */
    Sparty(const Sparty &) = delete;
    /** Assignment operator disabled */
    void operator=(const Sparty &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;
    void DrawSpring(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, double length, double width,
                    int numLinks);
    void Open() override;
    //void Update(double time) override;
    void Reset() override;
    void Advance(double delta) override;
};



#endif //SPARTY_H
