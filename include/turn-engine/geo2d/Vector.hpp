#pragma once

#include <type_traits>

namespace geo2d
{
    template <typename T>
    concept Numeric = std::is_arithmetic_v<T>;

    template <Numeric T>
    class Vector {
    public:
        T x, y;
        constexpr Vector(T x, T y) : x(x), y(y){};

        constexpr bool operator==(const Vector &another) const { return this->x == another.x && this->y == another.y; }
        constexpr bool operator!=(const Vector &another) const { return !operator==(another); }

        constexpr Vector operator*(T vi) const {
            return {
                vi * this->x,
                vi * this->y,
            };
        }

        constexpr Vector operator-() const { return operator*(-1); }

        constexpr Vector operator+(const Vector &another) const {
            return {
                this->x + another.x,
                this->y + another.y,
            };
        }

        constexpr Vector operator-(const Vector &another) const { return operator+(-another); }
    };

    template <Numeric T>
    using Position = Vector<T>;

    using VectorInt = Vector<int>;
    using PositionInt = Position<int>;
}