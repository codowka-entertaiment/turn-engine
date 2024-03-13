#pragma once

#include <type_traits>

namespace geo2d
{
    template <typename T>
    concept Numeric = std::is_arithmetic_v<T>;

    /// @brief
    /// Class represents Vector (or Point) and implements operations on it
    template <Numeric T>
    class Vector {
    public:
        T x, y;
        /// @brief
        /// the constructor
        /// @param Numeric x
        /// @param Numeric y
        constexpr Vector(T x, T y) : x(x), y(y){};

        /// @brief
        /// operator ==
        /// @param const Vector &another
        constexpr bool operator==(const Vector &another) const { return this->x == another.x && this->y == another.y; }

        /// @brief
        /// operator !=
        /// @param const Vector &another
        constexpr bool operator!=(const Vector &another) const { return !operator==(another); }

        /// @brief
        /// operator *
        /// @param T vi
        constexpr Vector operator*(T vi) const {
            return {
                vi * this->x,
                vi * this->y,
            };
        }

        /// @brief
        /// operator -
        constexpr Vector operator-() const { return operator*(-1); }

        /// @brief
        /// operator +
        /// @param const Vector &another
        constexpr Vector operator+(const Vector &another) const {
            return {
                this->x + another.x,
                this->y + another.y,
            };
        }

        /// @brief
        /// operator -
        /// @param const Vector &another
        constexpr Vector operator-(const Vector &another) const { return operator+(-another); }
    };

    template <Numeric T>
    using Position = Vector<T>;

    using VectorInt = Vector<int>;
    using PositionInt = Position<int>;
}