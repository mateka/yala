#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <compare>
#include <yala/matrix.h>


using namespace yala;

TEMPLATE_TEST_CASE("matrix can be created and accessed", "[matrix]", float, double) {
    SECTION("Created with default constructor") {
        matrix<TestType, 5, 4> m;

        REQUIRE(5 == m.x_size());
        REQUIRE(4 == m.y_size());

        REQUIRE(m[{4, 3}] == TestType{});
        constexpr TestType value_1 = 10.0f;
        m[{4, 1}] = value_1;
        REQUIRE(m[{4, 1}] == value_1);

        REQUIRE(m[{1, 3}] == TestType{});
        constexpr TestType value_3 = 3.14f;
        m[{1, 3}] = value_3;
        REQUIRE(m[{1, 3}] == value_3);
    }

    SECTION("Created with values constructor") {
        constexpr matrix<TestType, 3, 2> m{TestType(1), TestType(2), TestType(3),
                                           TestType(4), TestType(5), TestType(6)};
        REQUIRE(m[{0, 0}] == TestType(1));
        REQUIRE(m[{1, 0}] == TestType(2));
        REQUIRE(m[{2, 0}] == TestType(3));
        REQUIRE(m[{0, 1}] == TestType(4));
        REQUIRE(m[{1, 1}] == TestType(5));
        REQUIRE(m[{2, 1}] == TestType(6));

        REQUIRE(3 == m.x_size());
        REQUIRE(2 == m.y_size());
    }
}

TEMPLATE_TEST_CASE("matrix is container", "[matrix]", float, double) {
    constexpr std::array<TestType, 6> data{TestType(1), TestType(2), TestType(3),
                                           TestType(4), TestType(5), TestType(6)};
    constexpr matrix<TestType, 2, 3> m{TestType(1), TestType(2), TestType(3),
                                       TestType(4), TestType(5), TestType(6)};
    REQUIRE(std::equal(std::begin(m), std::end(m), std::begin(data), std::end(data)));
    REQUIRE(6 == m.size());
}

TEMPLATE_TEST_CASE("matrix can be compared", "[matrix]", float, double) {
    constexpr matrix<TestType, 2, 3> m1{TestType(1), TestType(2), TestType(3),
                                        TestType(4), TestType(5), TestType(6)};
    constexpr matrix<TestType, 2, 3> m2{TestType(1), TestType(2), TestType(3),
                                        TestType(4), TestType(5), TestType(6)};
    constexpr matrix<TestType, 2, 3> m3{TestType(4), TestType(3), TestType(2),
                                        TestType(1), TestType(5), TestType(6)};

    SECTION("Equality") {
        REQUIRE(m1 == m2);
        REQUIRE(m1 != m3);
    }
    SECTION("Less than") {
        REQUIRE(!(m1 < m2));
        REQUIRE(m1 < m3);
    }
    SECTION("Less equal than") {
        REQUIRE(m1 <= m2);
        REQUIRE(m1 <= m3);
        REQUIRE(!(m3 <= m1));
    }
    SECTION("Greater than") {
        REQUIRE(!(m1 > m2));
        REQUIRE(m3 > m1);
    }
    SECTION("Greater equal than") {
        REQUIRE(m1 >= m2);
        REQUIRE(m3 >= m1);
        REQUIRE(!(m1 >= m3));
    }
    SECTION("By ordering") {
        REQUIRE(std::is_eq(m1 <=> m2));
        REQUIRE(std::is_neq(m1 <=> m3));
        REQUIRE(std::is_lt(m1 <=> m3));
        REQUIRE(std::is_gt(m3 <=> m1));
    }
}

TEMPLATE_TEST_CASE("matrices are elements of linear space", "[matrix]", float, double) {
    SECTION("Can be negated") {
        constexpr matrix<TestType, 3, 2> m1{TestType(1), TestType(2), TestType(3),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m2{TestType(-1), TestType(-2), TestType(-3),
                                            TestType(-4), TestType(-5), TestType(-6)};
        REQUIRE(-m1 == m2);
    }
    SECTION("Can be added in place") {
        matrix<TestType, 3, 2> m1{TestType(1), TestType(2), TestType(3),
                                  TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m2{TestType(2), TestType(3), TestType(4),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m3{TestType(3), TestType(5),  TestType(7),
                                            TestType(8), TestType(10), TestType(12)};
        REQUIRE((m1 += m2) == m3);
    }
    SECTION("Can be added") {
        constexpr matrix<TestType, 3, 2> m1{TestType(1), TestType(2), TestType(3),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m2{TestType(2), TestType(3), TestType(4),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m3{TestType(3), TestType(5),  TestType(7),
                                            TestType(8), TestType(10), TestType(12)};
        constexpr auto sum = m1 + m2;
        REQUIRE(sum == m3);
    }
    SECTION("Can be substracted in place") {
        matrix<TestType, 3, 2> m1{TestType(1), TestType(2), TestType(3),
                                  TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m2{TestType(2), TestType(3), TestType(4),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m3{TestType(-1), TestType(-1), TestType(-1),
                                            TestType(0),  TestType(0),  TestType(0)};
        REQUIRE((m1 -= m2) == m3);
    }
    SECTION("Can be substracted") {
        constexpr matrix<TestType, 3, 2> m1{TestType(1), TestType(2), TestType(3),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m2{TestType(2), TestType(3), TestType(4),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m3{TestType(-1), TestType(-1), TestType(-1),
                                            TestType(0),  TestType(0),  TestType(0)};
        constexpr auto difference = m1 - m2;
        REQUIRE(difference == m3);
    }
    SECTION("Can be multiplied by scalar in place") {
        matrix<TestType, 3, 2> m1{TestType(1), TestType(2), TestType(3),
                                  TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m2{TestType(2), TestType(4),  TestType(6),
                                            TestType(8), TestType(10), TestType(12)};
        m1 *= 2;
        REQUIRE(m1 == m2);
    }
    SECTION("Can be multiplied by scalar") {
        constexpr matrix<TestType, 3, 2> m1{TestType(1), TestType(2), TestType(3),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> m2{TestType(3),  TestType(6),  TestType(9),
                                            TestType(12), TestType(15), TestType(18)};
        constexpr matrix<TestType, 3, 2> r1 = m1 * TestType(3);
        constexpr matrix<TestType, 3, 2> r2 = TestType(3) * m1;
        REQUIRE(r1 == m2);
        REQUIRE(r2 == m2);
    }
    SECTION("Can be divided by scalar in place") {
        matrix<TestType, 3, 2> m1{TestType(2), TestType(4),  TestType(6),
                                  TestType(8), TestType(10), TestType(12)};
        constexpr matrix<TestType, 3, 2> m2{TestType(1), TestType(2), TestType(3),
                                            TestType(4), TestType(5), TestType(6)};
        m1 /= 2;
        REQUIRE(m1 == m2);
    }
    SECTION("Can be divided by scalar") {
        constexpr matrix<TestType, 3, 2> m1{TestType(3),  TestType(6),  TestType(9),
                                            TestType(12), TestType(15), TestType(18)};
        constexpr matrix<TestType, 3, 2> m2{TestType(1), TestType(2), TestType(3),
                                            TestType(4), TestType(5), TestType(6)};
        constexpr matrix<TestType, 3, 2> r = m1 / TestType(3);
        REQUIRE(r == m2);
    }
}

TEMPLATE_TEST_CASE("matrices can be multiplied", "[matrix]", float, double) {
    constexpr matrix<TestType, 3, 2> m1{TestType(1), TestType(2), TestType(3),
                                        TestType(4), TestType(5), TestType(6)};
    constexpr matrix<TestType, 4, 3> m2{TestType(1), TestType(2),  TestType(3),  TestType(4),
                                        TestType(5), TestType(6),  TestType(7),  TestType(8),
                                        TestType(9), TestType(10), TestType(11), TestType(12)};
    constexpr matrix<TestType, 4, 2> expected{
            TestType(38), TestType(44), TestType(50),  TestType(56),
            TestType(83), TestType(98), TestType(113), TestType(128),
    };
    constexpr matrix<TestType, 4, 2> result = m1 * m2;
    REQUIRE(result == expected);
}

TEMPLATE_TEST_CASE("matrices can be transposed", "[matrix]", float, double) {
    constexpr matrix<TestType, 3, 2> m{TestType(1), TestType(2), TestType(3),
                                       TestType(4), TestType(5), TestType(6)};
    constexpr matrix<TestType, 2, 3> expected{TestType(1), TestType(4), TestType(2),
                                              TestType(5), TestType(3), TestType(6)};
    constexpr matrix<TestType, 2, 3> result = transpose(m);
    REQUIRE(result == expected);
}
