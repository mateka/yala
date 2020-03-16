#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <yala/hello.h>

TEST_CASE( "Sums are computed", "[add]" ) {
    REQUIRE( add(1, 2) == 3 );
    REQUIRE( add(2, 0) == 2 );
    REQUIRE( add(0, 6) == 6 );
}