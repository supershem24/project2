/**
 * @file MachineFactories.cpp
 * @author Shawn_Porto
 */

#include "pch.h"
#include "MachineFactories.h"
#include "Machine.h"
#include "Box.h"
#include "Cam.h"
#include "Crank.h"
#include "MusicBox.h"
#include "Pulley.h"
#include "Shaft.h"
#include "Sparty.h"

/**
 * A machine factory constructor
 * @param imagesDir the images directory
 */
Machine1Factory::Machine1Factory(std::wstring imagesDir) :
    mResourcesDir(imagesDir)
{

}

/**
 * Construct a machine
 * @param location the location the machine will be constructed at
 * @return a pointer to the machine
 */
std::shared_ptr<Machine> Machine1Factory::CreateMachine(wxPoint location)
{
    std::shared_ptr<Machine> machine = std::make_shared<Machine>(location);

    std::wstring imagesDir = mResourcesDir + std::wstring(L"/images");

    // make box
    auto box = std::make_shared<Box>(imagesDir, 250, 240);
    box->SetPosition(wxPoint(0, 0));

    // make sparty
    auto sparty = std::make_shared<Sparty>(imagesDir + std::wstring(L"/sparty.png"), 200, 39);
    sparty->SetPosition(wxPoint(0, -10));

    // make crank
    auto crank = std::make_shared<Crank>(0.25);
    crank->SetPosition(wxPoint(150, -110));
    machine->AddComponent(box);
    machine->AddComponent(sparty);
    machine->AddComponent(crank);

    // make shaft
    auto shaft = std::make_shared<Shaft>(10, 100);
    shaft->SetPosition(wxPoint(50, -100));
    crank->GetSource()->AddSink(shaft);
    machine->AddComponent(shaft);

    // make pulley
    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->SetPosition(wxPoint(75, -100));
    shaft->GetSource()->AddSink(pulley1);
    machine->AddComponent(pulley1);

    // make belt connected pulley
    auto pulley2 = std::make_shared<Pulley>(40);
    pulley2->SetPosition(wxPoint(75, -175));
    pulley1->ConnectTo(pulley2);
    machine->AddComponent(pulley2);

    // make shaft
    auto shaft2 = std::make_shared<Shaft>(10, 200);
    shaft2->SetPosition(wxPoint(-100, -175));
    pulley2->GetSource()->AddSink(shaft2);
    machine->AddComponent(shaft2);

    // make cam
    auto cam = std::make_shared<Cam>(imagesDir);
    cam->SetPosition(wxPoint(-100, -175));
    cam->AddOpenable(box);
    cam->AddOpenable(sparty);
    shaft2->GetSource()->AddSink(cam);
    machine->AddComponent(cam);

    return machine;
}

/**
 * A machine factory constructor
 * @param resourcesDir the images directory
 */
Machine2Factory::Machine2Factory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{

}

/**
 * Construct a machine
 * @param location the location the machine will be constructed at
 * @return a pointer to the machine
 */
std::shared_ptr<Machine> Machine2Factory::CreateMachine(wxPoint location)
{
    std::shared_ptr<Machine> machine = std::make_shared<Machine>(location);

    std::wstring imagesDir = mResourcesDir + std::wstring(L"/images");

    // make box
    auto box = std::make_shared<Box>(imagesDir, 250, 240);
    box->SetPosition(wxPoint(0, 0));

    // make sparty
    auto sparty = std::make_shared<Sparty>(imagesDir + std::wstring(L"/sparty2.png"), 200, 42);
    sparty->SetPosition(wxPoint(0, -10));

    // make crank
    auto crank = std::make_shared<Crank>(0.25);
    crank->SetPosition(wxPoint(150, -220));

    // make shaft
    auto shaft = std::make_shared<Shaft>(10, 100);
    shaft->SetPosition(wxPoint(50, -210));
    crank->GetSource()->AddSink(shaft);

    // make music box
    auto musicBox = std::make_shared<MusicBox>(mResourcesDir, L"songs/pop.xml");
    musicBox->SetPosition(wxPoint(-25, -100));
    shaft->GetSource()->AddSink(musicBox);

    // double pulley
    auto pulley1 = std::make_shared<Pulley>(20);
    pulley1->SetPosition(wxPoint(50, -210));
    shaft->GetSource()->AddSink(pulley1);
    auto pulley2 = std::make_shared<Pulley>(50);
    pulley2->SetPosition(wxPoint(50, -100));
    pulley1->ConnectTo(pulley2);

    // another shaft
    auto shaft2 = std::make_shared<Shaft>(10, 150);
    shaft2->SetPosition(wxPoint(-100, -100));
    pulley2->GetSource()->AddSink(shaft2);

    // double pulley
    auto pulley3 = std::make_shared<Pulley>(20);
    pulley3->SetPosition(wxPoint(-100, -100));
    shaft2->GetSource()->AddSink(pulley3);
    auto pulley4 = std::make_shared<Pulley>(20);
    pulley4->SetPosition(wxPoint(-100, -200));
    pulley3->ConnectTo(pulley4);

    // cam shaft
    auto shaft3 = std::make_shared<Shaft>(10, 30);
    shaft3->SetPosition(wxPoint(-100, -200));
    pulley4->GetSource()->AddSink(shaft3);

    auto cam = std::make_shared<Cam>(imagesDir);
    cam->SetPosition(wxPoint(-70, -200));
    cam->AddOpenable(box);
    cam->AddOpenable(sparty);
    shaft3->GetSource()->AddSink(cam);


    machine->AddComponent(box);
    machine->AddComponent(sparty);
    machine->AddComponent(shaft);
    machine->AddComponent(crank);
    machine->AddComponent(shaft2);
    machine->AddComponent(shaft3);
    machine->AddComponent(musicBox);
    machine->AddComponent(pulley1);
    machine->AddComponent(pulley2);
    machine->AddComponent(pulley3);
    machine->AddComponent(pulley4);
    machine->AddComponent(cam);

    return machine;
}
