#pragma once

#include "SDL2/SDL.h"

#include <optional>
#include <span>

#include "Enums.hpp"
#include "Surface.hpp"
#include "Texture.hpp"
#include "Window.hpp"

namespace TurnEngine {

    class Texture;

    class RendererInfo {
        SDL_RendererInfo info_{};

    public:
        constexpr SDL_RendererInfo const* native_handle() const noexcept { return &info_; }

        constexpr SDL_RendererInfo* native_handle() noexcept { return &info_; }

        constexpr std::string_view name() const noexcept { return info_.name; }

        constexpr RendererFlags flags() const noexcept { return static_cast<RendererFlags>(info_.flags); }

        std::span<PixelFormatEnum const> texture_formats() const noexcept;

        constexpr int max_texture_width() const noexcept { return info_.max_texture_width; }

        constexpr int max_texture_height() const noexcept { return info_.max_texture_height; }
    };

    class Renderer {
        SDL_Renderer* renderer_;

    public:
        constexpr explicit Renderer(SDL_Renderer* r) noexcept
                : renderer_{r} {}

        Renderer(Renderer const&) = delete;

        Renderer& operator=(Renderer const&) = delete;

        Renderer& operator=(Renderer&&) = delete;

        constexpr Renderer(Renderer&& other) noexcept
                : renderer_(std::exchange(other.renderer_, nullptr)) {}

        Renderer(Window& win, RendererFlags flags, int device_index = -1) noexcept;

        explicit Renderer(Surface& s) noexcept;

        ~Renderer() noexcept;

        void destroy() noexcept;

        constexpr SDL_Renderer* native_handle() const noexcept { return renderer_; }

        constexpr explicit operator bool() const noexcept { return renderer_ != nullptr; }

        constexpr bool is_ok() const noexcept { return renderer_ != nullptr; }

        BlendMode draw_blend_mode() const noexcept;

        rgba<> draw_color() const noexcept;

        RendererInfo info() const noexcept;

        wh<> output_size() const noexcept;

        optional_ref<SDL_Texture const> get_target() const noexcept;

        optional_ref<SDL_Texture> get_target() noexcept;

        bool clear() noexcept;

        bool copy(Rect<int> const& render_rect, Texture const& txr, Rect<int> const& txr_rect) noexcept;

        bool copy(Texture const& txr, Rect<int> const& txr_rect) noexcept;

        bool copy(Rect<int> const& render_rect, Texture const& txr) noexcept;

        bool copy(Texture const& txr) noexcept;

        bool copy_ex(Rect<int> const& render_rect, Texture const& txr, Rect<int> const& txr_rect, double const angle, Point<int> const& center, RendererFlip flip = RendererFlip::NONE) noexcept;

        bool copy_ex(Texture const& txr, Rect<int> const& txr_rect, double angle, Point<int> const& center, RendererFlip flip = RendererFlip::NONE) noexcept;

        bool copy_ex(Rect<int> const& render_rect, Texture const& txr, double angle, Point<int> const& center, RendererFlip flip = RendererFlip::NONE) noexcept;

        bool copy_ex(Texture const& txr, double angle, Point<int> const& center, RendererFlip flip = RendererFlip::NONE) noexcept;

        bool copy_ex(Texture const& txr, Rect<int> const& txr_rect, double angle = 0.0, RendererFlip flip = RendererFlip::NONE) noexcept;

        bool copy_ex(Rect<int> const& render_rect, Texture const& txr, double angle = 0.0, RendererFlip flip = RendererFlip::NONE) noexcept;

        bool copy_ex(Texture const& txr, double angle = 0.0, RendererFlip flip = RendererFlip::NONE) noexcept;

        template<class Rep>
        bool draw_line(Point<Rep> const& from, Point<Rep> const& to) noexcept;

        template<class Rep>
        bool draw_lines(std::span<Point<Rep> const> points) noexcept;

        template<class Rep>
        bool draw_point(Point<Rep> const& p) noexcept;

        template<class Rep>
        bool draw_points(std::span<Point<Rep> const> points) noexcept;

        template<class Rep>
        bool draw_rect(Rect<Rep> const& r) noexcept;

        bool draw_outline() noexcept;

        template<class Rep>
        bool draw_rects(std::span<Rect<Rep> const> rs) noexcept;

        template<class Rep>
        bool fill_rect(Rect<Rep> const& r) noexcept;

        bool fill_target() noexcept;

        template<class Rep>
        bool fill_rects(std::span<Rect<Rep> const> rs) noexcept;

        Rect<int> clip_rect() const noexcept;

        bool integer_scale() const noexcept;

        wh<> logical_size() const noexcept;

        xy<float> scale() const noexcept;

        Rect<int> viewport() const noexcept;

        bool is_clip_enabled() const noexcept;

        void present() const noexcept;

        bool read_pixels(Rect<int> const& r, PixelFormatEnum fmt, void* pixels, int pitch) const noexcept;

        bool read_pixels(PixelFormatEnum fmt, void* pixels, int const pitch) const noexcept;

        bool read_pixels(Rect<int> const& r, void* pixels, int pitch) const noexcept;

        bool read_pixels(void* pixels, int pitch) const noexcept;

        bool set_clip_rect(Rect<int> const& clip) noexcept;

        bool disable_clipping() noexcept;

        bool set_integer_scale(bool enable) noexcept;

        bool set_logical_size(wh<int> const& size) noexcept;

        bool set_scale(xy<float> const& scale) noexcept;

        bool set_viewport(Rect<int> const& r) noexcept;

        bool reset_viewport() noexcept;

        static bool target_supported(Renderer const& r) noexcept;

        bool set_draw_blend_mode(BlendMode mode) noexcept;

        bool set_draw_color(rgba<> color) noexcept;

        bool set_render_target(Texture const& t) noexcept;

        bool reset_render_target() noexcept;
    };

    inline std::pair<Window, Renderer> create_window_and_renderer(wh<int> wh, WindowFlags flags) noexcept;

    template<class Rep>
    bool Renderer::draw_line(Point<Rep> const& from, Point<Rep> const& to) noexcept {
        if constexpr (std::is_same_v<Rep, int>)
            return SDL_RenderDrawLine(renderer_, from.x(), from.y(), to.x(), to.y()) == 0;
        else
            return SDL_RenderDrawLineF(renderer_, from.x(), from.y(), to.x(), to.y()) == 0;
    }

    template<class Rep>
    bool Renderer::draw_lines(std::span<Point<Rep> const> const points) noexcept {
    if constexpr (std::is_same_v<Rep, int>)
    return SDL_RenderDrawLines(renderer_, points.data()->native_handle(), static_cast<int>(points.size())) == 0;
    else
    return SDL_RenderDrawLinesF(renderer_, points.data()->native_handle(), static_cast<int>(points.size())) == 0;
}

template<class Rep>
bool Renderer::draw_point(Point<Rep> const& p) noexcept {
    if constexpr (std::is_same_v<Rep, int>)
        return SDL_RenderDrawPoint(renderer_, p.x(), p.y()) == 0;
    else
        return SDL_RenderDrawPointF(renderer_, p.x(), p.y()) == 0;
}

template<class Rep>
bool Renderer::draw_points(std::span<Point<Rep> const> const points) noexcept {
if constexpr (std::is_same_v<Rep, int>)
return SDL_RenderDrawPoints(renderer_, points.data()->native_handle(), static_cast<int>(points.size())) == 0;
else
return SDL_RenderDrawPointsF(renderer_, points.data()->native_handle(), static_cast<int>(points.size())) == 0;
}

template<class Rep>
bool Renderer::draw_rect(Rect<Rep> const& r) noexcept {
    if constexpr (std::is_same_v<Rep, int>)
        return SDL_RenderDrawRect(renderer_, r.native_handle()) == 0;
    else
        return SDL_RenderDrawRectF(renderer_, r.native_handle()) == 0;
}

template<class Rep>
bool Renderer::draw_rects(std::span<Rect<Rep> const> const r) noexcept {
if constexpr (std::is_same_v<Rep, int>)
return SDL_RenderDrawRects(renderer_, r.data().native_handle(), static_cast<int>(r.size())) == 0;
else
return SDL_RenderDrawRectsF(renderer_, r.data().native_handle(), static_cast<int>(r.size())) == 0;
}

template<class Rep>
bool Renderer::fill_rect(Rect<Rep> const& r) noexcept {
    if constexpr (std::is_same_v<Rep, int>)
        return SDL_RenderFillRect(renderer_, r.native_handle()) == 0;
    else
        return SDL_RenderFillRectF(renderer_, r.native_handle()) == 0;
}

template<class Rep>
bool Renderer::fill_rects(std::span<Rect<Rep> const> const r) noexcept {
if constexpr (std::is_same_v<Rep, int>)
return SDL_RenderFillRects(renderer_, r.data().native_handle(), static_cast<int>(r.size())) == 0;
else
return SDL_RenderFillRectsF(renderer_, r.data().native_handle(), static_cast<int>(r.size())) == 0;
}

}