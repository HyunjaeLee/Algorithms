---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/dijkstra.test.cpp
    title: test/graph/dijkstra.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/goldberg_radzik.test.cpp
    title: test/graph/goldberg_radzik.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/tree/tree_diameter.test.cpp
    title: test/tree/tree_diameter.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/csr_graph.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <ranges>\n#include <vector>\n\ntemplate <typename T> struct csr_graph {\n  \
    \  csr_graph(int n) : n_(n) {}\n    void add_edge(int u, int v, T w) {\n     \
    \   assert(!built_);\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n\
    \        edges_.push_back({u, v, w});\n    }\n    void build() {\n        assert(!built_);\n\
    \        start_.assign(n_ + 1, 0);\n        csr_.resize(edges_.size());\n    \
    \    for (auto [u, v, w] : edges_) {\n            ++start_[u + 1];\n        }\n\
    \        for (int i = 0; i < n_; ++i) {\n            start_[i + 1] += start_[i];\n\
    \        }\n        auto pos = start_;\n        for (auto [u, v, w] : edges_)\
    \ {\n            csr_[pos[u]++] = {v, w};\n        }\n        built_ = true;\n\
    \    }\n    auto operator[](int u) const {\n        assert(built_);\n        assert(0\
    \ <= u && u < n_);\n        return std::ranges::subrange(csr_.begin() + start_[u],\
    \ csr_.begin() + start_[u + 1]);\n    }\n    int size() const { return n_; }\n\
    \nprivate:\n    int n_;\n    bool built_ = false;\n    std::vector<std::tuple<int,\
    \ int, T>> edges_;\n    std::vector<std::pair<int, T>> csr_;\n    std::vector<int>\
    \ start_;\n};\n\n\n"
  code: "#ifndef CSR_GRAPH_HPP\n#define CSR_GRAPH_HPP\n\n#include <cassert>\n#include\
    \ <ranges>\n#include <vector>\n\ntemplate <typename T> struct csr_graph {\n  \
    \  csr_graph(int n) : n_(n) {}\n    void add_edge(int u, int v, T w) {\n     \
    \   assert(!built_);\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n\
    \        edges_.push_back({u, v, w});\n    }\n    void build() {\n        assert(!built_);\n\
    \        start_.assign(n_ + 1, 0);\n        csr_.resize(edges_.size());\n    \
    \    for (auto [u, v, w] : edges_) {\n            ++start_[u + 1];\n        }\n\
    \        for (int i = 0; i < n_; ++i) {\n            start_[i + 1] += start_[i];\n\
    \        }\n        auto pos = start_;\n        for (auto [u, v, w] : edges_)\
    \ {\n            csr_[pos[u]++] = {v, w};\n        }\n        built_ = true;\n\
    \    }\n    auto operator[](int u) const {\n        assert(built_);\n        assert(0\
    \ <= u && u < n_);\n        return std::ranges::subrange(csr_.begin() + start_[u],\
    \ csr_.begin() + start_[u + 1]);\n    }\n    int size() const { return n_; }\n\
    \nprivate:\n    int n_;\n    bool built_ = false;\n    std::vector<std::tuple<int,\
    \ int, T>> edges_;\n    std::vector<std::pair<int, T>> csr_;\n    std::vector<int>\
    \ start_;\n};\n\n#endif // CSR_GRAPH_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/csr_graph.hpp
  requiredBy: []
  timestamp: '2026-10-12 17:31:27+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/goldberg_radzik.test.cpp
  - test/graph/dijkstra.test.cpp
  - test/tree/tree_diameter.test.cpp
documentation_of: graph/csr_graph.hpp
layout: document
redirect_from:
- /library/graph/csr_graph.hpp
- /library/graph/csr_graph.hpp.html
title: graph/csr_graph.hpp
---
