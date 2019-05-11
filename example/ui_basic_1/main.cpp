#include <iostream>

//#include "rgui/RGSDLWindow.hpp"






#include "EmptyApp.hpp"

#include <iostream>



//========================================================================
int main(int argc, char *argv[]){

    RGApp* app = new EmptyApp();

    app->runApp(1024,768);

    return 0;
}


/*int main() {
    std::cout << "test\n";
//
//     SDL_Init(SDL_INIT_VIDEO);
//
//	SDL_Window *window = SDL_CreateWindow(
//		"SDL2Test",
//		SDL_WINDOWPOS_UNDEFINED,
//		SDL_WINDOWPOS_UNDEFINED,
//		640,
//		480,
//		0
//	);
//
//	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//	SDL_RenderClear(renderer);
//	SDL_RenderPresent(renderer);
//
//	SDL_Delay(3000);
//
//	SDL_DestroyWindow(window);
//	SDL_Quit();

    auto title = "Example Title"s;
    auto app_window = new RGSDLWindow();
    app_window->openWindow(640, 480, false, title);

    SDL_Delay(3000);


	return 0;
}*/