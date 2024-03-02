#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"

#include "Enums.hpp"
#include "Shapes.hpp"
#include "surface.hpp"
#include "Utils.hpp"

#include <array>
#include <cstdint>
#include <optional>
#include <span>
#include <string_view>

namespace TurnEngine {
    class window {
        SDL_Window *window_;
    public:

        constexpr explicit window(SDL_Window *window) noexcept
                : window_(window) {}

        window(window const &) = delete;

        window &operator=(window const &) = delete;

        window &operator=(window &&) = delete;

        constexpr window(window &&other) noexcept
                : window_(std::exchange(other.window_, nullptr)) {}

        window(null_term_string title, xy<int> xy, wh<int> wh, window_flags flgs) noexcept;

        ~window() noexcept;

        void destroy() noexcept;

        constexpr auto native_handle() const noexcept { return window_; }

        constexpr explicit operator bool() const noexcept { return window_ != nullptr; }

        constexpr bool is_ok() const noexcept { return window_ != nullptr; }

        static constexpr xy<int> pos_centered{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};

        static constexpr xy<int> pos_undefined{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED};

        static window copy(window const &other) noexcept;

        std::optional<tlbr<int>> borders_size() noexcept;

        float brightness() const noexcept;

        int display_index() const noexcept;

        std::optional<SDL_DisplayMode> display_mode() const noexcept;

        window_flags flags() const noexcept;

        rgb<std::array<std::uint16_t, 256>> gamma_ramp() const noexcept;

        bool is_grabbed() const noexcept;

        std::uint32_t id() const noexcept;

        wh<int> maximum_size() const noexcept;

        wh<int> minimum_size() const noexcept;

        float opacity() const noexcept;

        pixel_format_enum pixel_format() const noexcept;

        xy<int> position() const noexcept;

        wh<int> size() const noexcept;

        std::string_view title() const noexcept;

        std::optional<SDL_SysWMinfo> wm_info() const noexcept;

        void hide() noexcept;

        void maximize() noexcept;

        void minimize() noexcept;

        void raise() noexcept;

        void restore() noexcept;

        void set_bordered(bool const bordered) noexcept;

        bool set_brightness(float const brightness) noexcept;

        bool set_display_mode(SDL_DisplayMode const &dm) noexcept;

        bool set_display_mode() noexcept;

        bool set_fullscreen(fullscreen_flags const flags) noexcept;

        bool set_gamma_ramp(std::span<std::uint16_t const, 256> const r,
                            std::span<std::uint16_t const, 256> const g,
                            std::span<std::uint16_t const, 256> const b) noexcept;

        void set_grabbed(bool grabbed = true) noexcept;

        bool set_hit_test(function_ref<SDL_HitTestResult(window &, point<int>)> const fn) noexcept;

        bool set_hit_test(function_ref<SDL_HitTestResult(window const &, point<int>)> const fn) noexcept;

        void set_icon(surface const &s) noexcept;

        bool set_input_focus() noexcept;

        void set_maximum_size(wh<int> wh) noexcept;

        void set_minimum_size(wh<int> const wh) noexcept;

        bool set_modal_for(window const &parent) noexcept;

        bool set_opacity(float const opacity) noexcept;

        void set_position(xy<int> const xy) noexcept;

        void set_resizable(bool const resizable) noexcept;

        void set_size(wh<int> const wh) noexcept;

        void set_title(null_term_string const title) noexcept;

        bool show_simple_message_box(message_box_flags const flags, null_term_string const title,
                                     null_term_string const message) noexcept;

        void show() noexcept;

        bool update_surface() noexcept;

        bool update_surface_rects(std::span<rect < int> const

        > const rects) noexcept;
    };

}