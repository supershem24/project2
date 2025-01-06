/**
 * @file Controller.h
 * @author Charles Owen
 *
 * This class supports the control of the
 * application using the command line.
 */

#ifndef CANADIANEXPERIENCE_CONTROLLER_H
#define CANADIANEXPERIENCE_CONTROLLER_H

#include <list>

class MachineDemoMainFrame;
class MachineView;
class ControlPanel;

/**
 * This class supports the control of the
 * application using the command line.
 */
class Controller final {
private:
    /// The MainFrame window
    MachineDemoMainFrame* mMainFrame = nullptr;

    /// The Machine System view
    MachineView* mMachineView = nullptr;

    /// The control panel
    ControlPanel* mControlPanel = nullptr;

    /// Controller task base class
    class Task {
    protected:
        /// Control this is a member of
        Controller* mController;

    public:
        /**
         * Constructor
         * @param controller Controller this is a member of
         */
        Task(Controller* controller) : mController(controller) {}

        /// Destructor
        virtual ~Task() = default;

        /// Default constructor (disabled)
        Task() = delete;

        /// Copy constructor (disabled)
        Task(const Task &) = delete;

        /// Assignment operator
        void operator=(const Task &) = delete;

        /**
         * Execute this task,
         * @return
         */
        virtual bool Execute() = 0;
    };

    /// Frame selection task
    class TaskFrame : public Task {
    private:
        /// Frame to move to
        int mFrame;

    public:
        TaskFrame(Controller* controller, const wxString &arg);
        bool Execute() override;
    };

    /// Machine selection task
    class TaskMachine : public Task {
    private:
        /// Machine to select
        int mMachine;

    public:
        TaskMachine(Controller* controller, const wxString &arg);
        bool Execute() override;
    };

    /// Capture a frame task
    class TaskCapture : public Task {
    private:
        /// Filename to capture to
        wxString mFilename;

    public:
        TaskCapture(Controller* controller, const wxString &arg);
        bool Execute() override;
    };

    /// Write sequence of images as a GIF file
    class TaskWriteGIF : public Task {
    private:
        /// GIF filename
        wxString mFilename;

        /// Duoration of a frame in seconds
        double mDuration;

    public:
        TaskWriteGIF(Controller* controller, const wxString &arg1, const wxString &arg2);
        bool Execute() override;
    };

    /// Exit the application taask
    class TaskExit : public Task {
    public:
        /**
         * Constructor
         * @param controller The controller
         */
        explicit TaskExit(Controller* controller) : Task(controller) {}
        bool Execute() override;
    };

    /// The list of tasks
    std::list<std::shared_ptr<Task>> mTasks;

    /// The list of saved images
    std::vector<wxImage> mImages;

public:
    Controller() = default;

    void OnInitCmdLine(wxCmdLineParser& parser);
    bool OnCmdLineParsed(wxCmdLineParser& parser);
    void SetWindows(MachineDemoMainFrame *frame,
            MachineView* machineView, ControlPanel* controlPanel);

    void Execute();
};

#endif //CANADIANEXPERIENCE_CONTROLLER_H
