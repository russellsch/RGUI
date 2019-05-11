#pragma once
#include <vector>
#include "RGHierarchyComponent.h"

using namespace std;

class RGDrawVisitor;
class RGDrawInterface;

class RGHierarchyComposite : public RGHierarchyComponent {
public:
	RGHierarchyComposite(int x, int y, int w, int h);
	void addChild( RGHierarchyComponent* newChildPointer );
	void printLeaves();
	unsigned int getChildrenCount();
	RGHierarchyComponent* getChild(unsigned int index);


	bool acceptDrawVisitor( RGDrawVisitor* visitor );

	//virtual void drawBackground(RGDrawInterface* d)=0;	//!<Drawn before children are drawn
	//virtual void drawForeground(RGDrawInterface* d)=0;	//!<Drawn after children are drawn

protected:
	vector<RGHierarchyComponent*> children;

};