#ifndef RGFRAME_H
#define RGFRAME_H

#include "RGObj.hpp"


//!Simple frame object that can hold other objects
class DLLHELPER RGFrame : public RGObj
{
    public:
        string label;

        RGFrame(string name, int xNew, int yNew, int wNew, int hNew);
        RGFrame(string name, int xNew, int yNew, int wNew, int hNew, string labelNew);
        virtual ~RGFrame();
        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);
    protected:
    private:
};

#endif // RGFRAME_H
