#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <cinttypes>
#include <expected>
#include <fstream>
#include <string_view>

namespace sdl
{
    enum class SurfaceError : std::uint8_t { WrongFilename, CantLoadSurface };

    class Surface {
        friend class Texture;
        friend class Window;

    private:
        SDL_Surface *m_surface;
        explicit Surface(SDL_Surface *surface);

    public:
        Surface(const Surface &other);
        Surface(Surface &&other) noexcept;

        static std::expected<Surface, SurfaceError> load(std::string_view filename);

        ~Surface();
    };
}
