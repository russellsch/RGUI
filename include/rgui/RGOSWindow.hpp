#ifndef RGOSWINDOW_H
#define RGOSWINDOW_H

#include <string>
#include <queue>

using namespace std;



//!Stores input events from a window
/*!
Used to encapsulate various windowing library's poll based event systems
*/
class RGInputEvent {
public:
    struct KeyEvent {
        int code;
        bool alt;
        bool shift;
        bool control;
    };
    struct MouseButtonEvent {
        int button;     //!<1-left, 2-right, 3-middle
        int x;
        int y;
    };
    struct MouseMoveEvent{
        int x;
        int y;
    };
    struct MouseWheelEvent{
        int Delta;
    };
    struct ResizeEvent {
        unsigned int width;
        unsigned int height;
    };

    enum InputEventType {
        Closed,
        Resized,
        TextEntered,
        KeyPressed,
        KeyReleased,
        MouseWheelMoved,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseEntered,
        MouseLeft,
        Quit,

        Count
    };

    InputEventType type;

    //union brings the structs from each event type into this single class
    union {
        MouseMoveEvent      mouseMove;
        ResizeEvent         resize;
        MouseWheelEvent     mouseWheel;
        KeyEvent            key;
        MouseButtonEvent    mouseButton;
    };
};

//!Base class for encapsulating various windowing libraries
class RGOSWindow {
    public:
        RGOSWindow();
        virtual void init() { }                 //!<Initialize the windowing library
                                                //!Opens a new window with a given width, height, title and fullscreen parameter
        virtual void openWindow(unsigned int width, unsigned int height, bool fullscreen, string title) { }

        virtual unsigned int getWindowH() { return 0; }   //!<Returnes window height
        virtual unsigned int getWindowW() { return 0; }   //!<Returnes window width

        virtual bool isOpen() { return false; }              //!< Returns true if the window is hasn't been closed

        virtual void display() { }              //!<Swaps opengl buffer and redraws the window

        virtual void close() { }               //!<Force window to close and release window resources

        virtual bool getEvent(RGInputEvent& event) { return false; }            //!<Returns true if an event is available

        virtual ~RGOSWindow();
    protected:

    private:


};







#endif // RGOSWINDOW_H
