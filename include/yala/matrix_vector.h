#pragma once

#include <yala/constexpr_math.h>
#include <yala/matrix.h>
#include <yala/vec.h>
#include <yala/yala_export.h>


namespace yala {

template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr vec<Scalar, M> operator*(matrix<Scalar, N, M> const &m,
                                               vec<Scalar, N> const &v) noexcept {
    return vec<Scalar, M>{m * matrix<Scalar, 1, N>(v)};
}

template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr vec<Scalar, M> operator*(vec<Scalar, N> const &v,
                                               matrix<Scalar, M, N> const &m) noexcept {
    return vec<Scalar, M>{matrix<Scalar, N, 1>(v) * m};
}

}// namespace yala