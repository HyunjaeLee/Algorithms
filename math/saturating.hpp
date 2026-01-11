#ifndef SATURATING_HPP
#define SATURATING_HPP

#include <compare>
#include <concepts>
#include <iostream>
#include <limits>

template <std::integral T> struct Saturating {
    T val;
    static constexpr T MAX = std::numeric_limits<T>::max();
    static constexpr T MIN = std::numeric_limits<T>::min();
    constexpr Saturating(T v = 0) : val(v) {}
    auto operator<=>(const Saturating &) const = default;
    constexpr Saturating &operator+=(Saturating other) {
        if (__builtin_add_overflow(val, other.val, &val)) {
            val = (val < 0) ? MAX : MIN;
        }
        return *this;
    }
    constexpr Saturating &operator-=(Saturating other) {
        if (__builtin_sub_overflow(val, other.val, &val)) {
            val = (val < 0) ? MAX : MIN;
        }
        return *this;
    }
    constexpr Saturating &operator*=(Saturating other) {
        auto sign = val ^ other.val;
        if (__builtin_mul_overflow(val, other.val, &val)) {
            val = (sign < 0) ? MIN : MAX;
        }
        return *this;
    }
    constexpr Saturating &operator/=(Saturating other) {
        if (val == MIN && other.val == -1) {
            val = MAX;
        } else {
            val /= other.val;
        }
        return *this;
    }
    friend constexpr Saturating operator+(Saturating a, Saturating b) {
        a += b;
        return a;
    }
    friend constexpr Saturating operator-(Saturating a, Saturating b) {
        a -= b;
        return a;
    }
    friend constexpr Saturating operator*(Saturating a, Saturating b) {
        a *= b;
        return a;
    }
    friend constexpr Saturating operator/(Saturating a, Saturating b) {
        a /= b;
        return a;
    }
    constexpr Saturating operator+() const { return *this; }
    constexpr Saturating operator-() const {
        if (val == MIN) {
            return {MAX};
        }
        return {-val};
    }
    constexpr Saturating abs() const {
        if (val == MIN) {
            return {MAX};
        }
        return (val < 0) ? Saturating(-val) : *this;
    }
    constexpr Saturating pow(unsigned long long exp) const {
        Saturating res = 1;
        Saturating base = *this;
        while (exp) {
            if (exp & 1) {
                res *= base;
            }
            base *= base;
            exp >>= 1;
        }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, Saturating s) { return os << s.val; }
    friend std::istream &operator>>(std::istream &is, Saturating &s) { return is >> s.val; }
};

#endif SATURATING_HPP