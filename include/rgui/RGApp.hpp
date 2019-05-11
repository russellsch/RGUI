#ifndef RGAPP_H
#define RGAPP_H



#include "RGRoot.hpp"
#include "math.h"
#include "RGOSWindow.hpp"




using namespace std;
//!Subclass this to make your application, encapsulates windowing functionality and input
/*!
Todo:
Add timing functionality so a framerate can be returned
Add functionality to skip draw if it's faster than the desired framerate
Add options to limit both draw and update to the desired framerate

Can the draw object and root object be encapsulated in this?

*/
class DLLHELPER RGApp{
    public:
        RGApp();
        virtual ~RGApp();

        int mouseX, mouseY;


		virtual void setup(){}
		virtual void update(){}
		virtual void draw(){}
		virtual void exit(){}


		virtual void windowResized(int w, int h){}

		virtual void keyPressed( int key ){}
		virtual void keyReleased( int key ){}

		virtual void mouseMoved( int x, int y ){}
		virtual void mouseDragged( int x, int y, int button ){}
		virtual void mousePressed( int x, int y, int button ){}
		virtual void mouseReleased(){}
		virtual void mouseReleased(int x, int y, int button ){}


        void runApp(int w, int h);
        int getWindowW();
        int getWindowH();

        void setTitleBar(string newTitleBar);

    protected:
        void setupGLView();

        void processEvents();

        int windowW, windowH;
        string titleBar;

        RGOSWindow* window;

    private:
        bool mouseIsPressed;    //used to detect dragging
        int mousePressedButton;     //1-left, 2-right, 3-middle


};

static RGApp* appPointer;





#endif // RGAPP_H
