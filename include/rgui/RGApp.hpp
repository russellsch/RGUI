#ifndef RGAPP_H
#define RGAPP_H



//#include "ofBaseApp.h"
//#include "ofAppGlutWindow.h"
//#include "ofAppRunner.h"
#include "RGRoot.hpp"
#include "GL/glew.h"
#include "windows.h"
#include "math.h"

#include "RGOSWindow.hpp"





static HHOOK rGMouseHook;

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

        //ofAppGlutWindow window;
};

static RGApp* appPointer;

static LRESULT CALLBACK mouseCallback( int code, WPARAM wparam, LPARAM lparam);




/*class RGofWrapper : public ofBaseApp{
	public:
        RGofWrapper();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

};
*/

#endif // RGAPP_H
