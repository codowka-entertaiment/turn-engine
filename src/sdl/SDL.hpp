#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "iostream"

namespace sdl
{
    int SDLLibInit(Uint32 SDLFlags, int SDLIMGFlags) {
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
    void SDLLibClose() {
        SDL_Quit();
        IMG_Quit();
    }
}
