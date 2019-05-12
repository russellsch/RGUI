#include "rgui/RGApp.hpp"
#include "rgui/RGSDLWindow.hpp"


RGApp::RGApp(){
    appPointer = this;
    mouseIsPressed = false;




}
RGApp::~RGApp() {
    //delete window;
}


void RGApp::runApp(unsigned int w, unsigned int h) {
    windowW = w;
    windowH = h;

	setup();        // Call user's overridden setup function

    window = new RGSDLWindow();
    window->init();
    window->openWindow(w, h, false, title);


	//setup screen
	setupGLView();

    sp = new RGShader("circle.vsh", "circle.fsh");



    bool running = true;

	while(window->isOpen()) {
		processEvents();        //process mouse events and keyboard
		update();               // Call user's overridden update function
		draw();                 // Call user's overridden draw function

		window->display();

	}
	cout << "RGApp Window closed \n";
}

void RGApp::processEvents() {
    RGInputEvent event;

    while (window->getEvent(event)) {
        if(event.type == RGInputEvent::Closed) {
            cout << "RGApp got closed input event \n";
            window->close();
            exit();             //user's custom on-exit code
        }
        if(event.type == RGInputEvent::MouseButtonPressed) {
            mouseIsPressed = true;
            mousePressedButton = event.mouseButton.button;
            mousePressed(event.mouseButton.x, event.mouseButton.y, mousePressedButton);
        }else if(event.type == RGInputEvent::MouseButtonReleased) {
            mouseIsPressed = false;
            mouseReleased(event.mouseButton.x, event.mouseButton.y, mousePressedButton);
        }else if(event.type == RGInputEvent::MouseMoved && mouseIsPressed) {
            mouseDragged(event.mouseMove.x, event.mouseMove.y, mousePressedButton);
        }
        if(event.type == RGInputEvent::Resized) {  //if we resize the window... update the RGApp's window size vars and setup the OpenGL view again
            cout << "resize: " << event.resize.width << " " << event.resize.height <<endl;
            windowW = event.resize.width;
            windowH = event.resize.height;
            windowResized(windowW, windowH);
            setupGLView();
        }

    }
}



void RGApp::setupGLView() {
    cout << "setupGLView ";
	//setup screen
	/*float halfFov, theTan, screenFov, aspect;
	screenFov 		= 60.0f;
	float eyeX 		= (float)windowW / 2.0;
	float eyeY 		= (float)windowH / 2.0;
	halfFov 		= PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;	// near / far clip plane
	float farDist 	= dist * 10.0;
	aspect 			= (float)windowW/(float)windowH;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(screenFov, aspect, nearDist, farDist);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);*/


    //this as a much simpler way to do a 2d setup..., but it won:t work with 3d at all...
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowW, 0, windowH);

	glScalef(1, -1, 1);					// invert they axis so y goes down.
  	glTranslatef(0, -windowH, 0);       // shift origin to the upper left corner.

  	glMatrixMode(GL_MODELVIEW);*/

    glViewport(0,0, windowW, windowH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0, windowW, windowH, 0);
    glOrtho(0, windowW, windowH, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    //glEnable(GL_TEXTURE_2D);    //enable 2d textures
    glLoadIdentity();


    //enable alpha transparency blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //cout << " done \n";
}


/*LRESULT CALLBACK mouseCallback( int code, WPARAM wparam, LPARAM lparam){
    return CallNextHookEx(rGMouseHook, code, wparam, lparam);
}*/
