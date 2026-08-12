---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/csr_graph.hpp
    title: graph/csr_graph.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/tree/tree_diameter.test.cpp
    title: test/tree/tree_diameter.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/tree_diameter.hpp\"\n\n\n\n#line 1 \"graph/csr_graph.hpp\"\
    \n\n\n\n#include <cassert>\n#include <ranges>\n#include <vector>\n\ntemplate <typename\
    \ EdgeWeight = int> struct CSRGraph {\n    struct Edge {\n        int u;\n   \
    \     int v;\n        EdgeWeight w;\n        int i;\n    };\n    CSRGraph(int\
    \ n) : n_(n) {}\n    void add_edge(int u, int v, EdgeWeight w = 1) {\n       \
    \ assert(!built_);\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n  \
    \      auto i = int(edges_.size());\n        edges_.push_back({u, v, w, i});\n\
    \    }\n    void build_undirected() {\n        assert(!built_);\n        start_.assign(n_\
    \ + 1, 0);\n        csr_.resize(2 * edges_.size());\n        for (const auto &e\
    \ : edges_) {\n            ++start_[e.u + 1];\n            ++start_[e.v + 1];\n\
    \        }\n        for (int i = 0; i < n_; ++i) {\n            start_[i + 1]\
    \ += start_[i];\n        }\n        auto pos = start_;\n        for (const auto\
    \ &e : edges_) {\n            csr_[pos[e.u]++] = {e.u, e.v, e.w, e.i};\n     \
    \       csr_[pos[e.v]++] = {e.v, e.u, e.w, e.i};\n        }\n        built_ =\
    \ true;\n    }\n    void build_directed() {\n        assert(!built_);\n      \
    \  start_.assign(n_ + 1, 0);\n        csr_.resize(edges_.size());\n        for\
    \ (const auto &e : edges_) {\n            ++start_[e.u + 1];\n        }\n    \
    \    for (int i = 0; i < n_; ++i) {\n            start_[i + 1] += start_[i];\n\
    \        }\n        auto pos = start_;\n        for (const auto &e : edges_) {\n\
    \            csr_[pos[e.u]++] = e;\n        }\n        built_ = true;\n    }\n\
    \    auto operator[](int u) const {\n        assert(built_);\n        assert(0\
    \ <= u && u < n_);\n        return std::ranges::subrange(csr_.begin() + start_[u],\
    \ csr_.begin() + start_[u + 1]);\n    }\n    int size() const { return n_; }\n\
    \nprivate:\n    int n_;\n    bool built_ = false;\n    std::vector<Edge> edges_;\n\
    \    std::vector<Edge> csr_;\n    std::vector<int> start_;\n};\n\n\n#line 5 \"\
    tree/tree_diameter.hpp\"\n#include <algorithm>\n#line 8 \"tree/tree_diameter.hpp\"\
    \n\n// requires non-negative edge weights\n// return (diameter, path)\n// for\
    \ an unweighted tree, centers are path[d / 2] and path[(d + 1) / 2]\ntemplate\
    \ <typename EdgeWeight> auto tree_diameter(const CSRGraph<EdgeWeight> &g) {\n\
    \    assert(0 < g.size());\n    auto n = int(g.size());\n    std::vector<int>\
    \ parent(n, -1);\n    std::vector<EdgeWeight> depth(n);\n    auto dfs = [&](int\
    \ x) {\n        std::vector<int> st;\n        st.push_back(x);\n        parent[x]\
    \ = -1;\n        depth[x] = 0;\n        while (!st.empty()) {\n            auto\
    \ u = st.back();\n            st.pop_back();\n            for (const auto &e :\
    \ g[u]) {\n                if (e.v != parent[u]) {\n                    st.push_back(e.v);\n\
    \                    parent[e.v] = u;\n                    depth[e.v] = depth[u]\
    \ + e.w;\n                }\n            }\n        }\n        auto it = std::ranges::max_element(depth);\n\
    \        auto r = int(it - depth.begin());\n        return std::pair(r, *it);\n\
    \    };\n    auto x = dfs(0).first;\n    auto [y, d] = dfs(x);\n    std::vector<int>\
    \ path;\n    for (auto u = y; ~u; u = parent[u]) {\n        path.push_back(u);\n\
    \    }\n    return std::pair(d, path);\n}\n\n\n"
  code: "#ifndef TREE_DIAMETER_HPP\n#define TREE_DIAMETER_HPP\n\n#include \"graph/csr_graph.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n// requires non-negative\
    \ edge weights\n// return (diameter, path)\n// for an unweighted tree, centers\
    \ are path[d / 2] and path[(d + 1) / 2]\ntemplate <typename EdgeWeight> auto tree_diameter(const\
    \ CSRGraph<EdgeWeight> &g) {\n    assert(0 < g.size());\n    auto n = int(g.size());\n\
    \    std::vector<int> parent(n, -1);\n    std::vector<EdgeWeight> depth(n);\n\
    \    auto dfs = [&](int x) {\n        std::vector<int> st;\n        st.push_back(x);\n\
    \        parent[x] = -1;\n        depth[x] = 0;\n        while (!st.empty()) {\n\
    \            auto u = st.back();\n            st.pop_back();\n            for\
    \ (const auto &e : g[u]) {\n                if (e.v != parent[u]) {\n        \
    \            st.push_back(e.v);\n                    parent[e.v] = u;\n      \
    \              depth[e.v] = depth[u] + e.w;\n                }\n            }\n\
    \        }\n        auto it = std::ranges::max_element(depth);\n        auto r\
    \ = int(it - depth.begin());\n        return std::pair(r, *it);\n    };\n    auto\
    \ x = dfs(0).first;\n    auto [y, d] = dfs(x);\n    std::vector<int> path;\n \
    \   for (auto u = y; ~u; u = parent[u]) {\n        path.push_back(u);\n    }\n\
    \    return std::pair(d, path);\n}\n\n#endif // TREE_DIAMETER_HPP"
  dependsOn:
  - graph/csr_graph.hpp
  isVerificationFile: false
  path: tree/tree_diameter.hpp
  requiredBy: []
  timestamp: '2026-08-12 07:38:15+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/tree/tree_diameter.test.cpp
documentation_of: tree/tree_diameter.hpp
layout: document
redirect_from:
- /library/tree/tree_diameter.hpp
- /library/tree/tree_diameter.hpp.html
title: tree/tree_diameter.hpp
---
