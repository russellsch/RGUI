#pragma once

#include "RGConst.hpp"
#include "RGColor.hpp"

/*!
Implementation base class for various drawing implementations.
Used by the RGDrawInterface to use various drawing systems and wrappers
*/
class RGDrawImplementation {
public:
	virtual void noStroke() {};
    virtual void stroke(int r, int g, int b, int a) {};

    virtual void noFill() {};
    virtual void fill(int r, int g, int b, int a) {};

    virtual void line(int x1, int y1, int x2, int y2) {};
    virtual void rect(int x1, int y1, int w, int h) {};
    virtual void circle(float x1, float y1, float radius) {};
    virtual void circle(float x1, float y1, float radius, int res) {};

    virtual void pushMatrix() {};
    virtual void popMatrix() {};

    virtual void translate(float x, float y) {};           //!<translate the canvas in 2d using a float
    virtual void translate(float x, float y, float z) {};  //!<translate the canvas in 3d using a float

};