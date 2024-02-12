#pragma once

#include "Vector.hpp"

#include <cinttypes>
#include <expected>

namespace math
{
    enum class ShapeError : std::uint8_t {
        WrongPositions,
        WrongDimensions,
    };

    template <Numeric T>
    struct Shape {
        virtual bool contains(const Position<T> &position) const = 0;
    };

    template <Numeric T>
    class Rectangle : public Shape<T> {
    private:
        Position<T> m_pos1, m_pos2;

        constexpr Rectangle(Position<T> pos1, Position<T> pos2) : m_pos1(pos1), m_pos2(pos2) {}
        constexpr Rectangle(Position<T> pos1, Dimensions<T> dims) : m_pos1(pos1), m_pos2(pos1 + dims) {}

    public:
        constexpr static std::expected<Rectangle<T>, ShapeError> init(Position<T> pos1, Position<T> pos2) {
            if (pos2.x <= pos1.x || pos2.y <= pos1.y)
                return std::unexpected(ShapeError::WrongPositions);
            else
                return Rectangle(pos1, pos2);
        }

        constexpr static std::expected<Rectangle<T>, ShapeError> init(Position<T> pos1, Dimensions<T> dims) {
            if (dims.x <= 0 || dims.y <= 0)
                return std::unexpected(ShapeError::WrongDimensions);
            else
                return Rectangle(pos1, dims);
        }

        constexpr bool contains(const Position<T> &position) const override {
            return m_pos1.x <= position.x && position.x <= m_pos2.x && m_pos1.y <= position.y && position.y <= m_pos2.y;
        }
    };

    using RectangleInt = Rectangle<int>;
}