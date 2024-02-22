#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

namespace sdl
{
    int SDLLibInit(Uint32 SDLFlags, int SDLIMGFlags);
    void SDLLibClose();
}
