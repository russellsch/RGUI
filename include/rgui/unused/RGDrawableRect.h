#pragma once

#include "RGRect.h"
//#include "RGDrawVisitor.h"

class RGDrawInterface;

//!Provides drawing functionality to a rectangle
/*!

*/
class RGDrawableRect: public RGRect {
public:
	RGDrawableRect(int x, int y, int w, int h);

    //int getChildXRel2Self(unsigned int childIndex);	//!<X distance between this object's origin and child's origin
    //int getChildYRel2Self(unsigned int childIndex);	//!<Y distance between this object's origin and child's origin

	virtual void drawBackground(RGDrawInterface* d){};	//!<Drawn before children are drawn
	virtual void drawForeground(RGDrawInterface* d){};	//!<Drawn after children are drawn

private:


};