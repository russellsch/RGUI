#ifndef RGCOLOR_H
#define RGCOLOR_H

#include <cstdint>
#include "rgui/RGConst.hpp"

//!Represents a single color and transparency
class RGColor {
    public:
        uint8_t r, g, b, a;
        RGColor();
        explicit RGColor(uint8_t brightness);    //!Set R, G, and B to a single value
        RGColor(uint8_t brightness, uint8_t a); //!Set R, G, and B to a single value, and alpha to another
        RGColor(uint8_t r, uint8_t g, uint8_t b);   //!Set R, G, and B individually
        RGColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);    //!Set R, G, B, and alpha individually
};

#endif // RGCOLOR_H
