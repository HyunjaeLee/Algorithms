#ifndef SQRT_FREQ_TABLE_HPP
#define SQRT_FREQ_TABLE_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

struct SqrtFreqTable {
    explicit SqrtFreqTable(int max_val)
        : m_(std::max(1, max_val)), b_sz_(int(std::sqrt(m_))), freq_(m_ + 1),
          bucket_(m_ / b_sz_ + 1) {}
    void insert(int x) { // O(1)
        assert(0 <= x && x <= m_);
        ++freq_[x];
        ++bucket_[x / b_sz_];
        ++total_;
        distinct_ += int(freq_[x] == 1);
    }
    void erase(int x) { // O(1)
        assert(0 <= x && x <= m_);
        assert(0 < freq_[x]);
        --freq_[x];
        --bucket_[x / b_sz_];
        --total_;
        distinct_ -= int(freq_[x] == 0);
    }
    int count(int x) const { // O(1)
        assert(0 <= x && x <= m_);
        return freq_[x];
    }
    int size() const { return total_; }
    int count_distinct() const { return distinct_; }
    int kth(int k) const { // O(sqrt(M)), 0-indexed
        auto cnt = 0;
        for (auto i = 0; i < m_ / b_sz_ + 1; ++i) {
            if (cnt + bucket_[i] <= k) {
                cnt += bucket_[i];
                continue;
            }
            auto x = i * b_sz_;
            while ((cnt += freq_[x]) <= k) {
                ++x;
            }
            return x;
        }
        return -1;
    };
    int rank(int x) const { // O(sqrt(M)), count y s.t. y < x
        assert(0 <= x);
        if (m_ < x) {
            return total_;
        }
        auto cnt = 0;
        for (auto i = 0; i < x / b_sz_; ++i) {
            cnt += bucket_[i];
        }
        for (auto i = x / b_sz_ * b_sz_; i < x; ++i) {
            cnt += freq_[i];
        }
        return cnt;
    }

private:
    const int m_, b_sz_;
    std::vector<int> freq_, bucket_;
    int total_ = 0, distinct_ = 0;
};

#endif // SQRT_FREQ_TABLE_HPP