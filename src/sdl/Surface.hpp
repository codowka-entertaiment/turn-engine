#pragma once

#include <cinttypes>
#include <expected>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "sdl/Texture.hpp"
#include "string_view"

namespace sdl
{
    enum class SurfaceError : std::uint8_t { WrongFilename, CantLoadSurface };

    class Surface {
        friend class Texture;

    private:
        SDL_Surface *surface;

    public:
        explicit Surface(SDL_Surface *surface);
        static std::expected<Surface, SurfaceError> init(std::string_view filename);
        ~Surface();
    };
}
