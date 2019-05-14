#include "rgui/ui/RGFrame.hpp"

RGFrame::RGFrame(string name, int xNew, int yNew, int wNew, int hNew, string label): RGObj(name, "frame", xNew,yNew,wNew,hNew) {
    this->label = label;
    textColor = ColorRGBA(80);
}
RGFrame::RGFrame(string name, int xNew, int yNew, int wNew, int hNew): RGObj(name, "frame", xNew,yNew,wNew,hNew) {
    label = "";
    textColor = ColorRGBA(80);
}



void RGFrame::postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer){
    draw->rectMode(CORNER);
    draw->noFill();
    draw->stroke(80);
    draw->textSize(fontSize);

    draw->stroke(80);
    auto height = this->shape.getH();
    auto width = this->shape.getW();

    if(label.empty()) {
        draw->line(XOffset, YOffset, XOffset, YOffset + height + 1);
        draw->line(XOffset, YOffset + height, XOffset + width, YOffset + height);
        draw->line(XOffset + width, YOffset + height, XOffset + width, YOffset);
        draw->line(XOffset, YOffset, XOffset + width, YOffset);
    } else {
        int labelW = draw->textWidth(label);
        int labelH = draw->textHeight(label);
        draw->line(XOffset, YOffset + (labelH/2), XOffset, YOffset + shape.getH() + 1);
        draw->line(XOffset, YOffset + height, XOffset + width, YOffset + height);
        draw->line(XOffset + shape.getW(), YOffset + shape.getH(), XOffset + width, YOffset + (labelH/2));

        draw->line(XOffset, YOffset + (labelH/2), XOffset+(shape.getW()-labelW)/2, YOffset + (labelH/2));
        draw->line(XOffset + shape.getW() - (shape.getW() - labelW)/2, YOffset + (labelH/2), XOffset + shape.getW(), YOffset + (labelH/2));

        draw->fill(textColor);
        draw->text(label, XOffset + (shape.getW()/2) - (labelW/2), YOffset + (labelH/2) + 1);
    }

    //draw->noFill();
    draw->fill(0, 100, 200, 128);
    draw->stroke(0);
    draw->rect(10, 10, 30, 30);

}
