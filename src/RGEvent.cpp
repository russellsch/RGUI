#include "rgui/RGEvent.hpp"

RGEvent::RGEvent(RGRoot* rootNew) {
    this->rootObject = rootNew;
}

void RGEvent::event(int event) {
    if(event == PRESSED) {
        pressed();
    }
}

void RGEvent::pressed() { }
void RGEvent::released() { }
void RGEvent::clicked() { }

/*!
Refers to a change in state of the object in question.
For a normal button this means when pressed and released.
For a toggle button this means when it toggles
For a slider this means when the slider changes position.

Refer to the documentation of the object for when the changed event is sent.
*/
void RGEvent::changed() { }

void RGEvent::dragged() { }

void RGEvent::resized() { }

