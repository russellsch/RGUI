#include "EmptyApp.hpp"

void EmptyApp::setup(){

    root = new RGRoot(1024,768, this);

	RGButton* testButton = new RGButton("test", 50,50,70,30, L"テスト");

    testButton->setEventHandler(new ButtonEvent(root));
    root->addChild(testButton);
    cout << "setup\n";


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
ButtonEvent::ButtonEvent(RGRoot* root) : RGEventBase(root) { }


void EmptyApp::draw(){
    root->render(0,0);
    //cout << "draw\n";
}


void EmptyApp::keyPressed(int key){

}


void EmptyApp::keyReleased(int key){
    //cout << "mouse: " << mouseX << "," << mouseY << endl;
}


void EmptyApp::mouseMoved(unsigned int x, unsigned int y ){

}

void EmptyApp::mouseDragged(unsigned int x, unsigned int y, int button){
    //rgMain1->event(DRAGGED, x,y);
    root->dragEvent(x,y, button);
}


void EmptyApp::mousePressed(unsigned int x, unsigned int y, int button){
    //rgMain1->event(PRESSED, x,y);
    root->pressEvent(x,y);
}


void EmptyApp::mouseReleased(unsigned int x, unsigned int y, int button){
    //rgMain1->event(RELEASED, x,y);
    root->releaseEvent(x,y);
}



void EmptyApp::windowResized(unsigned int w, unsigned int h){
    //rgMain->resizeEvent(w, h);
}

