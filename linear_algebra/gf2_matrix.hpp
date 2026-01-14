#ifndef GF2_MATRIX_HPP
#define GF2_MATRIX_HPP

#include <bit>
#include <string_view>
#include <vector>

#ifdef __x86_64__
#define USE_AVX2
#endif

#ifdef USE_AVX2
#include <immintrin.h>
#endif

struct GF2Matrix {
    GF2Matrix(int r, int c) : rows_(r), cols_(c), stride_((c + 63) / 64) {
        data_ = new unsigned long long[rows_ * stride_]{};
    }
    ~GF2Matrix() { delete[] data_; }
    void set(int r, int c) { data_[r * stride_ + (c / 64)] |= (1ULL << (c % 64)); }
    void flip(int r, int c) { data_[r * stride_ + (c / 64)] ^= (1ULL << (c % 64)); }
    bool get(int r, int c) { return (data_[r * stride_ + (c / 64)] >> (c % 64)) & 1; }
#ifdef USE_AVX2
    __attribute__((target("avx2"))) void xor_rows(unsigned long long *d,
                                                  const unsigned long long *s, int start_idx) {
        int i = start_idx;
        for (; i + 4 <= stride_; i += 4) {
            auto dst = reinterpret_cast<__m256i *>(&d[i]);
            auto src = reinterpret_cast<const __m256i *>(&s[i]);
            auto sum = _mm256_xor_si256(_mm256_loadu_si256(dst), _mm256_loadu_si256(src));
            _mm256_storeu_si256(dst, sum);
        }
        for (; i < stride_; ++i) {
            d[i] ^= s[i];
        }
    }
#else
    void xor_rows(unsigned long long *d, const unsigned long long *s, int start_idx) {
        for (int i = start_idx; i < stride_; ++i) {
            d[i] ^= s[i];
        }
    }
#endif
#ifdef USE_AVX2
    __attribute__((target("avx2"))) void set_row(int row, std::string_view s) {
        auto n = (int)s.size();
        auto one = _mm256_set1_epi8('1');
        auto str = s.data();
        auto dst = (unsigned int *)data_;
        auto i = 0;
        for (; i + 32 <= n; i += 32) {
            auto src = reinterpret_cast<const __m256i *>(&str[i]);
            dst[row * stride_ * 2 + i / 32] =
                (unsigned int)_mm256_movemask_epi8(_mm256_cmpeq_epi8(_mm256_loadu_si256(src), one));
        }
        for (; i < n; i++) {
            if (s[i] == '1') {
                set(row, i);
            }
        }
    }
#else
    void set_row(int row, std::string_view s) {
        auto n = (int)s.size();
        for (auto i = 0; i < n; i++) {
            if (s[i] == '1') {
                set(row, i);
            }
        }
    }
#endif
    int gaussian_elimination() { // O(min(N, M) * N * M / 64)
        int pivot_row = 0;
        for (int col = 0; col < cols_ && pivot_row < rows_; ++col) {
            int chunk_idx = col / 64;
            unsigned long long bit_mask = (1ULL << (col % 64));
            int target = -1;
            for (int i = pivot_row; i < rows_; ++i) {
                if (data_[i * stride_ + chunk_idx] & bit_mask) {
                    target = i;
                    break;
                }
            }
            if (target == -1) {
                continue;
            }
            if (pivot_row != target) {
                xor_rows(data_ + pivot_row * stride_, data_ + target * stride_, chunk_idx);
            }
            for (int i = pivot_row + 1; i < rows_; ++i) {
                if (data_[i * stride_ + chunk_idx] & bit_mask) {
                    xor_rows(data_ + i * stride_, data_ + pivot_row * stride_, chunk_idx);
                }
            }
            ++pivot_row;
        }
        return pivot_row;
    }
    int gauss_jordan_elimination() {
        int pivot_row = 0;
        for (int col = 0; col < cols_ && pivot_row < rows_; ++col) {
            int chunk_idx = col / 64;
            unsigned long long bit_mask = (1ULL << (col % 64));
            int target = -1;
            for (int i = pivot_row; i < rows_; ++i) {
                if (data_[i * stride_ + chunk_idx] & bit_mask) {
                    target = i;
                    break;
                }
            }
            if (target == -1) {
                continue;
            }
            if (pivot_row != target) {
                xor_rows(data_ + pivot_row * stride_, data_ + target * stride_, chunk_idx);
            }
            for (int i = 0; i < rows_; ++i) {
                if (i != pivot_row && (data_[i * stride_ + chunk_idx] & bit_mask)) {
                    xor_rows(data_ + i * stride_, data_ + pivot_row * stride_, chunk_idx);
                }
            }
            ++pivot_row;
        }
        return pivot_row;
    }
    template <typename T = std::vector<bool>> std::vector<T> solve() {
        auto rank = gauss_jordan_elimination();
        std::vector<int> pivot(rank);
        std::vector<char> is_pivot_col(cols_);
        for (auto i = 0, j = 0; i < rank;) {
            if (data_[i * stride_ + j]) {
                pivot[i] = 64 * j + std::countr_zero(data_[i * stride_ + j]);
                is_pivot_col[pivot[i]] = true;
                ++i;
            } else {
                ++j;
            }
        }
        if (is_pivot_col[cols_ - 1]) {
            return {};
        }
        T ans(cols_ - 1);
        for (auto i = 0; i < rank; ++i) {
            ans[pivot[i]] = get(i, cols_ - 1);
        }
        std::vector<T> ret = {ans};
        ret.reserve(cols_ - rank);
        for (auto j = 0; j < cols_ - 1; ++j) {
            if (is_pivot_col[j]) {
                continue;
            }
            T basis(cols_ - 1);
            basis[j] = true;
            for (auto i = 0; i < rank; ++i) {
                basis[pivot[i]] = get(i, j);
            }
            ret.push_back(basis);
        }
        return ret;
    }
    const int rows_, cols_, stride_;
    unsigned long long *data_;
};

#endif // GF2_MATRIX_HPP