#pragma once

#include "SDL2/SDL.h"

#include <optional>
#include <span>

#include "Enums.hpp"
#include "Surface.hpp"
#include "Texture.hpp"
#include "Window.hpp"

namespace TurnEngine {

    class texture;

    class renderer_info {
        SDL_RendererInfo info_{};

    public:
        constexpr SDL_RendererInfo const* native_handle() const noexcept { return &info_; }

        constexpr SDL_RendererInfo* native_handle() noexcept { return &info_; }

        constexpr std::string_view name() const noexcept { return info_.name; }

        constexpr renderer_flags flags() const noexcept { return static_cast<renderer_flags>(info_.flags); }

        std::span<pixel_format_enum const> texture_formats() const noexcept;

        constexpr int max_texture_width() const noexcept { return info_.max_texture_width; }

        constexpr int max_texture_height() const noexcept { return info_.max_texture_height; }
    };

    class renderer {
        SDL_Renderer* renderer_;

    public:
        constexpr explicit renderer(SDL_Renderer* r) noexcept
                : renderer_{r} {}

        renderer(renderer const&) = delete;

        renderer& operator=(renderer const&) = delete;

        renderer& operator=(renderer&&) = delete;

        constexpr renderer(renderer&& other) noexcept
                : renderer_(std::exchange(other.renderer_, nullptr)) {}

        renderer(window& win, renderer_flags flags, int device_index = -1) noexcept;

        explicit renderer(surface& s) noexcept;

        ~renderer() noexcept;

        void destroy() noexcept;

        constexpr SDL_Renderer* native_handle() const noexcept { return renderer_; }

        constexpr explicit operator bool() const noexcept { return renderer_ != nullptr; }

        constexpr bool is_ok() const noexcept { return renderer_ != nullptr; }

        blend_mode draw_blend_mode() const noexcept;

        rgba<> draw_color() const noexcept;

        renderer_info info() const noexcept;

        wh<> output_size() const noexcept;

        optional_ref<SDL_Texture const> get_target() const noexcept;

        optional_ref<SDL_Texture> get_target() noexcept;

        bool clear() noexcept;

        bool copy(rect<int> const& render_rect, texture const& txr, rect<int> const& txr_rect) noexcept;

        bool copy(texture const& txr, rect<int> const& txr_rect) noexcept;

        bool copy(rect<int> const& render_rect, texture const& txr) noexcept;

        bool copy(texture const& txr) noexcept;

        bool copy_ex(rect<int> const& render_rect, texture const& txr, rect<int> const& txr_rect, double const angle, point<int> const& center, renderer_flip flip = renderer_flip::NONE) noexcept;

        bool copy_ex(texture const& txr, rect<int> const& txr_rect, double angle, point<int> const& center, renderer_flip flip = renderer_flip::NONE) noexcept;

        bool copy_ex(rect<int> const& render_rect, texture const& txr, double angle, point<int> const& center, renderer_flip flip = renderer_flip::NONE) noexcept;

        bool copy_ex(texture const& txr, double angle, point<int> const& center, renderer_flip flip = renderer_flip::NONE) noexcept;

        bool copy_ex(texture const& txr, rect<int> const& txr_rect, double angle = 0.0, renderer_flip flip = renderer_flip::NONE) noexcept;

        bool copy_ex(rect<int> const& render_rect, texture const& txr, double angle = 0.0, renderer_flip flip = renderer_flip::NONE) noexcept;

        bool copy_ex(texture const& txr, double angle = 0.0, renderer_flip flip = renderer_flip::NONE) noexcept;

        template<class Rep>
        bool draw_line(point<Rep> const& from, point<Rep> const& to) noexcept;

        template<class Rep>
        bool draw_lines(std::span<point<Rep> const> points) noexcept;

        template<class Rep>
        bool draw_point(point<Rep> const& p) noexcept;

        template<class Rep>
        bool draw_points(std::span<point<Rep> const> points) noexcept;

        template<class Rep>
        bool draw_rect(rect<Rep> const& r) noexcept;

        bool draw_outline() noexcept;

        template<class Rep>
        bool draw_rects(std::span<rect<Rep> const> rs) noexcept;

        template<class Rep>
        bool fill_rect(rect<Rep> const& r) noexcept;

        bool fill_target() noexcept;

        template<class Rep>
        bool fill_rects(std::span<rect<Rep> const> rs) noexcept;

        rect<int> clip_rect() const noexcept;

        bool integer_scale() const noexcept;

        wh<> logical_size() const noexcept;

        xy<float> scale() const noexcept;

        rect<int> viewport() const noexcept;

        bool is_clip_enabled() const noexcept;

        void present() const noexcept;

        bool read_pixels(rect<int> const& r, pixel_format_enum fmt, void* pixels, int pitch) const noexcept;

        bool read_pixels(pixel_format_enum fmt, void* pixels, int const pitch) const noexcept;

        bool read_pixels(rect<int> const& r, void* pixels, int pitch) const noexcept;

        bool read_pixels(void* pixels, int pitch) const noexcept;

        bool set_clip_rect(rect<int> const& clip) noexcept;

        bool disable_clipping() noexcept;

        bool set_integer_scale(bool enable) noexcept;

        bool set_logical_size(wh<int> const& size) noexcept;

        bool set_scale(xy<float> const& scale) noexcept;

        bool set_viewport(rect<int> const& r) noexcept;

        bool reset_viewport() noexcept;

        static bool target_supported(renderer const& r) noexcept;

        bool set_draw_blend_mode(blend_mode mode) noexcept;

        bool set_draw_color(rgba<> color) noexcept;

        bool set_render_target(texture const& t) noexcept;

        bool reset_render_target() noexcept;
    };

    inline std::pair<window, renderer> create_window_and_renderer(wh<int> wh, window_flags flags) noexcept;

    template<class Rep>
    bool renderer::draw_line(point<Rep> const& from, point<Rep> const& to) noexcept {
        if constexpr (std::is_same_v<Rep, int>)
            return SDL_RenderDrawLine(renderer_, from.x(), from.y(), to.x(), to.y()) == 0;
        else
            return SDL_RenderDrawLineF(renderer_, from.x(), from.y(), to.x(), to.y()) == 0;
    }

    template<class Rep>
    bool renderer::draw_lines(std::span<point<Rep> const> const points) noexcept {
    if constexpr (std::is_same_v<Rep, int>)
    return SDL_RenderDrawLines(renderer_, points.data()->native_handle(), static_cast<int>(points.size())) == 0;
    else
    return SDL_RenderDrawLinesF(renderer_, points.data()->native_handle(), static_cast<int>(points.size())) == 0;
}

template<class Rep>
bool renderer::draw_point(point<Rep> const& p) noexcept {
    if constexpr (std::is_same_v<Rep, int>)
        return SDL_RenderDrawPoint(renderer_, p.x(), p.y()) == 0;
    else
        return SDL_RenderDrawPointF(renderer_, p.x(), p.y()) == 0;
}

template<class Rep>
bool renderer::draw_points(std::span<point<Rep> const> const points) noexcept {
if constexpr (std::is_same_v<Rep, int>)
return SDL_RenderDrawPoints(renderer_, points.data()->native_handle(), static_cast<int>(points.size())) == 0;
else
return SDL_RenderDrawPointsF(renderer_, points.data()->native_handle(), static_cast<int>(points.size())) == 0;
}

template<class Rep>
bool renderer::draw_rect(rect<Rep> const& r) noexcept {
    if constexpr (std::is_same_v<Rep, int>)
        return SDL_RenderDrawRect(renderer_, r.native_handle()) == 0;
    else
        return SDL_RenderDrawRectF(renderer_, r.native_handle()) == 0;
}

template<class Rep>
bool renderer::draw_rects(std::span<rect<Rep> const> const r) noexcept {
if constexpr (std::is_same_v<Rep, int>)
return SDL_RenderDrawRects(renderer_, r.data().native_handle(), static_cast<int>(r.size())) == 0;
else
return SDL_RenderDrawRectsF(renderer_, r.data().native_handle(), static_cast<int>(r.size())) == 0;
}

template<class Rep>
bool renderer::fill_rect(rect<Rep> const& r) noexcept {
    if constexpr (std::is_same_v<Rep, int>)
        return SDL_RenderFillRect(renderer_, r.native_handle()) == 0;
    else
        return SDL_RenderFillRectF(renderer_, r.native_handle()) == 0;
}

template<class Rep>
bool renderer::fill_rects(std::span<rect<Rep> const> const r) noexcept {
if constexpr (std::is_same_v<Rep, int>)
return SDL_RenderFillRects(renderer_, r.data().native_handle(), static_cast<int>(r.size())) == 0;
else
return SDL_RenderFillRectsF(renderer_, r.data().native_handle(), static_cast<int>(r.size())) == 0;
}

}