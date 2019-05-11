#include "RGMousable.h"

/*
RGMousable::RGMousable(int x, int y, int w, int h) : RGCompositeDrawableRect(x,y,w,h){
	dragOriginObjectPointer = NULL;
	draggingNow = false;
	initialDragFlag = true;
}
*/

/*! Command mouse position should be relative to this object's origin
The response only really matter for click and dragging behavior

TODO: refactor this to be easier to read and less hideous... and more testable
This is a goddamn monster. Triple state machines? something...
*/
/*
MouseCommandResponse RGMousable::processMouseCommand(MouseCommand command){
	//replace with a state machine class??????
	if(command.mouseEvent == MouseCommand::MouseButtonPressed) {
		for(unsigned int i=0; i<getChildrenCount(); i++) {
			//is the child physically under the mouse pointer?
			if( getChild(i)->intersect((float)command.mousePosX, (float)command.mousePosY) ){	
				//Yes, get it's response to the mouse command, shifting the command position to its origin
				MouseCommandResponse response = getChild(i)->processMouseCommand( mouseCommandRelativeToChild(command, i) );
				if(response != CommandNotAccepted) {
					dragOriginObjectPointer = getChild(i);
					if(response == CommandAccepted) {
						return CommandDelegated;
					} else {
						return response;
					}
				} else {
					//nop, go to next child
				}
			}
		}
		return CommandNotAccepted;
	} else if(command.mouseEvent == MouseCommand::MouseButtonReleased) {
		bool forwardedReleaseCommand = false;
		//notify the dragStartObject that we have been released
		if(dragOriginObjectPointer != NULL) {
			dragOriginObjectPointer->processMouseCommand( 
				MouseCommand( command.mouseEvent, command.mouseButton, 
				command.mousePosX-getDragStartXRel2Self(), command.mousePosY-getDragStartYRel2Self()) );
			forwardedReleaseCommand = true;
		}
		dragOriginObjectPointer = NULL;
		draggingNow = false;
		initialDragFlag = true;
		if(forwardedReleaseCommand) {
			return CommandDelegated;
		} else {
			return CommandAccepted;
		}
	} else if(command.mouseEvent == MouseCommand::MouseDragged) {
		if(draggingNow) {	//forward drag commands to whoever accepted them
			if(initialDragFlag == true) {
				initialDragFlag = false;
			}
			if(dragOriginObjectPointer == NULL) {
				return CommandNotAccepted;
			} else {	//forward the command
				dragOriginObjectPointer->processMouseCommand( 
					MouseCommand( command.mouseEvent, command.mouseButton, 
					command.mousePosX-getDragStartXRel2Self(), command.mousePosY-getDragStartYRel2Self()) );
				return CommandDelegated;
			}
		} else {	//find out of anyone accepts the drag command
			draggingNow = true;
			dragOriginX = command.mousePosX;
			dragOriginY = command.mousePosY;
			for(unsigned int i=0; i<getChildrenCount(); i++) {
				//is the child physically under the mouse pointer?
				if( getChild(i)->intersect((float)command.mousePosX, (float)command.mousePosY) ){	
					MouseCommandResponse response = getChild(i)->processMouseCommand( mouseCommandRelativeToChild(command, i) );
					if(response != CommandNotAccepted) {	//did the child accept the command?
						dragOriginObjectPointer = getChild(i);
						if(response == CommandAccepted) {
							return CommandDelegated;
						}
						return CommandAccepted;
					}
				}
			}
		}

	} else if(command.mouseEvent == MouseCommand::MouseMoved) {
		//!!!!!!!!!!NOTE IMPLEMENTED YET hrmmm
		return CommandNotAccepted;
	}
	return CommandNotAccepted;
}


//NOTE: if we make a 2d vector/point class... this could be replaced with some simple
//shift/translate commands
MouseCommand RGMousable::mouseCommandRelativeToChild(MouseCommand command, int childIndex){
	return MouseCommand(command.mouseEvent, command.mouseButton, 
		command.mousePosX - getChildXRel2Self(childIndex), 
		command.mousePosY - getChildYRel2Self(childIndex) );

}


int RGMousable::getDragStartXRel2Self() {
    return (int)dragOriginObjectPointer->getL();
}
int RGMousable::getDragStartYRel2Self() {
    return (int)dragOriginObjectPointer->getT();
}




///THIS COULD BE BAD!!... maybe we need to implement the hierarchy in a different way?
RGMousable* RGMousable::getChild(unsigned int index){
	return (RGMousable*)children.at(index);
}

*/