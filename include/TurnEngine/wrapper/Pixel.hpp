#pragma once

#include "SDL2/SDL.h"

#include <concepts>
#include <span>

#include "Enums.hpp"
#include "Utils.hpp"

namespace TurnEngine {

    template<bool Const>
    class BasicPaletteView {
        SDL_Palette* palette_;

    public:
        template<class P>
        requires std::same_as<SDL_Palette, std::remove_cvref_t<P>>
        constexpr BasicPaletteView(P&& palette) noexcept
                : palette_(std::addressof(palette)) {}

        constexpr BasicPaletteView(BasicPaletteView const&) noexcept = default;
        constexpr BasicPaletteView(BasicPaletteView&&) noexcept = default;
        constexpr BasicPaletteView& operator=(BasicPaletteView const&) noexcept = default;
        constexpr BasicPaletteView& operator=(BasicPaletteView&&) noexcept = default;

        constexpr SDL_Palette* native_handle() const noexcept { return palette_; }

        template<bool B = Const>
        requires(B == false)
        constexpr std::span<SDL_Color> colors() noexcept {
            return std::span{palette_->colors, static_cast<std::size_t>(palette_->ncolors)};
        }

        constexpr std::span<SDL_Color const> colors() const noexcept {
            return std::span{palette_->colors, static_cast<std::size_t>(palette_->ncolors)};
        }
    };

    BasicPaletteView(SDL_Palette&) -> BasicPaletteView<false>;
    BasicPaletteView(SDL_Palette const&) -> BasicPaletteView<true>;

    using palette_view = BasicPaletteView<false>;
    using const_palette_view = BasicPaletteView<true>;

    class PixelFormat {
        SDL_PixelFormat* fmt_;

    public:
        PixelFormat(PixelFormatEnum const fmt) noexcept
                : fmt_{SDL_AllocFormat(static_cast<std::uint32_t>(fmt))}
        {}

        constexpr PixelFormat(SDL_PixelFormat* fmt) noexcept
                : fmt_{fmt} {}

        ~PixelFormat() noexcept {
            if (fmt_)
                SDL_FreeFormat(fmt_);
        }

        constexpr PixelFormat(PixelFormat&& other) noexcept
                : fmt_(std::exchange(other.fmt_, nullptr))
        {}

        PixelFormat(PixelFormat const&) = delete;
        PixelFormat& operator=(PixelFormat const&) = delete;
        PixelFormat& operator=(PixelFormat&&) = delete;

        constexpr SDL_PixelFormat* native_handle() const noexcept { return fmt_; }

        constexpr PixelFormatEnum format() const noexcept { return static_cast<PixelFormatEnum>(fmt_->format); }

        constexpr bool has_palette() const noexcept { return fmt_->palette != nullptr; }

        constexpr palette_view palette() noexcept {
            SDL2_ASSERT(has_palette());
            return palette_view{*(fmt_->palette)};
        }
        constexpr const_palette_view palette() const noexcept  {
            SDL2_ASSERT(has_palette());
            return const_palette_view{*(fmt_->palette)};
        }
        constexpr std::uint8_t bits_per_pixel() const noexcept { return fmt_->BitsPerPixel; }
        constexpr std::uint8_t bytes_per_pixel() const noexcept { return fmt_->BytesPerPixel; }
        constexpr std::uint32_t rmask() const noexcept { return fmt_->Rmask; }
        constexpr std::uint32_t gmask() const noexcept { return fmt_->Gmask; }
        constexpr std::uint32_t bmask() const noexcept { return fmt_->Bmask; }
        constexpr std::uint32_t amask() const noexcept { return fmt_->Amask; }
    };

    template<bool Const>
    class BasicPixelFormatView {
        SDL_PixelFormat* fmt_;

    public:
        template<class PF>
        requires std::same_as<SDL_PixelFormat, std::remove_cvref_t<PF>>
        constexpr BasicPixelFormatView(PF* fmt) noexcept
                : fmt_{fmt} {}

        template<class PF>
        requires std::same_as<PixelFormat, std::remove_cvref_t<PF>>
        constexpr BasicPixelFormatView(PF&& fmt) noexcept
                : fmt_(fmt.native_handle()) {}

        BasicPixelFormatView(std::nullptr_t) = delete;

        constexpr BasicPixelFormatView(BasicPixelFormatView const&) = default;
        constexpr BasicPixelFormatView(BasicPixelFormatView&&) = default;
        constexpr BasicPixelFormatView& operator=(BasicPixelFormatView const&) = default;
        constexpr BasicPixelFormatView& operator=(BasicPixelFormatView&&) = default;

        constexpr SDL_PixelFormat* native_handle() const noexcept { return fmt_; }

        constexpr PixelFormatEnum format() const noexcept { return static_cast<PixelFormatEnum>(fmt_->format); }

        constexpr bool has_palette() const noexcept {
            return fmt_->palette != nullptr;
        }

        template<bool B = Const>
        requires (B == false)
        constexpr palette_view palette() noexcept {
            SDL2_ASSERT(has_palette());
            return palette_view{*(fmt_->palette)};
        }

        constexpr const_palette_view palette() const noexcept  {
            SDL2_ASSERT(has_palette());
            return const_palette_view{*(fmt_->palette)};
        }

        constexpr std::uint8_t bits_per_pixel() const noexcept { return fmt_->BitsPerPixel; }
        constexpr std::uint8_t bytes_per_pixel() const noexcept { return fmt_->BytesPerPixel; }
        constexpr std::uint32_t rmask() const noexcept { return fmt_->Rmask; }
        constexpr std::uint32_t gmask() const noexcept { return fmt_->Gmask; }
        constexpr std::uint32_t bmask() const noexcept { return fmt_->Bmask; }
        constexpr std::uint32_t amask() const noexcept { return fmt_->Amask; }
    };

    BasicPixelFormatView(SDL_PixelFormat*) -> BasicPixelFormatView<false>;
    BasicPixelFormatView(SDL_PixelFormat const*) -> BasicPixelFormatView<true>;
    BasicPixelFormatView(PixelFormat&) -> BasicPixelFormatView<false>;
    BasicPixelFormatView(PixelFormat const&) -> BasicPixelFormatView<true>;

    using pixel_format_view = BasicPixelFormatView<false>;
    using const_pixel_format_view = BasicPixelFormatView<true>;

    class Surface;

    class PixelValue {
        std::uint32_t col_;
        friend class Surface;

    public:
        constexpr explicit PixelValue(std::uint32_t const col) noexcept : col_(col) {}

        constexpr operator std::uint32_t() const noexcept { return col_; }
        constexpr std::uint32_t value() const noexcept { return col_; }

        explicit PixelValue(PixelFormat const& fmt, rgb<std::uint8_t> const rgb) noexcept
                : col_(SDL_MapRGB(fmt.native_handle(), rgb.r, rgb.g, rgb.b)) {}

        explicit PixelValue(PixelFormat const& fmt, rgba<std::uint8_t> const rgba) noexcept
                : col_(SDL_MapRGBA(fmt.native_handle(), rgba.r, rgba.g, rgba.b, rgba.a)) {}

        constexpr PixelValue(PixelValue const&) noexcept = default;
        constexpr PixelValue(PixelValue&&) noexcept = default;
        constexpr PixelValue& operator=(PixelValue const&) noexcept = default;
        constexpr PixelValue& operator=(PixelValue&&) noexcept = default;

        rgb<std::uint8_t> as_rgb(PixelFormat const& fmt) const noexcept {
            rgb<std::uint8_t> _rgb{};
            SDL_GetRGB(col_, fmt.native_handle(), &_rgb.r, &_rgb.g, &_rgb.b);
            return _rgb;
        }

        rgba<std::uint8_t> as_rgba(PixelFormat const& fmt) const noexcept {
            rgba<std::uint8_t> _rgba{};
            SDL_GetRGBA(col_, fmt.native_handle(), &_rgba.r, &_rgba.g, &_rgba.b, &_rgba.a);
            return _rgba;
        }
    };

}