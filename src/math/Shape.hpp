#pragma once

#include "Math.hpp"
#include "Vector.hpp"

#include <cinttypes>
#include <expected>
#include <numeric>

namespace math
{
    enum class RectangleShapeError : std::uint8_t {
        WrongVertices,
        WrongDimensions,
    };

    template <Numeric T>
    struct Shape {
        virtual bool contains(const Position<T> &position) const = 0;
    };

    template <Numeric T>
    class Rectangle : public Shape<T> {
    private:
        Position<T> m_vertex1, m_vertex2;
        constexpr Rectangle(Position<T> vertex1, Position<T> vertex2) : m_vertex1(vertex1), m_vertex2(vertex2) {}

    public:
        constexpr static std::expected<Rectangle<T>, RectangleShapeError> init(Position<T> vertex1, Position<T> vertex2) {
            if (vertex2.x <= vertex1.x || vertex2.y <= vertex1.y)
                return std::unexpected(RectangleShapeError::WrongVertices);
            else
                return Rectangle(vertex1, vertex2);
        }

        constexpr static std::expected<Rectangle<T>, RectangleShapeError> init(Position<T> vertex, T width, T height) {
            if (width <= 0 || height <= 0)
                return std::unexpected(RectangleShapeError::WrongDimensions);
            else
                return Rectangle(vertex, vertex + Position<T>(width, height));
        }

        constexpr bool contains(const Position<T> &position) const override {
            return (m_vertex1.x <= position.x && position.x <= m_vertex2.x) &&
                   (m_vertex1.y <= position.y && position.y <= m_vertex2.y);
        }
    };

    using RectangleInt = Rectangle<int>;

    enum class HexagonShapeError : std::uint8_t {
        WrongSide,
    };

    template <Numeric T>
    class Hexagon : public Shape<T> {
    private:
        Position<T> m_center;
        T m_side;
        constexpr Hexagon(Position<T> center, T side) : m_center(center), m_side(side) {}

    public:
        constexpr static std::expected<Hexagon<T>, HexagonShapeError> init(Position<T> center, T side) {
            if (side <= 0)
                return std::unexpected(HexagonShapeError::WrongSide);
            else
                return Hexagon(center, side);
        }

        constexpr bool contains(const Position<T> &position) const override {
            // check point under/upper sides
            auto pos = position - m_center;

            constexpr auto const1 = math::sqrt(3);
            constexpr auto const2 = const1 / 2.0;

            return (pos.y <= +const2 * m_side) &&            // F1
                   (pos.y <= -const1 * (pos.x - m_side)) &&  // F2
                   (pos.y >= +const1 * (pos.x - m_side)) &&  // F3
                   (pos.y >= -const2 * m_side) &&            // F4
                   (pos.y >= -const1 * (pos.x + m_side)) &&  // F5
                   (pos.y <= +const1 * (pos.x + m_side));    // F6
        }
    };

    using HexagonInt = Hexagon<int>;
}