#include "../../include/turn-engine/sdl/Texture.hpp"

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