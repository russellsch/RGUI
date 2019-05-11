#pragma once

#include "RGDrawImplementation.h"
#include "RGConst.hpp"
#include "RGColor.hpp"

/*!
Must be used with a valid opengl context... god knows what will happen otherwise
*/
class RGDrawImplementationOpengl: public RGDrawImplementation {
public:
	RGDrawImplementationOpengl();

	void noStroke();
	void stroke(int r, int g, int b, int a);

	void noFill();
	void fill(int r, int g, int b, int a);

	void pushMatrix();
    void popMatrix();

	void translate(float x, float y);
    void translate(float x, float y, float z);

private:
    bool fillEnable;
    bool strokeEnable;
    RGColor fillColor;
    RGColor strokeColor;

};


