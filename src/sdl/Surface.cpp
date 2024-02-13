#include "Surface.hpp"

namespace sdl
{
    
    std::expected<Surface, SurfaceError> Surface::init(std::string_view filename) {
        std::ifstream file(filename.data());
        if (!file.good()) {
            return std::unexpected(SurfaceError::WrongFilename);
        }
        SDL_Surface *surface = IMG_Load(filename.data());
        if (!surface)
            return std::unexpected(SurfaceError::WrongFilename);
        else
            return Surface(surface);
    }

    Surface::Surface(SDL_Surface *surface) : image(surface) {}

    Surface::~Surface() {
        SDL_FreeSurface(image);
    }
}