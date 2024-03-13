#pragma once

#include "../Vector.hpp"

#include <cinttypes>
#include <expected>

namespace geo2d {
    /// @brief
    /// Abstract class for implementing shapes
    template<Numeric T>
    struct Shape {

        /// @brief
        /// that method checks if shape contains point
        /// @param const Position<T> position
        constexpr virtual bool contains(const Position<T> &position) const noexcept = 0;

        /// @brief
        /// setter for position
        /// @param const Position<T> position
        virtual void setPosition(const Position<T> &position) = 0;
    };
}