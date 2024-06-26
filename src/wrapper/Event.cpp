#include "TurnEngine/wrapper/Event.hpp"

using namespace TurnEngine;

bool event_queue_t::has(SDL_EventType const type) noexcept {
    return SDL_HasEvent(type) == SDL_TRUE;
}

bool event_queue_t::has(SDL_EventType const min, SDL_EventType const max) noexcept {
    return SDL_HasEvents(min, max) == SDL_TRUE;
}

void event_queue_t::pump() noexcept {
    SDL_PumpEvents();
}

std::optional<SDL_Event> event_queue_t::poll() noexcept {
    SDL_Event e{};
    if (SDL_PollEvent(&e))
        return e;
    return {};
}

event_queue_t::push_result event_queue_t::push(SDL_Event& e) noexcept {
    return static_cast<event_queue_t::push_result>(SDL_PushEvent(&e));
}

event_queue_t::push_result event_queue_t::push(SDL_Event&& e) noexcept {
    return static_cast<event_queue_t::push_result>(SDL_PushEvent(&e));
}

std::optional<std::size_t> event_queue_t::add(std::span<SDL_Event> const events) noexcept {
    if (auto const num = SDL_PeepEvents(events.data(), events.size(), SDL_ADDEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT); num >= 0)
        return static_cast<std::size_t>(num);
    return {};
}

std::optional<SDL_Event> event_queue_t::wait() noexcept {
    SDL_Event e{};
    if (SDL_WaitEvent(&e))
        return e;
    return {};
}

void event_queue_t::flush(SDL_EventType const type) noexcept {
    SDL_FlushEvent(type);
}

void event_queue_t::flush(SDL_EventType const min, SDL_EventType const max) noexcept {
    SDL_FlushEvents(min, max);
}

event_queue_t::event_state event_queue_t::get_event_state(SDL_EventType const type) noexcept {
    return static_cast<event_queue_t::event_state>(SDL_GetEventState(type));
}

event_queue_t::event_state event_queue_t::set_event_state(SDL_EventType const type, event_queue_t::event_state const state) noexcept {
    return static_cast<event_queue_t::event_state>(SDL_EventState(type, static_cast<int>(state)));
}

bool event_queue_t::quit_requested() noexcept {
    return SDL_QuitRequested() == SDL_TRUE;
}

/*
function_ref<bool(SDL_Event&)> event_queue_t::get_event_filter() noexcept {
    SDL_EventFilter filter;
    void* userdata;
    if (SDL_GetEventFilter(&filter, &userdata) == SDL_TRUE)
        return *static_cast<function_ref<bool(SDL_Event&)>*>(userdata);
    return {};
}
*/

std::span<std::uint8_t const, NUM_SCANCODES> keyboard_t::state() noexcept {
    return std::span<std::uint8_t const, NUM_SCANCODES>{SDL_GetKeyboardState(nullptr), NUM_SCANCODES};
}

SDL_Keymod keyboard_t::mod_state() noexcept {
    return SDL_GetModState();
}

void keyboard_t::set_mod_state(SDL_Keymod const mod) noexcept {
    SDL_SetModState(mod);
}

bool keyboard_t::has_screen_support() noexcept {
    return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
}

bool keyboard_t::is_screen_shown(Window const& win) noexcept {
    return SDL_IsScreenKeyboardShown(win.native_handle()) == SDL_TRUE;
}

int touch_t::num_devices() noexcept {
    return SDL_GetNumTouchDevices();
}

int touch_t::num_fingers(SDL_TouchID const id) noexcept {
    return SDL_GetNumTouchFingers(id);
}

SDL_TouchID touch_t::get_device(int const index) noexcept {
    return SDL_GetTouchDevice(index);
}

optional_ref<SDL_Finger> touch_t::get_finger(SDL_TouchID const id, int const index) noexcept {
    if (auto const finger = SDL_GetTouchFinger(id, index); finger != nullptr)
        return *finger;
    return {};
}

bool touch_t::record_gesture(SDL_TouchID const id) noexcept {
    return SDL_RecordGesture(id) == 1;
}

bool touch_t::record_all_gestures() noexcept {
    return SDL_RecordGesture(-1) == 1;
}

int touch_t::load_dollar_templates(SDL_TouchID const id, SDL_RWops& src) noexcept {
    return SDL_LoadDollarTemplates(id, &src);
}

int touch_t::save_all_dollar_templates(SDL_RWops& dst) noexcept {
    return SDL_SaveAllDollarTemplates(&dst);
}

bool touch_t::save_dollar_template(SDL_GestureID const id, SDL_RWops& dst) noexcept {
    return SDL_SaveDollarTemplate(id, &dst) == 1;
}