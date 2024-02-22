#pragma once

#include <cinttypes>
#include <expected>
#include <string_view>
#include "../geo2d/Shapes.hpp"
#include "../geo2d/Vector.hpp"
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
        static std::expected<Window, WindowError> init(std::string_view title, const geo2d::Rectangle<int> &rectangle,
                                                       Uint32 flags);
        Window(const Window& other);
        Window(Window&& other) noexcept;
        ~Window();
        geo2d::VectorInt getSize();
        Surface getSurface();
        void raise();
        void setIcon(std::string_view filename);
    };

}
