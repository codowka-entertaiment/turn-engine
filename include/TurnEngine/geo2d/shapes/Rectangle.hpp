#pragma once

#include "Shape.hpp"

namespace geo2d
{
    enum class RectangleShapeError : std::uint8_t {
        WrongVertices,
        WrongDimensions,
    };

    /// @brief
    /// Class representing rectangle shape
    template <Numeric T>
    class Rectangle : public Shape<T> {
    protected:
        Position<T> m_vertex;
        T m_width, m_height;

        constexpr Rectangle(Position<T> vertex, Position<T> dims) : m_vertex(vertex), m_width(dims.x), m_height(dims.y) {}
        constexpr Rectangle(Position<T> vertex, T width, T height) : m_vertex(vertex), m_width(width), m_height(height) {}

    public:
        /// @brief
        /// that static method inits rectangle shape with checks
        /// @param Position<T> vertex1
        /// @param Position<T> vertex2
        /// @return std::expected<Rectangle<T>, RectangleShapeError>
        constexpr static std::expected<Rectangle<T>, RectangleShapeError> init(Position<T> vertex1, Position<T> vertex2) {
            if (vertex2.x <= vertex1.x || vertex2.y <= vertex1.y)
                return std::unexpected(RectangleShapeError::WrongVertices);
            else
                return Rectangle(vertex1, vertex2 - vertex1);
        }

        /// @brief
        /// that static method inits rectangle shape with checks
        /// @param Position<T> vertex
        /// @param T width
        /// @param T height
        /// @return std::expected<Rectangle<T>, RectangleShapeError>
        constexpr static std::expected<Rectangle<T>, RectangleShapeError> init(Position<T> vertex, T width, T height) {
            if (width <= 0 || height <= 0)
                return std::unexpected(RectangleShapeError::WrongDimensions);
            else
                return Rectangle(vertex, width, height);
        }

        /// @brief
        /// that static method inits rectangle shape without checks
        /// @param Position<T> vertex1
        /// @param Position<T> vertex2
        /// @return Rectangle<T>*
        constexpr static Rectangle<T>* init_uncheck(Position<T> vertex1, Position<T> vertex2) {
            return new Rectangle(vertex1, vertex2 - vertex1);
        }

        /// @brief
        /// that static method inits rectangle shape without checks
        /// @param Position<T> vertex
        /// @param T width
        /// @param T height
        /// @return Rectangle<T>*
        constexpr static Rectangle<T>* init_uncheck(Position<T> vertex, T width, T height) {
            return new Rectangle(vertex, width, height);
        }

        /// @brief
        /// getter for vertex
        /// @return Position<T>&
        constexpr const Position<T> &vertex() const { return m_vertex; }

        /// @brief
        /// getter for width
        /// @return Position<T>&
        constexpr const T &width() const { return m_width; }

        /// @brief
        /// getter for height
        /// @return Position<T>&
        constexpr const T &height() const { return m_height; }

        /// @brief
        /// that method checks if rectangle shape contains point
        /// @param const Position<T> position
        /// @return `true` if rectangle shape contains point, else `false`
        constexpr bool contains(const Position<T> &position) const noexcept override {
            auto pos = position - m_vertex;
            return (pos.x > 0 && pos.x < m_width) && (pos.y > 0 && pos.y < m_height);
        }

        /// @brief
        /// setter for position
        /// @param const Position<T> position
        void setPosition(const Position<T> &position) override {
            m_vertex = position;
        }
    };

    using RectangleInt = Rectangle<int>;
}