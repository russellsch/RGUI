//wrap all openframeworks calls if possible

#include "RGDraw.hpp"

#include "GL/glew.h"

//Platform switch to allow getting the current working directory
//because microsoft breaks posix getcwd and renames it to _getcwd
//they also put it in a different header
#ifdef TARGET_WIN32_VC
    #include "direct.h"
    #define getcwd _getcwd
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#else
    #include "unistd.h"
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


//#include <SFML/Window.hpp>

/*#ifdef TARGET_OSX
	#include <OpenGL/glu.h>
#endif

#ifdef TARGET_OPENGLES
	#include "glu.h"
#endif

#ifdef TARGET_LINUX
	#include "GL/glu.h"
#endif

#ifdef TARGET_WIN32
	#include "glu.h"
#endif*/


RGDraw::RGDraw() {
    //intialize variables
    rectMode(CORNER);
    circleResolution(20);

    fillColor = RGColor(0,0,0);
    strokeColor = RGColor(0,0,0);

    fontSizePts = 15;
    fontFile = "data/wqy-microhei.ttc";

    //ofEnableAlphaBlending();
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    font = RGTTF();
    font.loadFont(fontFile, fontSizePts);

}



void RGDraw::line(int x1, int y1, int x2, int y2){
    //ofSetColor(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);
    //ofLine(x1,y1,x2,y2);

    glColor4ub(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);

    float linePoints[4];
    linePoints[0] = (float)x1;
	linePoints[1] = (float)y1;
	linePoints[2] = (float)x2;
	linePoints[3] = (float)y2;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, &linePoints[0]);
	glDrawArrays(GL_LINES, 0, 2);
}
void RGDraw::rect(int x1, int y1, int w, int h) {
    float cornerPoints[8];

    if(rectDrawMode == CORNER) {
        cornerPoints[0] = (float) x1;
        cornerPoints[1] = (float) y1;
        cornerPoints[2] = (float) (x1+w);
        cornerPoints[3] = (float) y1;
        cornerPoints[4] = (float) (x1+w);
        cornerPoints[5] = (float) (y1+h);
        cornerPoints[6] = (float) (x1-1);
        cornerPoints[7] = (float) (y1+h);
    } else {
        cornerPoints[0] = (float) (x1-w/2-1);
        cornerPoints[1] = (float) (y1-h/2);
        cornerPoints[2] = (float) (x1+w/2);
        cornerPoints[3] = (float) (y1-h/2);
        cornerPoints[4] = (float) (x1+w/2);
        cornerPoints[5] = (float) (y1+h/2);
        cornerPoints[6] = (float) (x1-w/2);
        cornerPoints[7] = (float) (y1+h/2);
    }
    //fill
    if(fillEna) {
        glColor4ub(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &cornerPoints[0]);
        glDrawArrays(GL_QUADS, 0, 4);
    }
    //border
    if(strokeEna) {
        glColor4ub(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &cornerPoints[0]);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

}
void RGDraw::circle(float x1, float y1, float radius) {
    if(currentCircleRes == -1) {    //make sure a circle resolution is set
        currentCircleRes = 30;
    }
    circle(x1, y1, radius, currentCircleRes);
}
void RGDraw::circle(float x1, float y1, float radius, int res) {
    if(res != currentCircleRes) {
        circleResolution(res);
    }

	for(int i = 0; i < currentCircleRes*2; i+=2){
		circlePts[i]   = x1 + circleCalcPts[i] * radius;
		circlePts[i+1] = y1 + circleCalcPts[i+1] * radius;
 	}
    //fill
    if(fillEna) {
        glColor4ub(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &circlePts[0]);
        glDrawArrays( GL_POLYGON, 0, currentCircleRes);
    }
    //border
    if(strokeEna) {
        glColor4ub(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &circlePts[0]);
        glDrawArrays( GL_LINE_LOOP, 0, currentCircleRes);
    }
}
void RGDraw::ellipse(int x1, int y1, int w, int h) {
    if(currentCircleRes == -1) {    //make sure a circle resolution is set
        currentCircleRes = 30;
    }
    ellipse(x1, y1, w, h, currentCircleRes);
}
void RGDraw::ellipse(int x1, int y1, int w, int h, int res) {
    if(res != currentCircleRes) {
        circleResolution(res);
    }

	for(int i = 0; i < currentCircleRes*2; i+=2){
		circlePts[i]   = x1 + circleCalcPts[i] * w * .5;
		circlePts[i+1] = y1 + circleCalcPts[i+1] * h * .5;
 	}
    //fill
    if(fillEna) {
        glColor4ub(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &circlePts[0]);
        glDrawArrays( GL_POLYGON, 0, currentCircleRes);
    }
    //border
    if(strokeEna) {
        glColor4ub(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, &circlePts[0]);
        glDrawArrays( GL_LINE_LOOP, 0, currentCircleRes);
    }
}
void RGDraw::arc(int x, int y, float radius, float startAngle, float arcAngle, int resolution){
    //glColor4ub(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);


    float theta = arcAngle/float(resolution-1);
    float tFactor = tanf(theta);
    float radFactor = cosf(theta);

    //float x2 = radius*cosf(startAngle);
    ///float y2 = radius*sinf(startAngle);

    if(fillEna) {
        float x2 = radius*cosf(startAngle);
        float y2 = radius*sinf(startAngle);

        glColor4ub(fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        glBegin(GL_POLYGON);
        for(int i=0; i < resolution; i++) {
            glVertex2f(x2+x,y2+y);

            float tx = -y2;
            float ty = x2;

            x2 = (x2+tx*tFactor)*radFactor;
            y2 = (y2+ty*tFactor)*radFactor;
        }
        glVertex2f(x,y);
        glEnd();
    }

    if(strokeEna) {
        float x2 = radius*cosf(startAngle);
        float y2 = radius*sinf(startAngle);

        glColor4ub(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);
        glBegin(GL_LINE_STRIP);
        for(int i=0; i < resolution; i++) {
            glVertex2f(x2+x,y2+y);

            float tx = -y2;
            float ty = x2;

            x2 = (x2+tx*tFactor)*radFactor;
            y2 = (y2+ty*tFactor)*radFactor;
        }
        glEnd();
    }

}


/*!
Assumes you've done some sort of glBegin(___);
*/
void RGDraw::arcVertex(int x, int y, float radius, float startAngle, float arcAngle, int resolution){
    float theta = arcAngle/float(resolution-1);
    float tFactor = tanf(theta);
    float radFactor = cosf(theta);

    float x2 = radius*cosf(startAngle);
    float y2 = radius*sinf(startAngle);

    for(int i=0; i < resolution; i++) {
        glVertex2f(x2+x,y2+y);

        float tx = -y2;
        float ty = x2;

        x2 = (x2+tx*tFactor)*radFactor;
        y2 = (y2+ty*tFactor)*radFactor;
    }
}


void RGDraw::rectMode(int mode) {
    if(mode == CORNER) {
        rectDrawMode = CORNER;
    } else {
        rectDrawMode = CENTER;
    }
}


/*!Builds a sine/cosine table for use for calculating circle vertexes much faster
*/
void RGDraw::circleResolution(int res) {
    int validRes = rgClamp(res, 1, RG_MAX_CIRCLE_PTS); //validate the resolution
    if(validRes != currentCircleRes) {
        float angle = 0.0f;
        float angleAdd = (2*PI) / (float)validRes;
        for(int i=0; i<validRes*2; i+=2){
            circleCalcPts[i] = cos(angle);
            circleCalcPts[i+1] = sin(angle);
            angle += angleAdd;
        }
        currentCircleRes = validRes;
    }
}


/*void RGDraw::beginShape(){
    ofBeginShape();
}
void RGDraw::endShape(){
    ofEndShape();
}
void RGDraw::vertex(int x, int y){
    ofVertex(x,y);
}*/
/*void RGDraw::curveVertex(int x, int y){
    ofCurveVertex(x,y);
}
void RGDraw::bezierVertex(int x1, int y1, int x2, int y2, int x3, int y3){
    ofBezierVertex(x1,y1,x2,y2,x3,y3);
}*/
/*void RGDraw::quadBezVertex(int prevX, int prevY, int x1, int y1, int x2, int y2){
    int lx = prevX +(2.0/3.0)*(x1-prevX);
    int ly = prevY +(2.0/3.0)*(y1-prevY);
    int p2x = lx + (x2-prevX)/3.0;
    int p2y = ly + (y2-prevY)/3.0;

    bezierVertex(lx,ly,p2x,p2y,x2,y2);

}*/


void RGDraw::roundRect(int x, int y, int w, int h, int radius) {
    roundRect(x, y, w, h, radius, 8);
}

//this still needs some tweaking
void RGDraw::roundRect(int x, int y, int w, int h, int radius, int resolution){
    int r;
    //make sure the radius isn:t larger than half of the smallest dimension
    if(h>w && radius > w/2.0)  {
        r = w/2;
    } else if(w>h && radius > h/2.0) {
        r = h/2;
    } else {
        r = radius;
    }
    if(resolution < 2) { resolution = 2; } //make sure resolution is a useful number

    if(fillEna) {
        glBegin(GL_POLYGON);
        glColor4ub(fillColor.r, fillColor.g, fillColor.b, fillColor.a);

        arcVertex(x+r-1, y+r, r, -PI, PI/2, resolution);
        glVertex2f(x+r-1,y);
        glVertex2f(x+w-r,y);

        arcVertex(x+w-r, y+r, r, -PI/2, PI/2, resolution);
        glVertex2f(x+w,y+r);
        glVertex2f(x+w,y+h-r+1);

        arcVertex(x+w-r, y+h-r+1, r, 0, PI/2, resolution);
        glVertex2f(x+r-1,y+h);
        glVertex2f(x+w-r,y+h);

        arcVertex(x+r-1, y+h-r+1, r, PI/2, PI/2, resolution);
        glVertex2f(x,y+r);
        glVertex2f(x,y+h-r+1);

        glEnd();
    }
    if(strokeEna) {
        glBegin(GL_LINE_LOOP);
        glColor4ub(strokeColor.r, strokeColor.g, strokeColor.b, strokeColor.a);

        arcVertex(x+r-1, y+r, r, -PI, PI/2, resolution);
        glVertex2f(x+r-1,y);
        glVertex2f(x+w-r,y);

        arcVertex(x+w-r, y+r, r, -PI/2, PI/2, resolution);
        glVertex2f(x+w,y+r);
        glVertex2f(x+w,y+h-r+1);

        arcVertex(x+w-r, y+h-r+1, r, 0, PI/2, resolution);
        glVertex2f(x+r-1,y+h);
        glVertex2f(x+w-r,y+h);

        arcVertex(x+r-1, y+h-r+1, r, PI/2, PI/2, resolution);
        glVertex2f(x,y+r);
        glVertex2f(x,y+h-r+1);

        glEnd();
    }

}

/*! Color1 at the top and color 2 at the bottom */
void RGDraw::gradientRect(int x, int y, int w, int h, RGColor color1, RGColor color2) {
    gradientRect(x, y,w, h, color1, color2, RG_VERTICAL);
}

/*! Orientation should be RG_HORIZONTAL or RG_VERTICAL. Color1 is on the top if horizontal, and the left if vertical. */
void RGDraw::gradientRect(int x, int y, int w, int h, RGColor color1, RGColor color2, int orientation){
    glBegin(GL_QUADS);

    glColor4ub(color1.r, color1.g, color1.b, color1.a);
    glVertex2f((GLfloat)x,(GLfloat)y);

    if(orientation == RG_VERTICAL) {
        glColor4ub(color1.r, color1.g, color1.b, color1.a);
    } else {
        glColor4ub(color2.r, color2.g, color2.b, color2.a);
    }
    glVertex2f(x+w,y);

    glColor4ub(color2.r, color2.g, color2.b, color2.a);
    glVertex2f((GLfloat)(x+w),(GLfloat)(y+h));

    if(orientation == RG_VERTICAL) {
        glColor4ub(color2.r, color2.g, color2.b, color2.a);
    } else {
        glColor4ub(color1.r, color1.g, color1.b, color1.a);
    }
    glVertex2f((GLfloat)x,(GLfloat)(y+h));

    glEnd();
}

//offset shifts from the upper left corner, steps is how many new lines to draw, spread is their width
/*void RGDraw::rectDropShadow(RGColor startColor, int x, int y, int w, int h,int steps) {
    rectMode(CORNER);
    int spread=1;
    ofNoFill();
    for(int i=0; i<steps; i++) {
        //ofSetColor( (int)((255-startColor.r)/steps)*(i+1),
        //           (int)((255-startColor.g)/steps)*(i+1),
        //           (int)((255-startColor.b)/steps)*(i+1));
        ofSetColor(startColor.r, startColor.g, startColor.b, 255-(int)((255)/steps)*(i+1));
        ofRect(x-i,y-i,w+(i*2*spread),h+(i*2*spread));
        ofLine(x-i, y-i, x-i, y-i+h+(i*2)+1);
    }

}*/



void RGDraw::pushMatrix() {
    glPushMatrix();
}
void RGDraw::popMatrix() {
    glPopMatrix();
}

void RGDraw::translate(int x, int y) {
    glTranslatef((GLfloat)x, (GLfloat)y, 0);
}
void RGDraw::translate(float x, float y) {
    glTranslatef((GLfloat)x, (GLfloat)y, 0);
}
void RGDraw::translate(int x, int y, int z) {
    glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
}
void RGDraw::translate(float x, float y, float z) {
    glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
}

void RGDraw::rotate(float degrees) {
    glRotatef(degrees, 0,0,1);
}


void RGDraw::noStroke() {
    strokeEna = false;
}
void RGDraw::stroke(RGColor newStroke) {
    strokeEna = true;
    strokeColor = newStroke;
}
void RGDraw::stroke(RGColor newStroke, int a) {
    strokeEna = true;
    strokeColor = newStroke;
    strokeColor.a = rgClamp(a,0,255);
}
void RGDraw::stroke(int brightness) {
    strokeEna = true;
    strokeColor.r = rgClamp(brightness,0,255);
    strokeColor.g = rgClamp(brightness,0,255);
    strokeColor.b = rgClamp(brightness,0,255);
    strokeColor.a = 255;
}
void RGDraw::stroke(int brightness, int alpha) {
    strokeEna = true;
    strokeColor.r = rgClamp(brightness,0,255);
    strokeColor.g = rgClamp(brightness,0,255);
    strokeColor.b = rgClamp(brightness,0,255);
    strokeColor.a = rgClamp(alpha,0,255);
}
void RGDraw::stroke(int r, int g, int b) {
    strokeEna = true;
    strokeColor.r = rgClamp(r,0,255);
    strokeColor.g = rgClamp(g,0,255);
    strokeColor.b = rgClamp(b,0,255);
    strokeColor.a = 255;
}
void RGDraw::stroke(int r, int g, int b, int a) {
    strokeEna = true;
    strokeColor.r = rgClamp(r,0,255);
    strokeColor.g = rgClamp(g,0,255);
    strokeColor.b = rgClamp(b,0,255);
    strokeColor.a = rgClamp(a,0,255);
}


void RGDraw::noFill() {
    fillEna = false;
}
void RGDraw::fill(RGColor newFill) {
    fillEna = true;
    fillColor = newFill;
}
void RGDraw::fill(int brightness) {
    fillEna = true;
    fillColor.r = rgClamp(brightness,0,255);
    fillColor.g = rgClamp(brightness,0,255);
    fillColor.b = rgClamp(brightness,0,255);
    fillColor.a = 255;
}
void RGDraw::fill(int brightness, int alpha) {
    fillEna = true;
    fillColor.r = rgClamp(brightness,0,255);
    fillColor.g = rgClamp(brightness,0,255);
    fillColor.b = rgClamp(brightness,0,255);
    fillColor.a = rgClamp(alpha,0,255);
}
void RGDraw::fill(int r, int g, int b) {
    fillEna = true;
    fillColor.r = rgClamp(r,0,255);
    fillColor.g = rgClamp(g,0,255);
    fillColor.b = rgClamp(b,0,255);
    fillColor.a = 255;
}
void RGDraw::fill(int r, int g, int b, int a) {
    fillEna = true;
    fillColor.r = rgClamp(r,0,255);
    fillColor.g = rgClamp(g,0,255);
    fillColor.b = rgClamp(b,0,255);
    fillColor.a = rgClamp(a,0,255);
}



void RGDraw::text(string text, int x, int y) {
    this->text( toWString(text), x,y);
}

/*
note: if you try to draw with no fill color set, but a stroke color set, the function will
assume you want to use your stroke color for the text
*/
void RGDraw::text(wstring text, int x, int y) {
    //fill
    if(fillEna) {
        fill(fillColor);
        if(font.isValid()) {
            font.drawString(text,x,y, fillColor);
        }
    }
    //if a fill color is not set, but stroke is, assume they want to use the stroke color isntead
    if(strokeEna && !fillEna) {
        if(font.isValid()) {
            font.drawString(text,x,y, strokeColor);
        }
    }
}

void RGDraw::textSize(int size) {
    /*if(fonts.count(fontSize)>0) {
    } else {
        fonts[fontSize] = RGTTF();
        fonts[fontSize].loadFont(fontFile, fontSize);
    }*/
    font.setFontSize(size);
}

int RGDraw::textWidth(wstring text) {
    if(font.isValid()) {
        pair<int,int> dims = font.boundingDims(text);
        return dims.first;
        //return fonts2[fontSize].stringWidth(text);
    } else {
        return 0;
    }
}
int RGDraw::textWidth(string text) {
    return textWidth(toWString(text));
}
int RGDraw::textHeight(wstring text) {
    if(font.isValid()) {
        //return fonts2[fontSize].stringHeight(text);
        pair<int,int> dims = font.boundingDims(text);
        return dims.second;
    } else {
        return 0;
    }
}
int RGDraw::textHeight(string text) {
    return textHeight(toWString(text));
}



float RGDraw::map(float value, float inputMin, float inputMax, float outputMin, float outputMax) {
    float output = outputMin;
    if( fabs(inputMin - inputMax) > FLT_EPSILON ) {
        output = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
    }
    return output;
    //return ofMap(value, inputMin, inputMax, outputMin, outputMax);
}




float rgMap(float value, float inputMin, float inputMax, float outputMin, float outputMax) {
    float output = outputMin;
    if( fabs(inputMin - inputMax) > FLT_EPSILON ) {
        output = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
    }
    return output;
    //return ofMap(value, inputMin, inputMax, outputMin, outputMax);
}
int rgMin(int a, int b) {
    return (((a) < (b)) ? (a) : (b));
}
float rgMin(float a, float b) {
    return (((a) < (b)) ? (a) : (b));
}
int rgMax(int a, int b) {
    return (((a) > (b)) ? (a) : (b));
}
float rgMax(float a, float b) {
    return (((a) > (b)) ? (a) : (b));
}

int rgClamp(int input, int min, int max){
    return rgMax(rgMin(input, max), min);
}
float rgClamp(float input, float min, float max){
    return rgMax(rgMin(input, max), min);
}

string toString(int input){
    stringstream stream;
    stream << input;
    return stream.str();
}

string toString(float input, int precision){
    stringstream stream;
    stream << fixed << setprecision(precision) << input;
    return stream.str();
}
string toString(float input){
    return toString(input, 2);
}


wstring toWString(string text) {
    std::wstring temp(text.length(), L' ');
    std::copy(text.begin(), text.end(), temp.begin());
    return temp;
}