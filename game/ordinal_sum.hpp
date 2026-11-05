#ifndef ORDINAL_SUM_HPP
#define ORDINAL_SUM_HPP

#include "surreal.hpp"
#include <cstdlib>

// G : 0 = G and 0 : G = G
// Ordinal sum is associative: (G : H) : J = G : (H : J)
// https://arxiv.org/pdf/2305.16516
// ordinal sum of numbers where the base is in canonical form
Surreal ordinal_sum(Surreal g, Surreal h) {
    using S = Surreal;
    if (h == 0) {
        return g;
    }
    if (g == 0) {
        return h;
    }
    if (g < 0) {
        // If G and H are positions, −(G : H) = (−G) : (−H).
        return -ordinal_sum(-g, -h);
    }
    auto n = std::abs(g.p) >> g.q;
    auto a = std::abs(g.p) & ((1LL << g.q) - 1);
    auto p = g.q;
    auto m = std::abs(h.p) >> h.q;
    auto b = std::abs(h.p) & ((1LL << h.q) - 1);
    auto q = h.q;
    if (a == 0) {
        if (0 <= h) {
            return S(n) + S(m) + S(b, q);
        } else {
            return S(n) - S(1) + S(1, m) - S(b, m + q + 1);
        }
    } else {
        if (0 <= h) {
            return S(n) + S(a + 1, p) - S(1, p + m) + S(b, p + m + q + 1);
        } else {
            return S(n) + S(a - 1, p) + S(1, p + m) - S(b, p + m + q + 1);
        }
    }
}

#endif // ORDINAL_SUM_HPP