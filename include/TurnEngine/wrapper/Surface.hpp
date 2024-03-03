#pragma once

#include "SDL2/SDL.h"

#include <atomic>
#include <optional>

#include "Pixel.hpp"
#include "Shapes.hpp"
#include "Utils.hpp"

namespace TurnEngine {
    class Surface {
        SDL_Surface* surface_;

    public:

        constexpr explicit Surface(SDL_Surface* s) noexcept
                : surface_(s) {}

        Surface(Surface const&) = delete;

        Surface& operator=(Surface const&) = delete;

        Surface& operator=(Surface&&) = delete;

        constexpr Surface(Surface&& other) noexcept;

        Surface(wh<int> wh, int depth, rgba<std::uint32_t> masks) noexcept;

        Surface(void* pixels, int pitch, wh<int> wh, int depth, rgba<std::uint32_t> masks) noexcept;

        Surface(PixelFormatEnum fmt, int depth, wh<int> wh) noexcept;

        Surface(void* pixels, int pitch, PixelFormatEnum fmt, int depth, wh<int> wh) noexcept;

        explicit Surface(null_term_string file) noexcept;

        ~Surface() noexcept;

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

        constexpr Rect<int> clip_rect() const noexcept;

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

        bool blit(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept;

        bool blit(Surface& dst, Rect<int>& dstrect) noexcept;

        bool blit(Surface& dst) noexcept;

        bool blit(Rect<int> const& srcrect, Surface& dst) noexcept;

        bool blit_scaled(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept;

        bool blit_scaled(Surface& dst, Rect<int>& dstrect) noexcept;

        bool blit_scaled(Surface& dst) noexcept;

        bool blit_scaled(Rect<int> const& srcrect, Surface& dst) noexcept;

        bool lower_blit(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept;

        bool lower_blit(Surface& dst, Rect<int>& dstrect) noexcept;

        bool lower_blit(Surface& dst) noexcept;

        bool lower_blit(Rect<int> const& srcrect, Surface& dst) noexcept;

        bool lower_blit_scaled(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept;

        bool lower_blit_scaled(Surface& dst, Rect<int>& dstrect) noexcept;

        bool lower_blit_scaled(Surface& dst) noexcept;

        bool lower_blit_scaled(Rect<int> const& srcrect, Surface& dst) noexcept;

        bool fill_rect(Rect<int> const& rect, PixelValue color) noexcept;

        bool fill(PixelValue color) noexcept;

        bool fill_rects(std::span<Rect<int> const> rects, PixelValue color) noexcept;

        bool convert(TurnEngine::PixelFormat const& fmt) noexcept;

        Surface convert_to_new(TurnEngine::PixelFormat const& fmt) const noexcept;

        std::optional<PixelValue> color_key() const noexcept;

        std::uint8_t alpha_mod() const noexcept;

        TurnEngine::BlendMode blend_mode() const noexcept;

        rgb<std::uint8_t> color_mod() const noexcept;

        bool set_clip_rect(Rect<int> const& rect) noexcept;

        bool disable_clipping() noexcept;

        bool set_color_key(bool enable, PixelValue color) noexcept;

        bool set_alpha_mod(std::uint8_t const alpha) noexcept;

        bool set_blend_mode(TurnEngine::BlendMode mode) noexcept;

        bool set_color_mode(rgb<std::uint8_t> rgb) noexcept;

        bool set_palette(palette_view p) noexcept;

        bool set_rle(bool enable) noexcept;

        bool save_bmp_to_file(null_term_string file) const noexcept;
    };

    bool convert_pixels(wh<int> wh, Surface const& src, Surface& dst) noexcept;

}