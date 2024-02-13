#pragma once

#include "Vector.hpp"

#include <cinttypes>
#include <expected>

namespace math
{
    enum class RectangleShapeError : std::uint8_t {
        WrongVertices,
        NegativeDimensions,
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
                return std::unexpected(RectangleShapeError::NegativeDimensions);
            else
                return Rectangle(vertex, vertex + Position<T>(width, height));
        }

        constexpr bool contains(const Position<T> &position) const override {
            return (m_vertex1.x <= position.x && position.x <= m_vertex2.x) &&
                   (m_vertex1.y <= position.y && position.y <= m_vertex2.y);
        }
    };

    using RectangleInt = Rectangle<int>;
}