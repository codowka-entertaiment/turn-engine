#pragma once

#include <string_view>
#include "../math/Shape.hpp"
#include "../math/Vector.hpp"
#include "SDL2/SDL.h"

namespace sdl
{

    class Window {
    private:
        SDL_Window *window;

    public:
        Window(std::string_view title, int x, int y, int w, int h,
               Uint32 flags);
        ~Window();
        [[nodiscard]] SDL_Window *getWindow() const;
        math::VectorInt getWindowSize();
        SDL_Surface *getWindowSurface();
    };

}
