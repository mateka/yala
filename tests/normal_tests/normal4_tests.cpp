#include <catch2/catch.hpp>

#include <yala/normal.h>


using namespace yala;

TEMPLATE_TEST_CASE("normal4 can be accessed with custom accessors", "[vec, vec4, normal, normal4]",
                   float, double) {
    SECTION("Reading") {
        constexpr auto x = TestType(0);
        constexpr auto y = TestType(1);
        constexpr auto z = TestType(0);
        constexpr auto w = TestType(0);
        constexpr normal v{x, y, z, w};
        REQUIRE(v[0] == x);
        REQUIRE(v.x() == x);
        REQUIRE(v[1] == y);
        REQUIRE(v.y() == y);
        REQUIRE(v[2] == z);
        REQUIRE(v.z() == z);
        REQUIRE(v[3] == w);
        REQUIRE(v.w() == w);
    }
    SECTION("Base vectors") {
        constexpr auto i = normal<TestType, 4>::i();
        REQUIRE(normal{TestType{1}, TestType{0}, TestType{0}, TestType{0}} == i);

        constexpr auto j = normal<TestType, 4>::j();
        REQUIRE(normal{TestType{0}, TestType{1}, TestType{0}, TestType{0}} == j);

        constexpr auto k = normal<TestType, 4>::k();
        REQUIRE(normal{TestType{0}, TestType{0}, TestType{1}, TestType{0}} == k);

        constexpr auto l = normal<TestType, 4>::l();
        REQUIRE(normal{TestType{0}, TestType{0}, TestType{0}, TestType{1}} == l);
    }
}