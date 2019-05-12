#ifndef RGSDLWINDOW_H
#define RGSDLWINDOW_H

#include <rgui/RGOSWindow.hpp>
#include <iostream>


#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/glu.h>
//struct SDL_Surface;


class RGSDLWindow : public RGOSWindow {
    public:
        void init() override;
        void openWindow(unsigned int width, unsigned int height, bool fullscreen, std::string title) override;
        bool isOpen() override;
        void display() override;
        void close() override;
        bool getEvent(RGInputEvent& event) override ;

    protected:
        SDL_Window* window;
        SDL_GLContext glContext;
        SDL_Renderer* sdl_renderer;
        bool running;

    private:
        queue<RGInputEvent> events;


};


#endif // RGSDLWINDOW_H
