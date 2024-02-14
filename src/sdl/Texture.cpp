#include "Texture.hpp"

namespace sdl
{
    Texture::Texture(SDL_Texture *texture) : texture(texture) {}

    Texture::~Texture() {
        SDL_DestroyTexture(texture);
    }
    std::expected<Texture, TextureError> Texture::init(Renderer *renderer, Surface *surface) {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer->renderer, surface->surface);
        if (texture != nullptr)
            return Texture(texture);
        else
            return std::unexpected(TextureError::CantLoadTexture);
    }
}