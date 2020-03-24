#include <catch2/catch.hpp>

#include <yala/normal.h>


using namespace yala;

TEMPLATE_TEST_CASE("normal3 can be accessed with custom accessors", "[vec, vec3, normal, normal3]",
                   float, double) {
    SECTION("Reading") {
        constexpr auto x = TestType(0);
        constexpr auto y = TestType(0);
        constexpr auto z = TestType(1);
        constexpr normal v{x, y, z};
        REQUIRE(v[0] == x);
        REQUIRE(v.x() == x);
        REQUIRE(v[1] == y);
        REQUIRE(v.y() == y);
        REQUIRE(v[2] == z);
        REQUIRE(v.z() == z);
    }
    SECTION("Base vectors") {
        constexpr auto i = normal<TestType, 3>::i();
        REQUIRE(normal{TestType{1}, TestType{0}, TestType{0}} == i);

        constexpr auto j = normal<TestType, 3>::j();
        REQUIRE(normal{TestType{0}, TestType{1}, TestType{0}} == j);

        constexpr auto k = normal<TestType, 3>::k();
        REQUIRE(normal{TestType{0}, TestType{0}, TestType{1}} == k);
    }
    SECTION("Cross product can be calculated") {
        constexpr normal i = normal<TestType, 3>::i();
        constexpr normal j = normal<TestType, 3>::j();
        constexpr normal k = normal<TestType, 3>::k();

        constexpr auto ixj = cross(i, j);
        constexpr auto jxk = cross(j, k);
        constexpr auto kxi = cross(k, i);
        REQUIRE(k == ixj);
        REQUIRE(i == jxk);
        REQUIRE(j == kxi);

        constexpr auto jxi = cross(j, i);
        constexpr auto kxj = cross(k, j);
        constexpr auto ixk = cross(i, k);
        REQUIRE(-k == jxi);
        REQUIRE(-i == kxj);
        REQUIRE(-j == ixk);
    }
}