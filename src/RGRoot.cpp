#include "rgui/RGRoot.hpp"

RGRoot::RGRoot(int wNew, int hNew, RGApp* newApp): RGObj("main", "main", 0,0,wNew,hNew) {
    bkgColor = ColorRGBA(128);

    resizable = true;
    stretchX = 0;
    stretchY = 0;
    anchorX = 1;
    anchorY= 1;

    //give this object the draw class so it passes down to any added children
    draw = new RGDraw();
    drawValid = true;

    //do the same for a pointer to this class
    setRoot(this);
    //rootObject = this;
    //rootObjectValid = true;

    //set the parent app object
    //app = newApp;
    //appValid = true;
    setApp(newApp);

    timer.start();

}

RGRoot::~RGRoot() {
    //dtor
}


void RGRoot::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {
    draw->rectMode(CORNER);
    draw->noFill();
    draw->stroke(0);
    draw->rect(0,0,getW()-1,getH()-1);

}



/*!
IMPORTANT: This will return NULL if nothing with that name is found. Make sure you have code in place to catch this!

As a convention, names are generally lowercase letters, numbers, and underscores (although other special characters are valid, but not
full UTF8).
*/
RGObj* RGRoot::findChildByName(string name) {
    map<string, RGObj*>::iterator iter = nameList.find(name);
    if(iter != nameList.end()){
        return iter->second;
    } else {
        return NULL;
    }

}

/*!
Adds the name of an object to an associative array that maps a name to an object. This allows for objects to be quickly found in the heierchy by name

If an object with the same name is added twice, the initial RGObj pointer will be overwritten with the new.
*/
void RGRoot::addName(RGObj* object, string name) {
    nameList.insert(std::pair<string, RGObj*>(name, object));
    //nameList[name] = object;
}

void RGRoot::removeName(string name) {
    //nameList.insert(std::pair<string, RGObj*>(name, object));
    nameList.erase(name);
}


void RGRoot::render(int XOffset, int YOffset) {
    RGObj::render(XOffset, YOffset, (unsigned int)timer.getTimeMs() );
}

double RGRoot::getTimeMs() {
    return timer.getTimeMs();
}
