#pragma once

#include <SDL2/SDL.h>

#include "Enums.hpp"
#include "Utils.hpp"
#include "Shapes.hpp"
#include "Surface.hpp"

#include <optional>

namespace TurnEngine {

    class Renderer;
    class Texture;

    class TextureLock {
        SDL_Texture* const texture_;
        std::byte* const pixels_;
        int const pitch_;

        friend class Texture;

        constexpr TextureLock(SDL_Texture* const t, std::byte* const pix, int const pitch) noexcept
                : texture_(t), pixels_(pix), pitch_(pitch) {}

    public:
        TextureLock(TextureLock const&) = delete;

        TextureLock& operator=(TextureLock const&) = delete;

        constexpr int pitch() const noexcept { return pitch_; }

        constexpr std::byte* pixels() const noexcept { return pixels_; }

        ~TextureLock() noexcept {
            SDL_UnlockTexture(texture_);
        }
    };

    class Texture {
        SDL_Texture* texture_;

    public:
        constexpr explicit Texture(SDL_Texture* t) noexcept
                : texture_(t) {}

        Texture(Renderer& r, PixelFormatEnum const format, TextureAccess const access, wh<int> const wh) noexcept;

        Texture(Renderer& r, Surface const& s) noexcept;

        Texture(Renderer& r, null_term_string file) noexcept;

        Texture(Texture const&) = delete;

        Texture& operator=(Texture const&) = delete;

        Texture& operator=(Texture&&) = delete;

        constexpr Texture(Texture&& other) noexcept
                : texture_(std::exchange(other.texture_, nullptr)) {}

        ~Texture() noexcept;

        void destroy() noexcept;

        constexpr SDL_Texture* native_handle() const noexcept { return texture_; }

        constexpr explicit operator bool() const noexcept { return texture_ != nullptr; }

        constexpr bool is_ok() const noexcept { return texture_ != nullptr; }

        TextureLock lock() noexcept;

        TextureLock lock(Rect<int> const& rect) noexcept;

        std::uint8_t alpha_mod() const noexcept;

        TurnEngine::BlendMode blend_mode() const noexcept;

        rgb<std::uint8_t> color_mod() const noexcept;

        struct texture_query {
            PixelFormatEnum format = PixelFormatEnum::UNKNOWN;
            TextureAccess access{};
            int width = 0, height = 0;
        };

        texture_query query() const noexcept;

        wh<int> size() const noexcept;

        PixelFormatEnum format() const noexcept;

        TextureAccess access() const noexcept;

        bool set_alpha_mod(std::uint8_t alpha) noexcept;

        bool set_blend_mode(TurnEngine::BlendMode mode) noexcept;

        bool set_color_mod(rgb<> const& mod) noexcept;

        bool update(Rect<int> const& rect, std::span<std::byte const> pixels, int pitch) noexcept;

        bool update(std::span<std::byte const> pixels, int pitch) noexcept;

        bool update_yuv(Rect<int> const& rect,
                        std::span<std::byte const> yplane, int ypitch,
                        std::span<std::byte const> uplane, int upitch,
                        std::span<std::byte const> vplane, int vpitch) noexcept;

        bool update_yuv(std::span<std::byte const> yplane, int ypitch,
                        std::span<std::byte const> uplane, int upitch,
                        std::span<std::byte const> vplane, int vpitch) noexcept;

    };

}