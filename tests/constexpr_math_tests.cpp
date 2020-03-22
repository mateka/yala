#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <compare>
#include <yala/constexpr_math.h>

namespace {
template<typename T>
constexpr auto const pi = T{3.1415};
}


TEMPLATE_TEST_CASE("Calculating pow", "[math, pow]", float, double) {
    SECTION("Anything to power 0 is 1") {
        constexpr TestType _2e0 = yala::pow(TestType{2}, 0u);
        REQUIRE(TestType{1} == _2e0);

        constexpr TestType _3_1415e0 = yala::pow(pi<TestType>, 0u);
        REQUIRE(TestType{1} == _3_1415e0);
    }

    SECTION("Anything to power 1 is anything") {
        constexpr TestType _2e1 = yala::pow(TestType{2}, 1u);
        REQUIRE(TestType{2} == _2e1);

        constexpr TestType _3_1415e1 = yala::pow(pi<TestType>, 1u);
        REQUIRE(pi<TestType> == _3_1415e1);
    }

    SECTION("Anything to power 2 is anything squared") {
        constexpr TestType _2e2 = yala::pow(TestType{2}, 2u);
        REQUIRE(TestType{4} == _2e2);

        constexpr TestType _3_1415e2 = yala::pow(pi<TestType>, 2u);
        REQUIRE(pi<TestType> * pi<TestType> == _3_1415e2);
    }

    SECTION("Anything to power 7 is anything to the power 7") {
        constexpr TestType _2e7 = yala::pow(TestType{2}, 7u);
        REQUIRE(TestType{2 * 2 * 2 * 2 * 2 * 2 * 2} == _2e7);

        constexpr TestType _3_1415e7 = yala::pow(pi<TestType>, 7u);
        REQUIRE(pi<TestType> * pi<TestType> * pi<TestType> * pi<TestType> * pi<TestType> *
                        pi<TestType> * pi<TestType> ==
                _3_1415e7);
    }
}

TEMPLATE_TEST_CASE("Calculating sqrt", "[math, sqrt]", float, double) {
    SECTION("Square roots of squares") {
        constexpr TestType _2 = yala::sqrt(TestType{4});
        REQUIRE(_2 == TestType{2});

        constexpr TestType _3 = yala::sqrt(TestType{9});
        REQUIRE(_3 == TestType{3});

        constexpr TestType _4 = yala::sqrt(TestType{16});
        REQUIRE(_4 == TestType{4});

        constexpr TestType _5 = yala::sqrt(TestType{25});
        REQUIRE(_5 == TestType{5});

        constexpr TestType _10 = yala::sqrt(TestType{100});
        REQUIRE(_10 == TestType{10});

        constexpr TestType _3_1415 = yala::sqrt(pi<TestType> * pi<TestType>);
        REQUIRE(_3_1415 == pi<TestType>);
    }
}
