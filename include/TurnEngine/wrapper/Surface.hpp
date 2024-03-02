#pragma once

#include "SDL2/SDL.h"

#include <atomic>
#include <optional>

#include "Pixel.hpp"
#include "Shapes.hpp"
#include "Utils.hpp"

namespace TurnEngine {
    class surface {
        SDL_Surface* surface_;

    public:

        constexpr explicit surface(SDL_Surface* s) noexcept
                : surface_(s) {}

        surface(surface const&) = delete;

        surface& operator=(surface const&) = delete;

        surface& operator=(surface&&) = delete;

        constexpr surface(surface&& other) noexcept;

        surface(wh<int> wh, int depth, rgba<std::uint32_t> masks) noexcept;

        surface(void* pixels, int pitch, wh<int> wh, int depth, rgba<std::uint32_t> masks) noexcept;

        surface(pixel_format_enum fmt, int depth, wh<int> wh) noexcept;

        surface(void* pixels, int pitch, pixel_format_enum fmt, int depth, wh<int> wh) noexcept;

        explicit surface(null_term_string file) noexcept;

        ~surface() noexcept;

        constexpr auto native_handle() const noexcept { return surface_; }

        constexpr explicit operator bool() const noexcept { return surface_ != nullptr; }

        constexpr bool is_ok() const noexcept { return surface_ != nullptr; }

        constexpr const_pixel_format_view pixel_format() const noexcept;

        constexpr int width() const noexcept;

        constexpr int height() const noexcept;

        constexpr int pitch() const noexcept;

        constexpr void const* pixels() const noexcept;

        constexpr void* pixels() noexcept;

        constexpr int num_pixels() const noexcept;

        constexpr void const* userdata() const noexcept;

        constexpr void* userdata() noexcept;

        constexpr void set_userdata(void* userdata) noexcept;

        constexpr rect<int> clip_rect() const noexcept;

        constexpr int refcount() const noexcept;

        constexpr int refcount_add(int amt = 1) noexcept;

        constexpr int refcount_sub(int amt = 1) noexcept;

//        int refcount_atomic_load(std::memory_order order = std::memory_order_seq_cst) const noexcept;
//
//        int refcount_atomic_fetch_add(int amt = 1, std::memory_order order = std::memory_order_seq_cst) noexcept;
//
//        int refcount_atomic_fetch_sub(int amt = 1, std::memory_order order = std::memory_order_seq_cst) noexcept;

        void lock() noexcept;

        void unlock() noexcept;

        bool must_lock() const noexcept;

        bool blit(rect<int> const& srcrect, surface& dst, rect<int>& dstrect) noexcept;

        bool blit(surface& dst, rect<int>& dstrect) noexcept;

        bool blit(surface& dst) noexcept;

        bool blit(rect<int> const& srcrect, surface& dst) noexcept;

        bool blit_scaled(rect<int> const& srcrect, surface& dst, rect<int>& dstrect) noexcept;

        bool blit_scaled(surface& dst, rect<int>& dstrect) noexcept;

        bool blit_scaled(surface& dst) noexcept;

        bool blit_scaled(rect<int> const& srcrect, surface& dst) noexcept;

        bool lower_blit(rect<int> const& srcrect, surface& dst, rect<int>& dstrect) noexcept;

        bool lower_blit(surface& dst, rect<int>& dstrect) noexcept;

        bool lower_blit(surface& dst) noexcept;

        bool lower_blit(rect<int> const& srcrect, surface& dst) noexcept;

        bool lower_blit_scaled(rect<int> const& srcrect, surface& dst, rect<int>& dstrect) noexcept;

        bool lower_blit_scaled(surface& dst, rect<int>& dstrect) noexcept;

        bool lower_blit_scaled(surface& dst) noexcept;

        bool lower_blit_scaled(rect<int> const& srcrect, surface& dst) noexcept;

        bool fill_rect(rect<int> const& rect, pixel_value color) noexcept;

        bool fill(pixel_value color) noexcept;

        bool fill_rects(std::span<rect<int> const> rects, pixel_value color) noexcept;

        bool convert(TurnEngine::pixel_format const& fmt) noexcept;

        surface convert_to_new(TurnEngine::pixel_format const& fmt) const noexcept;

        std::optional<pixel_value> color_key() const noexcept;

        std::uint8_t alpha_mod() const noexcept;

        TurnEngine::blend_mode blend_mode() const noexcept;

        rgb<std::uint8_t> color_mod() const noexcept;

        bool set_clip_rect(rect<int> const& rect) noexcept;

        bool disable_clipping() noexcept;

        bool set_color_key(bool enable, pixel_value color) noexcept;

        bool set_alpha_mod(std::uint8_t const alpha) noexcept;

        bool set_blend_mode(TurnEngine::blend_mode mode) noexcept;

        bool set_color_mode(rgb<std::uint8_t> rgb) noexcept;

        bool set_palette(palette_view p) noexcept;

        bool set_rle(bool enable) noexcept;

        bool save_bmp_to_file(null_term_string file) const noexcept;
    };

    bool convert_pixels(wh<int> wh, surface const& src, surface& dst) noexcept;

}