#include "rgui/ui/RGList.hpp"

RGList::RGList(string name, int xNew, int yNew, int wNew, int hNew): RGObj(name, "type", xNew,yNew,wNew,hNew) {
    //type = "list"

    listPosX = 0;
    listPosY = 0;

    clipChildren = true;
    bkgColor = ColorRGBA(128);

}



void RGList::updateChildPositions() {
    int xPosition = listPosX;
    int yPosition = listPosY;
    listW = 0;
    listH = 0;

    for(int i=0; i<getChildrenSize(); i++) {
        getChild(i)->shape.setX(xPosition);
        getChild(i)->shape.setY(yPosition);
        yPosition += getChild(i)->shape.getH();
        listH += getChild(i)->shape.getH();
        if(listW < getChild(i)->shape.getW()) {
            listW = getChild(i)->shape.getW();
        }
    }
}

/*!Subclassed addChild method, used to update the positions of the children in the list each time a new one is added.
This method calls the original RGObj method first.*/
void RGList::addChild(RGObj* newChild) {
    RGObj::addChild(newChild);
    updateChildPositions();
}


void RGList::preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer){
    updateChildPositions();
    //draw->fill(bkgColor);
    //draw->noStroke();
    draw->gradientRect(XOffset,YOffset, shape.getW(),shape.getH(), bkgColor, ColorRGBA(bkgColor.r(), bkgColor.g(), bkgColor.b() + 40),
                       RGOrientation::HORIZONTAL);
}


void RGList::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer){
    draw->rectMode(CORNER);
    draw->noFill();
    draw->stroke(0);
    draw->rect(XOffset, YOffset, shape.getW(), shape.getH());

    for(int i=0; i<4; i++) {  //shadow
        draw->stroke(0, 128 - i*60);
        draw->rect(XOffset + 1 + i, YOffset + 1 + i, shape.getW() - 2 - 2*i, shape.getH() - 2 - 2*i);
    }

    draw->fill(50, 50, 80);
    draw->noStroke();
    draw->roundRect(XOffset + shape.getW() - 5, YOffset+draw->map(listPosYInPerc(), -0.45, 1.6, 1.0, shape.getH() - 13), 4, 8, 2, 5);



}

MouseDelegation RGList::drag(int mouseXin, int mouseYin, MouseButton button) {
    MouseDelegation childrenDragResponse = RGObj::drag(mouseXin, mouseYin, button);
    //cout << "child drag resp:" << childrenDragResponse << endl;
    if(initialDrag) {
        listImgGrabPosX = mouseXin - listPosX;
        listImgGrabPosY = mouseYin - listPosY;
    }
    if(childrenDragResponse == MouseDelegation::NOT_ACCEPTED){
        listPosX = 0;
        listPosY = mouseYin-listImgGrabPosY;
        constrainListPos();
        return MouseDelegation::THIS_ACCEPTED;
    }
    return childrenDragResponse;
}

void RGList::constrainListPos() {
    if(listPosY < -1*(listH - 50) ) {
        listPosY =  -1*(listH - 50);
    } else if(listPosY>(shape.getH() - 50)) {
        listPosY = (shape.getH() - 50);
    }
    if(listPosX < (listW-50)* - 1 ) {
        listPosX =  (listW-50)* - 1;
    }  else if(listPosX>(shape.getW() - 50)) {
        listPosX = (shape.getW() - 50);
    }
   //cout << "listpos%:" << listPosYInPerc();
}

float RGList::listPosYInPerc() {
    return (float)listPosY/listH;
}
