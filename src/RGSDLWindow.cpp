#include "rgui/RGSDLWindow.hpp"


void RGSDLWindow::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "ERROR: SDL INIT FAIL!! QUITING" << endl;
        SDL_Quit();
        exit(1);
    }
}



void RGSDLWindow::openWindow(unsigned int width, unsigned int height, bool fullscreen,  std::string title){
    this->window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                width, height, SDL_WINDOW_OPENGL); // | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    this->glContext = SDL_GL_CreateContext(this->window);

    
    running = true;
    if(window == nullptr) {
        cout << "ERROR: SDL WINDOW FAILED TO CREATE!! QUITING" << endl;
        running = false;
        exit(1);
    }
    cout << "SDL openWindow, running: " << running << "\n";
}

bool RGSDLWindow::isOpen() {
    return running;
}


void RGSDLWindow::display() {
    SDL_GL_SwapWindow(this->window);
}

void RGSDLWindow::close() {

    running = false;
    SDL_Quit();
}


bool RGSDLWindow::getEvent(RGInputEvent& event){
    SDL_Event libEvent;
    while(SDL_PollEvent(&libEvent)){
        cout << "event";
        RGInputEvent newEvent;
        if(libEvent.type == SDL_QUIT) {
            cout << "SDLQuit Event\n";
            newEvent.type = RGInputEvent::Quit;
            running = false;

            events.push(newEvent);
        } else if(libEvent.type == SDL_MOUSEBUTTONDOWN || libEvent.type == SDL_MOUSEBUTTONUP) {
            newEvent.type = (libEvent.type == SDL_MOUSEBUTTONDOWN ? RGInputEvent::MouseButtonPressed
                                                                  : RGInputEvent::MouseButtonReleased);
            newEvent.mouseButton.x = libEvent.button.x;
            newEvent.mouseButton.y = libEvent.button.y;
            if (libEvent.button.button == SDL_BUTTON_LEFT) { newEvent.mouseButton.button = 1; }
            else if (libEvent.button.button == SDL_BUTTON_RIGHT) { newEvent.mouseButton.button = 2; }
            else if (libEvent.button.button == SDL_BUTTON_MIDDLE) { newEvent.mouseButton.button = 3; }

            events.push(newEvent);

        } else if(libEvent.type == SDL_MOUSEBUTTONDOWN) {
            newEvent.type = RGInputEvent::MouseMoved;
            newEvent.mouseMove.x = libEvent.motion.x;
            newEvent.mouseMove.y = libEvent.motion.y;
            events.push(newEvent);
        }


    }

    if(!events.empty()) {
        event = events.front();
        events.pop();
        return true;
    }
    return false;

}
