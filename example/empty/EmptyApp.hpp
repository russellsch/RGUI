#pragma once
#include "rgui.hpp"


class EmptyApp : public RGApp{
    RGRoot* root;

	public:
		void setup() override;
		void draw() override;

		void keyPressed (int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void windowResized(int w, int h) override;

};

class ButtonEvent : public RGEvent {
    public:
        ButtonEvent(RGRoot* root);
        void released();
};
