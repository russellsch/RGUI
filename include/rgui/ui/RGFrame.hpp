#ifndef RGFRAME_H
#define RGFRAME_H

#include "rgui/RGObj.hpp"


//!Simple frame object that can hold other objects
class RGFrame : public RGObj
{
    public:
        string label;

        RGFrame(string name, int xNew, int yNew, int wNew, int hNew);
        RGFrame(string name, int xNew, int yNew, int wNew, int hNew, string label);
        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer) override;
    protected:
    private:
};

#endif // RGFRAME_H
