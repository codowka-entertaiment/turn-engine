#include <catch2/catch_test_macros.hpp>

#include "../src/math/Vector.hpp"

using math::Vector;

TEST_CASE("Test math::Vector") {
    SECTION("constructor") {
        auto vector = Vector(2, 3);
        REQUIRE(vector.x == 2);
        REQUIRE(vector.y == 3);
    }
    SECTION("compare equals") {
        REQUIRE(Vector(2, 3) == Vector(2, 3));
    }
    SECTION("compare not equals") {
        REQUIRE(Vector(2, 3) != Vector(3, 2));
    }
    SECTION("unary minus") {
        REQUIRE(-Vector(2, 3) == Vector(-2, -3));
    }
    SECTION("numeric multiplication") {
        REQUIRE(Vector(2, 8) * 4 == Vector(8, 32));
    }
    SECTION("vector addition") {
        REQUIRE(Vector(2, 8) + Vector(8, 2) == Vector(10, 10));
    }
    SECTION("vector subtraction") {
        REQUIRE(Vector(10, 10) - Vector(8, 2) == Vector(2, 8));
    }
}