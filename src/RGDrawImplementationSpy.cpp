#include "RGDrawImplementationSpy.h"


RGDrawImplementationSpy::RGDrawImplementationSpy() {
	stringLog.push_back(string("rgdrawimplementationspy"));
}


void RGDrawImplementationSpy::noStroke(){
	stringLog.push_back(string("nostroke"));
}
void RGDrawImplementationSpy::stroke(int r, int g, int b, int a){
	stringstream ss;
	ss << "stroke:" << r << "," << g << "," << b << "," << a; 
	stringLog.push_back(ss.str());
}
void RGDrawImplementationSpy::noFill(){
	stringLog.push_back(string("nofill"));
}
void RGDrawImplementationSpy::fill(int r, int g, int b, int a){
	stringstream ss;
	ss << "fill:" << r << "," << g << "," << b << "," << a; 
	stringLog.push_back(ss.str());
}


void RGDrawImplementationSpy::line(int x1, int y1, int x2, int y2){
	stringstream ss;
	ss << "line:" << x1 << "," << y1 << "," << x2 << "," << y2; 
	stringLog.push_back(ss.str());
}
void RGDrawImplementationSpy::rect(int x1, int y1, int w, int h){
	stringstream ss;
	ss << "rect:" << x1 << "," << y1 << "," << w << "," << h; 
	stringLog.push_back(ss.str());
}
void RGDrawImplementationSpy::circle(float x1, float y1, float radius){
	stringstream ss;
	ss << "circle:" << x1 << "," << y1 << "," << radius; 
	stringLog.push_back(ss.str());
}
void RGDrawImplementationSpy::circle(float x1, float y1, float radius, int res){
	stringstream ss;
	ss << "circle:" << x1 << "," << y1 << "," << radius << "," << res; 
	stringLog.push_back(ss.str());
}


void RGDrawImplementationSpy::pushMatrix(){
	stringLog.push_back(string("pushmatrix"));
}
void RGDrawImplementationSpy::popMatrix(){
	stringLog.push_back(string("popmatrix"));
}

void RGDrawImplementationSpy::translate(float x, float y){
	stringstream ss;
	ss << "translate:" << x << "," << y; 
	stringLog.push_back(ss.str());
}
void RGDrawImplementationSpy::translate(float x, float y, float z){
	stringstream ss;
	ss.precision(2);
	ss << "translate:" << fixed << x << "," << y << "," << z; 
	stringLog.push_back(ss.str());
}



unsigned int RGDrawImplementationSpy::getLogSize(){
	return stringLog.size();
}
string RGDrawImplementationSpy::getLogItemString(unsigned int index){
	return stringLog.at(index);
}
void RGDrawImplementationSpy::clearLog(){
	stringLog.clear();
}