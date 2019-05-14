#include "rgui/ui/RGSlider.hpp"
#include "rgui/ColorRGBA.hpp"

RGSlider::RGSlider(string name, int xNew, int yNew, int wNew, int hNew, string labelNew, float sliderMin, float sliderMax): RGObj(name, "slider", xNew,yNew,wNew,hNew){
    label = labelNew;

    value = .5;
    sliderMapMin = 0;
    sliderMapMax = 250;
    sliderSize = 8;

    numberMode = RG_INT;
    floatPrecision = 1;

    bkgColor = ColorRGBA(200);
    textColor = ColorRGBA(0);

    sliderMode = RGOrientation::HORIZONTAL;
    if(wNew < hNew) {
        sliderMode = RGOrientation::VERTICAL;
    }

    sliderMapMin = sliderMin;
    sliderMapMax = sliderMax;
}



MouseDelegation RGSlider::press(int mouseXin, int mouseYin) {
    cout << "Slider: press received("<<mouseXin<<","<<mouseYin<<")";
    if(sliderMode == RGOrientation::HORIZONTAL) {
        value = draw->map(mouseXin, sliderSize, shape.getW() - sliderSize, 0, 1);
    } else {    //RG_VERTICAL
        value = draw->map(mouseYin, sliderSize, shape.getH() - sliderSize, 0, 1);
    }

    if(value<0){ value=0; }
    if(value>1){ value=1; }
    pMouseX = mouseXin;
    pMouseY = mouseYin;
    if(eventHandler != nullptr) { eventHandler->changed(); }

    return MouseDelegation::THIS_ACCEPTED;
}


MouseDelegation RGSlider::drag(int mouseXin, int mouseYin, int button)  {
    RGObj::drag(mouseXin, mouseYin, button);
    if(!dragging) {
        pMouseX = mouseXin;
        pMouseY = mouseYin;
    }
    if(sliderMode == RGOrientation::HORIZONTAL) {
        if(mouseYin < 0 || mouseYin > shape.getH()) {
            value += draw->map( (float)((mouseXin-pMouseX)/(.1*abs(mouseYin) + 0.0001)), 0,1, 0,
                    (1/((float)shape.getW() - (2*sliderSize)))   );
        } else {
            value = draw->map(mouseXin, sliderSize, shape.getW() - sliderSize, 0, 1);
        }
    } else {    //RG_VERTICAL
        if(mouseXin < 0 || mouseXin > shape.getW()) {
            value += draw->map( (float)((mouseYin - pMouseY)/(.1*abs(mouseXin) + 0.0001)), 0,1, 0,
                    (1/((float)shape.getH() - (2*sliderSize)))   );
        } else {
            value = draw->map(mouseYin, sliderSize, shape.getH() - sliderSize, 0, 1);
        }

    }
    if(value<0){ value=0; }
    if(value>1){ value=1; }
    pMouseX = mouseXin;
    pMouseY = mouseYin;

    if(eventHandler != nullptr) { eventHandler->changed(); }

    return MouseDelegation::THIS_ACCEPTED;
}


void RGSlider::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) {
    //build the value label
    char valueText[255];
    if(numberMode == RG_FLOAT){
        char floatPrintf[10];
        sprintf(floatPrintf, "%%.%df", floatPrecision);
        sprintf( valueText, floatPrintf, draw->map(value, 0,1, sliderMapMin,sliderMapMax) );
    } else if(numberMode == RG_INT){
        sprintf( valueText, "%.0f", draw->map(value, 0,1, sliderMapMin,sliderMapMax) );
    }

    draw->pushMatrix();
    draw->translate(XOffset,YOffset);

    draw->fill(bkgColor);
    draw->stroke(0);
    draw->rectMode(CORNER);
    draw->rect(0, 0, shape.getW(), shape.getH());

    if(sliderMode == RGOrientation::HORIZONTAL) {
        draw->stroke(0);
        draw->line(sliderSize, (3*shape.getH()/4), shape.getW() - sliderSize, (3*shape.getH()/4));
        draw->line(sliderSize, (3*shape.getH()/4) + 1, shape.getW() - sliderSize,(3*shape.getH()/4) + 1);
        draw->line(sliderSize, (3*shape.getH()/4)+4,sliderSize, (3*shape.getH()/4) - 3);
        draw->line(shape.getW() - sliderSize, (3*shape.getH()/4) + 4, shape.getW() - sliderSize, (3*shape.getH()/4) - 3);

        draw->noStroke();
        draw->fill(60,60,255);
        draw->circle(draw->map(value*shape.getW(), 0, shape.getW(), sliderSize, shape.getW() - sliderSize),
                (3*shape.getH()/4) + 0.5, (sliderSize/2), 10);

        draw->fill(textColor);
        draw->textSize(fontSize);
        draw->text(label, 0, draw->textHeight(label) - 1);

        draw->text(valueText, draw->textWidth(label) + 5, draw->textHeight(valueText) - 1 );
    } else {    //sliderMode == RG_VERTICAL
        draw->line((3*shape.getW()/4), sliderSize, (3*shape.getW()/4), shape.getH()-sliderSize);

        draw->noStroke();
        draw->fill(60, 60, 255);
        draw->circle((3*shape.getW()/4), draw->map(value*shape.getH(), 0, shape.getH(), sliderSize,
                shape.getH() - sliderSize), (sliderSize/2), 10 );

        draw->fill(0);
        draw->noStroke();
        draw->textSize(fontSize);

        draw->pushMatrix();
        draw->rotateDeg(-90);

        draw->fill(0);
        draw->text(valueText, -1*(draw->textWidth(valueText) + 6), draw->textHeight(valueText) - 1 );
        draw->text(label, -1*shape.getH() , draw->textHeight(label) - 1 );

        draw->popMatrix();
    }

    draw->popMatrix();
}


void RGSlider::setModeInt(){
    numberMode = RG_INT;
}
void RGSlider::setModeFloat(){
    setModeFloat(2);
}
void RGSlider::setModeFloat(int precision){
    numberMode = RG_FLOAT;
    floatPrecision = precision;
}

void RGSlider::setMinMax(float min, float max){
    sliderMapMin = min;
    sliderMapMax = max;
}


float RGSlider::getRawValue(){
    return value;
}

float RGSlider::getValue(){
    return draw->map(value, 0,1, sliderMapMin,sliderMapMax);
}

