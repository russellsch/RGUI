#include "RGRadioGroup.hpp"
#include "RGToggle.hpp"


RGRadioGroup::RGRadioGroup(string name, int xNew, int yNew, int wNew, int hNew): RGFrame(name, xNew,yNew,wNew,hNew) {
    setType("radiogroup");
}
RGRadioGroup::RGRadioGroup(string name, int xNew, int yNew, int wNew, int hNew, string labelNew): RGFrame(name, xNew,yNew,wNew,hNew, labelNew) {
    setType("radiogroup");
}

RGRadioGroup::~RGRadioGroup()
{
    //dtor
}


/*!Subclassed addChild method, used to update the positions of the children in the list each time a new one is added.
This method calls the original RGObj method first. This should only be used with objects that have a boolean value
variable such as RGToggle*/
void RGRadioGroup::addItem(string name, string label) {
    RGToggle* newChild = new RGToggle(name,0 ,0, 60,11, label );

    addChild(newChild);
    updateChildPositions();
}
void RGRadioGroup::addItem(string label) {
    string name = label;
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    addItem(name, label);
}


/*! Used to pack children into the group control. Eventually this should be replaced with a more multi-purpose
packing utility.
*/
void RGRadioGroup::updateChildPositions() {
    int xPosition = 4;
    int yPosition = (label == "" ? 7 : 17);
    int listW = 0;
    int listH = 0;

    for(int i=0; i<getChildrenSize(); i++) {
        getChild(i)->setX((int)xPosition);
        getChild(i)->setY((int)yPosition);
        yPosition += getChild(i)->getH()+2;
        listH += getChild(i)->getH()+2;
        if(listW < getChild(i)->getW()) {
            listW = getChild(i)->getW();
        }
    }
}



void RGRadioGroup::release(int mouseXin, int mouseYin) {
    //whenever a press is started dragstart is set to the object that accepted the click
    //this is done in case a drag begins the place where the drag started is known
    //we can use this to easily figure out which child was clicked

    //running the RGObj release method invalidates dragstart
    //so we make a copy before that
    RGObj* oldDragStart = NULL;
    bool oldDragStartValid = false;
    if(dragStartValid) {
        oldDragStart = dragStart;
        oldDragStartValid = true;
    }

    RGObj::release(mouseXin, mouseYin); //run the overriden RGObj release method

    if(oldDragStartValid) {
        //make sure the thing clicked actually got toggled and the user didn:t just drag
        //away outside of the control
        if(oldDragStart->getType() == "toggle") {
            if( ((RGToggle*)oldDragStart)->getValue() ) {

                //set all other children to off
                setAllChildrenOffExcept((RGToggle*)oldDragStart);
            }
        }
    }
}


void RGRadioGroup::setAllChildrenOffExcept(int exceptIndex) {
    if(exceptIndex >= 0 && exceptIndex < getChildrenSize()) {
        for(int i=0; i<getChildrenSize(); i++) {
            if( i != exceptIndex ) {
                if(getChild(i)->getType() == "toggle") {
                    ((RGToggle*)getChild(i))->setOff();
                }
            } else {
                if(getChild(i)->getType() == "toggle") {
                    ((RGToggle*)getChild(i))->setOn();
                }
            }
        }
    }
}

void RGRadioGroup::setAllChildrenOffExcept(RGToggle* exceptToggle) {
    for(int i=0; i<getChildrenSize(); i++) {
        if( exceptToggle != getChild(i) ) {
            if(getChild(i)->getType() == "toggle") {
                ((RGToggle*)getChild(i))->setOff();
            }
        } else {
            if(getChild(i)->getType() == "toggle") {
                ((RGToggle*)getChild(i))->setOn();
            }
        }
    }
}


/*!
Returns -1 if none is found. This method checks to make sure that each child has the type "toggle".
*/
int RGRadioGroup::getActiveIndex(){
    int index = -1;
    for(int i=0; i<getChildrenSize(); i++) {
        if(getChild(i)->getType() == "toggle") {
            if(((RGToggle*)getChild(i))->getValue()) {
                index = i;
                break;
            }
        }
    }
    return index;
}


bool RGRadioGroup::isActiveByIndex(int index) {
    if(index >= getChildrenSize() || index < 0 ) {
        return false;
    }
    if(getChild(index)->getType() == "toggle") {
        return ((RGToggle*)getChild(index))->getValue();
    }
}
