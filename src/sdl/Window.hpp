#pragma once

#include <cinttypes>
#include <expected>
#include <string_view>
#include "../math/Vector.hpp"
#include "../math/shapes/Rectangle.hpp"
#include "../math/shapes/Shape.hpp"
#include "SDL.h"
#include "sdl/Renderer.hpp"
#include "sdl/Surface.hpp"

namespace sdl
{
    enum class WindowError : std::uint8_t { WindowCreationError };
    class Window {
        friend class Renderer;

    private:
        SDL_Window *window;
        explicit Window(SDL_Window *window);

    public:
        static std::expected<Window, WindowError> init(std::string_view title, const math::Rectangle<int> &rectangle,
                                                       Uint32 flags);
        ~Window();
        math::VectorInt getWindowSize();
        Surface getWindowSurface();
    };

}
