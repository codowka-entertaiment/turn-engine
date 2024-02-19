#pragma once

#include <variant>

namespace ext::types
{
    template <typename... Types>
    class Enum : public std::variant<Types...> {
    private:
        using Base = std::variant<Types...>;

        using Base::index;
        using Base::valueless_by_exception;

        using Base::emplace;
        using Base::swap;

    public:
        constexpr Enum(const Enum &other) : Base(other) {}
        constexpr Enum(Enum &&other) noexcept : Base(other) {}

        template <class T>
        constexpr Enum(T &&t) noexcept : Base(t) {}
    };

    template <class... Ts>
    struct overloaded : Ts... {
        using Ts::operator()...;
    };

    template <class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;

    template <typename Val, typename... Ts>
    constexpr auto match(Val val, Ts... ts) {
        return std::visit(overloaded{ts...}, val);
    }
}

namespace std
{
    template <typename... L>
    struct variant_size<ext::types::Enum<L...>> : variant_size<typename ext::types::Enum<L...>::variant> {};

    template <std::size_t I, typename... L>
    struct variant_alternative<I, ext::types::Enum<L...>> : variant_alternative<I, typename ext::types::Enum<L...>::variant> {};
}
