#pragma once

#include <variant>

namespace ext::types
{
    struct NoneT {};
    constexpr auto None = NoneT();

    template <typename Some>
    class Option : public Enum<Some, NoneT> {
    private:
        using Base = Enum<Some, NoneT>;

    public:
        using Base::Base;
        using Base::operator=;

        [[nodiscard]] constexpr bool is_some() const { return std::holds_alternative<Some>(*this); }
        [[nodiscard]] constexpr bool is_none() const { return std::holds_alternative<NoneT>(*this); }

        constexpr operator bool() const { return is_some(); }  // NOLINT(*-explicit-constructor)
    };

    template <typename X>
    constexpr static X &&unwrap(Option<X> &&option) {
        return std::get<X>(std::move(option));
    }

    template <typename X>
    constexpr static const X &&unwrap(const Option<X> &&option) {
        return std::get<X>(option);
    }
}