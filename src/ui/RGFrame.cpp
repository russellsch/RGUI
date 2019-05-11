#include "rgui/ui/RGFrame.hpp"

RGFrame::RGFrame(string name, int xNew, int yNew, int wNew, int hNew, string label): RGObj(name, "frame", xNew,yNew,wNew,hNew) {
    this->label = label;
    textColor = RGColor(80);
}
RGFrame::RGFrame(string name, int xNew, int yNew, int wNew, int hNew): RGObj(name, "frame", xNew,yNew,wNew,hNew) {
    label = "";
    textColor = RGColor(80);
}



void RGFrame::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer){
    draw->rectMode(CORNER);
    draw->noFill();
    draw->stroke(80);
    draw->textSize(fontSize);

    draw->stroke(80);

    if(label == "") {
        draw->line(XOffset, YOffset, XOffset, YOffset+this->getH()+1);
        draw->line(XOffset, YOffset+this->getH(), XOffset+this->getW(), YOffset+this->getH());
        draw->line(XOffset+this->getW(), YOffset+this->getH(), XOffset+this->getW(), YOffset);
        draw->line(XOffset, YOffset, XOffset+this->getW(), YOffset);
    } else {
        int labelW = draw->textWidth(label);
        int labelH = draw->textHeight(label);
        draw->line(XOffset, YOffset+(labelH/2), XOffset, YOffset+getH()+1);
        draw->line(XOffset, YOffset+this->getH(), XOffset+this->getW(), YOffset+this->getH());
        draw->line(XOffset+getW(), YOffset+getH(), XOffset+this->getW(), YOffset+(labelH/2));

        draw->line(XOffset, YOffset+(labelH/2), XOffset+(getW()-labelW)/2, YOffset+(labelH/2));
        draw->line(XOffset+getW()-(getW()-labelW)/2, YOffset+(labelH/2), XOffset+getW(), YOffset+(labelH/2));

        draw->fill(textColor);
        draw->text(label, XOffset+ (getW()/2)-(labelW/2), YOffset+(labelH/2)+1);
    }

    //draw->noFill();
    draw->fill(0, 100, 200, 128);
    draw->stroke(0);
    draw->rect(10, 10, 30, 30);

}
