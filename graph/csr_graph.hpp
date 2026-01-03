#ifndef CSR_GRAPH_HPP
#define CSR_GRAPH_HPP

#include <cassert>
#include <ranges>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

template <typename NodeWeight = std::monostate, typename EdgeWeight = std::monostate>
struct CSRGraph {
    static constexpr bool HasNodeWeight = !std::is_same_v<NodeWeight, std::monostate>;
    CSRGraph(int n) : n_(n), start_(n + 1) {
        if constexpr (HasNodeWeight) {
            nodes_.resize(n_);
        }
    }
    void set_node(int u, NodeWeight w) {
        assert(0 <= u && u < n_);
        if constexpr (HasNodeWeight) {
            nodes_[u] = w;
        }
    }
    NodeWeight node_weight(int u) const {
        assert(0 <= u && u < n_);
        if constexpr (HasNodeWeight) {
            return nodes_[u];
        } else {
            return {};
        }
    }
    void add_edge(int u, int v, EdgeWeight w = {}) {
        assert(0 <= u && u < n_ && 0 <= v && v < n_);
        raw_edges_.push_back({u, v, w});
    }
    void build_undirected() {
        assert(!built_);
        edges_.resize(2 * raw_edges_.size());
        for (const auto &e : raw_edges_) {
            ++start_[e.u + 1];
            ++start_[e.v + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto counter = start_;
        for (const auto &e : raw_edges_) {
            edges_[counter[e.u]++] = {e.v, e.w};
            edges_[counter[e.v]++] = {e.u, e.w};
        }
        std::vector<RawEdge>().swap(raw_edges_);
        built_ = true;
    }
    void build_directed() {
        assert(!built_);
        edges_.resize(raw_edges_.size());
        for (const auto &e : raw_edges_) {
            ++start_[e.u + 1];
        }
        for (int i = 0; i < n_; ++i) {
            start_[i + 1] += start_[i];
        }
        auto counter = start_;
        for (const auto &e : raw_edges_) {
            edges_[counter[e.u]++] = {e.v, e.w};
        }
        std::vector<RawEdge>().swap(raw_edges_);
        built_ = true;
    }
    auto operator[](int u) const {
        assert(built_);
        assert(0 <= u && u < n_);
        constexpr auto f = [](Edge e) { return std::pair(e.to, e.w); };
        return std::ranges::subrange(edges_.begin() + start_[u], edges_.begin() + start_[u + 1]) |
               std::views::transform(f);
    }
    int size() const { return n_; }
    struct Edge {
        int to;
        [[no_unique_address]] EdgeWeight w;
    };
    struct RawEdge {
        int u, v;
        [[no_unique_address]] EdgeWeight w;
    };
    int n_;
    bool built_ = false;
    std::vector<Edge> edges_;
    std::vector<int> start_;
    std::vector<RawEdge> raw_edges_;
    std::vector<NodeWeight> nodes_;
};

#endif // CSR_GRAPH_HPP