#ifndef CSR_HPP
#define CSR_HPP

#include <cassert>
#include <ranges>
#include <utility>
#include <vector>

template <typename T> struct csr {
    explicit csr(int n) : n_(n) {}
    void add(int i, T x) {
        assert(!built_);
        assert(0 <= i && i < n_);
        buf_.emplace_back(i, x);
    }
    void build() {
        assert(!built_);
        ptr_.assign(n_ + 2, 0);
        csr_.resize(buf_.size());
        for (auto [i, x] : buf_) {
            ++ptr_[i + 2];
        }
        for (int i = 0; i < n_; ++i) {
            ptr_[i + 1] += ptr_[i];
        }
        for (auto [i, x] : buf_) {
            csr_[ptr_[i + 1]++] = x;
        }
        built_ = true;
    }
    auto operator[](int i) {
        assert(built_);
        assert(0 <= i && i < n_);
        return std::ranges::subrange(csr_.begin() + ptr_[i], csr_.begin() + ptr_[i + 1]);
    }
    auto operator[](int i) const {
        assert(built_);
        assert(0 <= i && i < n_);
        return std::ranges::subrange(csr_.begin() + ptr_[i], csr_.begin() + ptr_[i + 1]);
    }
    int size() const { return n_; }

private:
    int n_;
    bool built_ = false;
    std::vector<std::pair<int, T>> buf_;
    std::vector<T> csr_;
    std::vector<int> ptr_;
};

#endif // CSR_HPP