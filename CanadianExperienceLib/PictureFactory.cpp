/**
 * @file PictureFactory.cpp
 *
 * @author Charles Owen
 * @author Anik Momtaz
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "AdapterMachineDrawable.h"
#include "ImageDrawable.h"
#include "SarahFactory.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background2.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(150, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(650, 620));
    picture->AddActor(sparty);

    // Create and add Sarah
    SarahFactory sarahFactory;
    auto sarah = sarahFactory.Create(imagesDir);

    sarah->SetPosition(wxPoint(600, 600));
    picture->AddActor(sarah);

    // Create a machine
    std::shared_ptr<Actor> machine1 = std::make_shared<Actor>(L"Machine1");
    machine1->SetPosition(wxPoint(400, 700));

    auto drawable1 = std::make_shared<AdapterMachineDrawable>(L"Machine1", resourcesDir);
    machine1->AddDrawable(drawable1);
    picture->AddActor(machine1);
    drawable1->SetPosition(wxPoint(450,750));
    picture->AddMachineAdapter(drawable1);

    //create the second machine
    std::shared_ptr<Actor> machine2 = std::make_shared<Actor>(L"Machine2");
    machine2->SetPosition(wxPoint(1300, 800));

    auto drawable2 = std::make_shared<AdapterMachineDrawable>(L"Machine2", resourcesDir);
    machine2->AddDrawable(drawable2);
    picture->AddActor(machine2);
    drawable2->SetPosition(wxPoint(1300, 800));
    picture->AddMachineAdapter(drawable2);

    return picture;
}

