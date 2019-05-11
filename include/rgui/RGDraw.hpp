#ifndef RGDRAW_H
#define RGDRAW_H



#include "RGConst.hpp"
#include "RGColor.hpp"
#include "RGTTF.hpp"

#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include "math.h"
#include "float.h"


//!Drawing object for a canvas
class RGDraw {
    public:
        RGDraw();

        void noStroke();
        void stroke(RGColor newStroke);     //!<Set stroke color using an RGColor
        void stroke(RGColor newStroke, int a);     //!<Set stroke color using an RGColor, overriding the alpha
        void stroke(int brightness);
        void stroke(int brightness, int alpha);
        void stroke(int r, int g, int b);
        void stroke(int r, int g, int b, int a);

        void noFill();
        void fill(RGColor newFill);
        void fill(int brightness);
        void fill(int brightness, int alpha);
        void fill(int r, int g, int b);
        void fill(int r, int g, int b, int a);

        void line(int x1, int y1, int x2, int y2);
        void rect(int x1, int y1, int w, int h);
        void circle(float x1, float y1, float radius);
        void circle(float x1, float y1, float radius, int res);
        void ellipse(int x1, int y1, int w, int h);
        void ellipse(int x1, int y1, int w, int h, int res);
        void arc(int x, int y, float r, float angle1, float angle2, int resolution);
        void arcVertex(int x, int y, float radius, float startAngle, float arcAngle, int resolution); //!<spits out raw opengl vertexes along an arc

        void rectMode(int mode);    //!<Sets the point where a rectangle is drawn from
        void circleResolution(int res);     //!<Sets the current circle resolution

        void beginShape();
        void endShape();
        void vertex(int x, int y);
        void curveVertex(int x, int y);
        void bezierVertex(int x1, int y1, int x2, int y2, int x3, int y3);
        void quadBezVertex(int prevX, int prevY, int x1, int y1, int x2, int y2);

        void roundRect(int x, int y, int w, int h, int radius);
        void roundRect(int x, int y, int w, int h, int radius, int resolution);
        void gradientRect(int x, int y, int w, int h, RGColor color1, RGColor color2);  //!<Draw a rectangle with a vertical gradient
        void gradientRect(int x, int y, int w, int h, RGColor color1, RGColor color2, int orientation); //!<Draw a rectangle with a vertical gradient

        void rectDropShadow(RGColor startColor, int x, int y, int w, int h, int steps);

        void pushMatrix();
        void popMatrix();

        void translate(int x, int y);               //!<translate the canvas in 2d using an integer
        void translate(float x, float y);           //!<translate the canvas in 2d using a float
        void translate(int x, int y, int z);        //!<translate the canvas in 3d using an integer
        void translate(float x, float y, float z);  //!<translate the canvas in 3d using a float
        void rotateDeg(float degrees);

        void text(wstring text, int x, int y);//!<Draws unicode text to the screen using truetype font textures
        void text(string text, int x, int y);//!<Draws ascii text to the screen using truetype font textures
        void textFont();
        void textSize(int size);
        int textWidth(string text);
        int textWidth(wstring text);
        int textHeight(string text);
        int textHeight(wstring text);

        float map(float value, float inputMin, float inputMax, float outputMin, float outputMax);


    protected:
        bool fillEnabled;
        bool strokeEnabled;
        RGColor fillColor;
        RGColor strokeColor;

        int rectDrawMode;

        //circle stuff
        int currentCircleRes;
        float circleCalcPts[RG_MAX_CIRCLE_PTS*2];
        float circlePts[RG_MAX_CIRCLE_PTS*2];

        //font
        string fontFile;

        int fontSizePts;
        bool fontValid;

        //std::map<int, ofTrueTypeFont> fonts;
        RGTTF font;

        int transformDepth; //Track depth of push and pop operations



    private:
};

//THESE NEED TO BE MOVED TO SOME SORT OF UTILITIES FILE
float rgMap(float value, float inputMin, float inputMax, float outputMin, float outputMax);


int clamp(int input, int min, int max);
float clamp(float input, float min, float max);


string toString(int input);
string toString(float input, int precision);
string toString(float input);

wstring toWString(string text);





#endif // RGDRAW_H
