#ifndef CSR_GRAPH_HPP
#define CSR_GRAPH_HPP

#include <cassert>
#include <ranges>
#include <vector>

template <typename T> struct csr_graph {
    csr_graph(int n) : n_(n) {}
    void add_edge(int u, int v, T w) {
        assert(!built_);
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        edges_.push_back({u, v, w});
    }
    void build() {
        assert(!built_);
        start_.assign(n_ + 1, 0);
        csr_.resize(edges_.size());
        for (auto [u, v, w] : edges_) {
            ++start_[u + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto pos = start_;
        for (auto [u, v, w] : edges_) {
            csr_[pos[u]++] = {v, w};
        }
        built_ = true;
    }
    auto operator[](int u) const {
        assert(built_);
        assert(0 <= u && u < n_);
        return std::ranges::subrange(csr_.begin() + start_[u], csr_.begin() + start_[u + 1]);
    }
    int size() const { return n_; }

private:
    int n_;
    bool built_ = false;
    std::vector<std::tuple<int, int, T>> edges_;
    std::vector<std::pair<int, T>> csr_;
    std::vector<int> start_;
};

#endif // CSR_GRAPH_HPP