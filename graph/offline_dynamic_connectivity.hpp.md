---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/offline_dynamic_connectivity.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cassert>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\ntemplate <typename DisjointSet> struct\
    \ offline_dynamic_connectivity {\n    explicit offline_dynamic_connectivity(int\
    \ n) : n_(n), timer_(0) {}\n    void toggle_edge(int u, int v) {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        if (u > v) {\n            std::swap(u,\
    \ v);\n        }\n        edges_.push_back({u, v, timer_});\n    }\n    int snapshot()\
    \ { return timer_++; }\n    void reserve(int n) { edges_.reserve(n); }\n    template\
    \ <typename Function>\n    std::vector<std::invoke_result_t<Function, DisjointSet,\
    \ int>>\n    solve(Function f) {\n        auto k = timer_;\n        if (k == 0)\
    \ {\n            return {};\n        }\n        std::sort(edges_.begin(), edges_.end());\n\
    \        std::vector<std::vector<std::pair<int, int>>> segment(2 * k);\n     \
    \   auto edges_size = static_cast<int>(edges_.size());\n        for (auto i =\
    \ 0; i < edges_size; ++i) {\n            auto [u, v, l] = edges_[i];\n       \
    \     auto r = k;\n            if (i + 1 < edges_size && u == edges_[i + 1][0]\
    \ &&\n                v == edges_[i + 1][1]) {\n                r = edges_[++i][2];\n\
    \            }\n            l += k;\n            r += k;\n            while (l\
    \ < r) {\n                if (l & 1) {\n                    segment[l++].push_back({u,\
    \ v});\n                }\n                if (r & 1) {\n                    segment[--r].push_back({u,\
    \ v});\n                }\n                l >>= 1;\n                r >>= 1;\n\
    \            }\n        }\n        DisjointSet dsu(n_);\n        std::vector<std::invoke_result_t<Function,\
    \ DisjointSet, int>> result(k);\n        auto dfs = [&](auto self, int node) ->\
    \ void {\n            auto count = 0;\n            for (auto [u, v] : segment[node])\
    \ {\n                if (dsu.merge(u, v)) {\n                    ++count;\n  \
    \              }\n            }\n            if (node < k) {\n               \
    \ self(self, 2 * node);\n                self(self, 2 * node + 1);\n         \
    \   } else {\n                result[node - k] = f(dsu, node - k);\n         \
    \   }\n            dsu.rollback(count);\n        };\n        dfs(dfs, 1);\n  \
    \      return result;\n    }\n\nprivate:\n    int n_, timer_;\n    std::vector<std::array<int,\
    \ 3>> edges_;\n};\n\n\n"
  code: "#ifndef OFFLINE_DYNAMIC_CONNECTIVITY_HPP\n#define OFFLINE_DYNAMIC_CONNECTIVITY_HPP\n\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\ntemplate <typename DisjointSet> struct\
    \ offline_dynamic_connectivity {\n    explicit offline_dynamic_connectivity(int\
    \ n) : n_(n), timer_(0) {}\n    void toggle_edge(int u, int v) {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        if (u > v) {\n            std::swap(u,\
    \ v);\n        }\n        edges_.push_back({u, v, timer_});\n    }\n    int snapshot()\
    \ { return timer_++; }\n    void reserve(int n) { edges_.reserve(n); }\n    template\
    \ <typename Function>\n    std::vector<std::invoke_result_t<Function, DisjointSet,\
    \ int>>\n    solve(Function f) {\n        auto k = timer_;\n        if (k == 0)\
    \ {\n            return {};\n        }\n        std::sort(edges_.begin(), edges_.end());\n\
    \        std::vector<std::vector<std::pair<int, int>>> segment(2 * k);\n     \
    \   auto edges_size = static_cast<int>(edges_.size());\n        for (auto i =\
    \ 0; i < edges_size; ++i) {\n            auto [u, v, l] = edges_[i];\n       \
    \     auto r = k;\n            if (i + 1 < edges_size && u == edges_[i + 1][0]\
    \ &&\n                v == edges_[i + 1][1]) {\n                r = edges_[++i][2];\n\
    \            }\n            l += k;\n            r += k;\n            while (l\
    \ < r) {\n                if (l & 1) {\n                    segment[l++].push_back({u,\
    \ v});\n                }\n                if (r & 1) {\n                    segment[--r].push_back({u,\
    \ v});\n                }\n                l >>= 1;\n                r >>= 1;\n\
    \            }\n        }\n        DisjointSet dsu(n_);\n        std::vector<std::invoke_result_t<Function,\
    \ DisjointSet, int>> result(k);\n        auto dfs = [&](auto self, int node) ->\
    \ void {\n            auto count = 0;\n            for (auto [u, v] : segment[node])\
    \ {\n                if (dsu.merge(u, v)) {\n                    ++count;\n  \
    \              }\n            }\n            if (node < k) {\n               \
    \ self(self, 2 * node);\n                self(self, 2 * node + 1);\n         \
    \   } else {\n                result[node - k] = f(dsu, node - k);\n         \
    \   }\n            dsu.rollback(count);\n        };\n        dfs(dfs, 1);\n  \
    \      return result;\n    }\n\nprivate:\n    int n_, timer_;\n    std::vector<std::array<int,\
    \ 3>> edges_;\n};\n\n#endif // OFFLINE_DYNAMIC_CONNECTIVITY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/offline_dynamic_connectivity.hpp
  requiredBy: []
  timestamp: '2022-09-09 09:09:24+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/offline_dynamic_connectivity.hpp
layout: document
redirect_from:
- /library/graph/offline_dynamic_connectivity.hpp
- /library/graph/offline_dynamic_connectivity.hpp.html
title: graph/offline_dynamic_connectivity.hpp
---
