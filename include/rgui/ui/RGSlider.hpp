#ifndef RGHSLIDER_H
#define RGHSLIDER_H

#include "rgui/RGObj.hpp"

#include <iostream>
#include <cstdio>


//!General purpose 1D slider widget
/*!
This object acts as a horizontal or vertical slider depending on whether it's width or length is longer, and will change how it looks accordingly.
By setModeInt() or setModeFloat() the style in which numbers are displayed can be changed.
Additionally the number of digits after the decimal can be set as well when using floats.
*/
class RGSlider : public RGObj {
    public:
        float value; //!Always between 0 and 1 internally
        float sliderMapMin, sliderMapMax;
        int sliderSize;
        string label;

        int numberMode;
        int floatPrecision;

        //ofColor bkgColor, textColor;
        int pMouseX, pMouseY;

        RGOrientation sliderMode;

        RGSlider(string name, int xNew, int yNew, int wNew, int hNew, string labelNew);
        RGSlider(string name, int xNew, int yNew, int wNew, int hNew, string labelNew, float sliderMin, float sliderMax);

        MouseDelegation press(int mouseXin, int mouseYin);
        MouseDelegation drag(int mouseXin, int mouseYin, int button);

        void postChildrenRender(int XOffset, int YOffset, unsigned int milliSecondTimer);
        virtual ~RGSlider();

        void setModeInt();
        void setModeFloat();
        void setModeFloat(int precision);

        void setMinMax(float min, float max);

        float getRawValue();
        float getValue();

    protected:
    private:
};




#endif // RGHSLIDE_H
