#pragma once

#include "../../ext/Math.hpp"
#include "Shape.hpp"

namespace geo2d
{
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

        constexpr static Hexagon<T>* init_uncheck(Position<T> center, T side) {  // take away, clang-format
            return new Hexagon(center, side);
        }

        constexpr const Position<T> &center() const { return m_center; }
        constexpr const T &side() const { return m_side; }

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
    };

    using HexagonInt = Hexagon<int>;
}
