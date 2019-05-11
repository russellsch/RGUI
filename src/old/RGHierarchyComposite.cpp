#include "RGHierarchyComposite.h"
#include "RGDrawVisitor.h"


RGHierarchyComposite::RGHierarchyComposite(int x, int y, int w, int h):RGHierarchyComponent(x,y,w,h){

}

void RGHierarchyComposite::addChild( RGHierarchyComponent* newChildPointer ) {
	children.push_back( newChildPointer );
}
void RGHierarchyComposite::printLeaves() {
	for(unsigned int i=0; i < children.size(); i++) {
		children[i]->printLeaves();
	}
}

unsigned int RGHierarchyComposite::getChildrenCount(){
	return children.size();
}

RGHierarchyComponent* RGHierarchyComposite::getChild(unsigned int index){
	return children.at(index);
}


bool RGHierarchyComposite::acceptDrawVisitor( RGDrawVisitor* visitor ){
	return visitor->visit(this);
}