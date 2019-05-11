#include "RGApp.hpp"
#include "RGSDLWindow.hpp"

/*void RGApp::runApp(int w, int h) {
    appPointer = this;

    windowW = w;
    windowH = h;


    HINSTANCE hinst = GetModuleHandle( NULL );
    //UnhookWindowsHookEx(rGMouseHook);
    rGMouseHook = SetWindowsHookEx( WH_MOUSE, &mouseCallback, hinst, GetCurrentThreadId() );

    ofSetupOpenGL(&window, w,h, OF_WINDOW);
    ofRunApp( this );

}*/

//Timing information (on an intel i7 950)


RGApp::RGApp(){
    appPointer = this;
	//HINSTANCE hinst = GetModuleHandle( NULL );
    //rGMouseHook = SetWindowsHookEx( WH_MOUSE, &mouseCallback, hinst, GetCurrentThreadId() );

    mouseIsPressed = false;
}
RGApp::~RGApp() {
    //delete window;
}

/*!
appName sets the program's name in the titlebar
*/
void RGApp::runApp(int w, int h) {
    windowW = w;
    windowH = h;

	setup();



    window = new RGSDLWindow();
    window->init();
    window->openWindow(w, h, false, titleBar);



	//setup screen
	setupGLView();



    /*if(GLEW_OK != glewInit()){
        cout << "GLEW ERROR!!";
        return;    //glew failed
    }
    if(!GLEW_EXT_framebuffer_object) {
        cout << "No EXT_fbo!!";
    } else {
        cout <<"FBO is GOOOOOOO!";
    }*/


	bool running = true;

	while(window->isOpen()) {


		processEvents();        //process mouse events and keyboard
		update();               //run user's update method

        //glClear(GL_COLOR_BUFFER_BIT);   //Screen clearing before drawing the gui, we may want to take this out later to increase flexibility
                                        //right now this is essentially done anyways because RGRoot renders as non-transparent
        //glLoadIdentity();

		draw();                 //run user's draw method

		window->display();

	}
    return;
}

void RGApp::processEvents() {
    RGInputEvent event;

    while (window->getEvent(event)) {
        if(event.type == RGInputEvent::Closed) {
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


int RGApp::getWindowW() {
    return windowW;
}
int RGApp::getWindowH() {
    return windowH;
}

void RGApp::setTitleBar(string newTitleBar){
    titleBar = newTitleBar;
}

void RGApp::setupGLView() {
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


}


/*LRESULT CALLBACK mouseCallback( int code, WPARAM wparam, LPARAM lparam){
    return CallNextHookEx(rGMouseHook, code, wparam, lparam);
}*/
