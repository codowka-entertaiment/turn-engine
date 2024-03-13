#pragma once

#include "SDL2/SDL.h"

#include <atomic>
#include <optional>

#include "Pixel.hpp"
#include "Shapes.hpp"
#include "Utils.hpp"

namespace TurnEngine {
    /**
     * @brief
     * That class wraps SDL_Surface SDL structure
     */
    class Surface {
    public:
        SDL_Surface* surface_;

        /**
         * @brief
         * @param s
         */
        constexpr explicit Surface(SDL_Surface* s) noexcept
                : surface_(s) {}

        /**
         * @brief Copy constructor deleted.
         */
        Surface(Surface const&) = delete;

        /**
         * @brief Copy assignment deleted.
         */
        Surface& operator=(Surface const&) = delete;

        /**
         * @brief Move assignment deleted.
         */
        Surface& operator=(Surface&&) = delete;

        /**
         * @brief Move constructor.
         * @param other The surface object to move into this surface.
         */
        constexpr Surface(Surface&& other) noexcept;

        /**
         * @brief
         * @param wh
         * @param depth
         * @param masks
         */
        Surface(wh<int> wh, int depth, rgba<std::uint32_t> masks) noexcept;

        /**
         * @brief
         * @param pixels
         * @param pitch
         * @param wh
         * @param depth
         * @param masks
         */
        Surface(void* pixels, int pitch, wh<int> wh, int depth, rgba<std::uint32_t> masks) noexcept;

        /**
         * @brief
         * @param fmt
         * @param depth
         * @param wh
         */
        Surface(PixelFormatEnum fmt, int depth, wh<int> wh) noexcept;

        /**
         * @brief
         * @param pixels
         * @param pitch
         * @param fmt
         * @param depth
         * @param wh
         */
        Surface(void* pixels, int pitch, PixelFormatEnum fmt, int depth, wh<int> wh) noexcept;

        /**
         * @brief
         * @param file
         */
        explicit Surface(null_term_string file) noexcept;

        /**
         * @brief The destructor.
         */
        ~Surface() noexcept;

        /**
         * @brief Get a pointer to the underlying SDL representation.
         * @return A pointer to the underlying SDL_Surface.
         */
        constexpr auto native_handle() const noexcept { return surface_; }

        /**
         * @brief Checks if the surface is in a valid state.
         * @return True if valid, false if not.
         */
        constexpr explicit operator bool() const noexcept { return surface_ != nullptr; }

        /**
         * @brief Checks if the surface is in a valid state.
         * @return True if valid, false if not.
         */
        constexpr bool is_ok() const noexcept { return surface_ != nullptr; }

        /**
         * @brief
         * @return
         */
        constexpr const_pixel_format_view pixel_format() const noexcept;

        /**
          * @brief
          * @return
          */
        constexpr int width() const noexcept { return surface_->w; };

        /**
         * @brief
         * @return
         */
        constexpr int height() const noexcept { return surface_->h; };

        /**
         * @brief
         * @return
         */
        constexpr int pitch() const noexcept;

        /**
         * @brief
         * @return
         */
        constexpr void const* pixels() const noexcept;

        /**
         * @brief
         * @return
         */
        constexpr void* pixels() noexcept;

        /**
         * @brief
         * @return
         */
        constexpr int num_pixels() const noexcept;

        /**
         * @brief
         * @return
         */
        constexpr void const* userdata() const noexcept;

        /**
         * @brief
         * @return
         */
        constexpr void* userdata() noexcept;

        /**
         * @brief
         * @param userdata
         */
        constexpr void set_userdata(void* userdata) noexcept;

        /**
         * @brief
         * @return
         */
        constexpr Rect<int> clip_rect() const noexcept;

        /**
         * @brief
         * @return
         */
        constexpr int refcount() const noexcept;

        /**
         * @brief
         * @param amt
         * @return
         */
        constexpr int refcount_add(int amt = 1) noexcept;

        /**
         * @brief
         * @param amt
         * @return
         */
        constexpr int refcount_sub(int amt = 1) noexcept;

//        int refcount_atomic_load(std::memory_order order = std::memory_order_seq_cst) const noexcept;
//
//        int refcount_atomic_fetch_add(int amt = 1, std::memory_order order = std::memory_order_seq_cst) noexcept;
//
//        int refcount_atomic_fetch_sub(int amt = 1, std::memory_order order = std::memory_order_seq_cst) noexcept;

        /**
         * @brief
         */
        void lock() noexcept;

        /**
         * @brief
         */
        void unlock() noexcept;

        /**
         * @brief
         * @return
         */
        bool must_lock() const noexcept;

        /**
         * @brief
         * @param srcrect
         * @param dst
         * @param dstrect
         * @return True if succeeded, false if failed.
         */
        bool blit(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept;

        /**
         * @brief
         * @param dst
         * @param dstrect
         * @return True if succeeded, false if failed.
         */
        bool blit(Surface& dst, Rect<int>& dstrect) noexcept;

        /**
         * @brief
         * @param dst
         * @return True if succeeded, false if failed.
         */
        bool blit(Surface& dst) noexcept;

        /**
         * @brief
         * @param srcrect
         * @param dst
         * @return True if succeeded, false if failed.
         */
        bool blit(Rect<int> const& srcrect, Surface& dst) noexcept;

        /**
         * @brief
         * @param srcrect
         * @param dst
         * @param dstrect
         * @return True if succeeded, false if failed.
         */
        bool blit_scaled(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept;

        /**
         * @brief
         * @param dst
         * @param dstrect
         * @return True if succeeded, false if failed.
         */
        bool blit_scaled(Surface& dst, Rect<int>& dstrect) noexcept;

        /**
         * @brief
         * @param dst
         * @return True if succeeded, false if failed.
         */
        bool blit_scaled(Surface& dst) noexcept;

        /**
         * @brief
         * @param srcrect
         * @param dst
         * @return True if succeeded, false if failed.
         */
        bool blit_scaled(Rect<int> const& srcrect, Surface& dst) noexcept;

        /**
         * @brief
         * @param srcrect
         * @param dst
         * @param dstrect
         * @return True if succeeded, false if failed.
         */
        bool lower_blit(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept;

        /**
         * @brief
         * @param dst
         * @param dstrect
         * @return True if succeeded, false if failed.
         */
        bool lower_blit(Surface& dst, Rect<int>& dstrect) noexcept;

        /**
         * @brief
         * @param dst
         * @return True if succeeded, false if failed.
         */
        bool lower_blit(Surface& dst) noexcept;

        /**
         * @brief
         * @param srcrect
         * @param dst
         * @return True if succeeded, false if failed.
         */
        bool lower_blit(Rect<int> const& srcrect, Surface& dst) noexcept;

        /**
         * @brief
         * @param srcrect
         * @param dst
         * @param dstrect
         * @return True if succeeded, false if failed.
         */
        bool lower_blit_scaled(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept;

        /**
         * @brief
         * @param dst
         * @param dstrect
         * @return True if succeeded, false if failed.
         */
        bool lower_blit_scaled(Surface& dst, Rect<int>& dstrect) noexcept;

        /**
         * @brief
         * @param dst
         * @return True if succeeded, false if failed.
         */
        bool lower_blit_scaled(Surface& dst) noexcept;

        /**
         * @brief
         * @param srcrect
         * @param dst
         * @return True if succeeded, false if failed.
         */
        bool lower_blit_scaled(Rect<int> const& srcrect, Surface& dst) noexcept;

        /**
         * @brief
         * @param rect
         * @param color
         * @return True if succeeded, false if failed.
         */
        bool fill_rect(Rect<int> const& rect, PixelValue color) noexcept;

        /**
         * @brief
         * @param color
         * @return True if succeeded, false if failed.
         */
        bool fill(PixelValue color) noexcept;

        /**
         * @brief
         * @param rects
         * @param color
         * @return True if succeeded, false if failed.
         */
        bool fill_rects(std::span<Rect<int> const> rects, PixelValue color) noexcept;

        /**
         * @brief
         * @param fmt
         * @return True if succeeded, false if failed.
         */
        bool convert(TurnEngine::PixelFormat const& fmt) noexcept;

        /**
         * @brief
         * @param fmt
         * @return
         */
        Surface convert_to_new(TurnEngine::PixelFormat const& fmt) const noexcept;

        /**
         * @brief
         * @return
         */
        std::optional<PixelValue> color_key() const noexcept;

        /**
         * @brief
         * @return
         */
        std::uint8_t alpha_mod() const noexcept;

        /**
         * @brief
         * @return
         */
        TurnEngine::BlendMode blend_mode() const noexcept;

        /**
         * @brief
         * @return
         */
        rgb<std::uint8_t> color_mod() const noexcept;

        /**
         * @brief
         * @return True if succeeded, false if failed.
         */
        bool set_clip_rect(Rect<int> const& rect) noexcept;

        /**
         * @brief
         * @return True if succeeded, false if failed.
         */
        bool disable_clipping() noexcept;

        /**
         * @brief
         * @param color
         * @return True if succeeded, false if failed.
         */
        bool set_color_key(bool enable, PixelValue color) noexcept;

        /**
         * @brief
         * @param alpha
         * @return True if succeeded, false if failed.
         */
        bool set_alpha_mod(std::uint8_t const alpha) noexcept;

        /**
         * @brief
         * @param mode
         * @return True if succeeded, false if failed.
         */
        bool set_blend_mode(TurnEngine::BlendMode mode) noexcept;

        /**
         * @brief
         * @param rgb
         * @return True if succeeded, false if failed.
         */
        bool set_color_mode(rgb<std::uint8_t> rgb) noexcept;

        /**
         * @brief
         * @param p
         * @return True if succeeded, false if failed.
         */
        bool set_palette(palette_view p) noexcept;

        /**
         * @brief
         * @param enable
         * @return True if succeeded, false if failed.
         */
        bool set_rle(bool enable) noexcept;

        /**
         * @brief
         * @param file
         * @return True if succeeded, false if failed.
         */
        bool save_bmp_to_file(null_term_string file) const noexcept;
    };

    /**
     * @brief
     * @param wh
     * @param src
     * @param dst
     * @return True if succeeded, false if failed.
     */
    bool convert_pixels(wh<int> wh, Surface const& src, Surface& dst) noexcept;

}