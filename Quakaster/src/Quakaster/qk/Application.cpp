#include "Application.h"
//#include "SDL2/SDL.h"

namespace qk {
    Application::Application(int argc, char** argv) {
        // Initialize SDL. It's gonna be used regardless
        SDL_Init(SDL_INIT_VIDEO);


    }

    Application::~Application() {
        // and destroy the SDL instance
        SDL_Quit();
    }
}