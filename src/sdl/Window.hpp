#pragma once

#include <string_view>
#include "../math/Vector.hpp"
#include "../math/shapes/Rectangle.hpp"
#include "../math/shapes/Shape.hpp"
#include "SDL.h"
#include "sdl/Renderer.hpp"
#include "sdl/Surface.hpp"

namespace sdl
{

    class Window {
        friend class Renderer;

    private:
        SDL_Window *window;

    public:
        Window(std::string_view title, const math::Rectangle<int> &rectangle, Uint32 flags);
        ~Window();
        math::VectorInt getWindowSize();
        Surface getWindowSurface();
    };

}
