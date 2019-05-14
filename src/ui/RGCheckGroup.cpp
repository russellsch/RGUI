#include "rgui/ui/RGCheckGroup.hpp"
#include "rgui/ui/RGToggle.hpp"

RGCheckGroup::RGCheckGroup(string name, int xNew, int yNew, int wNew, int hNew): RGFrame(name, xNew,yNew,wNew,hNew) {
    setType("checkgroup");
    packVertical = true;
}
RGCheckGroup::RGCheckGroup(string name, int xNew, int yNew, int wNew, int hNew, string labelNew): RGFrame(name, xNew,yNew,wNew,hNew, labelNew) {
    setType("checkgroup");
    packVertical = true;
}



void RGCheckGroup::addItem(string label){
    string name = label;
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    addItem(name, label);
}


void RGCheckGroup::addItem(string name, string label){
    RGToggle* newChild = new RGToggle(name,0 ,0, 60,11, label );
    newChild->setStyle(2);

    addChild(newChild);
    if(packVertical) {
        updateChildPositions();
    } else {
        updateChildPositionsHoriz();
    }

}
void RGCheckGroup::addItem(string name, string label, bool state){
    RGToggle* newChild = new RGToggle(name,0 ,0, 60,11, label );
    newChild->setStyle(2);

    addChild(newChild);
    if(packVertical) {
        updateChildPositions();
    } else {
        updateChildPositionsHoriz();
    }
    if(state){ newChild->setOn(); }
    else{ newChild->setOff(); }
}

void RGCheckGroup::release(int mouseXin, int mouseYin){
    //whenever a press is started dragstart is set to the object that accepted the click
    //this is done in case a drag begins the place where the drag started is known
    //we can use this to easily figure out which child was clicked

    //running the RGObj release method invalidates dragstart
    //so we make a copy before that
    RGObj* oldDragStart=NULL;
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
                //setAllChildrenOffExcept((RGToggle*)oldDragStart);
            }
        }
    }
}

vector<int> RGCheckGroup::getActiveIndexes(){
    vector<int> indexes;
    for(int i=0; i<getChildrenSize(); i++) {
        if(getChild(i)->getType() == "toggle") {
            if(((RGToggle*)getChild(i))->getValue()) {
                indexes.push_back(i);
                break;
            }
        }
    }
    return indexes;
}
bool RGCheckGroup::isActiveByIndex(int index){
    if(index >= getChildrenSize() || index < 0 ) {
        return false;
    }
    if(getChild(index)->getType() == "toggle") {
        return ((RGToggle*)getChild(index))->getValue();
    }
	return false;
}

void RGCheckGroup::setHorizontalPacking() {
    packVertical = false;
}

void RGCheckGroup::updateChildPositions(){
    int xPosition = 4;
    int yPosition = (label == "" ? 7 : 17);
    int listW = 0;
    int listH = 0;

    for(int i=0; i<getChildrenSize(); i++) {
        auto child = getChild(i);
        child->shape.setX(xPosition);
        child->shape.setY(yPosition);
        yPosition += child->shape.getH()+2;
        listH += child->shape.getH()+2;
        if(listW < child->shape.getW()) {
            listW = child->shape.getW();
        }
    }
}

void RGCheckGroup::updateChildPositionsHoriz(){
    int xPosition = 4;
    int yPosition = (label == "" ? 7 : 17);
    int listW = 0;
    int listH = 0;

    for(int i=0; i<getChildrenSize(); i++) {
        auto child = getChild(i);
        child->shape.setX(xPosition);
        child->shape.setY(yPosition);
        xPosition += child->shape.getW()+2;
        listW += child->shape.getW()+2;
        if(listH < child->shape.getH()) {
            listH = child->shape.getH();
        }
    }
}
