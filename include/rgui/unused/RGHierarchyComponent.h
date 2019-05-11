#pragma once
#include "RGRect.h"
#include "RGDrawableRect.h"

class RGHierarchyComponent : public RGDrawableRect {
public:
	RGHierarchyComponent(int x, int y, int w, int h);
	virtual void printLeaves() = 0;
	void setParent(RGHierarchyComponent* newParent);
	
	
	//virtual void draw(){};

	virtual unsigned int getChildrenCount() {return 0;};

protected:
	RGHierarchyComponent* parent;
};