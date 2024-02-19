#include <catch2/catch_test_macros.hpp>

#include "../include/turn-engine/ext/Types.hpp"

using namespace ext::types;

TEST_CASE("Test ext::types::Enum") {
    SECTION("test match") {
        Enum<int, double> enum1 = 4;
        Enum<int, double> enum2 = 3.14;

        constexpr auto case1 = [&](const int &) {
            return 1;
        };
        constexpr auto case2 = [&](const double &) {
            return 2;
        };

        REQUIRE(match(enum1, case1, case2) == 1);
        REQUIRE(match(enum2, case1, case2) == 2);
    }
}

TEST_CASE("Test ext::types::Option") {
    SECTION("init some") {
        Option<int> option = 3;
        REQUIRE(option.is_some());
        REQUIRE_NOTHROW(unwrap(std::move(option)));
    }
    SECTION("init none") {
        Option<int> option = None;
        REQUIRE(option.is_none());
        REQUIRE_THROWS(unwrap(std::move(option)));
    }
}

TEST_CASE("Test ext::types::Result") {
    SECTION("init ok") {
        Result<double, int> result = 3.14;
        REQUIRE(result.is_ok());
        REQUIRE_NOTHROW(unwrap(std::move(result)));
    }
    SECTION("init error") {
        Result<double, int> result = 4;
        REQUIRE(result.is_err());
        REQUIRE_NOTHROW(unwrap_err(std::move(result)));
    }
}