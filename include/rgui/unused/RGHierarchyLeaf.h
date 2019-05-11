#pragma once
#include "RGHierarchyComponent.h"

class RGHierarchyLeaf : public RGHierarchyComponent {
public:
	void printLeaves();

	unsigned int getChildrenCount();

	virtual void draw();
};