#include "RGGLFWWindow.hpp"
#include "GL/glfw.h"

//global variable hack to bridge between member functions of RGGLFWWindow and GLFW callbacks
queue<RGInputEvent> GLFWInputEvents;

void GLFWCALL GLFWBridgeMouseButtonCallback(int button, int action) {
    RGInputEvent newEvent;
    newEvent.type = (action==GLFW_PRESS ? RGInputEvent::MouseButtonPressed : RGInputEvent::MouseButtonReleased);
    if(button == GLFW_MOUSE_BUTTON_LEFT) { newEvent.mouseButton.button = 1; }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT) { newEvent.mouseButton.button = 2; }
    else if(button == GLFW_MOUSE_BUTTON_MIDDLE) { newEvent.mouseButton.button = 3; }

    int mouseX, mouseY;
    glfwGetMousePos(&mouseX, &mouseY);
    newEvent.mouseButton.x = mouseX;
    newEvent.mouseButton.y = mouseY;

    GLFWInputEvents.push(newEvent);
}

void GLFWCALL GLFWBridgeMousePosCallback(int x, int y) {
    RGInputEvent newEvent;
    newEvent.type = RGInputEvent::MouseMoved;
    newEvent.mouseButton.x = x;
    newEvent.mouseButton.y = y;
    GLFWInputEvents.push(newEvent);
}



void RGGLFWWindow::init() {
    glfwInit();

}


void RGGLFWWindow::openWindow(unsigned int width, unsigned int height, bool fullscreen, string title) {
    glfwOpenWindow(width, height,
                   0, 0, 0,
                   0, 0, 0,
                   (fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW));
    windowW = width;
    windowH = height;

    glfwSetMouseButtonCallback(&GLFWBridgeMouseButtonCallback);
    glfwSetMousePosCallback(&GLFWBridgeMousePosCallback);
}

bool RGGLFWWindow::isOpen() {
	return (glfwGetWindowParam( GLFW_OPENED ) > 0? true: false);
}


void RGGLFWWindow::display() {
    glfwSwapBuffers();
}

//This is really not a very graceful solution here
bool RGGLFWWindow::getEvent(RGInputEvent& event) {
    if(GLFWInputEvents.size()> 0) {
        event = GLFWInputEvents.front();
        GLFWInputEvents.pop();
        return true;
    }
    return false;
}


void RGGLFWWindow::close(){
    glfwTerminate();

}








