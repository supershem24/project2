/**
 * @file Picture.cpp
 * @author Charles B. Owen
 */
#include "pch.h"
#include <wx/stdpaths.h>

#include "Picture.h"
#include "PictureObserver.h"
#include "Actor.h"
#include "AdapterMachineDrawable.h"


/**
 * Constructor
*/
Picture::Picture()
{
}


/**
 * Set the current animation time
 *
 * This forces the animation of all
 * objects to the current animation location.
 * @param time The new time.
 */
void Picture::SetAnimationTime(double time)
{
    mTimeline.SetCurrentTime(time);
    UpdateObservers();

    for (auto actor : mActors)
    {
        actor->GetKeyframe();
    }
}

/**
 * Get the current animation time.
 * @return The current animation time
 */
double Picture::GetAnimationTime()
{
    return mTimeline.GetCurrentTime();
}

/**
 * Add an observer to this picture.
 * @param observer The observer to add
 */
void Picture::AddObserver(PictureObserver* observer)
{
    mObservers.push_back(observer);
}

/**
 * Remove an observer from this picture
 * @param observer The observer to remove
 */
void Picture::RemoveObserver(PictureObserver* observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/**
 * Advance all observers to indicate the picture has changed.
 */
void Picture::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}

/**
 * Draw this picture on a device context
 * @param graphics The device context to draw on
 */
void Picture::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto actor : mActors)
    {
        actor->Draw(graphics);
    }
}

/**
 * Add an actor to this drawable.
 * @param actor Actor to add
 */
void Picture::AddActor(std::shared_ptr<Actor> actor)
{
    mActors.push_back(actor);
    actor->SetPicture(this);
}

/**
 * Puts a new machine adapter in the picture
 * @param machineAdapter machine adapter to put in the picture
 */
void Picture::AddMachineAdapter(std::shared_ptr<AdapterMachineDrawable> machineAdapter)
{
    machineAdapter->SetTimeline(GetTimeline());
    mMachineAdapters.push_back(machineAdapter);
}

/**
 * Gets the machine adapter that is assigned to this number
 * @param machineNumber the machine number you want to access
 * @return The machine adapter requested
 */
std::shared_ptr<AdapterMachineDrawable> Picture::GetMachineAdapter(int machineNumber)
{
    machineNumber -= 1;
    if (machineNumber < mMachineAdapters.size())
    {
        return mMachineAdapters[machineNumber];
    }
    return nullptr;
}


/**
* Save the picture animation to a file
* @param filename File to save to.
*/
void Picture::Save(const wxString& filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"anim");
    xmlDoc.SetRoot(root);

    // Save the timeline animation into the XML
    mTimeline.Save(root);

    //
    // It is possible to add attributes to the root node here
    //
    //root->AddAttribute(L"something", mSomething);
    auto machinesNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"machines");
    for (int i = 0; i < mMachineAdapters.size(); i++)
    {
        auto machineNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"machine" + std::to_wstring(i));
        machineNode->AddAttribute(L"frameStart", std::to_wstring(mMachineAdapters[i]->GetFrameStart()));
        machineNode->AddAttribute(L"machineNumber", std::to_wstring(mMachineAdapters[i]->GetMachineNumber()));
        machinesNode->AddChild(machineNode);
    }
    root->AddChild(machinesNode);

    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}



/**
* Load a picture animation from a file
* @param filename file to load from
*/
void Picture::Load(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Animation file");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    // Load the animation from the XML
    mTimeline.Load(root);

    //
    // It is possible to load attributes from the root node here
    //
    // mSomething = root->GetAttribute(L"something", L"default");
    auto child = root->GetChildren();
    for (; child; child = child->GetNext())
    {
        if (child->GetName() == L"machines")
            break;
    }
    auto machineNode = child->GetChildren();
    for (int i = 0; i < mMachineAdapters.size(); i++)
    {
        int frameStart;
        int machineNumber;
        machineNode->GetAttribute(L"frameStart", L"0").ToInt(&frameStart);
        machineNode->GetAttribute(L"machineNumber", L"1").ToInt(&machineNumber);
        mMachineAdapters[i]->SetFrameStart(frameStart);
        mMachineAdapters[i]->SetMachineNumberInt(machineNumber);
        machineNode = machineNode->GetNext();
    }

    SetAnimationTime(0);
    UpdateObservers();
}
