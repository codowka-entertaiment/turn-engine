#pragma once

#include "SDL2/SDL.h"
#include "SDL_image.h"

namespace sdl
{
    int SDLLibInit(Uint32 SDLFlags) {
        return SDL_Init(SDLFlags);
    }
    void SDLLibClose() {
        SDL_Quit();
    }
}
