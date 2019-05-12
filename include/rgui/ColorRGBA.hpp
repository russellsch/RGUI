#ifndef COLORRGBA_H
#define COLORRGBA_H

#include <cstdint>
#include <array>


//! Represents a RGB+Alpha color
class ColorRGBA {
    protected:
        std::array<uint8_t, 4> rgba = {0, 0, 0, 255};

    public:

        ColorRGBA() = default;
        explicit ColorRGBA(uint8_t brightness) {rgba = {brightness, brightness, brightness, 255};}
        ColorRGBA(uint8_t brightness, uint8_t alpha) {rgba = {brightness, brightness, brightness, alpha};}
        ColorRGBA(uint8_t red, uint8_t green, uint8_t blue) {rgba = {red, green, blue, 255};}
        ColorRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {rgba = {red, green, blue, alpha};}

        uint8_t r() { return rgba[0]; }
        uint8_t red() { return rgba[0]; }
        void setR(uint8_t r) { rgba[0] = r; }
        void setRed(uint8_t red) { rgba[0] = red; }

        uint8_t g() { return rgba[1]; };
        uint8_t green() { return rgba[1]; };
        void setG(uint8_t g) { rgba[1] = g; }
        void setGreen(uint8_t green) { rgba[1] = green; }

        uint8_t b() { return rgba[2]; };
        uint8_t blue() { return rgba[2]; };
        void setB(uint8_t b) { rgba[2] = b; }
        void setBlue(uint8_t blue) { rgba[2] = blue; }

        uint8_t a() { return rgba[3]; };
        uint8_t alpha() { return rgba[3]; };
        void setA(uint8_t a) { rgba[3] = a; }
        void setAlpha(uint8_t alpha) { rgba[3] = alpha; }
};

#endif // COLORRGBA_H
