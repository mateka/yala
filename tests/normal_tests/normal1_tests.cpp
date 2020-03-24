#include <catch2/catch.hpp>

#include <yala/normal.h>


using namespace yala;

TEMPLATE_TEST_CASE("normal1 can be accessed with custom accessors", "[vec, vec1, normal, normal1]",
                   float, double) {
    SECTION("Reading") {
        constexpr auto x = TestType(1);
        normal v{x};
        REQUIRE(v[0] == x);
        REQUIRE(v.x() == x);
    }
    SECTION("Base vectors") {
        constexpr auto i = normal<TestType, 1>::i();
        REQUIRE(normal{TestType{1}} == i);
    }
}