#ifndef RGSDLWINDOW_H
#define RGSDLWINDOW_H

#include <rgui/RGOSWindow.hpp>
#include <iostream>

#include "SDL.h"
//#include <windows.h>

struct SDL_Surface;


class RGSDLWindow : public RGOSWindow {
    public:
        void init();
        void openWindow(unsigned int width, unsigned int height, bool fullscreen, string title);
        bool isOpen();
        void display();
        void close();
        bool getEvent(RGInputEvent& event);
    protected:
        //SDL_Surface* window;
        SDL_Window* window;
        bool running;
    private:
        queue<RGInputEvent> events;


		
};


#endif // RGSDLWINDOW_H
