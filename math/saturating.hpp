#ifndef SATURATING_HPP
#define SATURATING_HPP

#include <concepts>
#include <iostream>
#include <limits>

template <std::integral T> struct Saturating {
    static constexpr T MAX = std::numeric_limits<T>::max();
    static constexpr T MIN = std::numeric_limits<T>::min();
    constexpr Saturating(T v = 0) : val_(v) {}
    auto operator<=>(const Saturating &) const = default;
    constexpr Saturating &operator+=(Saturating other) {
        if (__builtin_add_overflow(val_, other.val_, &val_)) {
            val_ = (val_ < 0) ? MAX : MIN;
        }
        return *this;
    }
    constexpr Saturating &operator-=(Saturating other) {
        if (__builtin_sub_overflow(val_, other.val_, &val_)) {
            val_ = (val_ < 0) ? MAX : MIN;
        }
        return *this;
    }
    constexpr Saturating &operator*=(Saturating other) {
        auto sign = val_ ^ other.val_;
        if (__builtin_mul_overflow(val_, other.val_, &val_)) {
            val_ = (sign < 0) ? MIN : MAX;
        }
        return *this;
    }
    constexpr Saturating &operator/=(Saturating other) {
        if (val_ == MIN && other.val_ == -1) {
            val_ = MAX;
        } else {
            val_ /= other.val_;
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
        if (val_ == MIN) {
            return {MAX};
        }
        return {-val_};
    }
    constexpr Saturating abs() const {
        if (val_ == MIN) {
            return {MAX};
        }
        return (val_ < 0) ? Saturating(-val_) : *this;
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
    constexpr T val() const { return val_; }
    friend std::ostream &operator<<(std::ostream &os, Saturating s) { return os << s.val_; }
    friend std::istream &operator>>(std::istream &is, Saturating &s) { return is >> s.val_; }

private:
    T val_;
};

#endif // SATURATING_HPP