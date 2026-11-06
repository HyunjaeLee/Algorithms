#ifndef MODINT_HPP
#define MODINT_HPP

#include <cassert>
#include <concepts>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

template <std::signed_integral auto mod> struct modint {
    using T = decltype(mod);
    static_assert(0 < mod && mod <= std::numeric_limits<T>::max() / 2 + 1);
    constexpr modint() : v(0) {}
    constexpr modint(std::integral auto x) : v(T((x % mod + mod) % mod)) {}
    constexpr modint &operator+=(modint o) {
        v = (v + o.v) % mod;
        return *this;
    }
    constexpr modint &operator-=(modint o) {
        v = (v - o.v + mod) % mod;
        return *this;
    }
    constexpr modint &operator*=(modint o) {
        static_assert(sizeof(T) <= sizeof(long long));
        using U = std::conditional_t<sizeof(T) <= sizeof(int), long long, __int128>;
        v = T(U(v) * o.v % mod);
        return *this;
    }
    constexpr modint &operator/=(modint o) { return *this *= o.inv(); }
    constexpr modint operator-() const { return -v; }
    constexpr modint operator+() const { return *this; }
    friend constexpr modint operator+(modint l, modint r) { return l += r; }
    friend constexpr modint operator-(modint l, modint r) { return l -= r; }
    friend constexpr modint operator*(modint l, modint r) { return l *= r; }
    friend constexpr modint operator/(modint l, modint r) { return l /= r; }
    friend bool operator==(modint, modint) = default;
    constexpr modint pow(std::integral auto n) const {
        assert(0 <= n);
        modint x = *this, r = 1;
        for (; n; x *= x, n /= 2) {
            if (n & 1) {
                r *= x;
            }
        }
        return r;
    }
    constexpr modint inv() const {
        T a = v, b = mod, s = 1, t = 0;
        while (b) {
            T q = a / b;
            std::swap(a -= b * q, b);
            std::swap(s -= t * q, t);
        }
        assert(a == 1);
        return s;
    }
    constexpr T val() const { return v; }
    friend std::ostream &operator<<(std::ostream &os, modint a) { return os << a.v; }
    friend std::istream &operator>>(std::istream &is, modint &a) {
        long long x;
        is >> x;
        a = x;
        return is;
    }

private:
    T v;
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

#endif // MODINT_HPP