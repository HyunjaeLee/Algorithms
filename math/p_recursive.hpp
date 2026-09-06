#ifndef P_RECURSIVE_HPP
#define P_RECURSIVE_HPP

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>

// https://min-25.hatenablog.com/entry/2018/05/10/212805

template <typename Z>
std::vector<Z> extended(int n, const std::vector<std::vector<Z>> &coeffs,
                        const std::vector<Z> &terms) {
    std::vector<Z> ret(std::max(n + 1, int(terms.size())));
    std::copy(terms.begin(), terms.end(), ret.begin());
    auto order = int(coeffs.size()) - 1;
    auto deg = int(coeffs[0].size()) - 1;
    assert(order <= int(terms.size()));
    for (auto m = int(terms.size()); m <= n; ++m) {
        Z s = 0;
        for (auto i = 1; i <= order; ++i) {
            auto k = m - i;
            auto t = ret[k];
            for (auto d = 0; d <= deg; ++d) {
                s += t * coeffs[i][d];
                t *= k;
            }
        }
        Z denom = 0, mpow = 1;
        for (auto d = 0; d <= deg; ++d) {
            denom += mpow * coeffs[0][d];
            mpow *= m;
        }
        ret[m] = -s / denom;
    }
    return ret;
}

template <typename Z>
std::vector<std::vector<Z>> find_recurrence_relation(const std::vector<Z> &terms, int deg,
                                                     bool verify = true, bool verbose = true) {
    auto n = int(terms.size());
    auto B = (n + 2) / (deg + 2); // number of blocks
    auto C = B * (deg + 1);       // number of columns
    auto R = n - (B - 1);         // number of rows
    assert(2 <= B);
    assert(C - 1 <= R);
    auto error = [](int order, int d) {
        std::fprintf(stderr,
                     "Error: Could not find a recurrence relation "
                     "of order <= %d and degree <= %d.\n\n",
                     order, d);
        assert(0);
    };
    std::vector<std::vector<Z>> mat(R, std::vector<Z>(C));
    for (auto y = 0; y < R; ++y) {
        for (auto b = 0; b < B; ++b) {
            auto v = terms[y + b];
            for (auto d = 0; d <= deg; ++d) {
                mat[y][b * (deg + 1) + d] = v;
                v *= y + b;
            }
        }
    }
    auto rank = 0;
    for (auto x = 0; x < C; ++x) {
        auto pivot = -1;
        for (auto y = rank; y < R; ++y) {
            if (mat[y][x] != 0) {
                pivot = y;
                break;
            }
        }
        if (pivot < 0) {
            break;
        }
        if (pivot != rank) {
            std::swap(mat[rank], mat[pivot]);
        }
        auto inv = mat[rank][x].inv();
        for (auto x2 = x; x2 < C; ++x2) {
            mat[rank][x2] *= inv;
        }
        for (auto y = rank + 1; y < R; ++y) {
            if (mat[y][x] != 0) {
                auto c = -mat[y][x];
                for (auto x2 = x; x2 < C; ++x2) {
                    mat[y][x2] += c * mat[rank][x2];
                }
            }
        }
        ++rank;
    }
    if (rank == C) {
        error(B - 1, deg);
    }
    for (auto y = rank - 1; 0 <= y; --y) {
        if (mat[y][rank] != 0) {
            assert(mat[y][y] == 1);
            auto c = -mat[y][rank];
            for (int y2 = 0; y2 < y; ++y2) {
                mat[y2][rank] += c * mat[y2][y];
            }
        }
    }
    auto order = rank / (deg + 1);
    std::vector<std::vector<Z>> ret(order + 1, std::vector<Z>(deg + 1));
    ret[0][rank % (deg + 1)] = 1;
    for (auto y = rank - 1; 0 <= y; --y) {
        auto k = order - y / (deg + 1);
        auto d = y % (deg + 1);
        ret[k][d] = -mat[y][rank];
    }
    if (verify) {
        auto extended_terms =
            extended(n - 1, ret, std::vector<Z>(terms.begin(), terms.begin() + order));
        for (auto i = 0; i < int(terms.size()); ++i) {
            if (terms[i] != extended_terms[i]) {
                error(B - 1, deg);
            }
        }
    }
    if (verbose) {
        auto mod = Z::mod();
        auto last = verify ? n - 1 : order + R - 1;
        std::fprintf(stderr,
                     "[ Found a recurrence relation ]\n"
                     "- order %d\n"
                     "- degree %d\n"
                     "- verified up to a(%d) (number of non-trivial terms: %d)\n",
                     order, deg, last, (last + 1) - ((deg + 2) * (order + 1) - 2));
        std::fprintf(stderr, "{\n");
        for (auto k = 0; k <= order; ++k) {
            std::fprintf(stderr, "  {");
            for (auto d = 0; d <= deg; ++d) {
                if (d) {
                    std::fprintf(stderr, ", ");
                }
                auto v = ret[k][d].val();
                std::fprintf(stderr, "%d", v <= mod / 2 ? v : v - mod);
            }
            std::fprintf(stderr, "}%s\n", k == order ? "" : ",");
        }
        std::fprintf(stderr, "}\n\n");
    }
    return ret;
}

#endif // P_RECURSIVE_HPP