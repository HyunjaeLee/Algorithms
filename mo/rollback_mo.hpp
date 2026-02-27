#ifndef ROLLBACK_MO_HPP
#define ROLLBACK_MO_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>

struct RollbackMo {
    explicit RollbackMo(int n) : n_(n) {}
    void add(int l, int r) { // [l, r)
        assert(0 <= l && l <= r && r <= n_);
        queries_.emplace_back(l, r);
    }
    void solve(auto add, auto rollback, auto eval) { solve(add, add, rollback, eval); }
    void solve(auto add_left, auto add_right, auto rollback, auto eval) {
        const auto q = int(queries_.size());
        if (q == 0) {
            return;
        }
        const auto b_num = int(std::sqrt(q));
        const auto b_sz = (n_ + b_num - 1) / b_num;
        std::vector<std::vector<int>> buckets((n_ - 1) / b_sz + 1);
        auto rollback_n = [&](int n) {
            for (auto i = 0; i < n; ++i) {
                rollback();
            }
        };
        auto naive = [&](int qid) {
            auto [l, r] = queries_[qid];
            for (auto i = l; i < r; ++i) {
                add_right(i);
            }
            eval(qid);
            rollback_n(r - l);
        };
        for (auto qid = 0; qid < q; ++qid) {
            auto [l, r] = queries_[qid];
            auto il = l / b_sz, ir = r / b_sz;
            if (il == ir) {
                naive(qid);
            } else {
                buckets[il].push_back(qid);
            }
        }
        for (auto &bucket : buckets) {
            if (bucket.empty()) {
                continue;
            }
            std::ranges::sort(bucket, {}, [&](int i) { return queries_[i].second; });
            auto lmax = 0;
            for (auto qid : bucket) {
                auto [l, r] = queries_[qid];
                lmax = std::max(lmax, l);
            }
            auto l = lmax, r = lmax;
            for (auto qid : bucket) {
                auto [ql, qr] = queries_[qid];
                while (r < qr) {
                    add_right(r++);
                }
                while (ql < l) {
                    add_left(--l);
                }
                eval(qid);
                rollback_n(lmax - l);
                l = lmax;
            }
            rollback_n(r - l);
        }
    }

private:
    int n_;
    std::vector<std::pair<int, int>> queries_;
};

#endif // ROLLBACK_MO_HPP