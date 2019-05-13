#include "rgui/RGEventHandlerBase.hpp"

RGEventHandlerBase::RGEventHandlerBase(RGRoot* rootNew) {
    this->rootObject = rootNew;
}

void RGEventHandlerBase::event(int event) {
    if(event == PRESSED) {
        pressed();
    }
}
