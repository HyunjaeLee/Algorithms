#ifndef POTENTIALIZED_ROLLBACK_DSU
#define POTENTIALIZED_ROLLBACK_DSU

#include <algorithm>
#include <cassert>
#include <tuple>
#include <vector>

// A is an abelian group
template <typename A> struct PotentializedRollbackDSU {
    explicit PotentializedRollbackDSU(int n)
        : n_(n), valid_(true), parent_or_size_(n, -1), potential_(n, A::e()) {}
    int leader(int u) const { return parent_or_size_[u] < 0 ? u : leader(parent_or_size_[u]); }
    // returns p_u
    A potential(int u) const {
        return parent_or_size_[u] < 0 ? A::e()
                                      : A::op(potential_[u], potential(parent_or_size_[u]));
    }
    // returns p_v - p_u
    A diff(int u, int v) const {
        auto p_u = potential(u);
        auto p_v = potential(v);
        return A::op(p_v, A::inv(p_u));
    }
    // returns history accumulation count for offline dynamic connectivity
    // p_u + w = p_v
    int merge(int u, int v, A w) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        auto p_v = A::op(A::op(potential(u), w), A::inv(potential(v)));
        u = leader(u);
        v = leader(v);
        if (u == v) {
            history_.emplace_back(-1, 0, valid_);
            if (!(p_v == A::e())) {
                valid_ = false;
            }
            return 1;
        }
        // insert tree v into tree u
        if (-parent_or_size_[u] < -parent_or_size_[v]) {
            std::swap(u, v);
            p_v = A::inv(p_v);
        }
        history_.emplace_back(v, parent_or_size_[v], valid_);
        parent_or_size_[u] += parent_or_size_[v];
        parent_or_size_[v] = u;
        potential_[v] = p_v;
        return 1;
    }
    bool same(int u, int v) const {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        return leader(u) == leader(v);
    }
    int size(int u) const {
        assert(0 <= u && u < n_);
        return -parent_or_size_[leader(u)];
    }
    void rollback() {
        assert(!history_.empty());
        auto [v, size, valid] = history_.back();
        if (~v) {
            auto u = parent_or_size_[v];
            parent_or_size_[v] = size;
            parent_or_size_[u] -= size;
            potential_[v] = A::e();
        } else {
            valid_ = valid;
        }
        history_.pop_back();
    }
    void rollback(int count) {
        for (auto i = 0; i < count; ++i) {
            rollback();
        }
    }
    bool is_valid() const { return valid_; }

private:
    int n_;
    bool valid_;
    std::vector<int> parent_or_size_;
    std::vector<A> potential_;
    std::vector<std::tuple<int, int, bool>> history_;
};

#endif // POTENTIALIZED_ROLLBACK_DSU