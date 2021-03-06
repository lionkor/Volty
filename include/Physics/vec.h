#ifndef VEC_H
#define VEC_H

#include "Core/Math.h"
#include "Core/Object.h"
#include "Utils/DebugTools.h"
#include <SFML/Graphics.hpp>
#include <ostream>
#include <tuple>
#include <type_traits>

namespace V {

/// Minimal 2D-vector struct.
template<typename T>
struct vec {
    T x;
    T y;

    vec() = default;

    vec(const vec& other)
        : x(other.x)
        , y(other.y) {
    }

    vec& operator=(const vec& other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    vec(vec&& v) noexcept
        : x(std::move(v.x))
        , y(std::move(v.y)) {
        v.x = 0;
        v.y = 0;
    }

    explicit vec(const sf::Vector2f& other)
        : x(other.x)
        , y(other.y) {
    }

    explicit vec(const sf::Vector2i& other)
        : x(other.x)
        , y(other.y) {
    }

    template<std::convertible_to<T> OtherT>
    explicit vec(const vec<OtherT>& other)
        : x(T(other.x))
        , y(T(other.y)) {
    }

    template<std::convertible_to<T> OtherT>
    vec& operator=(const vec<OtherT>& other) {
        x = T(other.x);
        y = T(other.y);
        return *this;
    }

    vec(T _x, T _y)
        : x(static_cast<T>(_x))
        , y(static_cast<T>(_y)) { }

    explicit vec(T val)
        : x(static_cast<T>(val))
        , y(static_cast<T>(val)) { }

    inline std::tuple<T, T> get() const { return std::tie(x, y); }

    template<class IndexT>
    inline T& operator[](IndexT index) { return index == static_cast<IndexT>(0) ? x : y; }

    template<class IndexT>
    inline T operator[](IndexT index) const { return index == static_cast<IndexT>(0) ? x : y; }

    inline bool operator==(const vec& v) const { return std::tie(x, y) == std::tie(v.x, v.y); }
    inline bool operator!=(const vec& v) const { return !(*this == v); }

    inline bool operator<(const vec& v) const { return std::tie(x, y) < std::tie(v.x, v.y); }
    inline bool operator>(const vec& v) const { return std::tie(x, y) > std::tie(v.x, v.y); }
    inline bool operator<=(const vec& v) const { return std::tie(x, y) <= std::tie(v.x, v.y); }
    inline bool operator>=(const vec& v) const { return std::tie(x, y) >= std::tie(v.x, v.y); }

    inline vec<T> operator+(const vec& v) const { return vec<T>(x + v.x, y + v.y); }
    inline vec<T> operator-(const vec& v) const { return vec<T>(x - v.x, y - v.y); }
    inline vec<T> operator*(const T& i) const { return vec<T>(x * i, y * i); }
    inline vec<T> operator/(const T& i) const { return vec<T>(x / i, y / i); }
    inline vec<T> operator%(const T& i) const { return vec<T>(x % i, y % i); }

    inline vec<T> operator-() const { return vec<T>(-x, -y); }

    inline vec<T>& operator+=(const vec& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    inline vec<T>& operator-=(const vec& v) {
        return *this += -v;
    }
    template<typename AnyNumberT>
    inline vec<T>& operator*=(const AnyNumberT& i) {
        x *= i;
        y *= i;
        return *this;
    }
    template<typename AnyNumberT>
    inline vec<T>& operator/=(const AnyNumberT& i) {
        return *this *= static_cast<AnyNumberT>(1) / i;
    }

    T inline length() const noexcept {
        return std::sqrt(x * x + y * y);
    }

    void inline normalize() noexcept {
        *this = *this / length();
    }

    inline vec normalized() const noexcept {
        vec v = *this;
        v.normalize();
        return v;
    }

    inline vec abs() const noexcept {
        return vec(Math::abs(x), Math::abs(y));
    }

    static constexpr T distance_squared(const vec<T>& a, const vec<T>& b) noexcept {
        return (a.x - b.x) * (a.x - b.x)
            + (a.y - b.y) * (a.y - b.y);
    }
};

template<class T>
std::ostream& operator<<(std::ostream& os, const vec<T>& v) {
    return os << "(" << v.x << "," << v.y << ")";
}

template<typename T>
vec<T> operator*(T val, const vec<T>& vec) {
    return vec * val;
}

template<typename T>
vec<T> operator+(T val, const vec<T>& vec) {
    return { vec.x + val, vec.y + val };
}

template<typename T>
vec<T> operator+(const vec<T>& vec, T val) {
    return { vec.x + val, vec.y + val };
}

template<typename T>
vec<T> operator-(T val, const vec<T>& vec) {
    return { val - vec.x, val - vec.y };
}

template<typename T>
vec<T> operator-(const vec<T>& vec, T val) {
    return { vec.x - val, vec.y - val };
}

using vecd = vec<double>;
using veci = vec<int>;
using vecu = vec<unsigned>;

}

#endif // VEC_H
