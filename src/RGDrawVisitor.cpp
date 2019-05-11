#include "RGDrawVisitor.h"






/*void RGDrawer::draw(RGHierarchyComposite* drawee){
	//RGDrawVisitor* visitor = new RGDrawVisitor(drawInterface);

	//itterate composite structure... depth first

	//drawee->acceptDrawVisitor(visitor);

	//delete visitor;

}*/







RGDrawVisitor::RGDrawVisitor(RGDrawInterface* drawInterface){
	drawInterface = drawInterface;
}


/*void RGDrawVisitor::visit(RGDrawableRect* drawee) {
	drawee->drawBackground();

}*/

bool RGDrawVisitor::visit(RGHierarchyComposite* composite){
	drawInterface->pushMatrix();	//push
	drawInterface->translate(composite->getL(), composite->getT());//translate this object's offset from parent

	composite->drawBackground(drawInterface);

	//traverse children... replace this with a children itterator?? so we aren't tied to internal funcitons of
	//composite
	for(unsigned int i=0; i < composite->getChildrenCount(); i++) {
		((RGHierarchyComposite*)composite->getChild(i))->acceptDrawVisitor(this);
	}
	composite->drawForeground(drawInterface);

	drawInterface->popMatrix();	//pop

	return true; //always traverse entire depth
}
/*bool RGDrawVisitor::visitLeave(RGHierarchyComposite* composite){
	composite->drawForeground(drawInterface);
	return true;
}*/

