#include "UIBasicApp1.hpp"

void UIBasicApp1::setup(){

    root = new RGRoot(1024,768, this);

	auto testButton = new RGButton("test", 50,50,80,30,L"テスト123");

    testButton->setEventHandler(new ButtonEvent(root));
    root->addChild(testButton);


    auto label1 = new RGLabel("some_label", 300, 300, 100, 30);
    root->addChild(label1);

    auto frame1 = new RGFrame("frame1", 360,20, 200,200, "Rocket Control");
    root->addChild(frame1);

    RGRadioGroup* togGrp2 = new RGRadioGroup("thruster_dir", 10,10, 70,90, "RadioGroup");
    togGrp2->addItem("tog_a1", "Forward");
    togGrp2->addItem("tog_a2", "Backward");
    togGrp2->addItem("tog_a3", "Explode");
    root->addChild(frame1);



    RGList* list1 = new RGList("list1", 300,500,90,200);
    root->addChild(list1);

    RGSlider* slider1 = new RGSlider("slider1", 5,5,80,30, "GraphW", 0, 100);
    //crap1->setEventHandler(new TestSlideEvent(root));
    RGSlider* slider2 = new RGSlider("slider2", 5,40,80,30, "Y Stress", -1, 1);
    RGSlider* slider3 = new RGSlider("slider3", 0,0,80,30, "Z Stress", -500, 400);
    list1->addChild(slider1);
    list1->addChild(slider2);
    list1->addChild(slider3);


    RGRadioGroup* togGrp1 = new RGRadioGroup("togglegroup1", 500,300, 70,90, "RadioGroup");
    togGrp1->addItem("tog_a1", "Test1");
    togGrp1->addItem("tog_a2", "Test2");
    togGrp1->addItem("tog_a3", "Test3");
    root->addChild(togGrp1);

    RGCheckGroup* chkGrp1 = new RGCheckGroup("checkgroup1", 600,300, 70,90, "CheckGroup");
    chkGrp1->addItem("tog_b1", "Test1");
    chkGrp1->addItem("tog_b2", "Test2");
    chkGrp1->addItem("tog_b3", "Test3");
    root->addChild(chkGrp1);
    //RGToggle* check1 = new RGToggle("tog1", 10,10, 60,11, "Thrusters");
    //frame1->addChild(check1);


}


void ButtonEvent::released() {
    RGButton* target2 = (RGButton*)rootObject->findChildByName("test");
    if(target2 != nullptr) {
        if (target2->pressedColor.r() == 128) {
            target2->pressedColor = ColorRGBA(9);

        } else {
            target2->pressedColor = ColorRGBA(128);
        }
        cout << "ButtonEvent:release\n";
    }
}
ButtonEvent::ButtonEvent(RGRoot* root) : RGEventHandlerBase(root) { }


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

void UIBasicApp1::mouseDragged(unsigned int x, unsigned int y, MouseButton button){
    //rgMain1->event(DRAGGED, x,y);
    root->dragEvent(x,y, button);
}


void UIBasicApp1::mousePressed(unsigned int x, unsigned int y, MouseButton button){
    //rgMain1->event(PRESSED, x,y);
    root->pressEvent(x,y);
}


void UIBasicApp1::mouseReleased(unsigned int x, unsigned int y, MouseButton button){
    //rgMain1->event(RELEASED, x,y);
    root->releaseEvent(x,y);
}



void UIBasicApp1::windowResized(unsigned int w, unsigned int h){
    //UIBasicApp1->resizeEvent(w, h);
}

