/**
 * @file SarahFactory.cpp
 * @author Shawn_Porto
 */
 
#include "pch.h"
#include "SarahFactory.h"
#include "Actor.h"
#include "HeadTop.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"

using namespace std;

/**
 * This is a factory method that creates our Sarah actor.
 * @param imagesDir Directory that contains the images for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> SarahFactory::Create(std::wstring imagesDir)
{
    shared_ptr<Actor> actor = make_shared<Actor>(L"Sarah");

    auto dress = make_shared<ImageDrawable>(L"Dress", imagesDir + L"/sarah_dress.png");
    dress->SetCenter(wxPoint(44, 138));
    dress->SetPosition(wxPoint(0, -114));
    actor->SetRoot(dress);

    auto lleg = make_shared<ImageDrawable>(L"Left Leg", imagesDir + L"/jeans_lleg.png");
    lleg->SetCenter(wxPoint(11, 9));
    lleg->SetPosition(wxPoint(17, 0));
    dress->AddChild(lleg);

    auto rleg = make_shared<ImageDrawable>(L"Right Leg", imagesDir + L"/jeans_rleg.png");
    rleg->SetCenter(wxPoint(39, 9));
    rleg->SetPosition(wxPoint(-17, 0));
    dress->AddChild(rleg);

    auto headb = make_shared<ImageDrawable>(L"Head Bottom", imagesDir + L"/sarah_headb.png");
    headb->SetCenter(wxPoint(44, 31));
    headb->SetPosition(wxPoint(5, -130));
    dress->AddChild(headb);

    auto headt = make_shared<HeadTop>(L"Head Top", imagesDir + L"/sarah_headt.png");
    headt->SetCenter(wxPoint(55, 109));
    headt->SetEyesCenter(wxPoint(70, 80));
    headt->SetPosition(wxPoint(-20, -31));
    headb->AddChild(headt);

    auto larm = make_shared<ImageDrawable>(L"Left Arm", imagesDir + L"/dress_arm.png");
    larm->SetCenter(wxPoint(8, 9));
    larm->SetPosition(wxPoint(-45, -130));
    dress->AddChild(larm);

    auto rarm = make_shared<ImageDrawable>(L"Right Arm", imagesDir + L"/dress_arm.png");
    rarm->SetCenter(wxPoint(8, 9));
    rarm->SetPosition(wxPoint(50, -130));
    dress->AddChild(rarm);

    auto lhand = make_shared<PolyDrawable>(L"Left Hand");
    lhand->SetColor(wxColour(208,159,116));
    lhand->SetPosition(wxPoint(0, 90));
    lhand->AddPoint(wxPoint(-12, -2));
    lhand->AddPoint(wxPoint(-12, 17));
    lhand->AddPoint(wxPoint(11, 17));
    lhand->AddPoint(wxPoint(11, -2));
    larm->AddChild(lhand);

    auto rhand = make_shared<PolyDrawable>(L"Right Hand");
    rhand->SetColor(wxColour(208,159,116));
    rhand->SetPosition(wxPoint(0, 90));
    rhand->AddPoint(wxPoint(-12, -2));
    rhand->AddPoint(wxPoint(-12, 17));
    rhand->AddPoint(wxPoint(11, 17));
    rhand->AddPoint(wxPoint(11, -2));
    rarm->AddChild(rhand);

    auto mug = make_shared<ImageDrawable>(L"Mug", imagesDir + L"/mug-bw.png");
    mug->SetCenter(wxPoint(0, 30));
    mug->SetPosition(wxPoint(0, 10));
    rhand->AddChild(mug);

    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(rhand);
    actor->AddDrawable(lhand);
    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(dress);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);
    actor->AddDrawable(mug);

    return actor;
}
