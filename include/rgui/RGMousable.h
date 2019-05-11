#pragma once

#include "RGDrawableRect.h"

//CAN THESE BE TURNED INTO A VISITOR/ITTERATOR SORT OF THING?
//That operates on the composite... seperating the operation from the hierarchy would 
//be a good thing


//!Adds mouse command handling function to a hierarchy-aware, drawable, rectangle
/*!
Adds mouse command handling function to a hierarchy-aware, drawable, rectangle. Command is
processed by a state machine which may create a new command to be passed to children. How the
children respons to this command can also change the state.
*/


//!Represents a mouse event and a position as a command for RGMousable objects
/*!Commands are meant to be an abstraction of what is happening with the mouse.
Classes above should encapsulate dragging behavior.
For a click and drag the following commands should be sent:
MouseButtonPressed, MouseMoved&MouseDragged, MouseMoved&MouseDragged, MouseButtonReleased
*/
/*
class MouseCommand {
public:
    static enum MouseEvent {
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
		MouseDragged,
		MouseWheelUp,
		MouseWheelDown
    };
	MouseEvent mouseEvent;
	int mousePosX;
	int mousePosY;
	int mouseButton; //!< 1-Left, 2-Right, 3-Center, 0-none

	MouseCommand(MouseCommand::MouseEvent newEvent, int mouseButton, int mousePosX, int mousePosY){
		this->mouseEvent = newEvent;
		mouseButton = mouseButton;
		mousePosX = mousePosX;
		mousePosY = mousePosY;
	}
};

enum MouseCommandResponse {
	CommandNotAccepted,		//Will check others on same level of hierarchy
	CommandAccepted,
	CommandDelegated,
	CommandBlackhole		//Prevents otheres from being checked on this level of hierarchy
};


class RGMousable : protected RGCompositeDrawableRect  {
public:
	MouseCommandResponse processMouseCommand(MouseCommand command);
	RGMousable(int x, int y, int w, int h);

	MouseCommand mouseCommandRelativeToChild(MouseCommand command, int childIndex);

	int getDragStartXRel2Self();
	int getDragStartYRel2Self();

	RGMousable* getChild(unsigned int index);

private:
	RGMousable* dragOriginObjectPointer;
	int dragMouseButton;
	int dragOriginX;
	int dragOriginY;
	bool initialDragFlag;	//!<set low after first drag event is received
	bool draggingNow;		//!<set high when dragging

};


*/