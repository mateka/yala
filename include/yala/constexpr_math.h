#pragma once

#include <concepts>
#include <yala/yala_export.h>


namespace yala {

template<std::floating_point Scalar, std::unsigned_integral Exponent>
YALA_EXPORT inline constexpr Scalar pow(Scalar base, Exponent exponent) noexcept {
    if (exponent == 0) return {1};
    Scalar result = base;
    for (Exponent i = Exponent{1}; i < exponent; ++i) result *= base;
    return result;
}


template<std::floating_point Scalar>
YALA_EXPORT inline constexpr Scalar sqrt(Scalar arg, std::size_t iterations = 100) noexcept {
    Scalar x = arg / 2;
    for (std::size_t i = 0; i < iterations; ++i) x -= (x * x - arg) / (2 * x);
    return x;
}

}// namespace yala
