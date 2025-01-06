/**
 * @file Box.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include "Box.h"
#include "Polygon.h"

/// The background image to use
const std::wstring BoxBackgroundImage = L"/box-background.png";

/// The foreground image to use
const std::wstring BoxForegroundImage = L"/box-foreground.png";

/// The lid image to use
const std::wstring BoxLidImage = L"/box-lid.png";

/// The horizontal scale for the lid when the angle is zero
const double LidZeroAngleScale = 0.02;

/// How long it takes to up the lid in seconds
const double LidOpeningTime = 0.25;

/**
 * Constructor of box
 * @param imagesDir the images directory to pull the images from
 * @param boxSize the width and height of the box in pixels
 * @param lidSize the width and height of the lid in pixels
 */
Box::Box(std::wstring imagesDir, int boxSize, int lidSize)
{
    mBoxSize = boxSize;
    mBackground.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
    mBackground.SetImage(imagesDir + BoxBackgroundImage);
    mLid.Rectangle(-lidSize/2, 0, lidSize, lidSize);
    mLidAngle = 0;
    mLidHeight = LidZeroAngleScale;
    mLid.SetImage(imagesDir + BoxLidImage);
    mForeground.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
    mForeground.SetImage(imagesDir + BoxForegroundImage);
}

/**
 * Draw this component
 * @param graphics graphics component
 * @param x the x position of the object
 * @param y the y position of the object
 */
void Box::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{

    mBackground.DrawPolygon(graphics, x, y);
    graphics->PushState();
    //graphics->Translate(GetPosition().x, GetPosition().y - mBoxSize);
    graphics->Translate(x, y - mBoxSize);
    graphics->Scale(1, mLidHeight);
    mLid.DrawPolygon(graphics, x, y);
    graphics->PopState();
}

/**
 * Draw this part last
 * @param graphics graphics component
 * @param x the x position of the object
 * @param y the y position of the object
 */
void Box::DrawLast(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mForeground.DrawPolygon(graphics, x, y);
}

/**
 * Open the box
 */
void Box::Open()
{
    mIsOpen = true;
}

/**
 * Advance the animation in time
 * @param delta Amount of time to advance in seconds
 */
void Box::Advance(double delta)
{
    Component::Advance(delta);	// Upcall

    double openAngle = M_PI / 2;

    if(mIsOpen && mLidAngle < openAngle)
    {
        mLidAngle += openAngle * delta / LidOpeningTime;
        mLidHeight = sin(mLidAngle);

        if(mLidAngle > openAngle)
        {
            mLidAngle = openAngle;
            mLidHeight = sin(mLidAngle);
        }
    }
}

/**
 * Reset the box to where time = 0
 */
void Box::Reset()
{
    mIsOpen = false;
    mLidHeight = LidZeroAngleScale;
    mLidAngle = 0;
}
