#pragma once

#include "../../ext/Math.hpp"
#include "Shape.hpp"

namespace geo2d
{
    enum class HexagonShapeError : std::uint8_t {
        WrongSide,
    };

    /// @brief
    /// Class represents hexagon shape
    template <Numeric T>
    class Hexagon : public Shape<T> {
    private:
        Position<T> m_center;
        T m_side;
        constexpr Hexagon(Position<T> center, T side) : m_center(center), m_side(side) {}

    public:
        /// @brief
        /// that static method inits hexagon shape with checks
        /// @param Position<T> center
        /// @param T side
        /// @return std::expected<Rectangle<T>, RectangleShapeError>
        constexpr static std::expected<Hexagon<T>, HexagonShapeError> init(Position<T> center, T side) {
            if (side <= 0)
                return std::unexpected(HexagonShapeError::WrongSide);
            else
                return Hexagon(center, side);
        }

        /// @brief
        /// that static method inits hexagon shape without checks
        /// @param Position<T> center
        /// @param T side
        /// @return Hexagon<T>*
        constexpr static Hexagon<T>* init_uncheck(Position<T> center, T side) {  // take away, clang-format
            return new Hexagon(center, side);
        }

        /// @brief
        /// getter for center
        /// @return Position<T>&
        constexpr const Position<T> &center() const { return m_center; }

        /// @brief
        /// getter for side
        /// @return T&
        constexpr const T &side() const { return m_side; }

        /// @brief
        /// that method checks if hexagon shape contains point
        /// @param const Position<T> position
        /// @return `true` if rectangle shape contains point, else `false`
        constexpr bool contains(const Position<T> &position) const noexcept override {
            // check point under/upper sides
            auto pos = position - m_center;

            constexpr auto const1 = ext::math::sqrt(3);
            constexpr auto const2 = const1 / 2.0;
            return (pos.y <= +const2 * m_side) &&            // F1
                   (pos.y <= -const1 * (pos.x - m_side)) &&  // F2
                   (pos.y >= +const1 * (pos.x - m_side)) &&  // F3
                   (pos.y >= -const2 * m_side) &&            // F4
                   (pos.y >= -const1 * (pos.x + m_side)) &&  // F5
                   (pos.y <= +const1 * (pos.x + m_side));    // F6
        }

        /// @brief
        /// setter for position
        /// @param const Position<T> position
        void setPosition(const Position<T>& position) override {
            m_center = position;
        }
    };

    using HexagonInt = Hexagon<int>;
}
