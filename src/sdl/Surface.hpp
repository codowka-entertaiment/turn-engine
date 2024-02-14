#pragma once

#include <cinttypes>
#include <expected>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "string_view"

namespace sdl
{
    enum class SurfaceError : std::uint8_t { WrongFilename, CantLoadSurface };

    class Surface {
    private:
        SDL_Surface *image;

    public:
        explicit Surface(SDL_Surface *surface);
        static std::expected<Surface, SurfaceError> init(std::string_view filename);
        ~Surface();
    };
}
