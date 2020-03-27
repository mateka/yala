#pragma once

#include <yala/vec.h>
#include <yala/yala_export.h>


namespace yala {

template<std::floating_point Scalar, std::size_t N, std::size_t M>
class matrix;

template<std::floating_point Scalar, std::size_t Dimensions>
class YALA_EXPORT normal final : public vec<Scalar, Dimensions> {
public:
    template<std::size_t Dims = Dimensions>
    static constexpr std::enable_if_t<Dims == Dimensions && Dims <= 4, normal> i() noexcept {
        if constexpr (Dims == 1) return normal{Scalar{1}};
        else if constexpr (Dims == 2)
            return normal{Scalar{1}, Scalar{0}};
        else if constexpr (Dims == 3)
            return normal{Scalar{1}, Scalar{0}, Scalar{0}};
        else if constexpr (Dims == 4)
            return normal{Scalar{1}, Scalar{0}, Scalar{0}, Scalar{0}};
    }

    template<std::size_t Dims = Dimensions>
    static constexpr std::enable_if_t<Dims == Dimensions && 2 <= Dims && Dims <= 4, normal>
    j() noexcept {
        if constexpr (Dims == 2) return normal{Scalar{0}, Scalar{1}};
        else if constexpr (Dims == 3)
            return normal{Scalar{0}, Scalar{1}, Scalar{0}};
        else if constexpr (Dims == 4)
            return normal{Scalar{0}, Scalar{1}, Scalar{0}, Scalar{0}};
    }

    template<std::size_t Dims = Dimensions>
    static constexpr std::enable_if_t<Dims == Dimensions && 3 <= Dims && Dims <= 4, normal>
    k() noexcept {
        if constexpr (Dims == 3) return normal{Scalar{0}, Scalar{0}, Scalar{1}};
        else if constexpr (Dims == 4)
            return normal{Scalar{0}, Scalar{0}, Scalar{1}, Scalar{0}};
    }

    template<std::size_t Dims = Dimensions>
    static constexpr std::enable_if_t<Dims == Dimensions && Dims == 4, normal> l() noexcept {
        return normal{Scalar{0}, Scalar{0}, Scalar{0}, Scalar{1}};
    }

    constexpr normal() = delete;
    template<std::floating_point... Args>
    constexpr normal(Args... args) noexcept requires(sizeof...(Args) == Dimensions)
        : normal{vec{args...}} {}
    constexpr normal(vec const &v) noexcept : vec{v / v.length()} {}
    constexpr normal(normal const &) noexcept = default;
    constexpr normal(normal &&) noexcept = default;
    constexpr normal &operator=(normal const &) noexcept = default;
    constexpr normal &operator=(normal &&) noexcept = default;

    constexpr explicit normal(matrix<Scalar, Dimensions, 1> const &m) noexcept : normal{vec{m}} {}
    template<std::size_t K = Dimensions>
    constexpr explicit normal(matrix<Scalar, 1, K> const &m) noexcept requires(K == Dimensions &&
                                                                               K > 1)
        : normal{transpose(m)} {}

    constexpr normal &operator+=(vec const &v) noexcept = delete;
    constexpr normal &operator-=(vec const &v) noexcept = delete;

    constexpr normal &operator*=(Scalar const s) noexcept = delete;
    constexpr normal &operator/=(Scalar const s) noexcept = delete;

    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims <= 1 && 100 <= Dims, vec &> x(Scalar value) noexcept {
        (*this)[0] = value;
        return (*this);
    }
    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims <= 4, Scalar> x() const noexcept {
        return vec::x();
    }

    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims <= 1 && 100 <= Dims, vec &> y(Scalar value) noexcept {
        (*this)[1] = value;
        return (*this);
    }
    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims >= 2 && Dims <= 4, Scalar> y() const
            noexcept {
        return vec::y();
    }

    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims <= 1 && 100 <= Dims, vec &> z(Scalar value) noexcept {
        (*this)[2] = value;
        return (*this);
    }
    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims >= 3 && Dims <= 4, Scalar> z() const
            noexcept {
        return vec::z();
    }

    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims <= 1 && 100 <= Dims, vec &> w(Scalar value) noexcept {
        (*this)[3] = value;
        return (*this);
    }
    template<std::size_t Dims = Dimensions>
    constexpr std::enable_if_t<Dims == Dimensions && Dims == 4, Scalar> w() const noexcept {
        return vec::w();
    }
};

template<std::floating_point A1, std::floating_point... Args>
normal(A1, Args...)->normal<A1, 1 + sizeof...(Args)>;

}// namespace yala
