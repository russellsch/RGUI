#include "TestApp.hpp"






//--------------------------------------------------------------
void TestApp::setup(){

    root = new RGRoot(windowW,windowH, this);

    RGButton* testButton = new RGButton("test", 50,50,70,30,L"Test");
    testButton->setEventHandler(new TestButtonEvent(root));
    root->addChild(testButton);
    RGButton* testButton2 = new RGButton("llamas", 200,50,80,30,L"Llamas");
    testButton2->setStyle(1);
    root->addChild(testButton2);
    root->addChild(new RGSlider("slide1", 200,100,30,80, "eels"));

    RGFrame* frame1 = new RGFrame("frame1", 360,20, 200,200, "Test Frame");
    root->addChild(frame1);

    RGList* list1 = new RGList("list1", 300,300,90,200);

    RGSlider* crap1 = new RGSlider("crapslide1", 5,5,80,30, "GraphW");
    crap1->setEventHandler(new TestSlideEvent(root));
    RGSlider* crap2 = new RGSlider("crapslide2", 5,40,80,30, "Y Stress");
    RGSlider* crap3 = new RGSlider("crapslide3", 0,0,80,30, "Z Stress");
    RGFrame* frame2 = new RGFrame("frameitem", 0,0, 60,30);
    list1->addChild(crap1);
    list1->addChild(crap2);
    list1->addChild(frame2);

    root->addChild(list1);

    RGToggle* check1 = new RGToggle("tog1", 20,200, 60,11, "BEANS!!");
    root->addChild(check1);

    RGRadioGroup* togGrp1 = new RGRadioGroup("togglegroup1", 20,300, 70,90, "Pandas");
    togGrp1->addItem("tog_a1", "Test1");
    togGrp1->addItem("tog_a2", "Test2");
    togGrp1->addItem("tog_a3", "Test3");
    root->addChild(togGrp1);

    RGCheckGroup* chkGrp1 = new RGCheckGroup("checkgroup1", 100,300, 70,90, "Goats");
    chkGrp1->addItem("tog_b1", "Test1");
    chkGrp1->addItem("tog_b2", "Test2");
    chkGrp1->addItem("tog_b3", "Test3");
    root->addChild(chkGrp1);

    RGCheckGroup* chkGrp2 = new RGCheckGroup("checkgroup2", 100,400, 180,40, "Goats2");
    chkGrp2->setHorizontalPacking();
    chkGrp2->addItem("tog_c1", "Test1");
    chkGrp2->addItem("tog_c2", "Test2");
    chkGrp2->addItem("tog_c3", "Test3");
    root->addChild(chkGrp2);

    RGGraph* graph1 = new RGGraph("graph1", 450,300, 460,400);
    //RGLineGraph* graph2 = new RGLineGraph("graph2", 700,300, 200,200);
    int testPoints = 8000;
    vector<float> data, data2, data3;
    float angleDif = PI/400;
    float angleDif2 = PI/200;
    for(int i=0; i<testPoints; i++){
        data.push_back( sin(angleDif*(float)i)*10 );
        data2.push_back( sin(angleDif2*(float)i)*5 );
        data3.push_back( sin(angleDif2*2*(float)i)*3 + sin(angleDif*2*(float)i)*5 );
    }
    graph1->setMinMax(0,9000,-15,15);
    graph1->load1DLineFromFloat(&data[0], testPoints);
    graph1->load1DLineFromFloat(&data2[0], testPoints);
    graph1->load1DLineFromFloat(&data3[0], testPoints);
    //graph2->load1DLineFromFloat(&data[0], testPoints);
    //graph1->loadLineFromFloat(&data2[0], 200);
    root->addChild(graph1);
    //rgMain->addChild(graph2);

    //rectangle intersection test
    RGRect* r1 = new RGRect(1,0, 1,1, RG_TL);
    RGRect* r2 = new RGRect(0,1, 1,1, RG_TL);
    RGRect r3 = r1->getIntersection(r2);
    cout << "RECT TEST R3:" << r3 << endl;

}


void TestButtonEvent::clicked() {

    RGSlider* target = (RGSlider*)rootObject->findChildByName("slide1");

    cout << "Press Event";
    if(target->bkgColor.r==255) {
        target->bkgColor.r = 0;

    } else {
        target->bkgColor.r = 255;
    }
    target->resizable = true;
    target->anchorX=1;

    RGButton* target2 = (RGButton*)rootObject->findChildByName("llamas");
    if(target2->getStyle()==0) {
        target2->setStyle(1);

    } else {
        target2->setStyle(0);
    }

    cout << "TIMER: " << (int)rootObject->getTimeMs() << endl;
    //cout << "INDEX: " << ((RGRadioGroup*)rgMain->findChildByName("togglegroup1"))->getActiveIndex();

}
TestButtonEvent::TestButtonEvent(RGRoot* rootNew) : RGEvent(rootNew) {

}



void TestSlideEvent::changed() {
    RGSlider* target = (RGSlider*)rootObject->findChildByName("crapslide1");
    //rgMain->findChildByName("graph1")->setW( ((RGSlider*)rgMain->findChildByName("crapslide1"))->getValue() );
    rootObject->findChildByName("graph1")->setW( target->getValue() );
}
TestSlideEvent::TestSlideEvent(RGRoot* root) : RGEvent(root) {  }



void TestApp::update(){

}






void TestApp::draw(){
    root->render(0,0);
    root->draw->textSize(50);
    root->draw->text("abcdefghijklmnopqrstuvwxyz", 100,100);
    root->draw->textSize(25);
    root->draw->text("abcdefghijklmnopqrstuvwxyz", 100,200);
    root->draw->textSize(15);
}


void TestApp::keyPressed(int key){

}


void TestApp::keyReleased(int key){
    //cout << "framerate: " << ofGetFrameRate() << endl;
    //cout << "mouse: " << mouseX << "," << mouseY << endl;
}


void TestApp::mouseMoved(int x, int y ){

}

void TestApp::mouseDragged(int x, int y, int button){
    //rgMain1->event(DRAGGED, x,y);
    root->dragEvent(x,y, button);
}


void TestApp::mousePressed(int x, int y, int button){
    //rgMain1->event(PRESSED, x,y);
    root->pressEvent(x,y);
}


void TestApp::mouseReleased(int x, int y, int button){
    //rgMain1->event(RELEASED, x,y);
    root->releaseEvent(x,y);
}



void TestApp::windowResized(int w, int h){
    root->resizeEvent(w, h);
}



/*
BOOST_PYTHON_MODULE(rgui_ext) {
	using namespace boost::python;
	class_<TestApp>("TestApp")
		.def("runApp", &TestApp::runApp)
	;

}*/

