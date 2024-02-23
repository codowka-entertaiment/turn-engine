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
        Window(Window &&other) noexcept;

        ~Window();

        static std::expected<Window, WindowError> init(std::string_view title, const geo2d::Rectangle<int> &rect, Uint32 flags);
        /// getSize
        /// \return возращает текущий размер окна
        geo2d::VectorInt getSize();
        /// getSurface
        /// \return возращает поверхность текщего окна
        Surface getSurface();
        ///raise - разворачивает окно и даёт ему фокус
        void raise();
        /// setIcon - устанавливает иконку окна
        /// \param filename - имя файла для иконки
        void setIcon(std::string_view filename);
    };

}
