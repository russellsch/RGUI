#ifndef RGROOT_H
#define RGROOT_H

#include <string>
#include <map>

#include "rgui/RGObj.hpp"
#include "KSBasicTimer.h"


//!Root object that holds all other GUI objects (A Canvas Object)
/*!
This class also contains a timer that keeps track of how long the program has been running. This can be used to
add basic animations.
*/
class RGRoot : public RGObj {
    public:
        RGRoot(int wNew, int hNew, RGApp*);
        ~RGRoot() = default;

        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) override; //!<Override of base RGObj method to draw a 1 pixel border around the inside edge of the window.

        virtual RGObj& findChildByName(string name);	//!Returns a pointer to an object in the tree with a certain name

        virtual void addName(RGObj* view, string name); //!<Registers a GUI object so it can be found by it's name
        void removeName(string name);                   //!<Removes a GUI object from being found by it's name

        void render(int XOffset, int YOffset);          //!<Renders all objects connected to this root, passing RGRoot's timing information to them

        double getTimeMs();                             //!<Returns the elapsed time in milliseconds since this object was created

    protected:
        map<string, RGObj*> nameList;   //!<Associates names with pointers to objects, so objects can be easily located by their name

    private:
        KSBasicTimer timer;
};

#endif // RGMAIN_H
