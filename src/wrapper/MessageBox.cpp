#include "TurnEngine/wrapper/MessageBox.hpp"

using namespace TurnEngine;

constexpr MessageBox::MessageBox(MessageBoxFlags const flgs, std::span<SDL_MessageBoxButtonData const> const buttons, null_term_string const title,
                                 null_term_string const message) noexcept
        : data_{.flags = static_cast<std::uint32_t>(flgs),
        .window = nullptr,
        .title = title.data(),
        .message = message.data(),
        .numbuttons = static_cast<int>(buttons.size()),
        .buttons = buttons.data(),
        .colorScheme = nullptr}
{}

constexpr MessageBox::MessageBox(MessageBoxFlags const flgs, std::span<SDL_MessageBoxButtonData const> const buttons, null_term_string const title,
                                 null_term_string const message, Window const& win) noexcept
        : data_{.flags = static_cast<std::uint32_t>(flgs),
        .window = win.native_handle(),
        .title = title.data(),
        .message = message.data(),
        .numbuttons = static_cast<int>(buttons.size()),
        .buttons = buttons.data(),
        .colorScheme = nullptr}
{}

constexpr MessageBox::MessageBox(MessageBoxFlags const flgs, std::span<SDL_MessageBoxButtonData const> const buttons, null_term_string const title,
                                 null_term_string const message, std::span<SDL_MessageBoxColorScheme const> const scheme) noexcept
        : data_{.flags = static_cast<std::uint32_t>(flgs),
        .window = nullptr,
        .title = title.data(),
        .message = message.data(),
        .numbuttons = static_cast<int>(buttons.size()),
        .buttons = buttons.data(),
        .colorScheme = scheme.data()}
{}

template<std::size_t N>
constexpr MessageBox::MessageBox(MessageBoxFlags const flgs, std::span<SDL_MessageBoxButtonData const, N> const buttons, null_term_string const title,
                                 null_term_string const message, Window const& win, std::span<SDL_MessageBoxColorScheme const, N> const scheme) noexcept
        : data_{.flags = static_cast<std::uint32_t>(flgs),
        .window = win.native_handle(),
        .title = title.data(),
        .message = message.data(),
        .numbuttons = static_cast<int>(buttons.size()),
        .buttons = buttons.data(),
        .colorScheme = scheme.data()}
{}