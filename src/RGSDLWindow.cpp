#include "rgui/RGSDLWindow.hpp"


void RGSDLWindow::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "ERROR: SDL INIT FAIL!! QUITING" << endl;
        SDL_Quit();
        exit(1);
    }
}



void printSDLError(int lineNumber = -1)
{
    const char *error = SDL_GetError();
    if (*error != '\0')
    {
        cout << "SDL Error: " << error << "\n";
        if (lineNumber != -1) {
            cout << "line:" << lineNumber << "\n";
        }
        SDL_ClearError();
    }
}

void RGSDLWindow::openWindow(unsigned int width, unsigned int height, bool fullscreen,  std::string title){
    this->window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                width, height, SDL_WINDOW_OPENGL); // | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    printSDLError(__LINE__);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    this->glContext = SDL_GL_CreateContext(this->window);
    printSDLError(__LINE__);
    sdl_renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    printSDLError(__LINE__);


    GLenum glewError = glewInit();
    if( glewError != GLEW_OK ) {
        printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
    }
    
    running = true;
    if(window == nullptr) {
        cout << "ERROR: SDL WINDOW FAILED TO CREATE!! QUITING" << endl;
        running = false;
        exit(1);
    }
    cout << "SDL openWindow, running: " << running << "\n";
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
            if (libEvent.button.button == SDL_BUTTON_LEFT) { newEvent.mouseButton.button = MouseButton::Left; }
            else if (libEvent.button.button == SDL_BUTTON_RIGHT) { newEvent.mouseButton.button = MouseButton::Right; }
            else if (libEvent.button.button == SDL_BUTTON_MIDDLE) { newEvent.mouseButton.button = MouseButton::Middle; }

            events.push(newEvent);

        } else if(libEvent.type == SDL_MOUSEMOTION) {
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
