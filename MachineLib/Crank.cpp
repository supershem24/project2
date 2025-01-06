/**
 * @file Crank.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include "Crank.h"

/// The width of the crank on the screen in pixels
const int CrankWidth = 10;

/// The depth of the crank away from the screen in pixels
const int CrankDepth = 20;

/// The length of the crank in pixels
const int CrankLength = 50;

/// The diameter to draw the crank handle
const int HandleDiameter = 7;

/// How long the handle is in pixels
const int HandleLength = 40;

/// How much to the left of the crank X the handle starts in pixels
const int HandleStartX = -10;

/// Crank color
const wxColour CrankColor = wxColour(220, 220, 220);

/// Line color for the rod
const wxColour CrankHandleLineColor = wxColour(100, 100, 100);

/**
 * Constructor for Crank
 * @param speed speed of the crank
 */
Crank::Crank(double speed)
{
    mSpeed = speed;
}


/**
 * Draws the crank
 * @param graphics graphics component
 * @param x x component of the component
 * @param y y component of the component
 */
void Crank::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mHandle.SetSize(HandleDiameter, HandleLength);
    mHandle.SetColour(CrankColor);
    mHandle.SetLines(CrankHandleLineColor, 1, 4);

    double angle = mRotation * 2 * M_PI;
    double crankTipPos = cos(angle) * CrankLength;
    double handleY = GetPosition().y + crankTipPos + CrankDepth/2;
    double crankHeight = fabs(crankTipPos) + CrankDepth;
    double crankY = y;
    if (crankTipPos < 0)
    {
        crankY = GetPosition().y + crankTipPos;
    }

    mHandle.Draw(graphics, GetPosition().x + HandleStartX/2, handleY, mRotation);
    graphics->DrawRectangle(x, crankY, CrankWidth, crankHeight);
}

/**
 * Advances the component by delta
 * @param delta the amount of time to advance the component by
 */
void Crank::Advance(double delta)
{
    mRotation += delta*mSpeed;
    mSource.SetRotation(mRotation);
}

/**
 * Update the component
 * @param time time the machine is currently on
 */
void Crank::Update(double time)
{
    mRotation = time * mSpeed;
    mSource.SetRotation(mRotation);
}
