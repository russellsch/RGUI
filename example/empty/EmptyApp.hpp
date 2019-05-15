#pragma once
#include "rgui.hpp"


class EmptyApp : public RGApp{
    RGRoot* root;

	public:
		void onSetup() override;
		void onDraw() override;

		void keyPressed (int key) override;
		void keyReleased(int key) override;
		void mouseMoved(unsigned int x, unsigned int y ) override;
		void mouseDragged(unsigned int x, unsigned int y, MouseButton button) override;
		void mousePressed(unsigned int x, unsigned int y, MouseButton button) override;
		void mouseReleased(unsigned int x, unsigned int y, MouseButton button) override;
		void windowResized(unsigned int w, unsigned int h) override;

};

class ButtonEvent : public RGEventHandlerBase {
    public:
        ButtonEvent(RGRoot* root);
        void released();
};
