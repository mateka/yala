#include <catch2/catch.hpp>

#include <yala/vec.h>


using namespace yala;

TEMPLATE_TEST_CASE("vec2 can be accessed with custom accessors", "[vec, vec2]", float, double) {
    SECTION("Reading") {
        constexpr auto x = TestType(17);
        constexpr auto y = TestType(22);
        constexpr vec v{x, y};
        REQUIRE(v[0] == x);
        REQUIRE(v.x() == x);
        REQUIRE(v[1] == y);
        REQUIRE(v.y() == y);
    }
    SECTION("Writing") {
        vec v{TestType(17), TestType(22)};
        REQUIRE(v.x() == TestType(17));
        REQUIRE(v.y() == TestType(22));
        v.x(TestType(1));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(22));
        v.y(TestType(2));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(2));
    }
    SECTION("Perpendicular vector can be found in 2D") {
        constexpr vec v{TestType(3), TestType(4)};
        REQUIRE(perpendicular(v) == vec{TestType(4), -TestType(3)});
    }
}