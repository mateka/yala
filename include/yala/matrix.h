#pragma once

#include <yala/constexpr_math.h>
#include <yala/yala_export.h>

#include <array>
#include <compare>
#include <concepts>
#include <tuple>


namespace yala {

template<std::floating_point Scalar, std::size_t N, std::size_t M>
class YALA_EXPORT matrix {
public:
    using index_type = std::tuple<std::size_t, std::size_t>;

    constexpr matrix() noexcept : elements_{} {
        for (auto &e : elements_) e = Scalar{};
    }
    template<std::floating_point... Args>
    constexpr matrix(Args... args) noexcept requires(sizeof...(Args) == N * M)
        : elements_{args...} {}
    constexpr matrix(matrix const &) noexcept = default;
    constexpr matrix(matrix &&) noexcept = default;
    constexpr matrix &operator=(matrix const &) noexcept = default;
    constexpr matrix &operator=(matrix &&) noexcept = default;

    constexpr Scalar &operator[](index_type const i) noexcept {
        return elements_[std::get<0>(i) + N * std::get<1>(i)];
    }
    constexpr Scalar operator[](index_type const i) const noexcept {
        return elements_[std::get<0>(i) + N * std::get<1>(i)];
    }
    constexpr auto size() const noexcept { return x_size() * y_size(); }
    constexpr auto x_size() const noexcept { return N; }
    constexpr auto y_size() const noexcept { return M; }

    constexpr auto begin() noexcept { return std::begin(elements_); }
    constexpr auto begin() const noexcept { return std::begin(elements_); }
    constexpr auto cbegin() const noexcept { return std::cbegin(elements_); }

    constexpr auto end() noexcept { return std::end(elements_); }
    constexpr auto end() const noexcept { return std::end(elements_); }
    constexpr auto cend() const noexcept { return std::cend(elements_); }

    constexpr bool operator==(matrix const &m) const noexcept { return elements_ == m.elements_; }

    constexpr std::strong_ordering operator<=>(matrix const &m) const noexcept {
        for (std::size_t i = 0; i < N * M; ++i) {
            if (elements_[i] < m.elements_[i]) return std::strong_ordering::less;
            else if (elements_[i] > m.elements_[i])
                return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    }

    constexpr matrix &operator+=(matrix const &m) noexcept {
        for (std::size_t i = 0; i < N * M; ++i) elements_[i] += m.elements_[i];
        return *this;
    }
    constexpr matrix &operator-=(matrix const &m) noexcept { return (*this) += -m; }

    constexpr matrix &operator*=(Scalar const s) noexcept {
        for (auto &e : elements_) e *= s;
        return *this;
    }
    constexpr matrix &operator/=(Scalar const s) noexcept { return (*this) *= (Scalar{1} / s); }

private:
    std::array<Scalar, N * M> elements_;
};


template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr matrix<Scalar, N, M> operator-(matrix<Scalar, N, M> m) noexcept {
    return m *= Scalar{-1};
}

template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr matrix<Scalar, N, M> operator+(matrix<Scalar, N, M> m1,
                                                     matrix<Scalar, N, M> const &m2) noexcept {
    return m1 += m2;
}

template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr matrix<Scalar, N, M> operator-(matrix<Scalar, N, M> m1,
                                                     matrix<Scalar, N, M> const &m2) noexcept {
    return m1 + -m2;
}

template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr matrix<Scalar, N, M> operator*(matrix<Scalar, N, M> m,
                                                     Scalar const s) noexcept {
    return m *= s;
}

template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr matrix<Scalar, N, M> operator*(Scalar const s,
                                                     matrix<Scalar, N, M> m) noexcept {
    return m * s;
}

template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr matrix<Scalar, N, M> operator/(matrix<Scalar, N, M> m,
                                                     Scalar const s) noexcept {
    return m * (Scalar{1} / s);
}

template<std::floating_point Scalar, std::size_t N, std::size_t M, std::size_t K>
YALA_EXPORT constexpr matrix<Scalar, K, M> operator*(matrix<Scalar, N, M> const &m1,
                                                     matrix<Scalar, K, N> const &m2) noexcept {
    matrix<Scalar, K, M> result = {};
    for (std::size_t m = 0; m < M; ++m)
        for (std::size_t k = 0; k < K; ++k)
            for (std::size_t n = 0; n < N; ++n) result[{k, m}] += m1[{n, m}] * m2[{k, n}];
    return result;
}

template<std::floating_point Scalar, std::size_t N, std::size_t M>
YALA_EXPORT constexpr matrix<Scalar, M, N> transpose(matrix<Scalar, N, M> const &mat) {
    matrix<Scalar, M, N> result;
    for (std::size_t m = 0; m < M; ++m)
        for (std::size_t n = 0; n < N; ++n) result[{m, n}] += mat[{n, m}];
    return result;
}

}// namespace yala
