/**
 * @file Cam.cpp
 * @author Shawn_Porto
 */
#include "pch.h"

#include "Cam.h"

#include "IOpenable.h"

/// Width of the cam on the screen in pixels
const double CamWidth = 17;

/// Cam diameter
const double CamDiameter = 60;

/// How big is the hole in the cam?
const double HoleSize = 8;

/// The key image
const std::wstring KeyImage = L"/key.png";

/// The key image size
const int KeyImageSize = 20;

/// The amount the key drops into the hole
const int KeyDrop = 10;

/**
 * The Cam Constructor
 * @param imagesDir the images directory
 */
Cam::Cam(std::wstring imagesDir)
{
    mKey.SetImage(imagesDir + KeyImage);
    mKey.Rectangle(-KeyImageSize/2, 0, KeyImageSize, KeyImageSize);
}

/**
 * Draw this component
 * @param graphics graphics component
 * @param x the x position of the object
 * @param y the y position of the object
 */
void Cam::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    double angle = mRotation * 2 * M_PI;
    double holeYPos = cos(angle) * CamDiameter/2;
    double holeHeight = sin(angle) * HoleSize;

    if (holeYPos <= -CamDiameter/2 + holeHeight/2)
    {
        mKey.DrawPolygon(graphics, x, y - CamDiameter/2 + KeyDrop, 0);
        if (!mIsKeyed)
        {
            OpenOpenables();
            mIsKeyed = true;
        }
    }
    else
    {
        mIsKeyed = false;
        mKey.DrawPolygon(graphics, x, y - CamDiameter/2, 0);
    }

    mCylinder.SetSize(CamDiameter, CamWidth);
    mCylinder.Draw(graphics, x - CamWidth/2, y, mRotation);

    graphics->SetBrush(*wxBLACK_BRUSH);
    if (sin(angle) > 0)
    {
        graphics->DrawEllipse(x - HoleSize/2, y + holeYPos, HoleSize, holeHeight);
    }
}

/**
 * Opens all the openables that cam has access to
 */
void Cam::OpenOpenables()
{
    for (auto openable : mOpenables)
    {
        openable->Open();
    }
}

/**
 * Adds a new openable that cam gets access too
 * @param openable openable cam can now access
 */
void Cam::AddOpenable(std::shared_ptr<IOpenable> openable)
{
    mOpenables.push_back(openable);
}

/**
 * Sets the cams rotation
 * @param rotation the rotation the cam is supposed to be at
 */
void Cam::SetRotation(double rotation)
{
    mRotation = rotation;
}

