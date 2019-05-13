#include "rgui/RGEventBase.hpp"

RGEventBase::RGEventBase(RGRoot* rootNew) {
    this->rootObject = rootNew;
}

void RGEventBase::event(int event) {
    if(event == PRESSED) {
        pressed();
    }
}

void RGEventBase::pressed() { }
void RGEventBase::released() { }
void RGEventBase::clicked() { }

/*!
Refers to a change in state of the object in question.
For a normal button this means when pressed and released.
For a toggle button this means when it toggles
For a slider this means when the slider changes position.

Refer to the documentation of the object for when the changed event is sent.
*/
void RGEventBase::changed() { }

void RGEventBase::dragged() { }

void RGEventBase::resized() { }

