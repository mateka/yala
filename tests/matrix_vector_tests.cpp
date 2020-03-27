#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <yala/matrix.h>
#include <yala/matrix_vector.h>
#include <yala/normal.h>
#include <yala/vec.h>


using namespace yala;

TEMPLATE_TEST_CASE("one dimensional matrix and vector can be used interchangeably",
                   "[matrix, vec]", float, double) {
    SECTION("Vector from matrices") {
        constexpr matrix<TestType, 3, 1> m1{TestType(1), TestType(2), TestType(3)};
        constexpr matrix<TestType, 1, 3> m2{TestType(1), TestType(2), TestType(3)};

        constexpr vec<TestType, 3> v1{m1};
        constexpr vec<TestType, 3> v2{m2};
        constexpr vec<TestType, 3> expected{TestType(1), TestType(2), TestType(3)};

        REQUIRE(v1 == expected);
        REQUIRE(v2 == expected);
    }

    SECTION("Matrix from vector") {
        constexpr vec<TestType, 3> v{TestType(1), TestType(2), TestType(3)};
        constexpr matrix<TestType, 3, 1> m{v};
        constexpr matrix<TestType, 3, 1> expected{TestType(1), TestType(2), TestType(3)};

        REQUIRE(m == expected);
    }

    SECTION("Multiplying matrix by vector") {
        constexpr vec v{TestType(1), TestType(2), TestType(3)};
        constexpr matrix<TestType, 3, 3> m{TestType(10),   TestType(20),   TestType(30),
                                           TestType(100),  TestType(200),  TestType(300),
                                           TestType(1000), TestType(2000), TestType(3000)};
        constexpr vec<TestType, 3> result = m * v;
        constexpr vec expected{TestType(140), TestType(1400), TestType(14000)};
        REQUIRE(result == expected);
    }

    SECTION("Multiplying vector by matrix") {
        constexpr vec v{TestType(1), TestType(2), TestType(3)};
        constexpr matrix<TestType, 3, 3> m{TestType(10),   TestType(20),   TestType(30),
                                           TestType(100),  TestType(200),  TestType(300),
                                           TestType(1000), TestType(2000), TestType(3000)};
        constexpr vec<TestType, 3> result = v * m;
        constexpr vec expected{TestType(3210), TestType(6420), TestType(9630)};
        REQUIRE(result == expected);
    }
}


TEMPLATE_TEST_CASE("one dimensional matrix and normal can be used interchangeably",
                   "[matrix, vec, normal]", float, double) {
    SECTION("Normal from matrices") {
        constexpr matrix<TestType, 3, 1> m1{TestType(0), TestType(3.0 / 5.0), TestType(4.0 / 5.0)};
        constexpr matrix<TestType, 1, 3> m2{TestType(0), TestType(3.0 / 5.0), TestType(4.0 / 5.0)};

        constexpr normal<TestType, 3> v1{m1};
        constexpr normal<TestType, 3> v2{m2};
        constexpr normal<TestType, 3> expected{TestType(0), TestType(3.0 / 5.0),
                                               TestType(4.0 / 5.0)};

        REQUIRE(v1 == expected);
        REQUIRE(v2 == expected);
    }

    SECTION("Matrix from normal") {
        constexpr normal<TestType, 3> v{TestType(0), TestType(3.0 / 5.0), TestType(4.0 / 5.0)};
        constexpr matrix<TestType, 3, 1> m{v};
        constexpr matrix<TestType, 3, 1> expected{TestType(0), TestType(3.0 / 5.0),
                                                  TestType(4.0 / 5.0)};

        REQUIRE(m == expected);
    }

    SECTION("Multiplying matrix by normal") {
        constexpr normal v{TestType(0), TestType(3.0 / 5.0), TestType(4.0 / 5.0)};
        constexpr matrix<TestType, 3, 3> m{TestType(10),   TestType(20),   TestType(30),
                                           TestType(100),  TestType(200),  TestType(300),
                                           TestType(1000), TestType(2000), TestType(3000)};
        constexpr vec<TestType, 3> result = m * v;
        constexpr vec expected{TestType(36), TestType(360), TestType(3600)};
        REQUIRE(result == expected);
    }

    SECTION("Multiplying normal by matrix") {
        constexpr normal v{TestType(0), TestType(3.0 / 5.0), TestType(4.0 / 5.0)};
        constexpr matrix<TestType, 3, 3> m{TestType(10),   TestType(20),   TestType(30),
                                           TestType(100),  TestType(200),  TestType(300),
                                           TestType(1000), TestType(2000), TestType(3000)};
        constexpr vec<TestType, 3> result = v * m;
        constexpr vec expected{TestType(860), TestType(1720), TestType(2580)};
        REQUIRE(result == expected);
    }
}
