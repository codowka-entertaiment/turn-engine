#pragma once

#include <cinttypes>
#include <expected>
#include <string_view>
#include "../math/Vector.hpp"
#include "../math/shapes/Rectangle.hpp"
#include "../math/shapes/Shape.hpp"
#include "Renderer.hpp"
#include "SDL.h"
#include "Surface.hpp"
#include <iostream>

namespace sdl
{
    class Surface;
    enum class WindowError : std::uint8_t { WindowCreationError };
    class Window {
        friend class Renderer;

    private:
        SDL_Window *m_window;
        explicit Window(SDL_Window *window);

    public:
        static std::expected<Window, WindowError> init(std::string_view title, const math::Rectangle<int> &rectangle,
                                                       Uint32 flags);
        Window(const Window& other);
        Window(Window&& other) noexcept;
        ~Window();
        math::VectorInt getSize();
        Surface getSurface();
        void raise();
        void setIcon(std::string_view filename);
    };

}
