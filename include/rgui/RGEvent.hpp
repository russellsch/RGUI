#ifndef RGEVENT_H
#define RGEVENT_H
#include <iostream>
#include "rgui/RGConst.hpp"

class RGRoot;

//!A base class meant to be subclassed and overriden to add code to existing gui objects
/*!

*/
class DLLHELPER RGEvent
{
    public:
        RGRoot* rootObject;

        RGEvent(RGRoot* rootNew);

        virtual void event(int event);

        virtual void pressed();     //!<Sent when mouse is pressed and released over a control
        virtual void released();    //!<Sent when mouse is released after being pressed over a control
        virtual void clicked();     //!<Sent when mouse is pressed and released over a control

        virtual void changed();     //!<Sent when the state of the object changes
        virtual void dragged();     //!<Sent when a drag is performed, starting on this object

        virtual void resized();
    protected:
    private:
};

#endif // RGEVENT_H
