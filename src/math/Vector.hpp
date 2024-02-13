#pragma once

#include <expected>
#include <type_traits>

namespace math
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
    struct Position : public Vector<T> {
        constexpr Position(T x, T y) : Vector<T>(x, y) {}
        constexpr explicit Position(const Vector<T> &vector) : Vector<T>(vector) {}

        constexpr Position<T> operator+(const Vector<T> &vector) {
            return {
                this->x + vector.x,
                this->y + vector.y,
            };
        }
    };

    using VectorInt = Vector<int>;
    using PositionInt = Position<int>;
}