#include "UIBasicApp1.hpp"

void UIBasicApp1::setup(){

    root = new RGRoot(1024,768, this);

	RGButton* testButton = new RGButton("test", 50,50,70,30,L"テスト");

    testButton->setEventHandler(new ButtonEvent(root));
    root->addChild(testButton);


    RGFrame* frame1 = new RGFrame("frame1", 360,20, 200,200, "Rocket Control");
    root->addChild(frame1);

    //RGToggle* check1 = new RGToggle("tog1", 10,10, 60,11, "Thrusters");
    //frame1->addChild(check1);


}


void ButtonEvent::released() {
    RGButton* target2 = (RGButton*)rootObject->findChildByName("test");
    if(target2->pressedColor.r() == 128) {
        target2->pressedColor = ColorRGBA(9);

    } else {
        target2->pressedColor = ColorRGBA(128);
    }
    cout << "ButtonEvent:release\n";

}
ButtonEvent::ButtonEvent(RGRoot* root) : RGEvent(root) { }


void UIBasicApp1::draw(){
    root->render(0,0);

    auto d = root->draw;

    d->line(200,200, 300, 300);
    //cout << "draw\n";
}


void UIBasicApp1::keyPressed(int key){

}


void UIBasicApp1::keyReleased(int key){
    //cout << "framerate: " << ofGetFrameRate() << endl;
    //cout << "mouse: " << mouseX << "," << mouseY << endl;
}


void UIBasicApp1::mouseMoved(unsigned int x, unsigned int y ){

}

void UIBasicApp1::mouseDragged(unsigned int x, unsigned int y, int button){
    //rgMain1->event(DRAGGED, x,y);
    root->dragEvent(x,y, button);
}


void UIBasicApp1::mousePressed(unsigned int x, unsigned int y, int button){
    //rgMain1->event(PRESSED, x,y);
    root->pressEvent(x,y);
}


void UIBasicApp1::mouseReleased(unsigned int x, unsigned int y, int button){
    //rgMain1->event(RELEASED, x,y);
    root->releaseEvent(x,y);
}



void UIBasicApp1::windowResized(unsigned int w, unsigned int h){
    //UIBasicApp1->resizeEvent(w, h);
}

