#pragma once

#include <string_view>
#include "../math/Vector.hpp"
#include "../math/shapes/Shape.hpp"
#include "SDL.h"
#include "sdl/Surface.hpp"

namespace sdl
{

    class Window {
    private:
        SDL_Window *window;

    public:
        Window(std::string_view title, int x, int y, int w, int h, Uint32 flags);
        ~Window();
        [[nodiscard]] SDL_Window *getWindow() const;
        math::VectorInt getWindowSize();
        Surface getWindowSurface();
    };

}
