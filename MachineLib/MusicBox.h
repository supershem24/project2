/**
 * @file MusicBox.h
 * @author Shawn_Porto
 *
 * Music box that makes music while the box is winding
 */

#ifndef MUSICBOX_H
#define MUSICBOX_H
#include <wx/xml/xml.h>

#include "Component.h"
#include "Cylinder.h"
#include "IRotationSink.h"
#include "Polygon.h"

class wxSound;

/**
 * Music box that makes music while the box is winding
 */
class MusicBox : public Component, public IRotationSink
{
private:
    /// The cylinder that makes up the visible shaft
    cse335::Cylinder mShaft;
    /// THe image that has the mechanism shown on it
    cse335::Polygon mMusicMechanism;
    /// The current rotation of the shaft
    double mRotation = 0;
    /// The notes that are in the song ordered by the frame they play and the note name that is played
    std::unordered_map<double, wxSound*> mNotes;
    /// The next time to play a note
    double mNextNoteTime;
    /// The first note
    double mFirstNote = 0;
    /// The list of when each sound is played in order
    std::unordered_map<double, double> mNoteTimes;
    /// The beats per measure the song has
    int mBeatsPerMeasure = 0;
public:
    MusicBox(std::wstring resourcesDir, std::wstring audioFile);

    ///Default constructor disabled
    MusicBox() = delete;
    /** Copy constructor disabled */
    MusicBox(const MusicBox &) = delete;
    /** Assignment operator disabled */
    void operator=(const MusicBox &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;
    void SetRotation(double rotation) override;
    void Update(double time) override;
    void Reset() override;
};



#endif //MUSICBOX_H
