#include "TurnEngine/wrapper/Surface.hpp"

#include "SDL2/SDL.h"
#include "SDL_image.h"

using namespace TurnEngine;

Surface::Surface(wh<int> const _wh, int const depth, rgba<std::uint32_t> const masks) noexcept
        : surface_{SDL_CreateRGBSurface(0, _wh.width, _wh.height, depth, masks.r, masks.g, masks.b, masks.a)}
{}

Surface::Surface(void* const pixels, int const pitch, wh<int> const _wh,
                 int const depth, rgba<std::uint32_t> const masks) noexcept
        : surface_{SDL_CreateRGBSurfaceFrom(pixels, _wh.width, _wh.height, depth, pitch, masks.r, masks.g, masks.b, masks.a)}
{}

Surface::Surface(PixelFormatEnum const fmt, int const depth, wh<int> const _wh) noexcept
        : surface_{SDL_CreateRGBSurfaceWithFormat(0, _wh.width, _wh.height, depth, static_cast<std::uint32_t>(fmt))}
{}

Surface::Surface(void* const pixels, int const pitch, PixelFormatEnum const fmt, int const depth, wh<int> const _wh) noexcept
        : surface_{SDL_CreateRGBSurfaceWithFormatFrom(pixels, _wh.width, _wh.height, depth, pitch, static_cast<std::uint32_t>(fmt))}
{}

Surface::Surface(null_term_string const file) noexcept
        :surface_{IMG_Load(file.data())}
{}

constexpr Surface::Surface(Surface&& other) noexcept
        : surface_(std::exchange(other.surface_, nullptr))
{}

Surface::~Surface() noexcept {
    if (surface_)
        SDL_FreeSurface(surface_);
}

constexpr const_pixel_format_view Surface::pixel_format() const noexcept {
    SDL2_ASSERT(surface_->format != nullptr);
    return {surface_->format};
}

constexpr int Surface::width() const noexcept { return surface_->w; }
constexpr int Surface::height() const noexcept { return surface_->h; }
constexpr int Surface::pitch() const noexcept { return surface_->pitch; }
constexpr void const* Surface::pixels() const noexcept { return surface_->pixels; }
constexpr void* Surface::pixels() noexcept { return surface_->pixels; }
constexpr int Surface::num_pixels() const noexcept { return height() * pitch(); }
constexpr void const* Surface::userdata() const noexcept { return surface_->userdata; }
constexpr void* Surface::userdata() noexcept { return surface_->userdata; }
constexpr void Surface::set_userdata(void* const userdata) noexcept { surface_->userdata = userdata; }
constexpr Rect<int> Surface::clip_rect() const noexcept { return surface_->clip_rect; }
constexpr int Surface::refcount() const noexcept { return surface_->refcount; }
constexpr int Surface::refcount_add(int const amt) noexcept {
    surface_->refcount += amt;
    return surface_->refcount;
}
constexpr int Surface::refcount_sub(int const amt) noexcept {
    surface_->refcount -= amt;
    return surface_->refcount;
}

//int surface::refcount_atomic_load(std::memory_order const order) const noexcept {
//    return std::atomic_ref{surface_->refcount}.load(order);
//}
//int surface::refcount_atomic_fetch_add(int const amt, std::memory_order const order) noexcept {
//    return std::atomic_ref{surface_->refcount}.fetch_add(amt, order);
//}
//int surface::refcount_atomic_fetch_sub(int const amt, std::memory_order const order) noexcept {
//    return std::atomic_ref{surface_->refcount}.fetch_sub(amt, order);
//}

void Surface::lock() noexcept { SDL_LockSurface(surface_); }
void Surface::unlock() noexcept { SDL_UnlockSurface(surface_); }
bool Surface::must_lock() const noexcept { return SDL_MUSTLOCK(surface_); }

// blit
bool Surface::blit(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept {
    return SDL_BlitSurface(surface_, srcrect.native_handle(), dst.native_handle(), dstrect.native_handle()) == 0;
}
bool Surface::blit(Surface& dst, Rect<int>& dstrect) noexcept {
    return SDL_BlitSurface(surface_, nullptr, dst.native_handle(), dstrect.native_handle()) == 0;
}
bool Surface::blit(Surface& dst) noexcept {
    return SDL_BlitSurface(surface_, nullptr, dst.native_handle(), nullptr) == 0;
}
bool Surface::blit(Rect<int> const& srcrect, Surface& dst) noexcept {
    return SDL_BlitSurface(surface_, srcrect.native_handle(), dst.native_handle(), nullptr) == 0;
}

// blit_scaled
bool Surface::blit_scaled(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept {
    return SDL_BlitScaled(surface_, srcrect.native_handle(), dst.native_handle(), dstrect.native_handle()) == 0;
}
bool Surface::blit_scaled(Surface& dst, Rect<int>& dstrect) noexcept {
    return SDL_BlitScaled(surface_, nullptr, dst.native_handle(), dstrect.native_handle()) == 0;
}
bool Surface::blit_scaled(Surface& dst) noexcept {
    return SDL_BlitScaled(surface_, nullptr, dst.native_handle(), nullptr) == 0;
}
bool Surface::blit_scaled(Rect<int> const& srcrect, Surface& dst) noexcept {
    return SDL_BlitScaled(surface_, srcrect.native_handle(), dst.native_handle(), nullptr) == 0;
}

// lower_blit
bool Surface::lower_blit(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept {
    return SDL_LowerBlit(surface_, const_cast<SDL_Rect*>(srcrect.native_handle()), dst.native_handle(), dstrect.native_handle()) == 0;
}
bool Surface::lower_blit(Surface& dst, Rect<int>& dstrect) noexcept {
    return SDL_LowerBlit(surface_, nullptr, dst.native_handle(), dstrect.native_handle()) == 0;
}
bool Surface::lower_blit(Surface& dst) noexcept {
    return SDL_LowerBlit(surface_, nullptr, dst.native_handle(), nullptr) == 0;
}
bool Surface::lower_blit(Rect<int> const& srcrect, Surface& dst) noexcept {
    return SDL_LowerBlit(surface_, const_cast<SDL_Rect*>(srcrect.native_handle()), dst.native_handle(), nullptr) == 0;
}

// lower_blit_scaled
bool Surface::lower_blit_scaled(Rect<int> const& srcrect, Surface& dst, Rect<int>& dstrect) noexcept {
    return SDL_LowerBlitScaled(surface_, const_cast<SDL_Rect*>(srcrect.native_handle()), dst.native_handle(), dstrect.native_handle()) == 0;
}
bool Surface::lower_blit_scaled(Surface& dst, Rect<int>& dstrect) noexcept {
    return SDL_LowerBlitScaled(surface_, nullptr, dst.native_handle(), dstrect.native_handle()) == 0;
}
bool Surface::lower_blit_scaled(Surface& dst) noexcept {
    return SDL_LowerBlitScaled(surface_, nullptr, dst.native_handle(), nullptr) == 0;
}
bool Surface::lower_blit_scaled(Rect<int> const& srcrect, Surface& dst) noexcept {
    return SDL_LowerBlitScaled(surface_, const_cast<SDL_Rect*>(srcrect.native_handle()), dst.native_handle(), nullptr) == 0;
}

bool Surface::fill_rect(Rect<int> const& rect, PixelValue const color) noexcept {
    return SDL_FillRect(surface_, rect.native_handle(), color) == 0;
}
bool Surface::fill(PixelValue const color) noexcept {
    return SDL_FillRect(surface_, nullptr, color) == 0;
}
bool Surface::fill_rects(std::span<Rect<int> const> const rects, PixelValue const color) noexcept {
return SDL_FillRects(surface_, rects.data()->native_handle(), static_cast<int>(rects.size()), color) == 0;
}

bool Surface::convert(TurnEngine::PixelFormat const& fmt) noexcept {
    return SDL_ConvertSurface(surface_, fmt.native_handle(), 0) != nullptr ? true : false;
}

Surface Surface::convert_to_new(TurnEngine::PixelFormat const& fmt) const noexcept {
    return Surface{SDL_ConvertSurfaceFormat(surface_, static_cast<std::uint32_t>(fmt.format()), 0)};
}

std::optional<PixelValue> Surface::color_key() const noexcept {
    std::uint32_t key{};
    if (SDL_GetColorKey(surface_, &key) == 0)
        return PixelValue{key};
    return {};
}

std::uint8_t Surface::alpha_mod() const noexcept {
    std::uint8_t a{};
    [[maybe_unused]] auto const err = SDL_GetSurfaceAlphaMod(surface_, &a);
    SDL2_ASSERT(err == 0);
    return a;
}

TurnEngine::BlendMode Surface::blend_mode() const noexcept {
    SDL_BlendMode mode{};
    [[maybe_unused]] auto const err = SDL_GetSurfaceBlendMode(surface_, &mode);
    SDL2_ASSERT(err == 0);
    return static_cast<TurnEngine::BlendMode>(mode);
}

rgb<std::uint8_t> Surface::color_mod() const noexcept {
    rgb<std::uint8_t> ret;
    [[maybe_unused]] auto const err = SDL_GetSurfaceColorMod(surface_, &ret.r, &ret.g, &ret.b);
    SDL2_ASSERT(err == 0);
    return ret;
}

bool Surface::set_clip_rect(Rect<int> const& rect) noexcept {
    return SDL_SetClipRect(surface_, rect.native_handle()) == SDL_TRUE;
}

bool Surface::disable_clipping() noexcept {
    return SDL_SetClipRect(surface_, nullptr) == SDL_TRUE;
}

bool Surface::set_color_key(bool const enable, PixelValue const color) noexcept {
    return SDL_SetColorKey(surface_, static_cast<int>(enable), color);
}

bool Surface::set_alpha_mod(std::uint8_t const alpha) noexcept {
    return SDL_SetSurfaceAlphaMod(surface_, alpha) == 0;
}

bool Surface::set_blend_mode(TurnEngine::BlendMode const mode) noexcept {
    return SDL_SetSurfaceBlendMode(surface_, static_cast<SDL_BlendMode>(mode)) == 0;
}

bool Surface::set_color_mode(rgb<std::uint8_t> const _rgb) noexcept {
    return SDL_SetSurfaceColorMod(surface_, _rgb.r, _rgb.g, _rgb.b) == 0;
}

bool Surface::set_palette(palette_view const p) noexcept {
    return SDL_SetSurfacePalette(surface_, p.native_handle()) == 0;
}

bool Surface::set_rle(bool const enable) noexcept {
    return SDL_SetSurfaceRLE(surface_, static_cast<int>(enable)) == 0;
}

bool Surface::save_bmp_to_file(null_term_string const file) const noexcept {
    return SDL_SaveBMP(surface_, file.data()) == 0;
}

bool convert_pixels(wh<int> _wh, Surface const& src, Surface& dst) noexcept {
    return SDL_ConvertPixels(_wh.width, _wh.height,
                             static_cast<std::uint32_t>(src.pixel_format().format()), src.pixels(), src.pitch(),
                             static_cast<std::uint32_t>(dst.pixel_format().format()), dst.pixels(), dst.pitch()) == 0;
}