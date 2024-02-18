#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <cinttypes>
#include <expected>
#include "Renderer.hpp"
#include "Surface.hpp"

namespace sdl
{
    class Surface;
    class Renderer;
    enum class TextureError : std::uint8_t { CantLoadTexture };
    class Texture {
        friend class Renderer;

    private:
        SDL_Texture *m_texture;
        explicit Texture(SDL_Texture *texture);

    public:
        static std::expected<Texture, TextureError> init(Renderer &renderer, Surface &surface);
        ~Texture();
    };
}