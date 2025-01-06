/**
 * @file Sparty.cpp
 * @author Shawn_Porto
 */
#include "pch.h"
#include "Sparty.h"

/// The spring pen size to use in pixels
const double SpringWireSize = 2;

/// Minimum spacing between spring wire
const double SpringWireMinSpacing = 1;

/// Spring Stretched distance
const double SpringStretchedSpacing = 6;

/// Color to draw the spring
const wxColour SpringColor = wxColour(220, 220, 220);

/// Sparty popup time in seconds
const double SpartyPopupTime = 0.25;

/**
 * Sparty Constructor
 * @param spartyDir the sparty image
 * @param size size of the sparty
 * @param compressedLength length of spring when compressed
 */
Sparty::Sparty(std::wstring spartyDir, double size, double compressedLength)
{
    mSparty.Rectangle(-size/2, compressedLength / 2, size, size);
    mSpringLength = compressedLength;
    mCompressedLength = compressedLength;
    mSpartyWidth = size;
    mSparty.SetImage(spartyDir);
}

/**
 * Draw this component
 * @param graphics graphics component
 * @param x the x position of the object
 * @param y the y position of the object
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    DrawSpring(graphics, x, y, mSpringLength, mSpartyWidth/3, mCompressedLength/3);
    mSparty.DrawPolygon(graphics, x, y-mSpringLength);
}

/**
 * Draw a spring.
 * @param graphics Graphics context to render to
 * @param x X location of the bottom center of the spring in pixels
 * @param y Y location of the bottom center of the spring in pixels
 * @param length Length to draw the spring (bottom to top) in pixels
 * @param width Spring width in pixels
 * @param numLinks Number of links (loops) in the spring
 */
void Sparty::DrawSpring(std::shared_ptr<wxGraphicsContext> graphics,
                        int x, int y, double length, double width, int numLinks)
{
    auto path = graphics->CreatePath();

    // We keep track of three locations, the bottom of which
    // is y1. First half-loop will be y1 to y3, second half-loop
    // will be y3 to y2.
    double y1 = y;
    double linkLength = length / numLinks;

    // Left and right X values
    double xR = x + width / 2;
    double xL = x - width / 2;

    path.MoveToPoint(x, y1);

    for(int i=0; i<numLinks; i++)
    {
        auto y2 = y1 - linkLength;
        auto y3 = y2 - linkLength / 2;

        path.AddCurveToPoint(xR, y1, xR, y3, x, y3);
        path.AddCurveToPoint(xL, y3, xL, y2, x, y2);

        y1 = y2;
    }

    graphics->StrokePath(path);
}

/**
 * Open the sparty! (Makes it spring up)
 */
void Sparty::Open()
{
    mCompressed = false;
}

/**
 * Reset the sparty to be closed
 */
void Sparty::Reset()
{
    mSpringLength = mCompressedLength;
    mCompressed = true;
}

/**
 * Advance the sparty forward in time
 * @param delta amount to advance sparty
 */
void Sparty::Advance(double delta)
{
    Component::Advance(delta);

    double openLength = mCompressedLength * SpringStretchedSpacing;

    if(!mCompressed && mSpringLength < openLength)
    {
        mSpringLength += openLength * delta / SpartyPopupTime;

        if(mSpringLength > openLength)
        {
            mSpringLength = openLength;
        }
    }
}
