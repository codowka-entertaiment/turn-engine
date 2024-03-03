#pragma once

#include "SDL2/SDL.h"
#include "SDL_image.h"
#include <cstdint>
#include <string_view>

namespace TurnEngine {

    enum class SDLInitFlags : std::uint32_t {
        TIMER = SDL_INIT_TIMER,
        AUDIO = SDL_INIT_AUDIO,
        VIDEO = SDL_INIT_VIDEO,
        JOYSTICK = SDL_INIT_JOYSTICK,
        HAPTIC = SDL_INIT_HAPTIC,
        GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
        EVENTS = SDL_INIT_EVENTS,
        EVERYTHING = SDL_INIT_EVERYTHING,
        NOPARACHUTE = SDL_INIT_NOPARACHUTE,
    };

    inline constexpr SDLInitFlags operator|(SDLInitFlags const& a, SDLInitFlags const& b) noexcept {
        return static_cast<SDLInitFlags>(static_cast<std::uint32_t>(a) | static_cast<std::uint32_t>(b));
    }

    enum class IMGInitFlags : int {
        JPG = IMG_INIT_JPG,
        PNG = IMG_INIT_PNG,
        TIF = IMG_INIT_TIF,
        WEBP = IMG_INIT_WEBP,
        ALL = JPG | PNG | TIF | WEBP,
    };

    inline constexpr IMGInitFlags operator|(IMGInitFlags const& a, IMGInitFlags const& b) noexcept {
        return static_cast<IMGInitFlags>(static_cast<int>(a) | static_cast<int>(b));
    }

    enum class MessageBoxFlags : std::uint32_t {
        ERROR = SDL_MESSAGEBOX_ERROR,
        WARNING = SDL_MESSAGEBOX_WARNING,
        INFORMATION = SDL_MESSAGEBOX_INFORMATION,
    };

    enum class WindowFlags : std::uint32_t {
        NONE = 0,
        FULLSCREEN = SDL_WINDOW_FULLSCREEN,
        FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
        OPENGL = SDL_WINDOW_OPENGL,
        VULKAN = SDL_WINDOW_VULKAN,
        HIDDEN = SDL_WINDOW_HIDDEN,
        BORDERLESS = SDL_WINDOW_BORDERLESS,
        RESIZABLE = SDL_WINDOW_RESIZABLE,
        MINIMIZED = SDL_WINDOW_MINIMIZED,
        MAXIMIZED = SDL_WINDOW_MAXIMIZED,
        GRABBED = SDL_WINDOW_INPUT_GRABBED,
        ALLOW_HIGHDPI = SDL_WINDOW_ALLOW_HIGHDPI,
    };

    inline constexpr WindowFlags operator|(WindowFlags const& a, WindowFlags const& b) noexcept {
        return static_cast<WindowFlags>(static_cast<std::uint32_t>(a) | static_cast<std::uint32_t>(b));
    }

    inline constexpr bool operator&(WindowFlags const& a, WindowFlags const& b) noexcept {
        return static_cast<bool>(static_cast<std::uint32_t>(a) & static_cast<std::uint32_t>(b));
    }

    enum class RendererFlags : std::uint32_t  {
        SOFTWARE = SDL_RENDERER_SOFTWARE,
        ACCELERATED = SDL_RENDERER_ACCELERATED,
        PRESENTVSYNC = SDL_RENDERER_PRESENTVSYNC,
        TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE,
    };

    inline constexpr RendererFlags operator|(RendererFlags const& a, RendererFlags const& b) noexcept {
        return static_cast<RendererFlags>(static_cast<std::uint32_t>(a) | static_cast<std::uint32_t>(b));
    }

    inline constexpr bool operator&(RendererFlags const& a, RendererFlags const& b) noexcept {
        return static_cast<bool>(static_cast<std::uint32_t>(a) & static_cast<std::uint32_t>(b));
    }

    enum class BlendMode : int {
        INVALID = SDL_BLENDMODE_INVALID,
        NONE = SDL_BLENDMODE_NONE,
        BLEND = SDL_BLENDMODE_BLEND,
        ADD = SDL_BLENDMODE_ADD,
        MOD = SDL_BLENDMODE_MOD,
        MUL = SDL_BLENDMODE_MUL,
    };

    enum class FullscreenFlags : std::uint32_t {
        WINDOWED = 0,
        FULLSCREEN = SDL_WINDOW_FULLSCREEN,
        FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP
    };

    enum class TextureAccess : int {
        STATIC = SDL_TEXTUREACCESS_STATIC,
        STREAMING = SDL_TEXTUREACCESS_STREAMING,
        TARGET = SDL_TEXTUREACCESS_TARGET,
    };

    enum class PixelFormatEnum : std::uint32_t {
        UNKNOWN = SDL_PIXELFORMAT_UNKNOWN,
        INDEX1LSB = SDL_PIXELFORMAT_INDEX1LSB,
        INDEX1MSB = SDL_PIXELFORMAT_INDEX1MSB,
        INDEX4LSB = SDL_PIXELFORMAT_INDEX4LSB,
        INDEX4MSB = SDL_PIXELFORMAT_INDEX4MSB,
        INDEX8 = SDL_PIXELFORMAT_INDEX8,
        RGB332 = SDL_PIXELFORMAT_RGB332,
        RGB444 = SDL_PIXELFORMAT_RGB444,
        RGB555 = SDL_PIXELFORMAT_RGB555,
        BGR555 = SDL_PIXELFORMAT_BGR555,
        ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
        RGBA4444 = SDL_PIXELFORMAT_RGBA4444,
        ABGR4444 = SDL_PIXELFORMAT_ABGR4444,
        BGRA4444 = SDL_PIXELFORMAT_BGRA4444,
        ARGB1555 = SDL_PIXELFORMAT_ARGB1555,
        RGBA5551 = SDL_PIXELFORMAT_RGBA5551,
        ABGR1555 = SDL_PIXELFORMAT_ABGR1555,
        BGRA5551 = SDL_PIXELFORMAT_BGRA5551,
        RGB565 = SDL_PIXELFORMAT_RGB565,
        BGR565 = SDL_PIXELFORMAT_BGR565,
        RGB24 = SDL_PIXELFORMAT_RGB24,
        BGR24 = SDL_PIXELFORMAT_BGR24,
        RGB888 = SDL_PIXELFORMAT_RGB888,
        RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
        BGR888 = SDL_PIXELFORMAT_BGR888,
        BGRX8888 = SDL_PIXELFORMAT_BGRX8888,
        ARGB8888 = SDL_PIXELFORMAT_ARGB8888,
        RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
        ABGR8888 = SDL_PIXELFORMAT_ABGR8888,
        BGRA8888 = SDL_PIXELFORMAT_BGRA8888,
        ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,
        RGBA32 = SDL_PIXELFORMAT_RGBA32,
        ARGB32 = SDL_PIXELFORMAT_ARGB32,
        BGRA32 = SDL_PIXELFORMAT_BGRA32,
        ABGR32 = SDL_PIXELFORMAT_ABGR32,
        YV12 = SDL_PIXELFORMAT_YV12,
        IYUV = SDL_PIXELFORMAT_IYUV,
        YUY2 = SDL_PIXELFORMAT_YUY2,
        UYUY = SDL_PIXELFORMAT_UYVY,
        YVYU = SDL_PIXELFORMAT_YVYU,
        NV12 = SDL_PIXELFORMAT_NV12,
        NV21 = SDL_PIXELFORMAT_NV21,
    };

    enum class PixelType : std::uint32_t {
        UNKNOWN = SDL_PIXELTYPE_UNKNOWN,
        INDEX1 = SDL_PIXELTYPE_INDEX1,
        INDEX4 = SDL_PIXELTYPE_INDEX4,
        INDEX8 = SDL_PIXELTYPE_INDEX8,
        PACKED8 = SDL_PIXELTYPE_PACKED8,
        PACKED16 = SDL_PIXELTYPE_PACKED16,
        PACKED32 = SDL_PIXELTYPE_PACKED32,
        ARRAYU8 = SDL_PIXELTYPE_ARRAYU8,
        ARRAYU16 = SDL_PIXELTYPE_ARRAYU16,
        ARRAYU32 = SDL_PIXELTYPE_ARRAYU32,
        ARRAYF16 = SDL_PIXELTYPE_ARRAYF16,
        ARRAYF32 = SDL_PIXELTYPE_ARRAYF32,
    };

    enum class PixelOrder : std::uint32_t {
        BITMAP_NONE = SDL_BITMAPORDER_NONE,
        BITMAP_4321 = SDL_BITMAPORDER_4321,
        BITMAP_1234 = SDL_BITMAPORDER_1234,
        PACKED_NONE = SDL_PACKEDORDER_NONE,
        PACKED_XRGB = SDL_PACKEDORDER_XRGB,
        PACKED_RGBX = SDL_PACKEDORDER_RGBX,
        PACKED_ARGB = SDL_PACKEDORDER_ARGB,
        PACKED_RGBA = SDL_PACKEDORDER_RGBA,
        PACKED_XBGR = SDL_PACKEDORDER_XBGR,
        PACKED_BGRX = SDL_PACKEDORDER_BGRX,
        PACKED_ABGR = SDL_PACKEDORDER_ABGR,
        PACKED_BGRA = SDL_PACKEDORDER_BGRA,
        ARRAY_NONE = SDL_ARRAYORDER_NONE,
        ARRAY_RGB = SDL_ARRAYORDER_RGB,
        ARRAY_RGBA = SDL_ARRAYORDER_RGBA,
        ARRAY_ARGB = SDL_ARRAYORDER_ARGB,
        ARRAY_BGR = SDL_ARRAYORDER_BGR,
        ARRAY_BGRA = SDL_ARRAYORDER_BGRA,
        ARRAY_ABGR = SDL_ARRAYORDER_ABGR,
    };

    enum class PixelLayout : std::uint32_t {
        NONE = SDL_PACKEDLAYOUT_NONE,
        PACKED_332 = SDL_PACKEDLAYOUT_332,
        PACKED_444 = SDL_PACKEDLAYOUT_4444,
        PACKED_1555 = SDL_PACKEDLAYOUT_1555,
        PACKED_5551 = SDL_PACKEDLAYOUT_5551,
        PACKED_565 = SDL_PACKEDLAYOUT_565,
        PACKED_8888 = SDL_PACKEDLAYOUT_8888,
        PACKED_2101010 = SDL_PACKEDLAYOUT_2101010,
        PACKED_1010102 = SDL_PACKEDLAYOUT_1010102,
    };

    inline constexpr TurnEngine::PixelType pixel_type_for(PixelFormatEnum const& format) noexcept {
        return static_cast<PixelType>(SDL_PIXELTYPE(static_cast<std::uint32_t>(format)));
    }

    inline constexpr PixelOrder pixel_order_for(PixelFormatEnum const& format) noexcept {
        return static_cast<PixelOrder>(SDL_PIXELORDER(static_cast<std::uint32_t>(format)));
    }

    inline constexpr PixelLayout pixel_layout_for(PixelFormatEnum const& format) noexcept {
        return static_cast<PixelLayout>(SDL_PIXELORDER(static_cast<std::uint32_t>(format)));
    }

    inline constexpr std::uint32_t bits_per_pixel_for(PixelFormatEnum const& format) noexcept {
        return SDL_BITSPERPIXEL(static_cast<std::uint32_t>(format));
    }

    inline constexpr std::uint32_t bytes_per_pixel_for(PixelFormatEnum const& format) noexcept {
        return SDL_BYTESPERPIXEL(static_cast<std::uint32_t>(format));
    }

    inline constexpr bool is_pixel_format_indexed(PixelFormatEnum const& format) noexcept {
        return SDL_ISPIXELFORMAT_INDEXED(static_cast<std::uint32_t>(format));
    }

    inline constexpr bool is_pixel_format_alpha(PixelFormatEnum const& format) noexcept {
        return SDL_ISPIXELFORMAT_ALPHA(static_cast<std::uint32_t>(format));
    }

    inline constexpr bool is_pixel_format_four_cc(PixelFormatEnum const& format) noexcept {
        return SDL_ISPIXELFORMAT_FOURCC(static_cast<std::uint32_t>(format));
    }

    inline constexpr bool is_pixel_format_array(PixelFormatEnum const& format) noexcept {
        return SDL_ISPIXELFORMAT_ARRAY(static_cast<std::uint32_t>(format));
    }

    inline std::string_view pixel_format_name_for(PixelFormatEnum const& format) noexcept {
        return SDL_GetPixelFormatName(static_cast<std::uint32_t>(format));
    }

    enum class RendererFlip {
        NONE = SDL_FLIP_NONE,
        HORIZONTAL = SDL_FLIP_HORIZONTAL,
        VERTICAL = SDL_FLIP_VERTICAL,
    };

}