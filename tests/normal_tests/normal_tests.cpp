#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <compare>
#include <yala/normal.h>


using namespace yala;

TEMPLATE_TEST_CASE("normal can be created and accessed", "[vec, normal]", float, double) {
    SECTION("Created with values constructor") {
        constexpr normal<TestType, 6> v{TestType(0), TestType(1), TestType(0),
                                        TestType(0), TestType(0), TestType(0)};
        REQUIRE(v[0] == TestType(0));
        REQUIRE(v[1] == TestType(1));
        REQUIRE(v[2] == TestType(0));
        REQUIRE(v[3] == TestType(0));
        REQUIRE(v[4] == TestType(0));
        REQUIRE(v[5] == TestType(0));
    }
}

TEMPLATE_TEST_CASE("normal is container", "[vec, normal]", float, double) {
    constexpr std::array<TestType, 6> data{TestType(0), TestType(1), TestType(0),
                                           TestType(0), TestType(0), TestType(0)};
    constexpr normal<TestType, 6> v{TestType(0), TestType(1), TestType(0),
                                    TestType(0), TestType(0), TestType(0)};
    REQUIRE(std::equal(std::begin(v), std::end(v), std::begin(data), std::end(data)));
    REQUIRE(6 == v.size());
}

TEMPLATE_TEST_CASE("normal can be compared", "[vec, normal]", float, double) {
    constexpr normal v1{TestType(0), TestType(0), TestType(1), TestType(0)};
    constexpr normal v2{TestType(0), TestType(0), TestType(1), TestType(0)};
    constexpr normal v3{TestType(1), TestType(0), TestType(0), TestType(0)};

    SECTION("Equality") {
        REQUIRE(v1 == v2);
        REQUIRE(v1 != v3);
    }
    SECTION("Less than") {
        REQUIRE(!(v1 < v2));
        REQUIRE(v1 < v3);
    }
    SECTION("Less equal than") {
        REQUIRE(v1 <= v2);
        REQUIRE(v1 <= v3);
        REQUIRE(!(v3 <= v1));
    }
    SECTION("Greater than") {
        REQUIRE(!(v1 > v2));
        REQUIRE(v3 > v1);
    }
    SECTION("Greater equal than") {
        REQUIRE(v1 >= v2);
        REQUIRE(v3 >= v1);
        REQUIRE(!(v1 >= v3));
    }
    SECTION("By ordering") {
        REQUIRE(std::is_eq(v1 <=> v2));
        REQUIRE(std::is_neq(v1 <=> v3));
        REQUIRE(std::is_lt(v1 <=> v3));
        REQUIRE(std::is_gt(v3 <=> v1));
    }
}

TEMPLATE_TEST_CASE("normals are elements of linear space", "[vec, normal]", float, double) {
    SECTION("Can be negated") {
        constexpr normal v1{TestType(1), TestType(0), TestType(0)};
        constexpr normal v2{TestType(-1), TestType(0), TestType(0)};
        REQUIRE(-v1 == v2);
    }
    SECTION("Can be added") {
        constexpr normal v1{TestType(1), TestType(0), TestType(0)};
        constexpr normal v2{TestType(0), TestType(1), TestType(0)};
        constexpr vec v3{TestType(1), TestType(1), TestType(0)};
        constexpr auto sum = v1 + v2;
        REQUIRE(sum == v3);
    }
    SECTION("Can be substracted") {
        constexpr normal v1{TestType(0), TestType(1), TestType(0)};
        constexpr normal v2{TestType(0), TestType(0), TestType(1)};
        constexpr vec v3{TestType(0), TestType(1), TestType(-1)};
        constexpr auto difference = v1 - v2;
        REQUIRE(difference == v3);
    }
    SECTION("Can be multiplied by scalar") {
        constexpr normal v1{TestType(1), TestType(0), TestType(0)};
        constexpr vec v2{TestType(3), TestType(0), TestType(0)};
        constexpr vec r1 = v1 * TestType(3);
        constexpr vec r2 = TestType(3) * v1;
        REQUIRE(r1 == v2);
        REQUIRE(r2 == v2);
    }
    SECTION("Can be divided by scalar") {
        constexpr normal v1{TestType(1), TestType(0), TestType(0)};
        constexpr vec v2{TestType(1.0 / 3.0), TestType(0), TestType(0)};
        constexpr vec r = v1 / TestType(3);
        REQUIRE(r == v2);
    }
    SECTION("Dot product can be calculated") {
        constexpr normal v1{TestType(0), TestType(1), TestType(0),
                            TestType(0), TestType(0), TestType(0)};
        constexpr normal v2{TestType(0), TestType(1), TestType(0),
                            TestType(0), TestType(0), TestType(0)};
        constexpr TestType dot_product = v1 * v2;
        REQUIRE(dot_product == 1);
    }
    SECTION("Squared length can be computed") {
        constexpr normal v1{TestType(0), TestType(1), TestType(0),
                            TestType(0), TestType(0), TestType(0)};
        constexpr auto length_squared = v1.length_squared();
        REQUIRE(length_squared == 1);
    }
    SECTION("Length can be computed") {
        constexpr normal v1{TestType(0), TestType(0), TestType(0),
                            TestType(1), TestType(0), TestType(0)};
        constexpr auto length = v1.length();
        REQUIRE(length == 1);
    }
}
