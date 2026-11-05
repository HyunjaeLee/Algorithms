#ifndef SURREAL_HPP
#define SURREAL_HPP

#include <algorithm>
#include <bit>
#include <cassert>
#include <compare>
#include <limits>
#include <ostream>
#include <vector>

// g > 0: L wins
// g < 0: R wins
// g = 0: second wins
// https://nyaannyaan.github.io/library/game/surreal-number.hpp
struct Surreal {
    using S = Surreal;
    using i64 = long long;
    using u64 = unsigned long long;
    using i128 = __int128;
    i64 p, q; // p / 2^q

    Surreal(i64 p_ = 0, i64 q_ = 0) : p(p_), q(q_) {
        // normalize
        if (p) {
            auto k = std::min<i64>(std::countr_zero(u64(p)), q);
            p >>= k;
            q -= k;
        } else {
            q = 0;
        }
    }
    Surreal(const std::vector<S> &l, const std::vector<S> &r) {
        constexpr auto inf = std::numeric_limits<i64>::max();
        S lmax = l.empty() ? -inf : std::ranges::max(l);
        S rmin = r.empty() ? inf : std::ranges::min(r);
        assert(lmax < rmin);
        S u = 0;
        while (!(lmax < u && u < rmin)) {
            u = lmax < u ? u.left() : u.right();
        }
        *this = u;
    }

    friend S operator+(S l, S r) {
        auto cq = std::max(l.q, r.q);
        auto cp = (l.p << (cq - l.q)) + (r.p << (cq - r.q));
        return {cp, cq};
    }
    friend S operator-(S l, S r) {
        auto cq = std::max(l.q, r.q);
        auto cp = (l.p << (cq - l.q)) - (r.p << (cq - r.q));
        return {cp, cq};
    }
    S &operator+=(S r) { return *this = *this + r; }
    S &operator-=(S r) { return *this = *this - r; }

    S operator-() const { return {-p, q}; }
    S operator+() const { return *this; }

    friend std::strong_ordering operator<=>(S l, S r) {
        return l.p * (i128(1) << r.q) <=> r.p * (i128(1) << l.q);
    }
    friend bool operator==(S l, S r) { return l.p * (i128(1) << r.q) == r.p * (i128(1) << l.q); }

    S left() const { return *this - (p <= 0 && q == 0 ? 1 : S{1, q + 1}); }
    S right() const { return *this + (0 <= p && q == 0 ? 1 : S{1, q + 1}); }

    friend std::ostream &operator<<(std::ostream &os, S r) {
        os << r.p;
        if (r.q) {
            os << "/" << (1LL << r.q);
        }
        return os;
    }
};

#endif // SURREAL_HPP