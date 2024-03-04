#include "TurnEngine/wrapper/Renderer.hpp"

using namespace TurnEngine;

std::span<PixelFormatEnum const> RendererInfo::texture_formats() const noexcept {
    return std::span{reinterpret_cast<PixelFormatEnum const*>(info_.texture_formats), info_.num_texture_formats};
}

Renderer::Renderer(Window& win, RendererFlags const flags, int const device_index) noexcept\
    : renderer_{SDL_CreateRenderer(win.native_handle(), device_index, static_cast<std::uint32_t>(flags))}
{}

Renderer::Renderer(Surface& s) noexcept
        : renderer_{SDL_CreateSoftwareRenderer(s.native_handle())}
{}

Renderer::~Renderer() noexcept {
    if (renderer_)
        SDL_DestroyRenderer(renderer_);
}

void Renderer::destroy() noexcept {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
}

BlendMode Renderer::draw_blend_mode() const noexcept {
    SDL_BlendMode bm{};
    [[maybe_unused]] auto const err = SDL_GetRenderDrawBlendMode(renderer_, &bm);
    SDL2_ASSERT(err == 0);
    return static_cast<BlendMode>(bm);
}

rgba<> Renderer::draw_color() const noexcept {
    rgba<> val;
    [[maybe_unused]] auto const err = SDL_GetRenderDrawColor(renderer_, &val.r, &val.g, &val.b, &val.a);
    SDL2_ASSERT(err == 0);
    return val;
}

RendererInfo Renderer::info() const noexcept {
    RendererInfo info{};
    [[maybe_unused]] auto const err = SDL_GetRendererInfo(renderer_, info.native_handle());
    SDL2_ASSERT(err == 0);
    return info;
}

wh<> Renderer::output_size() const noexcept {
    wh<> val;
    [[maybe_unused]] auto const err = SDL_GetRendererOutputSize(renderer_, &val.width, &val.height);
    SDL2_ASSERT(err == 0);
    return val;
}

optional_ref<SDL_Texture const> Renderer::get_target() const noexcept {
    if (auto const t = SDL_GetRenderTarget(renderer_); t != nullptr)
        return *t;
    return {};
}

optional_ref<SDL_Texture> Renderer::get_target() noexcept {
    if (auto const t = SDL_GetRenderTarget(renderer_); t != nullptr)
        return *t;
    return {};
}

bool Renderer::draw_outline() noexcept {
    return SDL_RenderDrawRect(renderer_, nullptr) == 0;
}

bool Renderer::fill_target() noexcept {
    return SDL_RenderFillRect(renderer_, nullptr) == 0;
}

/// @brief
/// That function clears screen with the color last specified in set_draw_color
bool Renderer::clear() noexcept {
    return SDL_RenderClear(renderer_) == 0;
}

bool Renderer::copy(Rect<int> const& render_rect, Texture const& txr, Rect<int> const& txr_rect) noexcept {
    return SDL_RenderCopy(renderer_, txr.native_handle(), txr_rect.native_handle(), render_rect.native_handle()) == 0;
}
bool Renderer::copy(Texture const& txr, Rect<int> const& txr_rect) noexcept {
    return SDL_RenderCopy(renderer_, txr.native_handle(), txr_rect.native_handle(), nullptr) == 0;
}
bool Renderer::copy(Rect<int> const& render_rect, Texture const& txr) noexcept {
    return SDL_RenderCopy(renderer_, txr.native_handle(), nullptr, render_rect.native_handle()) == 0;
}
bool Renderer::copy(Texture const& txr) noexcept {
    return SDL_RenderCopy(renderer_, txr.native_handle(), nullptr, nullptr) == 0;
}

bool Renderer::copy_ex(Rect<int> const& render_rect, Texture const& txr, Rect<int> const& txr_rect, double const angle, Point<int> const& center, RendererFlip const flip) noexcept {
    return SDL_RenderCopyEx(renderer_, txr.native_handle(), txr_rect.native_handle(), render_rect.native_handle(), angle, center.native_handle(), static_cast<SDL_RendererFlip>(flip)) == 0;
}
bool Renderer::copy_ex(Texture const& txr, Rect<int> const& txr_rect, double const angle, Point<int> const& center, RendererFlip const flip) noexcept {
    return SDL_RenderCopyEx(renderer_, txr.native_handle(), txr_rect.native_handle(), nullptr, angle, center.native_handle(), static_cast<SDL_RendererFlip>(flip)) == 0;
}
bool Renderer::copy_ex(Rect<int> const& render_rect, Texture const& txr, double const angle, Point<int> const& center, RendererFlip const flip) noexcept {
    return SDL_RenderCopyEx(renderer_, txr.native_handle(), nullptr, render_rect.native_handle(), angle, center.native_handle(), static_cast<SDL_RendererFlip>(flip)) == 0;
}
bool Renderer::copy_ex(Texture const& txr, double const angle, Point<int> const& center, RendererFlip const flip) noexcept {
    return SDL_RenderCopyEx(renderer_, txr.native_handle(), nullptr, nullptr, angle, center.native_handle(), static_cast<SDL_RendererFlip>(flip)) == 0;
}
bool Renderer::copy_ex(Texture const& txr, Rect<int> const& txr_rect, double const angle, RendererFlip const flip) noexcept {
    return SDL_RenderCopyEx(renderer_, txr.native_handle(), txr_rect.native_handle(), nullptr, angle, nullptr, static_cast<SDL_RendererFlip>(flip)) == 0;
}
bool Renderer::copy_ex(Rect<int> const& render_rect, Texture const& txr, double const angle, RendererFlip const flip) noexcept {
    return SDL_RenderCopyEx(renderer_, txr.native_handle(), nullptr, render_rect.native_handle(), angle, nullptr, static_cast<SDL_RendererFlip>(flip)) == 0;
}
bool Renderer::copy_ex(Texture const& txr, double const angle, RendererFlip const flip) noexcept {
    return SDL_RenderCopyEx(renderer_, txr.native_handle(), nullptr, nullptr, angle, nullptr, static_cast<SDL_RendererFlip>(flip)) == 0;
}

Rect<int> Renderer::clip_rect() const noexcept {
    Rect<int> r;
    SDL_RenderGetClipRect(renderer_, r.native_handle());
    return r;
}

bool Renderer::integer_scale() const noexcept {
    return SDL_RenderGetIntegerScale(renderer_) == SDL_TRUE;
}

wh<> Renderer::logical_size() const noexcept {
    wh<> r;
    SDL_RenderGetLogicalSize(renderer_, &r.width, &r.height);
    return r;
}

xy<float> Renderer::scale() const noexcept {
    xy<float> r;
    SDL_RenderGetScale(renderer_, &r.x, &r.y);
    return r;
}

Rect<int> Renderer::viewport() const noexcept {
    Rect<int> r;
    SDL_RenderGetViewport(renderer_, r.native_handle());
    return r;
}

bool Renderer::is_clip_enabled() const noexcept {
    return SDL_RenderIsClipEnabled(renderer_) == SDL_TRUE;
}

void Renderer::present() const noexcept {
    SDL_RenderPresent(renderer_);
}

bool Renderer::read_pixels(Rect<int> const& r, PixelFormatEnum const fmt, void* const pixels, int const pitch) const noexcept {
    return SDL_RenderReadPixels(renderer_, r.native_handle(), static_cast<std::uint32_t>(fmt), pixels, pitch) == 0;
}
bool Renderer::read_pixels(PixelFormatEnum const fmt, void* const pixels, int const pitch) const noexcept {
    return SDL_RenderReadPixels(renderer_, nullptr, static_cast<std::uint32_t>(fmt), pixels, pitch) == 0;
}
bool Renderer::read_pixels(Rect<int> const& r, void* const pixels, int const pitch) const noexcept {
    return SDL_RenderReadPixels(renderer_, r.native_handle(), 0, pixels, pitch) == 0;
}
bool Renderer::read_pixels(void* const pixels, int const pitch) const noexcept {
    return SDL_RenderReadPixels(renderer_, nullptr, 0, pixels, pitch) == 0;
}

bool Renderer::set_clip_rect(Rect<int> const& clip) noexcept {
    return SDL_RenderSetClipRect(renderer_, clip.native_handle()) == 0;
}
bool Renderer::disable_clipping() noexcept {
    return SDL_RenderSetClipRect(renderer_, nullptr) == 0;
}

bool Renderer::set_integer_scale(bool const enabled) noexcept {
    return SDL_RenderSetIntegerScale(renderer_, static_cast<SDL_bool>(enabled)) == 0;
}

bool Renderer::set_logical_size(wh<int> const& size) noexcept {
    return SDL_RenderSetLogicalSize(renderer_, size.width, size.height) == 0;
}

bool Renderer::set_scale(xy<float> const& scale) noexcept {
    return SDL_RenderSetScale(renderer_, scale.x, scale.y) == 0;
}

bool Renderer::set_viewport(Rect<int> const& r) noexcept {
    return SDL_RenderSetViewport(renderer_, r.native_handle()) == 0;
}
bool Renderer::reset_viewport() noexcept {
    return SDL_RenderSetViewport(renderer_, nullptr) == 0;
}

bool Renderer::target_supported(Renderer const& r) noexcept {
    return SDL_RenderTargetSupported(r.native_handle()) == SDL_TRUE;
}

bool Renderer::set_draw_blend_mode(BlendMode const mode) noexcept {
    return SDL_SetRenderDrawBlendMode(renderer_, static_cast<SDL_BlendMode>(mode)) == 0;
}

bool Renderer::set_draw_color(rgba<> const color) noexcept {
    return SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a) == 0;
}

bool Renderer::set_render_target(Texture const& t) noexcept {
    SDL2_ASSERT(t.access() == TextureAccess::TARGET);
    return SDL_SetRenderTarget(renderer_, t.native_handle()) == 0;
}
bool Renderer::reset_render_target() noexcept {
    return SDL_SetRenderTarget(renderer_, nullptr) == 0;
}

inline std::pair<Window, Renderer> create_window_and_renderer(wh<int> const _wh, WindowFlags const flags) noexcept {
    SDL_Window* w{nullptr};
    SDL_Renderer* r{nullptr};
    SDL_CreateWindowAndRenderer(_wh.width, _wh.height, static_cast<std::uint32_t>(flags), &w, &r);
    return std::pair<Window, Renderer>(std::piecewise_construct, std::forward_as_tuple(w), std::forward_as_tuple(r));
}