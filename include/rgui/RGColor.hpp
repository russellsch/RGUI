#ifndef RGCOLOR_H
#define RGCOLOR_H
#include "rgui/RGConst.hpp"

//!Represents a single color and transparency
class DLLHELPER RGColor {
    public:
        int r,g,b,a;
        RGColor();
        RGColor(int brightness);    //!Set R, G, and B to a single value
        RGColor(int brightness, int a); //!Set R, G, and B to a single value, and alpha to another
        RGColor(int r, int g, int b);   //!Set R, G, and B individually
        RGColor(int r, int g, int b, int a);    //!Set R, G, B, and alpha individually
};

#endif // RGCOLOR_H
