#include <catch2/catch_test_macros.hpp>

#include "../src/math/Shapes.hpp"

using namespace math;

TEST_CASE("Test math::Vector") {
    SECTION("constructor") {
        auto vector = VectorInt(2, 3);
        REQUIRE(vector.x == 2);
        REQUIRE(vector.y == 3);
    }
    SECTION("compare equals") {
        REQUIRE(VectorInt(2, 3) == VectorInt(2, 3));
    }
    SECTION("compare not equals") {
        REQUIRE(VectorInt(2, 3) != VectorInt(3, 2));
    }
    SECTION("unary minus") {
        REQUIRE(-VectorInt(2, 3) == VectorInt(-2, -3));
    }
    SECTION("numeric multiplication") {
        REQUIRE(VectorInt(2, 8) * 4 == VectorInt(8, 32));
    }
    SECTION("vector addition") {
        REQUIRE(VectorInt(2, 8) + VectorInt(8, 2) == VectorInt(10, 10));
    }
    SECTION("vector subtraction") {
        REQUIRE(VectorInt(10, 10) - VectorInt(8, 2) == VectorInt(2, 8));
    }
}

TEST_CASE("Test math::Rectangle") {
    SECTION("Test position-position ok init") {
        auto rect = RectangleInt::init(PositionInt(1, 1), PositionInt(2, 2));
        REQUIRE(rect);
    }
    SECTION("Test position-position error init") {
        auto rect = RectangleInt::init(PositionInt(2, 2), PositionInt(1, 1));
        REQUIRE((!rect && rect.error() == RectangleShapeError::WrongVertices));
    }
    SECTION("Test position-dimensions ok init") {
        auto rect = RectangleInt::init(PositionInt(1, 1), 2, 2);
        REQUIRE(rect);
    }
    SECTION("Test position-dimensions error init") {
        auto rect = RectangleInt::init(PositionInt(2, 2), 0, 0);
        REQUIRE((!rect && rect.error() == RectangleShapeError::WrongDimensions));
    }

    SECTION("Test contains") {
        auto region = RectangleInt::init(PositionInt(100, 150), PositionInt(400, 350)).value();

        std::initializer_list<PositionInt> outside = {
            {0, 0}, {50, 50}, {100, 100}, {450, 400}, {500, 450},
        };
        std::initializer_list<PositionInt> inside = {
            {100, 150}, {400, 150}, {400, 350}, {100, 350}, {250, 250},
        };

        for (auto &point : outside)
            REQUIRE(!region.contains(point));

        for (auto &point : inside)
            REQUIRE(region.contains(point));
    }
}

TEST_CASE("Test math::Hexagon") {
    SECTION("Test position-dimension ok init") {
        auto hexagon = HexagonInt::init(PositionInt(0, 0), 2);
        REQUIRE(hexagon);
    }
    SECTION("Test position-dimension error init") {
        auto hexagon = HexagonInt::init(PositionInt(2, 2), 0);
        REQUIRE((!hexagon && hexagon.error() == HexagonShapeError::WrongSide));
    }

    SECTION("Test contains") {
        auto region = HexagonInt::init(PositionInt(5, 4), 2).value();

        std::initializer_list<math::PositionInt> outside = {
            {3, 2}, {4, 1}, {6, 1}, {7, 2}, {8, 4}, {7, 6}, {6, 7}, {4, 7}, {3, 6}, {2, 4},
        };
        std::initializer_list<math::PositionInt> inside = {
            {4, 3}, {5, 3}, {6, 3}, {4, 4}, {5, 4}, {6, 4}, {4, 5}, {5, 5}, {6, 5},
        };

        for (auto &point : outside)
            REQUIRE(!region.contains(point));

        for (auto &point : inside)
            REQUIRE(region.contains(point));
    }
}