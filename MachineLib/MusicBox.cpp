/**
 * @file MusicBox.cpp
 * @author Shawn_Porto
 */
#include "pch.h"

#include "MusicBox.h"

#include <wx/xml/xml.h>
#include <wx/sound.h>

/// The music box mechanism image filename
const std::wstring MusicBoxImage = L"/images/mechanism.png";

/// Size to draw the music box mechanism image in pixels
const int MusicBoxImageSize = 120;

/// The color of the rotating music box drum
const wxColour MusicBoxDrumColor = wxColour(248, 242, 191);

/// The color of the lines on the music box rotating drum
const wxColour MusicBoxDrumLineColor = wxColour(20, 20, 20);

/// The music box drum width
const int MusicBoxDrumWidth = 40;

/// The music box drum diameter
const int MusicBoxDrumDiameter = 33;

/// Number of beats per turn of the music box drum
/// This also determines how many lines to draw on the cylinder
const int BeatsPerRotation = 12;

/// The audio directory in the resources
const std::wstring AudioDirectory = L"/audio/";

/**
 * Constructor
 * @param resourcesDir resources directory
 * @param audioFile the audio file to find the songs in
 */
MusicBox::MusicBox(std::wstring resourcesDir, std::wstring audioFile)
{
    mMusicMechanism.Rectangle(0, 0, MusicBoxImageSize, MusicBoxImageSize);
    mMusicMechanism.SetImage(resourcesDir+MusicBoxImage);
    std::wstring musicPath = resourcesDir + AudioDirectory + audioFile;

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(musicPath))
    {
        wxMessageBox(L"Unable to load Music file");
        return;
    }

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    root->GetAttribute("beats").ToInt(&mBeatsPerMeasure);

    auto sounds = root->GetChildren();
    auto currNote = sounds->GetNext()->GetChildren();
    auto childrenSounds = sounds->GetChildren();

    std::unordered_map<std::wstring, std::wstring> soundMap;

    for ( ; childrenSounds; childrenSounds = childrenSounds->GetNext())
    {
        soundMap[childrenSounds->GetAttribute("note").ToStdWstring()] = resourcesDir + AudioDirectory + childrenSounds->GetAttribute("file").ToStdWstring();
    }

    int measure;
    currNote->GetAttribute(L"measure", "1").ToInt(&measure);
    double beat;
    currNote->GetAttribute(L"beat", "1").ToDouble(&beat);
    double absoluteBeat = (measure - 1) * mBeatsPerMeasure + (beat - 1);
    mFirstNote = absoluteBeat;

    for ( ; currNote; currNote = currNote->GetNext())
    {
        mNextNoteTime = absoluteBeat;
        currNote->GetAttribute(L"measure", "1").ToInt(&measure);
        currNote->GetAttribute(L"beat", "1").ToDouble(&beat);
        absoluteBeat = (measure - 1) * mBeatsPerMeasure + (beat - 1);
        mNoteTimes[mNextNoteTime] = absoluteBeat;
        mNotes[absoluteBeat] = new wxSound(soundMap[currNote->GetAttribute(L"note").ToStdWstring()]);
    }
    mNoteTimes[absoluteBeat] = -1;
    mNextNoteTime = mFirstNote;
}

/**
 * Draw the shaft at its current rotation
 * @param graphics graphics component
 * @param x x position of the shaft
 * @param y y position of the shaft
 */
void MusicBox::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mMusicMechanism.DrawPolygon(graphics, x - MusicBoxDrumWidth, y + MusicBoxImageSize/2);
    mShaft.SetSize(MusicBoxDrumDiameter, MusicBoxDrumWidth);
    mShaft.SetColour(MusicBoxDrumColor);
    mShaft.SetLines(MusicBoxDrumLineColor, 1, BeatsPerRotation);
    mShaft.Draw(graphics, x, y, mRotation);
}

/**
 * Set the rotation of the component
 * @param rotation rotation to set it too
 */
void MusicBox::SetRotation(double rotation)
{
    mRotation = rotation;
}

/**
 * Advance this component to the specified time
 * @param time the time to advance the component to
 */
void MusicBox::Update(double time)
{
    double currentBeat = BeatsPerRotation * mRotation;
    if (mNextNoteTime == -1)
        return;

    while (mNextNoteTime < currentBeat)
    {
        if (mNotes[mNextNoteTime]->IsOk())
        {
            mNotes[mNextNoteTime]->Play();
        }
        mNextNoteTime = mNoteTimes[mNextNoteTime];
        if (mNextNoteTime == -1)
                return;
    }
}

/**
 * Reset rhe
 */
void MusicBox::Reset()
{
    Component::Reset();

    mNextNoteTime = mFirstNote;
}
