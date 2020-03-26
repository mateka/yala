#pragma once

#include <yala/constexpr_math.h>
#include <yala/yala_export.h>

#include <array>
#include <compare>
#include <concepts>
#include <type_traits>


namespace yala {

template<std::floating_point Scalar, std::size_t Dimensions>
class YALA_EXPORT vec {
public:
    constexpr vec() noexcept : elements_{} {
        for (auto &e : elements_) e = Scalar{};
    }
    template<std::floating_point... Args>
    constexpr vec(Args... args) noexcept requires(sizeof...(Args) == Dimensions)
        : elements_{args...} {}
    constexpr vec(vec const &) noexcept = default;
    constexpr vec(vec &&) noexcept = default;
    constexpr vec &operator=(vec const &) noexcept = default;
    constexpr vec &operator=(vec &&) noexcept = default;

    constexpr Scalar &operator[](std::size_t const i) noexcept { return elements_[i]; }
    constexpr Scalar operator[](std::size_t const i) const noexcept { return elements_[i]; }

    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims <= 4, vec &> x(Scalar value) noexcept {
        (*this)[0] = value;
        return (*this);
    }
    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims <= 4, Scalar> x() const noexcept {
        return (*this)[0];
    }

    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims >= 2 && Dims <= 4, vec &>
    y(Scalar value) noexcept {
        (*this)[1] = value;
        return (*this);
    }
    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims >= 2 && Dims <= 4, Scalar> y() const
            noexcept {
        return (*this)[1];
    }

    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims >= 3 && Dims <= 4, vec &>
    z(Scalar value) noexcept {
        (*this)[2] = value;
        return (*this);
    }
    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims >= 3 && Dims <= 4, Scalar> z() const
            noexcept {
        return (*this)[2];
    }

    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims == 4, vec &> w(Scalar value) noexcept {
        (*this)[3] = value;
        return (*this);
    }
    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims == 4, Scalar> w() const noexcept {
        return (*this)[3];
    }

    constexpr auto size() const noexcept { return Dimensions; }

    constexpr auto begin() noexcept { return std::begin(elements_); }
    constexpr auto begin() const noexcept { return std::begin(elements_); }
    constexpr auto cbegin() const noexcept { return std::cbegin(elements_); }

    constexpr auto end() noexcept { return std::end(elements_); }
    constexpr auto end() const noexcept { return std::end(elements_); }
    constexpr auto cend() const noexcept { return std::cend(elements_); }

    constexpr bool operator==(vec const &v) const noexcept { return elements_ == v.elements_; }

    constexpr std::strong_ordering operator<=>(vec const &v) const noexcept {
        for (std::size_t i = 0; i < Dimensions; ++i) {
            if (elements_[i] < v.elements_[i]) return std::strong_ordering::less;
            else if (elements_[i] > v.elements_[i])
                return std::strong_ordering::greater;
        }
        return std::strong_ordering::equal;
    }

    constexpr vec &operator+=(vec const &v) noexcept {
        for (std::size_t i = 0; i < Dimensions; ++i) elements_[i] += v[i];
        return *this;
    }
    constexpr vec &operator-=(vec const &v) noexcept { return (*this) += -v; }

    constexpr vec &operator*=(Scalar const s) noexcept {
        for (auto &e : elements_) e *= s;
        return *this;
    }
    constexpr vec &operator/=(Scalar const s) noexcept { return (*this) *= (Scalar{1} / s); }

    constexpr Scalar length_squared() const noexcept { return (*this) * (*this); }
    constexpr Scalar length() const noexcept { return yala::sqrt(length_squared()); }

private:
    std::array<Scalar, Dimensions> elements_;
};

template<std::floating_point A1, std::floating_point... Args>
vec(A1, Args...)->vec<A1, 1 + sizeof...(Args)>;


template<std::floating_point Scalar, std::size_t Dimensions>
YALA_EXPORT constexpr vec<Scalar, Dimensions> operator-(vec<Scalar, Dimensions> v) noexcept {
    return v * Scalar{-1};
}

template<std::floating_point Scalar, std::size_t Dimensions>
YALA_EXPORT constexpr vec<Scalar, Dimensions>
operator+(vec<Scalar, Dimensions> v1, vec<Scalar, Dimensions> const &v2) noexcept {
    for (std::size_t i = 0; i < Dimensions; ++i) v1[i] += v2[i];
    return v1;
}

template<std::floating_point Scalar, std::size_t Dimensions>
YALA_EXPORT constexpr vec<Scalar, Dimensions>
operator-(vec<Scalar, Dimensions> v1, vec<Scalar, Dimensions> const &v2) noexcept {
    return v1 + -v2;
}

template<std::floating_point Scalar, std::size_t Dimensions>
YALA_EXPORT constexpr vec<Scalar, Dimensions> operator*(vec<Scalar, Dimensions> v,
                                                        Scalar const s) noexcept {
    for (std::size_t i = 0; i < Dimensions; ++i) v[i] *= s;
    return v;
}

template<std::floating_point Scalar, std::size_t Dimensions>
YALA_EXPORT constexpr vec<Scalar, Dimensions> operator*(Scalar const s,
                                                        vec<Scalar, Dimensions> v) noexcept {
    return v * s;
}

template<std::floating_point Scalar, std::size_t Dimensions>
YALA_EXPORT constexpr vec<Scalar, Dimensions> operator/(vec<Scalar, Dimensions> v,
                                                        Scalar const s) noexcept {
    return v * (Scalar{1} / s);
}

template<std::floating_point Scalar, std::size_t Dimensions>
YALA_EXPORT constexpr Scalar operator*(vec<Scalar, Dimensions> const &v1,
                                       vec<Scalar, Dimensions> const &v2) noexcept {
    // TODO: When inner_product is constexpr
    // return std::inner_product(std::cbegin(v1), std::cend(v1), std::cbegin(v1), Scalar{});
    Scalar result = {};
    for (std::size_t i = 0; i < Dimensions; ++i) result += v1[i] * v2[i];
    return result;
}

template<std::floating_point Scalar>
YALA_EXPORT constexpr vec<Scalar, 2> perpendicular(vec<Scalar, 2> const &v) noexcept {
    return {v.y(), -v.x()};
}

template<std::floating_point Scalar>
YALA_EXPORT constexpr vec<Scalar, 3> cross(vec<Scalar, 3> const &v1,
                                           vec<Scalar, 3> const &v2) noexcept {
    return {v1.y() * v2.z() - v1.z() * v2.y(), -(v1.x() * v2.z() - v1.z() * v2.x()),
            v1.x() * v2.y() - v1.y() * v2.x()};
}


}// namespace yala
