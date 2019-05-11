#ifndef RGSFMLWINDOW_H
#define RGSFMLWINDOW_H
#include "RGOSWindow.hpp"


namespace sf{
    class Window;
}


class RGSFMLWindow : public RGOSWindow {
    public:
        void openWindow(unsigned int width, unsigned int height, bool fullscreen, string title);
        bool isOpen();
        void display();
        void close();
        bool getEvent(RGInputEvent& event);
    protected:

    private:
        queue<RGInputEvent> events;
        sf::Window* window;
};

#endif // RGSFMLWINDOW_H
