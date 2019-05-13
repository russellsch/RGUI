#include "rgui.hpp"


class UIBasicApp1 : public RGApp{
    RGRoot* root;

	public:
		void setup() override;
		void draw() override;

		void keyPressed  (int key) override;
		void keyReleased(int key) override;
		void mouseMoved(unsigned int x, unsigned int y ) override;
		void mouseDragged(unsigned int x, unsigned int y, int button) override;
		void mousePressed(unsigned int x, unsigned int y, int button) override;
		void mouseReleased(unsigned int x, unsigned int y, int button) override;
		void windowResized(unsigned int w, unsigned h) override;

};

class ButtonEvent : public RGEventHandlerBase {
    public:
        ButtonEvent(RGRoot* root);
        void released();
};
