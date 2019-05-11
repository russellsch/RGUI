#pragma once

#include "RGVisitorBase.h"
#include "RGDrawInterface.h"
#include "RGDrawableRect.h"
#include "RGHierarchyComposite.h"


class RGDrawVisitor: public RGVisitorBase {
public:
	RGDrawVisitor(RGDrawInterface* drawInterface);
	bool visit(RGHierarchyComposite* composite);

	//bool visitEnter(RGHierarchyComposite* composite);
	//bool visitLeave(RGHierarchyComposite* composite);

private:
	RGDrawInterface* drawInterface;

};


