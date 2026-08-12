#ifndef CSR_GRAPH_HPP
#define CSR_GRAPH_HPP

#include <cassert>
#include <ranges>
#include <vector>

template <typename EdgeWeight = int> struct CSRGraph {
    struct Edge {
        int u;
        int v;
        EdgeWeight w;
        int i;
    };
    CSRGraph(int n) : n_(n) {}
    void add_edge(int u, int v, EdgeWeight w = 1) {
        assert(!built_);
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        auto i = int(edges_.size());
        edges_.push_back({u, v, w, i});
    }
    void build_undirected() {
        assert(!built_);
        start_.assign(n_ + 1, 0);
        csr_.resize(2 * edges_.size());
        for (const auto &e : edges_) {
            ++start_[e.u + 1];
            ++start_[e.v + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto pos = start_;
        for (const auto &e : edges_) {
            csr_[pos[e.u]++] = {e.u, e.v, e.w, e.i};
            csr_[pos[e.v]++] = {e.v, e.u, e.w, e.i};
        }
        built_ = true;
    }
    void build_directed() {
        assert(!built_);
        start_.assign(n_ + 1, 0);
        csr_.resize(edges_.size());
        for (const auto &e : edges_) {
            ++start_[e.u + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto pos = start_;
        for (const auto &e : edges_) {
            csr_[pos[e.u]++] = e;
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
    std::vector<Edge> edges_;
    std::vector<Edge> csr_;
    std::vector<int> start_;
};

#endif // CSR_GRAPH_HPP