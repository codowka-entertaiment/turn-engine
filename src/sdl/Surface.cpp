#include <turn-engine/sdl/Surface.hpp>

std::expected<sdl::Surface, sdl::SurfaceError> sdl::Surface::load(std::string_view filename) {
    std::ifstream file(filename.data());

    if (!file.good())
        return std::unexpected(SurfaceError::WrongFilename);

    SDL_Surface *surface = IMG_Load(filename.data());

    if (!surface)
        return std::unexpected(SurfaceError::WrongFilename);
    else
        return Surface(surface);
}

sdl::Surface::Surface(SDL_Surface *surface) : m_surface(surface) {}

sdl::Surface::~Surface() {
    SDL_FreeSurface(m_surface);
}

sdl::Surface::Surface(sdl::Surface &&other) noexcept {
    m_surface = other.m_surface;
    other.m_surface = nullptr;
}