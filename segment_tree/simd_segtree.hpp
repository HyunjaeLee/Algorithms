#ifndef SIMD_SEGTREE_HPP
#define SIMD_SEGTREE_HPP

#include <array>
#include <utility>
#include <cstddef>
#include <algorithm>

#pragma GCC optimize("O3,unroll-loops")
#ifdef __x86_64__
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif

template <typename T, int N> struct simd_segtree {
    static constexpr int cache_size = 64;
    static constexpr int reg_size = 32;
    static constexpr int reg_count = cache_size / reg_size;
    static constexpr int branching = cache_size / sizeof(T);
    static constexpr int branching_bits = std::__lg(branching);
    typedef T __attribute__((vector_size(reg_size))) vec;
    struct Precalc {
        alignas(cache_size) T mask[branching][branching];
        constexpr Precalc() : mask{} {
            for (int i = 0; i < branching; ++i)
                for (int j = 0; j < branching; ++j)
                    mask[i][j] = (i < j ? -1 : 0);
        }
    };
    static constexpr Precalc precalc{};
    static constexpr int calc_height(int n) {
        return (n <= branching ? 1 : calc_height(n / branching) + 1);
    }
    static constexpr int calc_offset(int h) {
        int s = 0, n = N;
        while (h--) {
            n = (n + branching - 1) / branching;
            s += n * branching + branching;
        }
        return s;
    }
    static constexpr int round(int k) { return k & ~(branching - 1); }
    static constexpr int H = calc_height(N);
    template <std::size_t... indices>
    static constexpr std::array<int, H + 1> calc_offsets(std::index_sequence<indices...>) {
        return {calc_offset(indices)...};
    }
    static constexpr auto offset = calc_offsets(std::make_index_sequence<H + 1>());
    alignas(cache_size) T values[offset[H]]{};
    void add(int k, T x) {
        vec v = x + vec{};
        for (int h = 0; h != H; ++h) {
            auto a = (vec *)&values[offset[h] + round(k)];
            const auto m = (const vec *)&precalc.mask[k % branching];
            for (int i = 0; i != reg_count; ++i)
                a[i] += v & m[i];
            k >>= branching_bits;
        }
    }
    T sum(int i) {
        T s = 0;
        for (int h = 0; h != H; ++h) {
            s += values[offset[h] + i];
            i >>= branching_bits;
        }
        return s;
    }
    T sum(int i, int j) {
        T s = 0;
        for (int h = 0; h != H; ++h) {
            s -= values[offset[h] + i];
            s += values[offset[h] + j];
            i >>= branching_bits;
            j >>= branching_bits;
        }
        return s;
    }
};

#endif // SIMD_SEGTREE_HPP