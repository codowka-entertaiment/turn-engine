#include "turn-engine/sdl/SDL.hpp"

int sdl::SDLLibInit(Uint32 SDLFlags, int SDLIMGFlags) {
    if (SDL_Init(SDLFlags) < 0) {
        std::cerr << "SDL_INIT: " << SDL_GetError() << "\n";
        return -1;
    }
    if ((IMG_Init(SDLIMGFlags) & SDLIMGFlags) != SDLIMGFlags) {
        std::cerr << "IMG_Init: " << IMG_GetError() << "\n";
        SDL_Quit();
        return -1;
    }
    return 0;
}

void sdl::SDLLibClose() {
    SDL_Quit();
    IMG_Quit();
}
