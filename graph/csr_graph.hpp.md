---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dp/rerooting.test.cpp
    title: test/dp/rerooting.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/csr_graph.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <ranges>\n#include <type_traits>\n#include <utility>\n#include <variant>\n#include\
    \ <vector>\n\ntemplate <typename NodeWeight = std::monostate, typename EdgeWeight\
    \ = std::monostate>\nstruct CSRGraph {\n    static constexpr bool HasNodeWeight\
    \ = !std::is_same_v<NodeWeight, std::monostate>;\n    CSRGraph(int n) : n_(n),\
    \ start_(n + 1) {\n        if constexpr (HasNodeWeight) {\n            nodes_.resize(n_);\n\
    \        }\n    }\n    void set_node(int u, NodeWeight w) {\n        assert(0\
    \ <= u && u < n_);\n        if constexpr (HasNodeWeight) {\n            nodes_[u]\
    \ = w;\n        }\n    }\n    NodeWeight node_weight(int u) const {\n        assert(0\
    \ <= u && u < n_);\n        if constexpr (HasNodeWeight) {\n            return\
    \ nodes_[u];\n        } else {\n            return {};\n        }\n    }\n   \
    \ void add_edge(int u, int v, EdgeWeight w = {}) {\n        assert(0 <= u && u\
    \ < n_ && 0 <= v && v < n_);\n        raw_edges_.push_back({u, v, w});\n    }\n\
    \    void build_undirected() {\n        assert(!built_);\n        edges_.resize(2\
    \ * raw_edges_.size());\n        for (const auto &e : raw_edges_) {\n        \
    \    ++start_[e.u + 1];\n            ++start_[e.v + 1];\n        }\n        for\
    \ (int i = 0; i < n_; ++i) {\n            start_[i + 1] += start_[i];\n      \
    \  }\n        auto counter = start_;\n        for (const auto &e : raw_edges_)\
    \ {\n            edges_[counter[e.u]++] = {e.v, e.w};\n            edges_[counter[e.v]++]\
    \ = {e.u, e.w};\n        }\n        std::vector<RawEdge>().swap(raw_edges_);\n\
    \        built_ = true;\n    }\n    void build_directed() {\n        assert(!built_);\n\
    \        edges_.resize(raw_edges_.size());\n        for (const auto &e : raw_edges_)\
    \ {\n            ++start_[e.u + 1];\n        }\n        for (int i = 0; i < n_;\
    \ ++i) {\n            start_[i + 1] += start_[i];\n        }\n        auto counter\
    \ = start_;\n        for (const auto &e : raw_edges_) {\n            edges_[counter[e.u]++]\
    \ = {e.v, e.w};\n        }\n        std::vector<RawEdge>().swap(raw_edges_);\n\
    \        built_ = true;\n    }\n    auto operator[](int u) const {\n        assert(built_);\n\
    \        assert(0 <= u && u < n_);\n        constexpr auto f = [](Edge e) { return\
    \ std::pair(e.to, e.w); };\n        return std::ranges::subrange(edges_.begin()\
    \ + start_[u], edges_.begin() + start_[u + 1]) |\n               std::views::transform(f);\n\
    \    }\n    int size() const { return n_; }\n    struct Edge {\n        int to;\n\
    \        [[no_unique_address]] EdgeWeight w;\n    };\n    struct RawEdge {\n \
    \       int u, v;\n        [[no_unique_address]] EdgeWeight w;\n    };\n    int\
    \ n_;\n    bool built_ = false;\n    std::vector<Edge> edges_;\n    std::vector<int>\
    \ start_;\n    std::vector<RawEdge> raw_edges_;\n    std::vector<NodeWeight> nodes_;\n\
    };\n\n\n"
  code: "#ifndef CSR_GRAPH_HPP\n#define CSR_GRAPH_HPP\n\n#include <cassert>\n#include\
    \ <ranges>\n#include <type_traits>\n#include <utility>\n#include <variant>\n#include\
    \ <vector>\n\ntemplate <typename NodeWeight = std::monostate, typename EdgeWeight\
    \ = std::monostate>\nstruct CSRGraph {\n    static constexpr bool HasNodeWeight\
    \ = !std::is_same_v<NodeWeight, std::monostate>;\n    CSRGraph(int n) : n_(n),\
    \ start_(n + 1) {\n        if constexpr (HasNodeWeight) {\n            nodes_.resize(n_);\n\
    \        }\n    }\n    void set_node(int u, NodeWeight w) {\n        assert(0\
    \ <= u && u < n_);\n        if constexpr (HasNodeWeight) {\n            nodes_[u]\
    \ = w;\n        }\n    }\n    NodeWeight node_weight(int u) const {\n        assert(0\
    \ <= u && u < n_);\n        if constexpr (HasNodeWeight) {\n            return\
    \ nodes_[u];\n        } else {\n            return {};\n        }\n    }\n   \
    \ void add_edge(int u, int v, EdgeWeight w = {}) {\n        assert(0 <= u && u\
    \ < n_ && 0 <= v && v < n_);\n        raw_edges_.push_back({u, v, w});\n    }\n\
    \    void build_undirected() {\n        assert(!built_);\n        edges_.resize(2\
    \ * raw_edges_.size());\n        for (const auto &e : raw_edges_) {\n        \
    \    ++start_[e.u + 1];\n            ++start_[e.v + 1];\n        }\n        for\
    \ (int i = 0; i < n_; ++i) {\n            start_[i + 1] += start_[i];\n      \
    \  }\n        auto counter = start_;\n        for (const auto &e : raw_edges_)\
    \ {\n            edges_[counter[e.u]++] = {e.v, e.w};\n            edges_[counter[e.v]++]\
    \ = {e.u, e.w};\n        }\n        std::vector<RawEdge>().swap(raw_edges_);\n\
    \        built_ = true;\n    }\n    void build_directed() {\n        assert(!built_);\n\
    \        edges_.resize(raw_edges_.size());\n        for (const auto &e : raw_edges_)\
    \ {\n            ++start_[e.u + 1];\n        }\n        for (int i = 0; i < n_;\
    \ ++i) {\n            start_[i + 1] += start_[i];\n        }\n        auto counter\
    \ = start_;\n        for (const auto &e : raw_edges_) {\n            edges_[counter[e.u]++]\
    \ = {e.v, e.w};\n        }\n        std::vector<RawEdge>().swap(raw_edges_);\n\
    \        built_ = true;\n    }\n    auto operator[](int u) const {\n        assert(built_);\n\
    \        assert(0 <= u && u < n_);\n        constexpr auto f = [](Edge e) { return\
    \ std::pair(e.to, e.w); };\n        return std::ranges::subrange(edges_.begin()\
    \ + start_[u], edges_.begin() + start_[u + 1]) |\n               std::views::transform(f);\n\
    \    }\n    int size() const { return n_; }\n    struct Edge {\n        int to;\n\
    \        [[no_unique_address]] EdgeWeight w;\n    };\n    struct RawEdge {\n \
    \       int u, v;\n        [[no_unique_address]] EdgeWeight w;\n    };\n    int\
    \ n_;\n    bool built_ = false;\n    std::vector<Edge> edges_;\n    std::vector<int>\
    \ start_;\n    std::vector<RawEdge> raw_edges_;\n    std::vector<NodeWeight> nodes_;\n\
    };\n\n#endif // CSR_GRAPH_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/csr_graph.hpp
  requiredBy: []
  timestamp: '2026-01-04 01:20:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dp/rerooting.test.cpp
documentation_of: graph/csr_graph.hpp
layout: document
redirect_from:
- /library/graph/csr_graph.hpp
- /library/graph/csr_graph.hpp.html
title: graph/csr_graph.hpp
---
