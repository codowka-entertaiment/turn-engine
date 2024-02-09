#include <catch2/catch_test_macros.hpp>

#include "../src/math/Vector.hpp"

using math::Vector2i;

TEST_CASE("Test math::Vector") {
    SECTION("constructor") {
        auto vector = Vector2i(2, 3);
        REQUIRE(vector.x == 2);
        REQUIRE(vector.y == 3);
    }
    SECTION("compare equals") {
        REQUIRE(Vector2i(2, 3) == Vector2i(2, 3));
    }
    SECTION("compare not equals") {
        REQUIRE(Vector2i(2, 3) != Vector2i(3, 2));
    }
    SECTION("unary minus") {
        REQUIRE(-Vector2i(2, 3) == Vector2i(-2, -3));
    }
    SECTION("numeric multiplication") {
        REQUIRE(Vector2i(2, 8) * 4 == Vector2i(8, 32));
    }
    SECTION("vector addition") {
        REQUIRE(Vector2i(2, 8) + Vector2i(8, 2) == Vector2i(10, 10));
    }
    SECTION("vector subtraction") {
        REQUIRE(Vector2i(10, 10) - Vector2i(8, 2) == Vector2i(2, 8));
    }
}