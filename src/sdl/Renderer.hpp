#pragma once

#include "../math/Vector.hpp"
#include "SDL2/SDL.h"
#include "Window.hpp"

namespace sdl
{
    class Renderer {
    private:
        SDL_Renderer *renderer;

    public:
        Renderer(const Window &window, int index, Uint32 flags);
        int setScale(float scaleX, float scaleY);
        std::pair<float, float> getScale();
        ~Renderer();
    };
}