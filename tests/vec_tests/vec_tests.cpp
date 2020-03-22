#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <compare>
#include <yala/vec.h>


using namespace yala;

TEMPLATE_TEST_CASE("vec can be created and accessed", "[vec]", float, double) {
    SECTION("Created with default constructor") {
        vec<TestType, 5> v;

        REQUIRE(v[1] == TestType{});
        constexpr TestType value_1 = 10.0f;
        v[1] = value_1;
        REQUIRE(v[1] == value_1);

        REQUIRE(v[3] == TestType{});
        constexpr TestType value_3 = 3.14f;
        v[3] = value_3;
        REQUIRE(v[3] == value_3);
    }

    SECTION("Created with values constructor") {
        constexpr vec<TestType, 6> v{TestType(1), TestType(2), TestType(3),
                                     TestType(4), TestType(5), TestType(6)};
        REQUIRE(v[0] == TestType(1));
        REQUIRE(v[1] == TestType(2));
        REQUIRE(v[2] == TestType(3));
        REQUIRE(v[3] == TestType(4));
        REQUIRE(v[4] == TestType(5));
        REQUIRE(v[5] == TestType(6));
    }
}

TEMPLATE_TEST_CASE("vec is container", "[vec]", float, double) {
    constexpr std::array<TestType, 6> data{TestType(1), TestType(2), TestType(3),
                                           TestType(4), TestType(5), TestType(6)};
    constexpr vec<TestType, 6> v{TestType(1), TestType(2), TestType(3),
                                 TestType(4), TestType(5), TestType(6)};
    REQUIRE(std::equal(std::begin(v), std::end(v), std::begin(data), std::end(data)));
    REQUIRE(6 == v.size());
}

TEMPLATE_TEST_CASE("vec can be compared", "[vec]", float, double) {
    constexpr vec<TestType, 4> v1{TestType(1), TestType(2), TestType(3), TestType(4)};
    constexpr vec<TestType, 4> v2{TestType(1), TestType(2), TestType(3), TestType(4)};
    constexpr vec<TestType, 4> v3{TestType(4), TestType(3), TestType(2), TestType(1)};

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

TEMPLATE_TEST_CASE("vecs are elements of linear space", "[vec]", float, double) {
    SECTION("Can be negated") {
        constexpr vec v1{TestType(1), TestType(2), TestType(3)};
        constexpr vec v2{TestType(-1), TestType(-2), TestType(-3)};
        REQUIRE(-v1 == v2);
    }
    SECTION("Can be added in place") {
        vec v1{TestType(1), TestType(2), TestType(3)};
        constexpr vec v2{TestType(2), TestType(3), TestType(4)};
        constexpr vec v3{TestType(3), TestType(5), TestType(7)};
        REQUIRE((v1 += v2) == v3);
    }
    SECTION("Can be added") {
        constexpr vec v1{TestType(1), TestType(2), TestType(3)};
        constexpr vec v2{TestType(2), TestType(3), TestType(4)};
        constexpr vec v3{TestType(3), TestType(5), TestType(7)};
        constexpr auto sum = v1 + v2;
        REQUIRE(sum == v3);
    }
    SECTION("Can be substracted in place") {
        vec v1{TestType(1), TestType(2), TestType(3)};
        constexpr vec v2{TestType(2), TestType(3), TestType(4)};
        constexpr vec v3{TestType(-1), TestType(-1), TestType(-1)};
        REQUIRE((v1 -= v2) == v3);
    }
    SECTION("Can be substracted") {
        constexpr vec v1{TestType(1), TestType(2), TestType(3)};
        constexpr vec v2{TestType(2), TestType(3), TestType(4)};
        constexpr vec v3{TestType(-1), TestType(-1), TestType(-1)};
        constexpr auto difference = v1 - v2;
        REQUIRE(difference == v3);
    }
    SECTION("Can be multiplied by scalar in place") {
        vec v1{TestType(1), TestType(2), TestType(3)};
        constexpr vec v2{TestType(2), TestType(4), TestType(6)};
        v1 *= 2;
        REQUIRE(v1 == v2);
    }
    SECTION("Can be multiplied by scalar") {
        constexpr vec v1{TestType(1), TestType(2), TestType(3)};
        constexpr vec v2{TestType(3), TestType(6), TestType(9)};
        constexpr vec r1 = v1 * TestType(3);
        constexpr vec r2 = TestType(3) * v1;
        REQUIRE(r1 == v2);
        REQUIRE(r2 == v2);
    }
    SECTION("Can be divided by scalar in place") {
        vec v1{TestType(2), TestType(4), TestType(6)};
        constexpr vec v2{TestType(1), TestType(2), TestType(3)};
        v1 /= 2;
        REQUIRE(v1 == v2);
    }
    SECTION("Can be divided by scalar") {
        constexpr vec v1{TestType(3), TestType(6), TestType(9)};
        constexpr vec v2{TestType(1), TestType(2), TestType(3)};
        constexpr vec r = v1 / TestType(3);
        REQUIRE(r == v2);
    }
    SECTION("Dot product can be calculated") {
        constexpr vec v1{TestType(1), TestType(2), TestType(3),
                         TestType(4), TestType(5), TestType(6)};
        constexpr vec v2{TestType(60), TestType(50), TestType(40),
                         TestType(30), TestType(20), TestType(10)};
        constexpr TestType dot_product = v1 * v2;
        REQUIRE(dot_product == (60 + 100 + 120 + 120 + 100 + 60));
    }
    SECTION("Squared length can be computed") {
        constexpr vec v1{TestType(1), TestType(2), TestType(3),
                         TestType(4), TestType(5), TestType(6)};
        constexpr auto length_squared = v1.length_squared();
        REQUIRE(length_squared == (1 + 4 + 9 + 16 + 25 + 36));
    }
    SECTION("Length can be computed") {
        constexpr vec v1{TestType(1), TestType(2), TestType(3),
                         TestType(4), TestType(5), TestType(6)};
        constexpr auto length = v1.length();
        REQUIRE(length == std::sqrt(TestType{1 + 4 + 9 + 16 + 25 + 36}));
    }
}
