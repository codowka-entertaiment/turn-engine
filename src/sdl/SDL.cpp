#include "turn-engine/sdl/SDL.hpp"

int sdl::sdl_init(Uint32 SDLFlags, int SDLIMGFlags) {
    if (SDL_Init(SDLFlags) < 0)
        return -1;

    if ((IMG_Init(SDLIMGFlags) & SDLIMGFlags) != SDLIMGFlags) {
        SDL_Quit();
        return -1;
    }
    return 0;
}

void sdl::sdl_close() {
    SDL_Quit();
    IMG_Quit();
}
