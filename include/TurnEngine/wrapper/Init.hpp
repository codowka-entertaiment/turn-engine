#pragma once

#include "SDL2/SDL.h"
#include "SDL_image.h"

#include "Enums.hpp"

#include <optional>
#include <string_view>

namespace TurnEngine {
    class SDL2 {
        bool valid_ = true;
        constexpr SDL2() noexcept = default;

    public:
        SDL2(SDL2 const&) = delete;
        SDL2& operator=(SDL2 const&) = delete;
        SDL2& operator=(SDL2&&) = delete;

        constexpr SDL2(SDL2&& other) noexcept = default;

        SDL2(sdl2_init_flags const& flgs) noexcept
                : valid_{SDL_Init(static_cast<std::uint32_t>(flgs)) == 0}
        {}

        ~SDL2() noexcept { if (valid_) SDL_Quit(); }

        constexpr explicit operator bool() const noexcept { return valid_; }

        constexpr bool is_ok() const noexcept { return valid_; }

        static std::string_view get_error() noexcept {
            return SDL_GetError();
        }
    };

    class IMG {
        bool valid_ = true;
        constexpr IMG() noexcept = default;

    public:
        IMG(IMG const&) = delete;
        IMG& operator=(IMG const&) = delete;
        IMG& operator=(IMG&&) = delete;

        constexpr IMG(IMG&& other) noexcept
                : valid_(std::exchange(other.valid_, false)) {}

        IMG(img_init_flags const& flgs) noexcept
                : valid_{IMG_Init(static_cast<int>(flgs)) == 0}
        {}

        ~IMG() noexcept { if (valid_) IMG_Quit(); }

        constexpr explicit operator bool() const noexcept { return valid_; }

        constexpr bool is_ok() const noexcept { return valid_; }

        static std::string_view get_error() noexcept {
            return IMG_GetError();
        }

    };

}