#include "rgui/ui/RGButton.hpp"

RGButton::RGButton(string name, int xNew, int yNew, int wNew, int hNew, std::wstring label): RGObj(name, "buttonspst", xNew,yNew,wNew,hNew) {
    verboseSPST = false;
    enabled = true;
    pressed = false;

    setStyle(0);
    this->label = label;
}
/*RGButton::RGButton(string name, int xNew, int yNew, int wNew, int hNew, string labelNew): RGObj(name, "buttonspst", xNew,yNew,wNew,hNew) {
    verboseSPST = false;
    enabled = true;
    pressed = false;

    setStyle(0);
    label=wstring(labelNew.c_str());
}*/


void RGButton::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {

    draw->pushMatrix();
    draw->translate(XOffset,YOffset);

    draw->rectMode(CORNER);

    if(style == 0) {
        if(pressed) {
            draw->stroke(0);
            draw->fill(pressedColor);
            //draw->roundRect(0,0,getW(),getH(), 10, 10);
            draw->rect(0, 0, shape.getW(), shape.getH());

            draw->noFill();
            draw->stroke(80, 80, 80);
            //draw->roundRect(1,1,getW()-1,getH()-1, 10, 10);
            draw->rect(1, 1, shape.getW() - 1, shape.getH() - 1);

        } else {
            draw->stroke(0);
            draw->fill(bkgColor);
            //draw->roundRect(0,0,getW(),getH(), 10, 10);
            draw->rect(0, 0, shape.getW(), shape.getH());
        }
        draw->stroke(textColor);
        draw->fill(textColor);
        draw->textSize(fontSize);
        draw->text(label, (shape.getW()/2) - ((draw->textWidth(label))/2), (shape.getH()/2) + 2);
    } else {
        if(milliSecondTimer % 1000 > 500) {
            bkgColor = ColorRGBA(255, 0, 0);
        } else {
            bkgColor = ColorRGBA(0, 255, 0);
        }
        if(pressed) {
            draw->stroke(pressedColor, 128);
            draw->fill(pressedColor);
            draw->ellipse(0 + shape.getW()/2, 0 + shape.getH()/2, shape.getW(), shape.getH(), 20);
        } else {
            draw->stroke(bkgColor, 128);
            draw->fill(bkgColor);
            draw->ellipse(0 + shape.getW()/2, 0 + shape.getH()/2, shape.getW(), shape.getH(), 20);
        }
        draw->stroke(textColor);
        draw->fill(textColor);
        draw->textSize(fontSize);
        draw->text(label, (shape.getW()/2) - ((draw->textWidth(label))/2), (shape.getH()/2) + 2);
    }
    draw->popMatrix();

}

void RGButton::preChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {

}

void RGButton::setStyle(int styleNew) {
    if(styleNew == 0){
        style = 0;
        bkgColor = ColorRGBA(200);
        textColor = ColorRGBA(0);
        pressedColor = ColorRGBA(128, 128, 200);
    } else {
        style = 1;
        bkgColor = ColorRGBA(60,153,49);
        textColor = ColorRGBA(0);
        pressedColor = ColorRGBA(240, 186, 54);
    }

}


MouseDelegation RGButton::press(int mouseXin, int mouseYin) {
    if(verboseSPST) { cout<<"SPST(): Press received("<<mouseXin<<","<<mouseYin<<")"<<endl; }

    pressed = true;

    if(eventHandler != nullptr) {
        eventHandler->changed();
        eventHandler->pressed();
    }

    return MouseDelegation::THIS_ACCEPTED;
}

void RGButton::release(int mouseXin, int mouseYin) {
    if(verboseSPST) { cout<<"SPST(): Release received("<<mouseXin<<","<<mouseYin<<")"<<endl; }

    pressed = false;

    if(eventHandler != nullptr) {
            eventHandler->changed();
            eventHandler->released();
    }
    //if you press the mouse on the button, and then drag away and let go it won't do anything
    if(mouseXin > 0 && mouseXin < shape.getW() && mouseYin > 0 && mouseYin < shape.getH()){
        if(eventHandler != nullptr) {
            eventHandler->clicked();
        }
    }

}
