#include "rgui/RGColor.hpp"

RGColor::RGColor()
{
    a = 255;
    r = 0;
    g = 0;
    b = 0;
    //ctor
}

RGColor::RGColor(int brightness)
{
    r = brightness;
    g = brightness;
    b = brightness;
    a = 255;
}

RGColor::RGColor(int brightness, int aNew)
{
    r = brightness;
    g = brightness;
    b = brightness;
    a = aNew;
}

RGColor::RGColor(int rNew, int gNew, int bNew)
{
    r = rNew;
    g = gNew;
    b = bNew;
    a = 255;
}

RGColor::RGColor(int rNew, int gNew, int bNew, int aNew)
{
    r = rNew;
    g = gNew;
    b = bNew;
    a = aNew;
}

