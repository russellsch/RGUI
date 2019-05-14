#ifndef RGSDLWINDOW_H
#define RGSDLWINDOW_H

#include <iostream>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <GL/glu.h>

#include <rgui/RGOSWindow.hpp>

class RGSDLWindow : public RGOSWindow {
    public:
        void init() override;
        void openWindow(unsigned int width, unsigned int height, bool fullscreen, std::string title) override;
        bool isOpen() override { return running; };
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
