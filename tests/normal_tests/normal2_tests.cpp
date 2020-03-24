#include <catch2/catch.hpp>

#include <yala/normal.h>


using namespace yala;

TEMPLATE_TEST_CASE("normal2 can be accessed with custom accessors", "[vec, vec2, normal, normal2]",
                   float, double) {
    SECTION("Reading") {
        constexpr auto x = TestType(0);
        constexpr auto y = TestType(1);
        constexpr normal v{x, y};
        REQUIRE(v[0] == x);
        REQUIRE(v.x() == x);
        REQUIRE(v[1] == y);
        REQUIRE(v.y() == y);
    }
    SECTION("Base vectors") {
        constexpr auto i = normal<TestType, 2>::i();
        REQUIRE(normal{TestType{1}, TestType{0}} == i);

        constexpr auto j = normal<TestType, 2>::j();
        REQUIRE(normal{TestType{0}, TestType{1}} == j);
    }
    SECTION("Perpendicular vector can be found in 2D") {
        constexpr normal v{TestType(3.0 / 5.0), TestType(4.0 / 5.0)};
        REQUIRE(perpendicular(v) == vec{TestType(4.0 / 5.0), -TestType(3.0 / 5.0)});
    }
}