#include "RGButton.hpp"

RGButton::RGButton(string name, int xNew, int yNew, int wNew, int hNew, wstring labelNew): RGObj(name, "buttonspst", xNew,yNew,wNew,hNew) {
    verboseSPST = false;
    enabled = true;
    pressed = false;

    setStyle(0);
    label=labelNew;
}
RGButton::RGButton(string name, int xNew, int yNew, int wNew, int hNew, string labelNew): RGObj(name, "buttonspst", xNew,yNew,wNew,hNew) {
    RGButton::RGButton( name, xNew, yNew, wNew, hNew, toWString(labelNew));
}


void RGButton::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {

    draw->pushMatrix();
    draw->translate(XOffset,YOffset);

    draw->rectMode(CORNER);

    if(style == 0) {
        if(pressed) {
            draw->stroke(0);
            draw->fill(pressedColor);
            draw->roundRect(0,0,getW(),getH(), 10, 10);

            draw->noFill();
            draw->stroke(80,80,80);
            draw->roundRect(1,1,getW()-1,getH()-1, 10, 10);

        } else {
            draw->stroke(0);
            draw->fill(bkgColor);
            draw->roundRect(0,0,getW(),getH(), 10, 10);
        }
        draw->stroke(textColor);
        draw->fill(textColor);
        draw->textSize(fontSize);
        draw->text(label, (getW()/2)-((draw->textWidth(label))/2),(getH()/2)+2);
    } else {
        if(milliSecondTimer%1000 > 500) {
            bkgColor = RGColor(255,0,0);
        } else {
            bkgColor = RGColor(0,255,0);
        }
        if(pressed) {
            draw->stroke(pressedColor, 128);
            draw->fill(pressedColor);
            draw->ellipse(0+getW()/2,0+getH()/2,getW(),getH(),20);
        } else {
            draw->stroke(bkgColor, 128);
            draw->fill(bkgColor);
            draw->ellipse(0+getW()/2,0+getH()/2,getW(),getH(),20);
        }
        draw->stroke(textColor);
        draw->fill(textColor);
        draw->textSize(fontSize);
        draw->text(label, (getW()/2)-((draw->textWidth(label))/2),(getH()/2)+2);
    }
    draw->popMatrix();

}

void RGButton::preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {

}

void RGButton::setStyle(int styleNew) {
    if(styleNew == 0){
        style = 0;
        bkgColor = RGColor(200);
        textColor = RGColor(0);
        pressedColor = RGColor(128, 128, 200);
    } else {
        style = 1;
        bkgColor = RGColor(60,153,49);
        textColor = RGColor(0);
        pressedColor = RGColor(240, 186, 54);
    }

}

int RGButton::getStyle() {
    return style;
}

int RGButton::press(int mouseXin, int mouseYin) {
    if(verboseSPST) { cout<<"SPST(): Press received("<<mouseXin<<","<<mouseYin<<")"<<endl; }

    pressed = true;

    if(eventHandlerValid) {
        eventHandler->changed();
        eventHandler->pressed();
    }

    return 1;
}

void RGButton::release(int mouseXin, int mouseYin) {
    if(verboseSPST) { cout<<"SPST(): Release received("<<mouseXin<<","<<mouseYin<<")"<<endl; }

    pressed = false;

    if(eventHandlerValid) {
            eventHandler->changed();
            eventHandler->released();
    }
    //if you press the mouse on the button, and then drag away and let go it won't do anything
    if(mouseXin>0 && mouseXin<getW() && mouseYin>0 && mouseYin<getH()){
        if(eventHandlerValid) {
            eventHandler->clicked();
        }
    }

}

RGButton::~RGButton()
{
    //dtor
}