#include <catch2/catch.hpp>

#include <yala/vec.h>


using namespace yala;

TEMPLATE_TEST_CASE("vec1 can be accessed with custom accessors", "[vec, vec1]", float, double) {
    SECTION("Reading") {
        constexpr auto x = TestType(17);
        constexpr vec v{x};
        REQUIRE(v[0] == x);
        REQUIRE(v.x() == x);
    }
    SECTION("Writing") {
        vec v{TestType(17)};
        REQUIRE(v.x() == TestType(17));
        v.x(TestType(1));
        REQUIRE(v.x() == TestType(1));
    }
}