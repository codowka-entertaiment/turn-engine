#pragma once

#include <SDL2/SDL.h>

#include "Enums.hpp"
#include "Utils.hpp"
#include "Shapes.hpp"
#include "Surface.hpp"

#include <optional>

namespace TurnEngine {

    class renderer;
    class texture;

    class texture_lock {
        SDL_Texture* const texture_;
        std::byte* const pixels_;
        int const pitch_;

        friend class texture;

        constexpr texture_lock(SDL_Texture* const t, std::byte* const pix, int const pitch) noexcept
                : texture_(t), pixels_(pix), pitch_(pitch) {}

    public:
        texture_lock(texture_lock const&) = delete;

        texture_lock& operator=(texture_lock const&) = delete;

        constexpr int pitch() const noexcept { return pitch_; }

        constexpr std::byte* pixels() const noexcept { return pixels_; }

        ~texture_lock() noexcept {
            SDL_UnlockTexture(texture_);
        }
    };

    class texture {
        SDL_Texture* texture_;

    public:
        constexpr explicit texture(SDL_Texture* t) noexcept
                : texture_(t) {}

        texture(renderer& r, pixel_format_enum const format, texture_access const access, wh<int> const wh) noexcept;

        texture(renderer& r, surface const& s) noexcept;

        texture(renderer& r, null_term_string file) noexcept;

        texture(texture const&) = delete;

        texture& operator=(texture const&) = delete;

        texture& operator=(texture&&) = delete;

        constexpr texture(texture&& other) noexcept
                : texture_(std::exchange(other.texture_, nullptr)) {}

        ~texture() noexcept;

        void destroy() noexcept;

        constexpr SDL_Texture* native_handle() const noexcept { return texture_; }

        constexpr explicit operator bool() const noexcept { return texture_ != nullptr; }

        constexpr bool is_ok() const noexcept { return texture_ != nullptr; }

        texture_lock lock() noexcept;

        texture_lock lock(rect<int> const& rect) noexcept;

        std::uint8_t alpha_mod() const noexcept;

        TurnEngine::blend_mode blend_mode() const noexcept;

        rgb<std::uint8_t> color_mod() const noexcept;

        struct texture_query {
            pixel_format_enum format = pixel_format_enum::UNKNOWN;
            texture_access access{};
            int width = 0, height = 0;
        };

        texture_query query() const noexcept;

        wh<int> size() const noexcept;

        pixel_format_enum format() const noexcept;

        texture_access access() const noexcept;

        bool set_alpha_mod(std::uint8_t alpha) noexcept;

        bool set_blend_mode(TurnEngine::blend_mode mode) noexcept;

        bool set_color_mod(rgb<> const& mod) noexcept;

        bool update(rect<int> const& rect, std::span<std::byte const> pixels, int pitch) noexcept;

        bool update(std::span<std::byte const> pixels, int pitch) noexcept;

        bool update_yuv(rect<int> const& rect,
                        std::span<std::byte const> yplane, int ypitch,
                        std::span<std::byte const> uplane, int upitch,
                        std::span<std::byte const> vplane, int vpitch) noexcept;

        bool update_yuv(std::span<std::byte const> yplane, int ypitch,
                        std::span<std::byte const> uplane, int upitch,
                        std::span<std::byte const> vplane, int vpitch) noexcept;

    };

}