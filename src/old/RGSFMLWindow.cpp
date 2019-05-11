#include "RGSFMLWindow.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//THIS WRAPPER IS CURRENTLY INCOMPLETE
//THINGS SUCH AS MOUSEWHEEL AND KEYBOARD HAVE NOT BEEN MOVED YET

void RGSFMLWindow::openWindow(unsigned int width, unsigned int height, bool fullscreen, string title) {
    window = new sf::Window(sf::VideoMode(width, height, 32), title);
    window->SetFramerateLimit(60);
}


bool RGSFMLWindow::isOpen() {
    return window->IsOpened();
}


void RGSFMLWindow::display() {
    window->Display();
}


void RGSFMLWindow::close() {
    window->Close();
}

bool RGSFMLWindow::getEvent(RGInputEvent& event){
    //load all new events from SFML into the RGUI input event queue
    //converting them from their event format to the RGUI event format
    sf::Event libEvent;
    while(window->GetEvent(libEvent)) {
        RGInputEvent newEvent;
        if(libEvent.Type == sf::Event::Closed) {
            newEvent.type = RGInputEvent::Closed;
            events.push(newEvent);
        } else if(libEvent.Type == sf::Event::MouseButtonPressed) {
            newEvent.type = RGInputEvent::MouseButtonPressed;
            newEvent.mouseButton.x = libEvent.MouseButton.X;
            newEvent.mouseButton.y = libEvent.MouseButton.Y;
            newEvent.mouseButton.button = libEvent.MouseButton.Button+1;
            events.push(newEvent);
        } else if(libEvent.Type == sf::Event::MouseButtonReleased) {
            newEvent.type = RGInputEvent::MouseButtonReleased;
            newEvent.mouseButton.x = libEvent.MouseButton.X;
            newEvent.mouseButton.y = libEvent.MouseButton.Y;
            newEvent.mouseButton.button = libEvent.MouseButton.Button+1;
            events.push(newEvent);
        } else if(libEvent.Type == sf::Event::MouseMoved) {
            newEvent.type = RGInputEvent::MouseMoved;
            newEvent.mouseMove.x = libEvent.MouseMove.X;
            newEvent.mouseMove.y = libEvent.MouseMove.Y;
            events.push(newEvent);
        } else {
            //event not yet supported
        }
    }

    //are there any events in our queue? then spit out the event,
    //pop it off the queue, and return true
    if(events.size()> 0) {
        event = events.front();
        events.pop();
        return true;
    }
    return false;
}
