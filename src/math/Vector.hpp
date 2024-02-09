#pragma once

namespace math
{
    class Vector {
    public:
        unsigned int x;
        unsigned int y;

        constexpr Vector(unsigned int x, unsigned int y) : x(x), y(y){};

        constexpr bool operator==(const Vector &another) const { return this->x == another.x && this->y == another.y; }

        constexpr bool operator!=(const Vector &another) const { return !operator==(another); }

        constexpr Vector operator*(unsigned int vi) const {
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

    // may have specific behavior, so let it inherit the vector
    struct Position : public Vector {};
}