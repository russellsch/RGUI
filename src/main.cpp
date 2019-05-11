//#include "RGApp.h"
#include <TestApp.hpp>

#include <iostream>

//========================================================================
#undef main

int main( ){

	RGApp* app = new TestApp();
	app->setTitleBar("RGUI Testing Application");
	app->runApp(1024,768);

    return 0;
}



