#include "rgui/RGObj.hpp"
//#include "RGRoot.hpp"
#include "rgui/RGApp.hpp"
//#include "RGRect.h"



//!Default object constructor

RGObj::RGObj(const std::string& name, const std::string& type, int xNew, int yNew, int wNew, int hNew) {
    this->shape = RGRect(xNew, yNew, wNew, hNew, RG_TL);

    clipChildren = true;
    resizable = false;
    stretchX = 0;
    stretchY = 0;
    anchorX = 1;
    anchorY= 1;

    fontSize = 12;

    bkgColor = ColorRGBA(230);

    initialDrag = true;
    dragging = false;
    dragStartValid = false;

    verboseRender = false;
    verboseRelease = true;
    verboseMouseOverChild = false;
    verbosePress = false;

    RGEventHandlerBase* eventHandler;

    this->name = name;
    this->type = type;
    if(type.empty()) { this->type="generic"; }

    cout << "RGObj constructor:   w:" << shape.getW() << " h:" << shape.getH() <<  " x:" << shape.getX() << " y:" << shape.getY();
}


//these event functions wrap the primary press, release and drag functions. This is so that after this object's function
//has been run, the object's eventhandler function can be run as well. This provides two methods for providing custom
//functionality, one for new types of subclassed RGObjs, and one for unique instances. These functions wrap the returned
//response where nescessary to allow it to propogate through the hierarchy properly.
MouseDelegation RGObj::pressEvent(int mouseXin, int mouseYin) {
    MouseDelegation response = press(mouseXin, mouseYin);
    if(eventHandler != nullptr) {
        eventHandler->pressed();
    }
    return response;
}

void RGObj::releaseEvent(int mouseXin, int mouseYin) {

    release(mouseXin, mouseYin);
    if(eventHandler != nullptr) {
        eventHandler->released();
    }
}

MouseDelegation RGObj::dragEvent(int mouseXin, int mouseYin, MouseButton button) {
    MouseDelegation response = drag(mouseXin, mouseYin, button);
    if(eventHandler != nullptr) {
        eventHandler->released();
    }
    return response;
}

//currently not working... needs a bit more work
void RGObj::resizeEvent(int wNew, int hNew) {
    if(resizable) {
        //UPPER LEFT CORNER
        //resize self
        //setW((wNew-getW())*stretchX);
        //setH((hNew-getH())*stretchY);
        //w+(wNew-w)*stretchX

        cout << "dx:" << (wNew - shape.getW()) << " stretch:" << stretchX << " change:"
             << (int)((wNew - shape.getW())*stretchX) << " leftover:"
             << (wNew - shape.getW())*stretchX - (int)((wNew - shape.getW())*stretchX) << std::endl;

        //w += (wNew-ofGetWidth())*stretchX + (int)leftOverStretchX;
        leftOverStretchX += (int)((wNew-shape.getW())*stretchX) - (wNew-shape.getW())*stretchX - (int)leftOverStretchX;

        //w += (int)leftOverStretchX;
        //leftOverStretchX -= (int)leftOverStretchX;

        shape.setY(shape.getT() + (hNew - shape.getH())*stretchY);

        //x += (wNew-w)*anchorX;
        //cout << "dx:" << (wNew-w) << " anchor:" << stretchX << " change:" << (wNew-w)*anchorX <<endl;

        //y += (hNew-h)*anchorY;

        shape.setW(shape.getW() + ((wNew - shape.getW())*anchorX));   //THIS DOESN'T ACCOUNT FOR THE REMAINDER STILL
        shape.setH(shape.getH() + ((hNew - shape.getH())*anchorY));   //THIS DOESN'T ACCOUNT FOR THE REMAINDER STILL


        //resize children
        for(int i=0; i<getChildrenSize(); i++) {
            getChild(i)->resizeEvent(getChild(i)->shape.getW() + -1*(shape.getW() - wNew), hNew - shape.getH());
        }

    }



}


//returns 0 if no one accepted the click
//returns 1 if this object accepted the click (click opaque)
//returns 2 if this object got someone else to accept the click (fell through and hit something opaque)
//returns 3 if this object didn't accept the click, but doesn't want others behind it to get it
//mouse coordinates should be relative to the objects origin
MouseDelegation RGObj::press(int mouseXin, int mouseYin) {
    if(verbosePress) { cout<<"pressed: " << name << " with " << getChildrenSize()<<" children ("<<mouseXin<<","<<mouseYin<<")"; }
    for(int i=0; i<getChildrenSize(); i++) {
        if(mouseOverChild(mouseXin, mouseYin, i)) {
            MouseDelegation response = getChild(i)->pressEvent( mouseXin-getChildXRel2Self(i), mouseYin-getChildYRel2Self(i) );
            if(response != MouseDelegation::NOT_ACCEPTED) {
                dragStart = getChild(i);
                dragStartValid = true;
                if(response == MouseDelegation::THIS_ACCEPTED) {
                    return MouseDelegation::CHILD_ACCEPTED;
                } else {
                    return response;
                }
            }
        } else {

        }
    }
    return MouseDelegation::NOT_ACCEPTED;
}

/*!
Sends a mouse release event to an object. If that object was passing along drag events to another object it forwards it on
as well.
*/
void RGObj::release(int mouseXin, int mouseYin) {
    if(dragStartValid) {
        dragStart->releaseEvent( mouseXin-getDragStartXRel2Self(), mouseYin-getDragStartYRel2Self() );
    }
    dragStartValid = false;
    dragging = false;
    initialDrag = true;
    if(verboseRelease) { cout << name << ": RELEASE" <<endl; }
}

/*!
A drag is treated as a seperate event as a click. Drags fall from the top down as well. If a drag falls and hits something that accepts it, all
subsequent drag events are sent to that object until the mouse is released. Each object within the hierarchy between the toppost object and the object
that accepted the drag will respond with one of the codes below.

returns 0 if no one accepted the drag (drag fell all the way through)
returns 1 if this object accepted the drag
returns 2 if this this object got someone else to accept the drag

If a response of 1 or 2 is received from it's children, then this object stores which child it was in dragStart, and sets dragStartValid to true.
Additionally, the position where the drag started is stored as well in dragStartX and dragStartY.

If this object receives a response of 1 from it's child, it will return 2, to let objects above it know that it got someone else to receive the drag.
*/
MouseDelegation RGObj::drag(int mouseXin, int mouseYin, MouseButton button) {
    if(dragging){
        if(initialDrag){
            initialDrag = false;
        }
        if(!dragStartValid){
            return MouseDelegation::NOT_ACCEPTED;
        } else {
            dragStart->drag(mouseXin-getDragStartXRel2Self(), mouseYin-getDragStartYRel2Self(), button);
            return MouseDelegation::CHILD_ACCEPTED;
        }
    } else {
        dragging = true;
        dragStartX = mouseXin;
        dragStartY = mouseYin;
        for(int i=0; i<getChildrenSize(); i++) {
            if(mouseOverChild(mouseXin, mouseYin, i)) {
                MouseDelegation response = getChild(i)->drag(mouseXin-getChildXRel2Self(i), mouseYin-getChildYRel2Self(i), button);
                if(response != MouseDelegation::NOT_ACCEPTED) {
                    dragStart = getChild(i);
                    dragStartValid = true;
                    //dragStartX = mouseXin;
                    //dragStartY = mouseYin;
                    if(response == MouseDelegation::THIS_ACCEPTED) {
                        return MouseDelegation::CHILD_ACCEPTED;
                    }
                    return MouseDelegation::THIS_ACCEPTED;
                }
            }
        }
        return MouseDelegation::NOT_ACCEPTED;
    }
}


RGObj* RGObj::getChild(uint32_t i) {
    return children.at(i);
}

/*!
Add's a child object to this object's list of children. Additonally it performs the following actions:
    - Parent of the child is set to this object
    - root object is propogated recursively to the child and it's children
    - draw object is propogated recursively to the child and it's children
*/
void RGObj::addChild(RGObj* newChild){
    //if draw object is valid, set the child's draw object to the same, this effects in anything added under main
    //receiving a valid pointer to the draw object
    propagateDrawObject(newChild);

    //give this child the root object and register it's name as well (this function is applied recursively to all children)
    propagateRootObject(newChild, true);

    //give this child the app object
    propagateAppObject(newChild);

    //update reference to child's parent
    newChild->parent = this;

    //add the child to the array of children pointers
    children.push_back(newChild);
}
int RGObj::getChildrenSize() const {
    return children.size();
}


/*!propogates the current draw object to a new object (usually a new child), as well as all of it's existing children*/
void RGObj::propagateDrawObject(RGObj* newChild) {
    if(draw != nullptr) {
        newChild->draw = draw;
        for(unsigned int i=0; i < newChild->children.size(); i++) {
            newChild->propagateDrawObject(newChild->children.at(i));
        }
    }
}

/*!propogates the current root object to a new object (usually a new child), as well as all of it's existing children.
If addNames is true, this object and all below it in the tree will register their names with the root object.
*/
void RGObj::propagateRootObject(RGObj* newChild, bool addNames) {
    if(rootObject != nullptr) {
        newChild->rootObject = rootObject;
        if(addNames) {
            rootObject->addName(newChild, newChild->getName() );
        }
        for(int i=0; i<newChild->children.size(); i++) {
            newChild->propagateRootObject(newChild->children.at(i), addNames);
        }

    }
}

/*!propogates the current app object to a new object (usually a new child), as well as all of it's existing children*/
void RGObj::propagateAppObject(RGObj* newChild) {
    if(app != nullptr) {
        newChild->app = app;
        for(int i=0; i<newChild->children.size(); i++) {
            newChild->propagateAppObject(newChild->children.at(i));
        }
    }
}


void RGObj::setName(const std::string& name) {
    this->name = name;
}

string RGObj::getType() const{
    return type;
}
void RGObj::setType(const std::string& type) {
    this->type = type;
}

void RGObj::setDrawObject(RGDraw* newDrawObject) {
    draw = newDrawObject;
}
RGDraw* RGObj::getDrawObject() {
    if( isDrawObjectValid() ) {
        return draw;
    } else {
        return nullptr;
    }
}
RGDraw* RGObj::d() {
    return getDrawObject();
}
bool RGObj::isDrawObjectValid() {
    return draw != nullptr;
}


void RGObj::setEventHandler(RGEventHandlerBase* newEventHandler){
    eventHandler = newEventHandler;
}

//modified to not use framebuffers for now
//XOffset and YOffset should be the absolute coordinates of the parent's top left corner
//this provides meaning to the child's x and y which are offsets from this

//we need some sort of way of passing the current clipping rectangle to children, so if they are
//outside the clipping region and having clipping enabled, they won't exceed the original clipping
//boundary
void RGObj::render(int XOffset, int YOffset, unsigned int milliSecondTimer) {
    if(draw != nullptr){
        preChildrenRender(XOffset, YOffset, milliSecondTimer);

        for(uint32_t i=0; i<getChildrenSize(); i++) {
            if(clipChildren && app != nullptr){
                glEnable(GL_SCISSOR_TEST);
                int clipY = app->getWindowH() - YOffset - shape.getH();
                glScissor(XOffset, clipY, shape.getW(), shape.getH());
            }
            getChild(i)->render(XOffset+getChild(i)->shape.getX(), YOffset+getChild(i)->shape.getY(), milliSecondTimer);
        }

        if(clipChildren){
            glDisable(GL_SCISSOR_TEST);
        }

        postChildrenRender(XOffset, YOffset, milliSecondTimer);
    }
}
void RGObj::preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {
    draw->pushMatrix();
    draw->translate(XOffset,YOffset);
    draw->rectMode(CORNER);
    draw->fill(bkgColor);
    draw->noStroke();
    draw->rect(0,0, shape.getW(),shape.getH());
    draw->popMatrix();
}

void RGObj::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {
    draw->pushMatrix();
    draw->translate(XOffset,YOffset);

	draw->stroke(0);
    draw->noFill();
    draw->rect(0,0, shape.getW() - 1,shape.getH() - 1);
    draw->popMatrix();

}


bool RGObj::mouseOverChild(int mouseX, int mouseY, uint32_t childIndex) {
    auto childLeftCoord = getChild(childIndex)->shape.getL();
    auto childRightCoord = childLeftCoord + getChild(childIndex)->shape.getW();
    auto childTopCoord = getChild(childIndex)->shape.getT();
    auto childBottomCoord = childTopCoord + getChild(childIndex)->shape.getH();

    if(mouseX > childLeftCoord &&
       mouseX < childRightCoord &&
       mouseY > childTopCoord &&
       mouseY < childBottomCoord ) {
        return true;
    }
    return false;
}




int RGObj::getChildXRel2Self(uint32_t childIndex) {
    return getChild(childIndex)->shape.getL();
}
int RGObj::getChildYRel2Self(uint32_t childIndex) {
    return getChild(childIndex)->shape.getT();
}
int RGObj::getDragStartXRel2Self() {
    return dragStart->shape.getL();
}
int RGObj::getDragStartYRel2Self() {
    return dragStart->shape.getT();
}


void RGObj::resize(uint16_t width, uint16_t height){
    if(eventHandler != nullptr) {
        eventHandler->released();
    }
    shape.setW(width);
    shape.setH(height);
}


RGObj* RGObj::getParent() {
    return parent;
}
RGApp* RGObj::getApp() {
    if(app != nullptr) {
        return app;
    } else {
        return nullptr;
    }
}
RGRoot* RGObj::getRoot(){
    if(rootObject != nullptr) {
        return rootObject;
    } else {
        return nullptr;
    }
}



void RGObj::setParent(RGObj* newParent) {
    parent = newParent;
}

void RGObj::setApp(RGApp* newApp) {
    app = newApp;
}

void RGObj::setRoot(RGRoot* newRoot) {
    rootObject = newRoot;
}
