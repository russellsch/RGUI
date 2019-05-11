#include "RGDrawImplementationOpengl.h"

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


RGDrawImplementationOpengl::RGDrawImplementationOpengl(){
	fillEnable = true;
	strokeEnable = true;
}


void RGDrawImplementationOpengl::noStroke() {
	strokeEnable = false;
}

void RGDrawImplementationOpengl::stroke(int r, int g, int b, int a){
	strokeEnable = true;
	strokeColor.r = r;
	strokeColor.g = g;
	strokeColor.b = b;
	strokeColor.a = a;
}

void RGDrawImplementationOpengl::noFill() {
	fillEnable = false;
}
void RGDrawImplementationOpengl::fill(int r, int g, int b, int a){
	fillEnable = true;
	fillColor.r = r;
	fillColor.g = g;
	fillColor.b = b;
	fillColor.a = a;
}


void RGDrawImplementationOpengl::pushMatrix() {
    glPushMatrix();
}
void RGDrawImplementationOpengl::popMatrix() {
    glPopMatrix();
}

void translate(float x, float y){
	glTranslatef((GLfloat)x, (GLfloat)y, 0);
}
void translate(float x, float y, float z){
	glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
}