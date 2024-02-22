#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Rect.hpp"
#include "Renderer.hpp"
#include "Surface.hpp"
#include "Texture.hpp"
#include "Window.hpp"

namespace sdl
{
    int SDLLibInit(Uint32 SDLFlags, int SDLIMGFlags);
    void SDLLibClose();
}
