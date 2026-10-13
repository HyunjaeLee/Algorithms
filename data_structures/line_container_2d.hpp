#ifndef LINE_CONTAINER_2D_HPP
#define LINE_CONTAINER_2D_HPP

#include "data_structures/line_container.hpp"
#include "math/rational.hpp"
#include <algorithm>
#include <limits>

template <typename T> struct line_container_2d {
    void add(T a, T b) {
        min_a = std::min(min_a, a);
        max_a = std::max(max_a, a);
        min_lc.add(a, b);
        max_lc.add(a, b);
    }
    T max(T x, T y) const {
        if (y == 0) {
            return x < 0 ? x * min_a : x * max_a;
        }
        rational<T> r(x, y);
        auto [a, b] = (y < 0 ? min_lc.query_line(r) : max_lc.query_line(r));
        return a * x + b * y;
    }
    T min(T x, T y) const { return -max(-x, -y); }

private:
    static constexpr auto inf = std::numeric_limits<T>::max();
    T min_a = inf, max_a = -inf;
    line_container<T, false> min_lc;
    line_container<T> max_lc;
};

#endif // LINE_CONTAINER_2D_HPP