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
        Texture(const Texture& other);
        Texture(Texture&& other) noexcept;
        static std::expected<Texture, TextureError> init(Renderer &renderer, Surface &surface);
        static std::expected<Texture, TextureError> load(Renderer &renderer, std::string_view filename);
        ~Texture();
    };
}