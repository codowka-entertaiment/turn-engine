#include <turn-engine/sdl/Texture.hpp>

sdl::Texture::Texture(SDL_Texture *texture) : m_texture(texture) {}

sdl::Texture::~Texture() {
    SDL_DestroyTexture(m_texture);
}

std::expected<sdl::Texture, sdl::TextureError> sdl::Texture::init(Renderer &renderer, Surface &surface) {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface.m_surface);

    if (texture != nullptr)
        return Texture(texture);
    else
        return std::unexpected(TextureError::CantLoadTexture);
}

sdl::Texture::Texture(sdl::Texture &&other) noexcept {
    m_texture = other.m_texture;
    other.m_texture = nullptr;
}

std::expected<sdl::Texture, sdl::TextureError> sdl::Texture::load(Renderer &renderer, std::string_view filename) {
    auto tempSurface = sdl::Surface::load(filename);
    return Texture(SDL_CreateTextureFromSurface(renderer.m_renderer, tempSurface->m_surface));
}