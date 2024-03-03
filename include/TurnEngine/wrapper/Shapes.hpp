#pragma once

#include "SDL2/SDL.h"

#include <concepts>
#include <type_traits>

#include "Utils.hpp"

namespace TurnEngine {

    template<class T>
    concept sdl2_shape_rep = std::disjunction_v<std::is_same<T, float>, std::is_same<T, int>>;

    template<sdl2_shape_rep T>
    class Rect {
        using sdl_rect_t = std::conditional_t<std::is_same_v<T, int>, SDL_Rect, SDL_FRect>;
        sdl_rect_t rect_;

    public:
        constexpr Rect(sdl_rect_t const& rect) noexcept
                : rect_{rect} {}

        constexpr Rect(T const x = T(0), T const y = T(0), T const w = T(0), T const h = T(0)) noexcept
                : rect_{x, y, w, h} {}

        constexpr Rect(Rect const&) noexcept = default;
        constexpr Rect(Rect&&) noexcept = default;
        constexpr Rect& operator=(Rect const&) noexcept = default;
        constexpr Rect& operator=(Rect&&) noexcept = default;

        constexpr sdl_rect_t const* native_handle() const noexcept { return &rect_; }
        constexpr sdl_rect_t* native_handle() noexcept { return &rect_; }

        constexpr auto const& x() const noexcept { return rect_.x; }
        constexpr auto const& y() const noexcept { return rect_.y; }
        constexpr auto const& w() const noexcept { return rect_.w; }
        constexpr auto const& h() const noexcept { return rect_.h; }

        constexpr auto& x() noexcept { return rect_.x; }
        constexpr auto& y() noexcept { return rect_.y; }
        constexpr auto& w() noexcept { return rect_.w; }
        constexpr auto& h() noexcept { return rect_.h; }

        constexpr auto size() const noexcept { return rect_.w * rect_.h; }

        constexpr xy<T> top_left() const noexcept { return {rect_.x, rect_.y}; };
        constexpr xy<T> top_right() const noexcept { return {rect_.x + rect_.w, rect_.y}; };
        constexpr xy<T> bottom_left() const noexcept { return {rect_.x, rect_.y + rect_.h}; };
        constexpr xy<T> bottom_right() const noexcept { return {rect_.x + rect_.w, rect_.y + rect_.h}; };
        constexpr xy<T> center() const noexcept {
            return {rect_.x + rect_.w / T{2}, rect_.y + rect_.h / T{2}};
        }

        template<std::size_t I>
        constexpr auto& get() noexcept {
            if constexpr (I == 0) return x();
            else if constexpr (I == 1) return y();
            else if constexpr (I == 2) return w();
            else if constexpr (I == 3) return h();
            else static_assert(always_false<T>::value, "invalid sdl2::rect::get<I>() index");
        }

        template<std::size_t I>
        constexpr auto const& get() const noexcept {
            if constexpr (I == 0) return x();
            else if constexpr (I == 1) return y();
            else if constexpr (I == 2) return w();
            else if constexpr (I == 3) return h();
            else static_assert(always_false<T>::value, "invalid sdl2::rect::get<I>() index");
        }

    };

    template<sdl2_shape_rep T>
    class Point {
        using sdl_point_t = std::conditional_t<std::is_same_v<T, int>, SDL_Point, SDL_FPoint>;
        sdl_point_t point_;

    public:
        constexpr Point(sdl_point_t const& p) noexcept
                : point_(p) {}

        constexpr Point(T const x = T(0), T const y = T(0)) noexcept
                : point_{x, y} {}

        constexpr Point(Point const&) noexcept = default;
        constexpr Point(Point&&) noexcept = default;
        constexpr Point& operator=(Point const&) noexcept = default;
        constexpr Point& operator=(Point&&) noexcept = default;

        constexpr sdl_point_t const* native_handle() const noexcept { return &point_; }
        constexpr sdl_point_t* native_handle() noexcept { return &point_; }

        constexpr auto const& x() const noexcept { return point_.x; }
        constexpr auto& x() noexcept { return point_.x; }
        constexpr auto const& y() const noexcept { return point_.y; }
        constexpr auto& y() noexcept { return point_.y; }

        template<std::size_t I>
        constexpr auto& get() noexcept {
            if constexpr (I == 0) return x();
            else if constexpr (I == 1) return y();
            else static_assert(always_false<T>::value, "invalid sdl2::point::get<I>() index");
        }

        template<std::size_t I>
        constexpr auto const& get() const noexcept {
            if constexpr (I == 0) return x();
            else if constexpr (I == 1) return y();
            else static_assert(always_false<T>::value, "invalid sdl2::point::get<I>() index");
        }
    };

}

namespace std {
    template<class T>
    struct tuple_size<TurnEngine::Rect<T>> {
    static constexpr std::size_t value = 4;
};

template<class T>
struct tuple_size<TurnEngine::Point<T>> {
    static constexpr std::size_t value = 2;
};
}