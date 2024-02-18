#pragma once

#include <cinttypes>
#include <expected>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.hpp"
#include "Window.hpp"
#include "string_view"

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
        static std::expected<Surface, SurfaceError> init(std::string_view filename);
        ~Surface();
    };
}
