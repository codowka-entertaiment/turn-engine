#pragma once

#include "SDL2/SDL.h"

#include "Enums.hpp"
#include "Utils.hpp"
#include "Window.hpp"

#include <cstdint>
#include <optional>
#include <span>
#include <string_view>

namespace TurnEngine {

    class MessageBox {
        SDL_MessageBoxData data_;

    public:
        constexpr MessageBox(MessageBoxFlags flgs, std::span<SDL_MessageBoxButtonData const> buttons, null_term_string title,
                             null_term_string message) noexcept;

        constexpr MessageBox(MessageBoxFlags flgs, std::span<SDL_MessageBoxButtonData const> buttons, null_term_string consttitle,
                             null_term_string message, Window const& win) noexcept;

        constexpr MessageBox(MessageBoxFlags flgs, std::span<SDL_MessageBoxButtonData const> buttons, null_term_string title,
                             null_term_string message, std::span<SDL_MessageBoxColorScheme const> scheme) noexcept;

        template<std::size_t N>
        constexpr MessageBox(MessageBoxFlags flgs, std::span<SDL_MessageBoxButtonData const, N> buttons, null_term_string title,
                             null_term_string message, Window const& win, std::span<SDL_MessageBoxColorScheme const, N> scheme) noexcept;

        constexpr auto native_handle() const noexcept { return data_; }

        constexpr MessageBoxFlags flags() const noexcept { return static_cast<MessageBoxFlags>(data_.flags); }
        constexpr void set_flats(MessageBoxFlags const flag) noexcept { data_.flags = static_cast<std::uint32_t>(flag); }

        constexpr void set_window(Window& win) noexcept { data_.window = win.native_handle(); }
        constexpr void remove_window() noexcept { data_.window = nullptr; }
        constexpr bool has_window() const noexcept { return data_.window != nullptr; }

        constexpr std::string_view title() const noexcept { return data_.title; }
        constexpr void set_title(null_term_string const title) noexcept { data_.title = title.data(); }

        constexpr std::string_view message() const noexcept { return data_.message; }
        constexpr void set_message(null_term_string const message) noexcept { data_.message = message.data(); }

        constexpr int num_buttons() const noexcept { return data_.numbuttons; }

        constexpr std::span<SDL_MessageBoxButtonData const> buttons() const noexcept {
            return std::span{data_.buttons, static_cast<std::size_t>(data_.numbuttons)};
        }

        constexpr void set_buttons(std::span<SDL_MessageBoxButtonData const> const buttons) noexcept {
            data_.buttons = buttons.data();
            data_.numbuttons = static_cast<int>(buttons.size());
        }

        constexpr std::span<SDL_MessageBoxColorScheme const> color_scheme() const noexcept {
            return std::span{data_.colorScheme, static_cast<std::size_t>(data_.numbuttons)};
        }

        constexpr void set_color_scheme(std::span<SDL_MessageBoxColorScheme const> const scheme) noexcept {
            SDL2_ASSERT(scheme.size() == static_cast<std::size_t>(data_.numbuttons));
            data_.colorScheme = scheme.data();
        }

        constexpr void remove_color_scheme() noexcept { data_.colorScheme = nullptr; }
        constexpr bool has_color_scheme() const noexcept { return data_.colorScheme != nullptr; }

        std::optional<int> show() const noexcept {
            if (int button{}; SDL_ShowMessageBox(&data_, &button) == 0)
                return button;
            return {};
        }
    };

}