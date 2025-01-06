/**
 * @file Shaft.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include "Shaft.h"

/// The color to draw the shaft
const wxColour ShaftColor = wxColour(220, 220, 220);

/// The color to draw the lines on the shaft
/// First parameter to Cylinder::SetLines
const wxColour ShaftLineColor = wxColour(100, 100, 100);

/// The width to draw the lines on the shaft
/// Second parameter to Cylinder::SetLines
const int ShaftLinesWidth = 1;

/// The number of lines to draw on the shaft
/// Third parameter to Cylinder::SetLines
const int ShaftNumLines = 4;

/**
 * Constructor
 * @param diameter diameter of the shaft
 * @param length length of the shaft
 */
Shaft::Shaft(int diameter, int length)
{
    mShaft.SetSize(diameter, length);

}

/**
 * Draw the shaft at its current rotation
 * @param graphics graphics component
 * @param x x position of the shaft
 * @param y yu position of the shaft
 */
void Shaft::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mShaft.SetColour(ShaftColor);
    mShaft.SetLines(ShaftLineColor, ShaftLinesWidth, ShaftNumLines);
    mShaft.Draw(graphics, x, y, mRotation);
}

/**
 * Set the rotation of the component
 * @param rotation rotation to set it too
 */
void Shaft::SetRotation(double rotation)
{
    mRotation = rotation;
    mSource.SetRotation(mRotation);
}