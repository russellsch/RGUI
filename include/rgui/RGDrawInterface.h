#pragma once

#include "RGDrawImplementation.h"

//!Decouples draw interface from implementation
/*!Implements the interface portion of the bridge pattern.

*/
class RGDrawInterface {
public:
	RGDrawInterface(RGDrawImplementation* newImp);

	void noStroke();
    //void stroke(RGColor newStroke);     //!<Set stroke color using an RGColor
    //void stroke(RGColor newStroke, int a);     //!<Set stroke color using an RGColor, overriding the alpha
    void stroke(int brightness);
    void stroke(int brightness, int alpha);
    void stroke(int r, int g, int b);
    void stroke(int r, int g, int b, int a);

    void noFill();
    //void fill(RGColor newFill);
    void fill(int brightness);
    void fill(int brightness, int alpha);
    void fill(int r, int g, int b);
    void fill(int r, int g, int b, int a);

    /*void line(int x1, int y1, int x2, int y2);
    void rect(int x1, int y1, int w, int h);
    void circle(float x1, float y1, float radius);
    void circle(float x1, float y1, float radius, int res);*/

    void pushMatrix();
    void popMatrix();

    void translate(int x, int y);               //!<translate the canvas in 2d using an integer
    void translate(float x, float y);           //!<translate the canvas in 2d using a float
    //void translate(int x, int y, int z);        //!<translate the canvas in 3d using an integer
    //void translate(float x, float y, float z);  //!<translate the canvas in 3d using a float


private:
	RGDrawImplementation* implementation;
	

};