#include "RGHierarchyComponent.h"

RGHierarchyComponent::RGHierarchyComponent(int x, int y, int w, int h): RGDrawableRect(x,y,w,h){
	parent = NULL;
}

void RGHierarchyComponent::setParent(RGHierarchyComponent* newParent){
	parent = newParent;
}