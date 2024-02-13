#include <catch2/catch_test_macros.hpp>

#include "../src/math/Shape.hpp"

using math::PositionInt;
using math::RectangleInt;
using math::ShapeError;
using math::VectorInt;

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
        REQUIRE((!rect && rect.error() == ShapeError::WrongPositions));
    }
    SECTION("Test position-dimensions ok init") {
        auto rect = RectangleInt::init(PositionInt(1, 1), 2, 2);
        REQUIRE(rect);
    }
    SECTION("Test position-dimensions error init") {
        auto rect = RectangleInt::init(PositionInt(2, 2), 0, 0);
        REQUIRE((!rect && rect.error() == ShapeError::WrongDimensions));
    }

    auto region = RectangleInt::init(PositionInt(100, 150), PositionInt(400, 350));

    std::vector<PositionInt> outside = {
        {0, 0}, {50, 50}, {100, 100}, {450, 400}, {500, 450},
    };
    std::vector<PositionInt> inside = {
        {100, 150}, {400, 150}, {400, 350}, {100, 350}, {250, 250},
    };

    for (auto &point : outside)
        REQUIRE(!region->contains(point));

    for (auto &point : inside)
        REQUIRE(region->contains(point));
}