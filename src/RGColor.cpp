#include "rgui/RGColor.hpp"

RGColor::RGColor()
{
    a = 255;
    r = 0;
    g = 0;
    b = 0;
    //ctor
}

RGColor::RGColor(uint8_t brightness)
{
    r = brightness;
    g = brightness;
    b = brightness;
    a = 255;
}

RGColor::RGColor(uint8_t brightness, uint8_t aNew)
{
    r = brightness;
    g = brightness;
    b = brightness;
    a = aNew;
}

RGColor::RGColor(uint8_t rNew, uint8_t gNew, uint8_t bNew)
{
    r = rNew;
    g = gNew;
    b = bNew;
    a = 255;
}

RGColor::RGColor(uint8_t rNew, uint8_t gNew, uint8_t bNew, uint8_t aNew)
{
    r = rNew;
    g = gNew;
    b = bNew;
    a = aNew;
}

