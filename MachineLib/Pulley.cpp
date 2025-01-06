/**
 * @file Pulley.cpp
 * @author Shawn_Porto
 */
#include "pch.h"

#include "Pulley.h"

#include <utility>

/// How wide the hub is on each side of the pulley
const double PulleyHubWidth = 3;

/// How deep the belt is into the pulley
const double PulleyBeltDepth = 3;

/// How wide the belt is
const double PulleyBeltWidth = 9;

/// The color to use for pulleys
const wxColour PulleyColor = wxColour(205, 250, 5);

/// The line color to use for the hub
/// First parameter to Cylinder::SetLines
const wxColour PulleyHubLineColor = wxColour(139, 168, 7);

/// The width to draw the lines on the hub
/// Second parameter to Cylinder::SetLines
const int PulleyHubLineWidth = 4;

/// The number of lines to draw on a pulley is the int(diameter / 6.0)
/// Third parameter to Cylinder::SetLines
const double PulleyHubLineCountDiviser = 6.0;

/**
 * Constructor
 * @param radius the radius of the pulley
 */
Pulley::Pulley(double radius)
{
    mRadius = radius;
}

/**
 * Draw this component
 * @param graphics graphics component
 * @param x the x position of the object
 * @param y the y position of the object
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mCylinderR.SetSize(mRadius * 2, PulleyHubWidth);
    mCylinderL.SetSize(mRadius * 2, PulleyHubWidth);
    mCylinderR.SetColour(PulleyColor);
    mCylinderL.SetColour(PulleyColor);
    mCylinderR.SetLines(PulleyHubLineColor, PulleyHubLineWidth, int(mRadius * 2 / PulleyHubLineCountDiviser));
    mCylinderL.SetLines(PulleyHubLineColor, PulleyHubLineWidth, int(mRadius * 2 / PulleyHubLineCountDiviser));
    mCylinderR.Draw(graphics, x + PulleyBeltWidth/2, y, mRotation);
    mCylinderL.Draw(graphics, x - PulleyBeltWidth/2 - PulleyHubWidth, y, mRotation);

    if (mBeltPulley != nullptr)
    {
        double distanceToOppositeBelt = mBeltPulley->GetPosition().y - GetPosition().y;
        graphics->SetPen(*wxBLACK_PEN);
        graphics->SetBrush(wxBrush(*wxBLACK_BRUSH));

        //Belt goes down
        if (distanceToOppositeBelt > 0)
        {
            graphics->DrawRectangle(x - PulleyBeltWidth/2, y - (mRadius - PulleyBeltDepth), PulleyBeltWidth,
                distanceToOppositeBelt + (mRadius - PulleyBeltDepth) + (mBeltPulley->GetRadius() - PulleyBeltDepth));
        }
        // Belt goes up
        else
        {
            graphics->DrawRectangle(x - PulleyBeltWidth/2, y + (mRadius - PulleyBeltDepth), PulleyBeltWidth,
                distanceToOppositeBelt - (mRadius - PulleyBeltDepth) - (mBeltPulley->GetRadius() - PulleyBeltDepth));
        }
    }
}

/**
 * Connet this pulley to another pulley
 * @param other the other pulley to connect to
 */
void Pulley::ConnectTo(const std::shared_ptr<Pulley>& other)
{
    mBeltPulley = other;
}

/**
 * Set the rotation of the component
 * @param rotation rotation to set it too
 */
void Pulley::SetRotation(double rotation)
{
    mRotation = rotation;
    mSource.SetRotation(mRotation);

    if (mBeltPulley != nullptr)
    {
        mBeltPulley->SetRotation(mRotation * (mRadius/mBeltPulley->GetRadius()));
    }
}
