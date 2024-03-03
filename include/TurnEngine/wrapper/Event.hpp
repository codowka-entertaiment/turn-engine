#pragma once

#include "SDL2/SDL.h"

#include <chrono>
#include <concepts>
#include <optional>
#include <span>

#include "Utils.hpp"
#include "Window.hpp"

namespace TurnEngine {

    template<class It, class Sent>
    concept sdl_event_output_pair = std::contiguous_iterator<It> && std::output_iterator<It, SDL_Event> && std::sentinel_for<It, Sent>;

    struct event_queue_t {

        constexpr explicit event_queue_t() noexcept = default;

        static bool has(SDL_EventType type) noexcept;

        static bool has(SDL_EventType min, SDL_EventType max) noexcept;

        static void pump() noexcept;

        static std::optional<SDL_Event> poll() noexcept;

        enum class push_result : int {
            SUCCESS = 1, FILTERED = 0, FAILED = -1,
        };

        static push_result push(SDL_Event& e) noexcept;

        static push_result push(SDL_Event&& e) noexcept;

        static std::optional<std::size_t> add(std::span<SDL_Event> events) noexcept;

        template<class It, class Sent>
        requires sdl_event_output_pair<It, Sent>
        static It peek(It first, Sent last, SDL_EventType min = SDL_FIRSTEVENT, SDL_EventType max = SDL_LASTEVENT) noexcept;

        template<class It, class Sent>
        requires sdl_event_output_pair<It, Sent>
        static It remove(It first, Sent last, SDL_EventType min = SDL_FIRSTEVENT, SDL_EventType max = SDL_LASTEVENT) noexcept;

        static std::optional<SDL_Event> wait() noexcept;

        template<class Rep, class Period>
        static std::optional<SDL_Event> wait_for(std::chrono::duration<Rep, Period> const& dur) noexcept;

        template<class Clock, class Dur>
        static std::optional<SDL_Event> wait_until(std::chrono::time_point<Clock, Dur> const& tp) noexcept;

        struct sentinel {};

        class iterator {
            SDL_Event e_{};
            bool done_ = false;

            friend class event_queue_t;

            explicit iterator() noexcept
                    : done_(SDL_PollEvent(&e_) == 0) {}

        public:
            using value_type = SDL_Event;
            using reference = SDL_Event&;
            using pointer = SDL_Event*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::input_iterator_tag;

            constexpr SDL_Event& operator*() noexcept {
                return e_;
            }

            constexpr SDL_Event* operator->() noexcept {
                return &e_;
            }

            iterator& operator++() noexcept {
                done_ = (SDL_PollEvent(&e_) == 0);
                return *this;
            }

            constexpr bool operator!=(sentinel) const noexcept {
                return !done_;
            }
        };

        static iterator begin() noexcept { return iterator{}; }

        constexpr static sentinel end() noexcept { return {}; }

        static void flush(SDL_EventType type) noexcept;

        static void flush(SDL_EventType min, SDL_EventType max) noexcept;

        enum class event_state : bool {
            ENABLED = SDL_ENABLE,
            DISABLED = SDL_DISABLE,
        };

        static event_state get_event_state(SDL_EventType type) noexcept;

        static event_state set_event_state(SDL_EventType type, event_state state) noexcept;

        static bool quit_requested() noexcept;

        template<class F>
        requires invocable_r<void, F, SDL_Event&>
        static void add_event_watch(F& callback) noexcept;

        template<class F>
        requires invocable_r<void, F, SDL_Event&>
        static void del_event_watch(F& callback) noexcept;

        template<class F>
        requires invocable_r<bool, F, SDL_Event&>
        static void set_event_filter(F& callback) noexcept;

        template<class F>
        requires invocable_r<bool, F, SDL_Event&>
        static void filter_events(F&& fn) noexcept;
    };

    inline constexpr event_queue_t event_queue{};

    static constexpr std::size_t NUM_SCANCODES = SDL_NUM_SCANCODES;

    struct keyboard_t {

        constexpr explicit keyboard_t() noexcept = default;

        static std::span<std::uint8_t const, NUM_SCANCODES> state() noexcept;

        static SDL_Keymod mod_state() noexcept;

        static void set_mod_state(SDL_Keymod mod) noexcept;

        static bool has_screen_support() noexcept;

        static bool is_screen_shown(Window const& win) noexcept;
    };

    inline constexpr keyboard_t keyboard{};

    struct touch_t {

        constexpr explicit touch_t() noexcept = default;

        static int num_devices() noexcept;

        static int num_fingers(SDL_TouchID id) noexcept;

        static SDL_TouchID get_device(int index) noexcept;

        static optional_ref<SDL_Finger> get_finger(SDL_TouchID id, int index) noexcept;

        static bool record_gesture(SDL_TouchID id) noexcept;

        static bool record_all_gestures() noexcept;

        static int load_dollar_templates(SDL_TouchID id, SDL_RWops& src) noexcept;

        static int save_all_dollar_templates(SDL_RWops& dst) noexcept;

        static bool save_dollar_template(SDL_GestureID id, SDL_RWops& dst) noexcept;

    };

    inline constexpr touch_t touch{};

    template<class It, class Sent>
    requires sdl_event_output_pair<It, Sent>
    It event_queue_t::peek(It const first, Sent const last, SDL_EventType const min, SDL_EventType const max) noexcept {
        auto const num_events = SDL_PeepEvents(std::to_address(first), std::distance(first, last), SDL_PEEKEVENT, min, max);
        return num_events > 0 ? first + num_events : first;
    }

    template<class It, class Sent>
    requires sdl_event_output_pair<It, Sent>
    It event_queue_t::remove(It const first, Sent const last, SDL_EventType const min, SDL_EventType const max) noexcept {
        auto const num_events = SDL_PeepEvents(std::to_address(first), std::distance(first, last), SDL_GETEVENT, min, max);
        return num_events > 0 ? first + num_events : first;
    }

    template<class Rep, class Period>
    std::optional<SDL_Event> event_queue_t::wait_for(std::chrono::duration<Rep, Period> const& dur) noexcept {
        using sdl_dur_t = std::chrono::duration<int, std::milli>;
        SDL_Event e{};
        if (SDL_WaitEventTimeout(&e, std::chrono::round<sdl_dur_t>(dur).count()))
            return e;
        return {};
    }

    template<class Clock, class Dur>
    std::optional<SDL_Event> event_queue_t::wait_until(std::chrono::time_point<Clock, Dur> const& tp) noexcept {
        auto const now = std::chrono::time_point_cast<decltype(tp)>(Clock::now());
        if (tp < now)
            return {};
        return wait_for(tp - now);
    }

    namespace detail {

        template<class F>
        constexpr static int _event_watch_impl(void* fn, SDL_Event* event) noexcept(std::is_nothrow_invocable_r_v<void, F, SDL_Event&>) {
            (*static_cast<F*>(fn))(*event);
            return 0;
        }

        template<class F>
        constexpr static int _event_filter_impl(void* fn, SDL_Event* event) noexcept(std::is_nothrow_invocable_r_v<bool, F, SDL_Event&>) {
            return static_cast<int>((*static_cast<F*>(fn))(*event));
        }

    }

    template<class F>
    requires invocable_r<void, F, SDL_Event&>
    void event_queue_t::add_event_watch(F& fn) noexcept {
        SDL_AddEventWatch(detail::_event_watch_impl<F>, std::addressof(fn));
    }

    template<class F>
    requires invocable_r<void, F, SDL_Event&>
    void event_queue_t::del_event_watch(F& fn) noexcept {
        SDL_DelEventWatch(detail::_event_watch_impl<F>, std::addressof(fn));
    }

    template<class F>
    requires invocable_r<bool, F, SDL_Event&>
    void event_queue_t::set_event_filter(F& fn) noexcept {
        SDL_SetEventFilter(detail::_event_filter_impl<F>, std::addressof(fn));
    }

    template<class F>
    requires invocable_r<bool, F, SDL_Event&>
    void event_queue_t::filter_events(F&& fn) noexcept {
        SDL_FilterEvents(detail::_event_filter_impl<F>, std::addressof(fn));
    }

}