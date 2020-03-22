#include <catch2/catch.hpp>

#include <yala/vec.h>


using namespace yala;

TEMPLATE_TEST_CASE("vec3 can be accessed with custom accessors", "[vec, vec3]", float, double) {
    SECTION("Reading") {
        constexpr auto x = TestType(17);
        constexpr auto y = TestType(22);
        constexpr auto z = TestType(33);
        constexpr vec v{x, y, z};
        REQUIRE(v[0] == x);
        REQUIRE(v.x() == x);
        REQUIRE(v[1] == y);
        REQUIRE(v.y() == y);
        REQUIRE(v[2] == z);
        REQUIRE(v.z() == z);
    }
    SECTION("Writing") {
        vec v{TestType(17), TestType(22), TestType(33)};
        REQUIRE(v.x() == TestType(17));
        REQUIRE(v.y() == TestType(22));
        REQUIRE(v.z() == TestType(33));
        v.x(TestType(1));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(22));
        REQUIRE(v.z() == TestType(33));
        v.y(TestType(2));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(2));
        REQUIRE(v.z() == TestType(33));
        v.z(TestType(3));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(2));
        REQUIRE(v.z() == TestType(3));
    }
    SECTION("Cross product can be calculated") {
        constexpr vec i = {TestType(1), TestType(0), TestType(0)};
        constexpr vec j = {TestType(0), TestType(1), TestType(0)};
        constexpr vec k = {TestType(0), TestType(0), TestType(1)};

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

        constexpr vec u = {TestType(1), TestType(1), TestType(3)};
        constexpr vec v = {TestType(0), TestType(2), TestType(-3)};
        constexpr auto uxv = cross(u, v);
        REQUIRE(vec{TestType(-9), TestType(3), TestType(2)} == uxv);
    }
}