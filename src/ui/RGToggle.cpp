#include "RGToggle.hpp"

RGToggle::RGToggle(string name, int xNew, int yNew, int wNew, int hNew, string labelNew): RGObj(name, "toggle", xNew,yNew,wNew,hNew) {
    label = labelNew;
    style = 3;
    value = false;
    textColor = RGColor(0);
    verboseToggle = false;
}

RGToggle::~RGToggle()
{
    //dtor
}




void RGToggle::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {
    draw->textSize(fontSize);
    draw->pushMatrix();
    draw->translate(XOffset, YOffset);

    if(style == 0) {    //toggle button


    } else if(style == 1) { //sliding toggle


    } else if(style == 2) {     //checkbox
        draw->noFill();
        draw->stroke(0);
        draw->rect(0,0, getH(),getH());
        if(value) {
            draw->line(0,1, getH(),getH()+1);
            draw->line(getH(),0, 0,getH());
        }
        draw->text(label, getH()+2,(getH()/2)+3);

    } else if(style == 3) {     //radio button
        draw->noFill();
        draw->stroke(0);
        draw->circle(getH()/2,getH()/2, (getH()/2)*.95);

        draw->fill(textColor);
        draw->noStroke();
        draw->text(label, getH()+2,(getH()/2)+2);
        if(value) {
            draw->fill(0);
            draw->circle(getH()/2,getH()/2, (getH()/2.0)*.5);
        }

    }

    draw->popMatrix();
}



void RGToggle::toggle() {
    if(style == 3) { //radio buttons only turn on when clicked
        value = true;
    } else {    //other button styles toggle
        if(value) {
            value = false;
        } else {
            value = true;
        }
    }

}


int RGToggle::press(int mouseXin, int mouseYin) {
    if(verboseToggle) { cout<<"Toggle(): Press received("<<mouseXin<<","<<mouseYin<<")"<<endl; }

    if(eventHandlerValid) {
        //eventHandler->changed();
        eventHandler->pressed();
    }

    return 1;
}

void RGToggle::release(int mouseXin, int mouseYin) {
    if(verboseToggle) { cout<<"Toggle(): Release received("<<mouseXin<<","<<mouseYin<<")"<<endl; }
    if(eventHandlerValid) { eventHandler->released(); }


    //if you press the mouse on the button, and then drag away and let go it won't do anything
    if(mouseXin>0 && mouseXin<getW() && mouseYin>0 && mouseYin<getH()){
        toggle();
        if(eventHandlerValid) {
            eventHandler->changed();
            eventHandler->clicked();
        }
    }
}


void RGToggle::setOff(){
    value = false;
}
void RGToggle::setOn(){
    value = true;
}

void RGToggle::setStyle(int styleNew){
    style = styleNew;
}

bool RGToggle::getValue(){
    return value;
}
