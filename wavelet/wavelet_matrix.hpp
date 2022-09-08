#ifndef WAVELET_MATRIX_HPP
#define WAVELET_MATRIX_HPP

#include <algorithm>
#include <cassert>
#include <limits>
#include <type_traits>
#include <vector>

struct bit_vector {
    explicit bit_vector(int n) : data_((n + 63) >> 6), sum_(data_.size() + 1) {}
    void set(int pos) { data_[pos >> 6] |= 1ULL << (pos & 63); }
    int rank(int l, int r, bool value) const {
        auto count = rank(r) - rank(l);
        return value ? count : r - l - count;
    }
    bool operator[](int pos) const {
        return static_cast<bool>(data_[pos >> 6] >> (pos & 63) & 1);
    }
    void build() {
        for (auto i = 0; i < static_cast<int>(data_.size()); ++i) {
            sum_[i + 1] = sum_[i] + __builtin_popcountll(data_[i]);
        }
    }

private:
    // Returns the number of bits that are set to true in [0, pos)
    int rank(int pos) const {
        return sum_[pos >> 6] +
               __builtin_popcountll(data_[pos >> 6] &
                                    ((1ULL << (pos & 63)) - 1ULL));
    }
    std::vector<unsigned long long> data_;
    std::vector<int> sum_;
};

template <typename T> struct wavelet_matrix {
    // data must not be empty
    wavelet_matrix(std::vector<T> data)
        : n_(static_cast<int>(data.size())),
          log_(std::numeric_limits<T>::digits), data_(log_, bit_vector(n_)),
          mid_(log_) {
        assert(std::all_of(data.begin(), data.end(),
                           [](auto x) { return x >= 0; }));
        for (auto i = log_ - 1; i >= 0; --i) {
            for (auto j = 0; j < n_; ++j) {
                if (data[j] >> i & 1) {
                    data_[i].set(j);
                }
            }
            data_[i].build();
            auto it =
                std::stable_partition(data.begin(), data.end(),
                                      [&](auto x) { return !(x >> i & 1); });
            mid_[i] = static_cast<int>(it - data.begin());
        }
    }
    T access(int pos) const {
        assert(0 <= pos && pos < n_);
        T result = 0;
        for (auto i = log_ - 1; i >= 0; --i) {
            if (data_[i][pos]) {
                result |= static_cast<T>(1) << i;
                pos = mid_[i] + data_[i].rank(0, pos, true);
            } else {
                pos = data_[i].rank(0, pos, false);
            }
        }
        return result;
    }
    int rank(int l, int r, T x) const {
        assert(0 <= l && l <= r && r <= n_);
        for (auto i = log_ - 1; i >= 0; --i) {
            if (x >> i & 1) {
                l = mid_[i] + data_[i].rank(0, l, true);
                r = mid_[i] + data_[i].rank(0, r, true);
            } else {
                l = data_[i].rank(0, l, false);
                r = data_[i].rank(0, r, false);
            }
        }
        return r - l;
    }
    T quantile(int l, int r, int k) const {
        assert(0 <= l && l <= r && r <= n_ && 0 <= k && k < r - l);
        T result = 0;
        for (auto i = log_ - 1; i >= 0; --i) {
            if (auto count = data_[i].rank(l, r, false); count <= k) {
                result |= static_cast<T>(1) << i;
                k -= count;
                l = mid_[i] + data_[i].rank(0, l, true);
                r = mid_[i] + data_[i].rank(0, r, true);
            } else {
                l = data_[i].rank(0, l, false);
                r = data_[i].rank(0, r, false);
            }
        }
        return result;
    }
    int range(int l, int r, T x, T y) const {
        return range(l, r, y) - range(l, r, x);
    }

private:
    int range(int l, int r, T x) const {
        auto count = 0;
        for (auto i = log_ - 1; i >= 0; --i) {
            if (x >> i & 1) {
                count += data_[i].rank(l, r, false);
                l = mid_[i] + data_[i].rank(0, l, true);
                r = mid_[i] + data_[i].rank(0, r, true);
            } else {
                l = data_[i].rank(0, l, false);
                r = data_[i].rank(0, r, false);
            }
        }
        return count;
    }
    const int n_, log_;
    std::vector<bit_vector> data_;
    std::vector<int> mid_;
};

#endif // WAVELET_MATRIX_HPP