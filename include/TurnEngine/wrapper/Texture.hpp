#pragma once

#include <SDL2/SDL.h>

#include "Enums.hpp"
#include "Utils.hpp"
#include "Shapes.hpp"
#include "Surface.hpp"

#include <optional>

namespace TurnEngine {

    class Renderer;
    class Texture;

    /**
     * @brief A lock handle to a portion of a texture.
     */
    class TextureLock {
        SDL_Texture* const texture_;
        std::byte* const pixels_;
        int const pitch_;

        friend class Texture;

        constexpr TextureLock(SDL_Texture* const t, std::byte* const pix, int const pitch) noexcept
                : texture_(t), pixels_(pix), pitch_(pitch) {}

    public:

        /**
         * @brief Copy constructor deleted.
         */
        TextureLock(TextureLock const&) = delete;

        /**
         * @brief Copy assignment deleted.
         */
        TextureLock& operator=(TextureLock const&) = delete;

        /**
         * @brief Get the pitch of the underlying texture pixel data.
         * @return The pitch value.
         */
        constexpr int pitch() const noexcept { return pitch_; }

        /**
         * @brief Get access to the locked texture's pixels.
         * @return Pointer to the pixel data.
         */
        constexpr std::byte* pixels() const noexcept { return pixels_; }

        /**
         * @brief The destructor.
         */
        ~TextureLock() noexcept {
            SDL_UnlockTexture(texture_);
        }
    };

    /**
     * @brief A wrapper around an SDL_Texture structure.
     */
    class Texture {
        SDL_Texture* texture_;

    public:

        /**
         * @brief Constructor for interfacing with SDL's C API.
         * @param t An SDL_Texture struct to take ownership of.
         */
        constexpr explicit Texture(SDL_Texture* t) noexcept
                : texture_(t) {}

        /**
         * @brief Creates a texture for a renderer.
         * @param r The rendering context.
         * @param format The pixel format.
         * @param access The texture access.
         * @param wh The size of the texture in pixels.
         */
        Texture(Renderer& r, PixelFormatEnum const format, TextureAccess const access, wh<int> const wh) noexcept;

        /**
         * @brief Creates a texture from an existing surface.
         * @param r The rendering context.
         * @param s The surface containing pixel data used to fill the texture.
         */
        Texture(Renderer& r, Surface const& s) noexcept;

        /**
         * @brief Create a texture from a file using SDL_Image API.
         * @param r The rendering context.
         * @param file The path to the file to load the texture from.
         * @note The IMG library must have been initialized for this to work
         * @note This creates a temporary surface to use to create the texture.
         */
        Texture(Renderer& r, null_term_string file) noexcept;

        /**
         * @brief Copy constructor deleted.
         */
        Texture(Texture const&) = delete;

        /**
         * @brief Copy assignment deleted.
         */
        Texture& operator=(Texture const&) = delete;

        /**
         * @brief Move assignment deleted.
         */
        Texture& operator=(Texture&&) = delete;

        /**
         * @brief Move constructor.
         * @param other The texture object to move into this texture.
         */
        constexpr Texture(Texture&& other) noexcept
                : texture_(std::exchange(other.texture_, nullptr)) {}

        /**
         * @brief The destructor.
         */
        ~Texture() noexcept;

        /**
         * @brief Destroy the underlying texture object.
         * @note Accessing the texture after this functional call is UB.
         */
        void destroy() noexcept;

        /**
         * @brief Get a pointer to the underlying SDL representation.
         * @return A pointer to the underlying SDL_Texture.
         */
        constexpr SDL_Texture* native_handle() const noexcept { return texture_; }

        /**
         * @brief Checks if the texture is in a valid state.
         * @return True if valid, false if not.
         */
        constexpr explicit operator bool() const noexcept { return texture_ != nullptr; }

        /**
         * @brief Checks if the texture is in a valid state.
         * @return True if valid, false if not.
         */
        constexpr bool is_ok() const noexcept { return texture_ != nullptr; }

        /**
         * @brief Locks the entire texture for write-only pixel access.
         * @return A lock handle to the texture.
         * @note Texture must have been created with texture_access::STREAMING.
         */
        TextureLock lock() noexcept;

        /**
         * @brief Locks a portion of the texture for write-only pixel access.
         * @param rect The area to lock for access.
         * @return A lock handle to the portion of the texture.
         * @note Texture must have been created with texture_access::STREAMING.
         */
        TextureLock lock(Rect<int> const& rect) noexcept;

        /**
         * @brief Gets the additional alpha value used in blit operations.
         * @return The current alpha value.
         */
        std::uint8_t alpha_mod() const noexcept;

        /**
         * @brief Gets the blend mode used for texture copy operations.
         * @return The current blend mode.
         */
        TurnEngine::BlendMode blend_mode() const noexcept;

        /**
         * @brief Gets the additional color value multiplied into the render copy operations.
         * @return The current color mod.
         */
        rgb<std::uint8_t> color_mod() const noexcept;

        /**
         * @brief A struct containing texture information.
         */
        struct texture_query {
            PixelFormatEnum format = PixelFormatEnum::UNKNOWN;
            TextureAccess access{};
            int width = 0, height = 0;
        };

        /**
         * @brief Queries the attributes of the texture.
         * @return A query struct filled with information about the texture.
         */
        texture_query query() const noexcept;

        /**
         * @brief Gets the size of the current texture.
         * @return The texture's size.
         */
        wh<int> size() const noexcept;

        /**
         * @brief Gets the pixel format of the texture.
         * @return The texture's pixel format.
         */
        PixelFormatEnum format() const noexcept;

        /**
         * @brief Gets the texture access of the texture.
         * @return The texture's access type.
         */
        TextureAccess access() const noexcept;

        /**
         * @brief Sets an additional alpha value multiplied into render copy operations.
         * @param alpha The alpha value to multiply into copy ops.
         * @return True if succeeded, false if failed.
         */
        bool set_alpha_mod(std::uint8_t alpha) noexcept;

        /**
         * @brief Sets the blend mode for the texture.
         * @param mode The mode to sure for texture blending.
         * @return True if succeeded, false if failed.
         */
        bool set_blend_mode(TurnEngine::BlendMode mode) noexcept;

        /**
         * @brief Sets the additional color value multiplied into render copy operatinos.
         * @param mod The color mod value.
         * @return True if succeeded, false if failed.
         */
        bool set_color_mod(rgb<> const& mod) noexcept;

        /**
         * @brief Updates a portion of the texture with new pixel data.
         * @param rect The area to update.
         * @param pixels The raw pixel data in the format of the texture.
         * @param pitch The number of bytes in a row of pixel data, including padding between lines.
         * @return True if succeeded, false if failed.
         */
        bool update(Rect<int> const& rect, std::span<std::byte const> pixels, int pitch) noexcept;

        /**
         * @brief Updates the entire texture with new pixel data.
         * @param pixels The raw pixel data in the format of the texture.
         * @param pitch The number of bytes in a row of pixel data, including padding between lines.
         * @return True if succeeded, false if failed.
         */
        bool update(std::span<std::byte const> pixels, int pitch) noexcept;

        /**
         * @brief Updates a rectangle within a planar TY12 or IYUV texture with new pixel data.
         * @param rect The area to update.
         * @param yplane Span of raw pixel data for the Y plane.
         * @param ypitch Number of bytes between rows of pixel data for the Y plane.
         * @param uplane Span of raw pixel data for the U plane.
         * @param upitch Number of bytes between rows of pixel data for the U plane.
         * @param vplane Span of raw pixel data for the V plane.
         * @param vpitch Number of bytes between rows of pixel data for the V plane.
         * @return True if succeeded, false if failed.
         */
        bool update_yuv(Rect<int> const& rect,
                        std::span<std::byte const> yplane, int ypitch,
                        std::span<std::byte const> uplane, int upitch,
                        std::span<std::byte const> vplane, int vpitch) noexcept;

        /**
         * @brief
         * @param yplane Span of raw pixel data for the Y plane.
         * @param ypitch Number of bytes between rows of pixel data for the Y plane.
         * @param uplane Span of raw pixel data for the U plane.
         * @param upitch Number of bytes between rows of pixel data for the U plane.
         * @param vplane Span of raw pixel data for the V plane.
         * @param vpitch Number of bytes between rows of pixel data for the V plane.
         * @return True if succeeded, false if failed.
         */
        bool update_yuv(std::span<std::byte const> yplane, int ypitch,
                        std::span<std::byte const> uplane, int upitch,
                        std::span<std::byte const> vplane, int vpitch) noexcept;

    };

}