#pragma once

#include <SDL.h>

#include <cinttypes>
#include <expected>
#include <string_view>

#include "turn-engine/geo2d/Shapes.hpp"
#include "turn-engine/geo2d/Vector.hpp"

#include "Renderer.hpp"
#include "Surface.hpp"

namespace sdl
{
    enum class WindowError : std::uint8_t { WindowCreationError };
    
    class Window {
        friend class Renderer;

    private:
        SDL_Window *m_window;
        explicit Window(SDL_Window *window);

    public:
        Window(const Window &other);
        Window(Window &&other) noexcept;

        ~Window();

        static std::expected<Window, WindowError> init(std::string_view title, const geo2d::Rectangle<int> &rect, Uint32 flags);

        geo2d::VectorInt getSize();
        Surface getSurface();
        void raise();
        void setIcon(std::string_view filename);
    };

}
