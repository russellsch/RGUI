#pragma once
#include <string>
#include <sstream>
#include <vector>

#include "RGDrawImplementation.h"


//!Record method calls coming into a drawing interface
/*!
Replaces a real drawing implementation, used to spy on calls 
coming out of the drawing interface. Logs calls to a vector and spits them out
when required.

Useful for unit testing things, not meant for use in production.
*/
using namespace std;

class RGDrawImplementationSpy: public RGDrawImplementation {
public:
	RGDrawImplementationSpy();

	void noStroke();
	void stroke(int r, int g, int b, int a);

	void noFill();
	void fill(int r, int g, int b, int a);

    void line(int x1, int y1, int x2, int y2);
    void rect(int x1, int y1, int w, int h);
    void circle(float x1, float y1, float radius);
    void circle(float x1, float y1, float radius, int res);


	void pushMatrix();
    void popMatrix();

	void translate(float x, float y);
    void translate(float x, float y, float z);





	unsigned int getLogSize();
	string getLogItemString(unsigned int index);
	void clearLog();
private:
	vector<string> stringLog;
	//some sort of log
};