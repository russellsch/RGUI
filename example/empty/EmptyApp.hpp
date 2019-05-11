#pragma once
#include "rgui.hpp"


class EmptyApp : public RGApp{
    RGRoot* root;

	public:
		void setup();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

};

class ButtonEvent : public RGEvent {
    public:
        ButtonEvent(RGRoot* root);
        void released();
};
