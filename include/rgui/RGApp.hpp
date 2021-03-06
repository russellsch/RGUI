#ifndef RGAPP_H
#define RGAPP_H



#include "RGRoot.hpp"
#include "math.h"
#include "RGOSWindow.hpp"
#include "RGConst.hpp"
#include "RGShader.hpp"


using namespace std;
//!Subclass this to make your application, encapsulates windowing functionality and input
/*!
Todo:
Add timing functionality so a framerate can be returned
Add functionality to skip draw if it's faster than the desired framerate
Add options to limit both draw and update to the desired framerate

Can the draw object and root object be encapsulated in this?

*/
class RGApp{
    public:
        RGApp();
        virtual ~RGApp();

        int mouseX, mouseY;


		virtual void onSetup(){}
		virtual void onUpdate(){}
		virtual void onDraw(){}
		virtual void onExit(){}


		virtual void windowResized(unsigned int w, unsigned int h){}

		virtual void keyPressed( int key ){}
		virtual void keyReleased( int key ){}

		virtual void mouseMoved( unsigned int x, unsigned int y ){}
		virtual void mouseDragged( unsigned int x, unsigned int y, MouseButton button ){}
		virtual void mousePressed( unsigned int x, unsigned int y, MouseButton button ){}
		virtual void mouseReleased(){}
		virtual void mouseReleased(unsigned int x, unsigned int y, MouseButton button ){}


        void runApp(unsigned int w, unsigned int h);
        unsigned int getWindowW() { return windowW;}
        unsigned int getWindowH() { return windowH;}

        void setTitleBar(string newTitleBar) { this->title = newTitleBar; };

        RGShader* sp;

    protected:
        void setupGLView();

        void processEvents(RGOSWindow& aWindow);

        unsigned int windowW, windowH;
        string title;

        RGOSWindow* window;



    private:
        bool mouseIsPressed;    //used to detect dragging
        MouseButton mousePressedButton;     //1-left, 2-right, 3-middle


};







#endif // RGAPP_H
