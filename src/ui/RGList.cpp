#include "rgui/ui/RGList.hpp"

RGList::RGList(string name, int xNew, int yNew, int wNew, int hNew): RGObj(name, "type", xNew,yNew,wNew,hNew) {
    //type = "list"

    listPosX = 0;
    listPosY = 0;

    clipChildren = true;
    bkgColor = RGColor(128);

}

RGList::~RGList()
{
    //dtor
}



void RGList::updateChildPositions() {
    int xPosition = listPosX;
    int yPosition = listPosY;
    listW = 0;
    listH = 0;

    for(int i=0; i<getChildrenSize(); i++) {
        getChild(i)->setX(xPosition);
        getChild(i)->setY(yPosition);
        yPosition += getChild(i)->getH();
        listH += getChild(i)->getH();
        if(listW < getChild(i)->getW()) {
            listW = getChild(i)->getW();
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
    draw->gradientRect(XOffset,YOffset, getW(),getH(), bkgColor, RGColor(bkgColor.r, bkgColor.g, bkgColor.b+40), RG_HORIZONTAL);
}


void RGList::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer){
    draw->rectMode(CORNER);
    draw->noFill();
    draw->stroke(0);
    draw->rect(XOffset,YOffset, getW(),getH());

    for(int i=0; i<4; i++) {  //shadow
        draw->stroke(0,128-i*60);
        draw->rect(XOffset+1+i,YOffset+1+i, getW()-2-2*i, getH()-2-2*i);
    }

    draw->fill(50,50,80);
    draw->noStroke();
    draw->roundRect(XOffset+getW()-5, YOffset+draw->map(listPosYInPerc(), -.45, 1.6, 1.0, getH()-13), 4, 8, 2, 5);



}

int RGList::drag(int mouseXin, int mouseYin, int button) {
    int childrenDragResponse = RGObj::drag(mouseXin, mouseYin, button);
    //cout << "child drag resp:" << childrenDragResponse << endl;
    if(initialDrag) {
        listImgGrabPosX = mouseXin - listPosX;
        listImgGrabPosY = mouseYin - listPosY;
    }
    if(childrenDragResponse == 0){
        listPosX = 0;
        listPosY = mouseYin-listImgGrabPosY;
        constrainListPos();
        return 1;
    }
    return childrenDragResponse;
}

void RGList::constrainListPos() {
    if(listPosY < (listH-50)*-1 ) {
        listPosY =  (listH-50)*-1;
    } else if(listPosY>(getH()-50)) {
        listPosY = (getH()-50);
    }
    if(listPosX < (listW-50)*-1 ) {
        listPosX =  (listW-50)*-1;
    }  else if(listPosX>(getW()-50)) {
        listPosX = (getW()-50);
    }
   //cout << "listpos%:" << listPosYInPerc();
}

float RGList::listPosYInPerc() {
    return (float)listPosY/listH;
}