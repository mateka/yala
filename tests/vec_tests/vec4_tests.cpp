#include <catch2/catch.hpp>

#include <yala/vec.h>


using namespace yala;

TEMPLATE_TEST_CASE("vec4 can be accessed with custom accessors", "[vec, vec4]", float, double) {
    SECTION("Reading") {
        constexpr auto x = TestType(17);
        constexpr auto y = TestType(22);
        constexpr auto z = TestType(33);
        constexpr auto w = TestType(44);
        constexpr vec v{x, y, z, w};
        REQUIRE(v[0] == x);
        REQUIRE(v.x() == x);
        REQUIRE(v[1] == y);
        REQUIRE(v.y() == y);
        REQUIRE(v[2] == z);
        REQUIRE(v.z() == z);
        REQUIRE(v[3] == w);
        REQUIRE(v.w() == w);
    }
    SECTION("Writing") {
        vec v{TestType(17), TestType(22), TestType(33), TestType(44)};
        REQUIRE(v.x() == TestType(17));
        REQUIRE(v.y() == TestType(22));
        REQUIRE(v.z() == TestType(33));
        REQUIRE(v.w() == TestType(44));
        v.x(TestType(1));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(22));
        REQUIRE(v.z() == TestType(33));
        REQUIRE(v.w() == TestType(44));
        v.y(TestType(2));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(2));
        REQUIRE(v.z() == TestType(33));
        REQUIRE(v.w() == TestType(44));
        v.z(TestType(3));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(2));
        REQUIRE(v.z() == TestType(3));
        REQUIRE(v.w() == TestType(44));
        v.w(TestType(4));
        REQUIRE(v.x() == TestType(1));
        REQUIRE(v.y() == TestType(2));
        REQUIRE(v.z() == TestType(3));
        REQUIRE(v.w() == TestType(4));
    }
}