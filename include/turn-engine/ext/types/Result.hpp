#pragma once

#include "Enum.hpp"

namespace ext::types
{
    template <typename Ok, typename Error>
    class Result : public Enum<Ok, Error> {
    private:
        using Base = Enum<Ok, Error>;

    public:
        using Base::Base;
        using Base::operator=;

        [[nodiscard]] constexpr bool is_ok() const { return std::holds_alternative<Ok>(*this); }
        [[nodiscard]] constexpr bool is_err() const { return std::holds_alternative<Error>(*this); }

        constexpr operator bool() const { return is_ok(); }  // NOLINT(*-explicit-constructor)
    };

    template <typename X, typename Y>
    constexpr static X &&unwrap(Result<X, Y> &&result) {
        return std::get<X>(std::move(result));
    }

    template <typename X, typename Y>
    constexpr static const X &&unwrap(const Result<X, Y> &&result) {
        return std::get<X>(result);
    }

    template <typename X, typename Y>
    constexpr static Y &&unwrap_err(Result<X, Y> &&result) {
        return std::get<Y>(std::move(result));
    }

    template <typename X, typename Y>
    constexpr static const Y &&unwrap_err(const Result<X, Y> &&result) {
        return std::get<Y>(result);
    }
}