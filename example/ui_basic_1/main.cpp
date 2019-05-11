#include <iostream>
#include "UIBasicApp1.hpp"

int main(int argc, char *argv[]){

    RGApp* app = new UIBasicApp1();

    app->runApp(1024,768);

    return 0;
}
