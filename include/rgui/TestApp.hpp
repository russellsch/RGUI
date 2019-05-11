#ifndef _TEST_APP
#define _TEST_APP


#include "RGApp.hpp"

#include "RGRoot.hpp"
#include "RGButton.hpp"
#include "RGSlider.hpp"
#include "RGList.hpp"
#include "RGFrame.hpp"
#include "RGToggle.hpp"
#include "RGRadioGroup.hpp"
#include "RGCheckGroup.hpp"
#include "RGGraph.hpp"

#ifdef TARGET_WIN32_VC
    #include "direct.h"
    #define getcwd _getcwd
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#else
    #include "unistd.h"
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

class DLLHELPER TestApp : public RGApp{
    RGRoot* root;

	public:
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


class TestButtonEvent : public RGEvent {
    public:
        TestButtonEvent(RGRoot* rootNew);
        void clicked();
};

class TestSlideEvent : public RGEvent {
    public:
        TestSlideEvent(RGRoot* rootNew);
        void changed();
};




#endif
