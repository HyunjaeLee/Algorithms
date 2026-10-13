#ifndef LINE_CONTAINER_HPP
#define LINE_CONTAINER_HPP

#include "math/rational.hpp"
#include <cassert>
#include <functional>
#include <set>
#include <utility>

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
template <typename T, bool maximize = true> struct line_container {
    struct line {
        T a, b;
        mutable rational<T> p;
        bool operator<(const line &o) const { return a < o.a; }
        bool operator<(auto x) const { return p < x; }
    };
    static constexpr auto inf = rational<T>(1, 0);
    bool isect(auto x, auto y) {
        if (y == lines.end()) {
            x->p = inf;
            return false;
        }
        if (x->a == y->a) {
            x->p = (y->b < x->b) ? inf : -inf;
        } else {
            x->p = rational<T>(y->b - x->b, x->a - y->a);
        }
        return x->p >= y->p;
    }
    void add(T a, T b) {
        if constexpr (!maximize) {
            a = -a;
            b = -b;
        }
        auto z = lines.emplace(a, b, 0);
        auto y = z++;
        auto x = y;
        while (isect(y, z)) {
            z = lines.erase(z);
        }
        if (x != lines.begin() && isect(--x, y)) {
            y = lines.erase(y);
            isect(x, y);
        }
        while ((y = x) != lines.begin() && (--x)->p >= y->p) {
            isect(x, lines.erase(y));
        }
    }
    std::pair<T, T> query_line(auto x) const {
        assert(!lines.empty());
        auto l = lines.lower_bound(x);
        if constexpr (maximize) {
            return {l->a, l->b};
        } else {
            return {-l->a, -l->b};
        }
    }
    T query(T x) const {
        auto [a, b] = query_line(x);
        return a * x + b;
    }

private:
    std::multiset<line, std::less<>> lines;
};

#endif // LINE_CONTAINER_HPP