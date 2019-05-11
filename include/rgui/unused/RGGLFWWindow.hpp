#ifndef RGGLFWWINDOW_HPP
#define RGGLFWWINDOW_HPP

#include "RGOSWindow.hpp"

#include <iostream>

class RGGLFWWindow : public RGOSWindow {
public:
    void init();
    void openWindow(unsigned int width, unsigned int height, bool fullscreen, string title);
    bool isOpen();
    void display();
    void close();
    bool getEvent(RGInputEvent& event);

private:
    int mouseX, mouseY, mouseButtonPressed;
    int windowW, windowH;
    bool mouseBut1, mouseBut2, mouseBut3;
};


#endif // RGGLFWWINDOW_HPP


