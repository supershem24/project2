/**
 * @file MachineView.cpp
 * @author Charles Owen
 */

#include "pch.h"

#include <wx/dcbuffer.h>

#include "MachineView.h"
#include "MachineDemoMainFrame.h"
#include "IMachineSystemIsolator.h"


/// View width
const int ViewWidth = 1200;

/// View height
const int ViewHeight = 800;

/// Amount we offset the X origin into the window in pixel
const int OffsetX = 150;

/// Amount we offset the Y origin into the window in pixel
const int OffsetY = 125;

/// How long to draw the coordinate axis in pixels
const int AxisLength = 70;

/// Length of the coordinate axis arrows in pixels
const int ArrowLength = 10;

/// Width of the coordinate axis arrows in pixels
const int ArrowWidth = 10;

/**
 * Constructor
 * @param mainFrame Parent MainFrame object
 * @param machineIsolator The machine isolator that takes care of creating machines
 * @param imagesDir Directory containing images
 */
MachineView::MachineView(MachineDemoMainFrame* mainFrame,
        std::shared_ptr<IMachineSystemIsolator> machineIsolator, std::wstring imagesDir) :
    wxScrolledCanvas(mainFrame, wxID_ANY), mMachineIsolator(machineIsolator)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &MachineView::OnPaint, this);

    SetupMachine();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void MachineView::OnPaint(wxPaintEvent& event)
{
    auto size = wxSize((int)(ViewWidth * mZoom), (int)(ViewHeight * mZoom));
    SetVirtualSize(size.GetWidth(), size.GetHeight());

    SetScrollRate(1, 1);

    auto clientSize = GetClientSize();

    if(mFirstDraw)
    {
        Scroll((size.GetWidth() - clientSize.GetWidth()) / 2,
                (size.GetHeight() - clientSize.GetHeight()) / 2);

    }

    auto pos = GetScrollPos(wxHORIZONTAL);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(mBackgroundColor);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    graphics->PushState();
    graphics->Scale(mZoom, mZoom);
    graphics->Translate(OffsetX, OffsetY);

    DrawAxis(graphics);

    mMachineIsolator->DrawMachine(graphics);

    graphics->PopState();
    mFirstDraw = false;
}

/**
 * Draw the x,y coordinate axis.
 * @param graphics Graphics object to draw on
 */
void MachineView::DrawAxis(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetPen(*wxWHITE_PEN);
    graphics->StrokeLine(0, 0, AxisLength, 0);
    graphics->StrokeLine(AxisLength-ArrowLength, 0-ArrowWidth/2, AxisLength, 0);
    graphics->StrokeLine(AxisLength-ArrowLength, 0+ArrowWidth/2, AxisLength, 0);

    graphics->StrokeLine(0, 0, 0, AxisLength);
    graphics->StrokeLine(0-ArrowWidth/2, AxisLength-ArrowLength, 0, AxisLength);
    graphics->StrokeLine(0+ArrowWidth/2, AxisLength-ArrowLength, 0, AxisLength);

    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxWHITE);

    graphics->DrawText(L"X", AxisLength + 5, -8);
    graphics->DrawText(L"Y", -6, AxisLength + 5);

    wxFont font2(wxSize(0, 10),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font2, *wxWHITE);

    graphics->DrawText(L"(0,0)", 3, -14);

}

/**
 * Set the machine frame
 * @param frame Frame number
 * @return The new computed machine time
 */
double MachineView::SetFrame(int frame)
{
    mFrame = frame;
    mMachineIsolator->SetMachineFrame(mFrame);
    Refresh();

    return mMachineIsolator->GetMachineTime();
}


/**
 * Set the zoom factor.
 *
 * This attempts to keep the center of the image the same during zoom.
 * @param zoom New zoom factor
 */
void MachineView::SetZoom(double zoom)
{
    // What is the center of the window?
    auto windowSize = GetClientSize();
    auto center = CalcUnscrolledPosition(wxPoint(windowSize.GetWidth() / 2, windowSize.GetHeight()/2));

    auto z1 = mZoom;
    auto z2 = zoom;

    auto viewStart = GetViewStart();

    // Set the new virtual size
    mZoom = zoom;
    auto size = wxSize((int)(ViewWidth * mZoom), (int)(ViewHeight * mZoom));
    SetVirtualSize(size.GetWidth(), size.GetHeight());

    auto viewStartX = lround(viewStart.x + center.x * (z2 - z1));
    if(viewStartX < 0)
    {
        viewStartX = 0;
    }

    auto viewStartY = lround(viewStart.y + center.y * (z2 - z1));
    if(viewStartY < 0)
    {
        viewStartY = 0;
    }

    Scroll(viewStartX, viewStartY);

    Refresh();
}

/**
 * Get the current machine time
 * @return Machine time in seconds
 */
double MachineView::GetMachineTime()
{
    return mMachineIsolator->GetMachineTime();
}

/**
 * Set up the machine:
 *  Location on screen
 *  Frame rate
 *  Current frame
 */
void MachineView::SetupMachine()
{
    mMachineIsolator->SetLocation(wxPoint(ViewWidth/2 - OffsetX, ViewHeight - 150 - OffsetY));

    mMachineIsolator->SetFrameRate(mFrameRate);
    mMachineIsolator->SetMachineFrame(mFrame);

    Refresh();
}

/**
 * Set the flag
 * @param flag Flag value to set
 */
void MachineView::SetFlag(int flag)
{
    mMachineIsolator->SetFlag(flag);
    Refresh();
}
