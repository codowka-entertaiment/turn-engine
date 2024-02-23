#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <cinttypes>
#include <expected>

#include "Renderer.hpp"
#include "Surface.hpp"

namespace sdl
{
    class Renderer;

    enum class TextureError : std::uint8_t { CantLoadTexture };

    class Texture {
        friend class Renderer;

    private:
        SDL_Texture *m_texture;
        explicit Texture(SDL_Texture *texture);

    public:
        Texture(Texture &&other) noexcept;

        ~Texture();
        /// init - создание текстуры из поверхности
        /// \param renderer - текущий рендерер
        /// \param surface - текущая поверхность
        /// \return возвращает объект текстуры
        static std::expected<Texture, TextureError> init(Renderer &renderer, Surface &surface);
        /// init - создание текстуры из файла
        /// \param renderer - текущий рендерер
        /// \param filename - имя файла
        /// \return возвращает объект текстуры
        static std::expected<Texture, TextureError> load(Renderer &renderer, std::string_view filename);
    };
}