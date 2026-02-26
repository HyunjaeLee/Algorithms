---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/directed_mst.hpp
    title: graph/directed_mst.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/directed_mst.test.cpp
    title: test/graph/directed_mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/directed_mst_minimum_cost_arborescence.test.cpp
    title: test/graph/directed_mst_minimum_cost_arborescence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/offline_dynamic_connectivity.test.cpp
    title: test/graph/offline_dynamic_connectivity.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structures/rollback_disjoint_set.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <stack>\n#include <utility>\n#include <vector>\n\nstruct\
    \ rollback_disjoint_set {\n    explicit rollback_disjoint_set(int n) : n_(n),\
    \ parent_or_size_(n, -1) {}\n    int find(int u) const {\n        return parent_or_size_[u]\
    \ < 0 ? u : find(parent_or_size_[u]);\n    }\n    bool merge(int u, int v) {\n\
    \        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        u = find(u);\n\
    \        v = find(v);\n        if (u == v) {\n            return false;\n    \
    \    }\n        if (-parent_or_size_[u] < -parent_or_size_[v]) {\n           \
    \ std::swap(u, v);\n        }\n        history_.emplace(v, parent_or_size_[v]);\n\
    \        parent_or_size_[u] += parent_or_size_[v];\n        parent_or_size_[v]\
    \ = u;\n        return true;\n    }\n    bool same(int u, int v) const {\n   \
    \     assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        return find(u) ==\
    \ find(v);\n    }\n    int size(int u) const {\n        assert(0 <= u && u < n_);\n\
    \        return -parent_or_size_[find(u)];\n    }\n    void rollback() {\n   \
    \     assert(!history_.empty());\n        auto [v, val] = history_.top();\n  \
    \      auto u = parent_or_size_[v];\n        parent_or_size_[v] = val;\n     \
    \   parent_or_size_[u] -= val;\n        history_.pop();\n    }\n    void rollback(int\
    \ count) {\n        for (auto i = 0; i < count; ++i) {\n            rollback();\n\
    \        }\n    }\n\nprivate:\n    int n_;\n    std::vector<int> parent_or_size_;\n\
    \    std::stack<std::pair<int, int>> history_;\n};\n\n\n"
  code: "#ifndef ROLLBACK_DISJOINT_SET_HPP\n#define ROLLBACK_DISJOINT_SET_HPP\n\n\
    #include <cassert>\n#include <stack>\n#include <utility>\n#include <vector>\n\n\
    struct rollback_disjoint_set {\n    explicit rollback_disjoint_set(int n) : n_(n),\
    \ parent_or_size_(n, -1) {}\n    int find(int u) const {\n        return parent_or_size_[u]\
    \ < 0 ? u : find(parent_or_size_[u]);\n    }\n    bool merge(int u, int v) {\n\
    \        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        u = find(u);\n\
    \        v = find(v);\n        if (u == v) {\n            return false;\n    \
    \    }\n        if (-parent_or_size_[u] < -parent_or_size_[v]) {\n           \
    \ std::swap(u, v);\n        }\n        history_.emplace(v, parent_or_size_[v]);\n\
    \        parent_or_size_[u] += parent_or_size_[v];\n        parent_or_size_[v]\
    \ = u;\n        return true;\n    }\n    bool same(int u, int v) const {\n   \
    \     assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        return find(u) ==\
    \ find(v);\n    }\n    int size(int u) const {\n        assert(0 <= u && u < n_);\n\
    \        return -parent_or_size_[find(u)];\n    }\n    void rollback() {\n   \
    \     assert(!history_.empty());\n        auto [v, val] = history_.top();\n  \
    \      auto u = parent_or_size_[v];\n        parent_or_size_[v] = val;\n     \
    \   parent_or_size_[u] -= val;\n        history_.pop();\n    }\n    void rollback(int\
    \ count) {\n        for (auto i = 0; i < count; ++i) {\n            rollback();\n\
    \        }\n    }\n\nprivate:\n    int n_;\n    std::vector<int> parent_or_size_;\n\
    \    std::stack<std::pair<int, int>> history_;\n};\n\n#endif // ROLLBACK_DISJOINT_SET_HPP"
  dependsOn: []
  isVerificationFile: false
  path: data_structures/rollback_disjoint_set.hpp
  requiredBy:
  - graph/directed_mst.hpp
  timestamp: '2026-02-03 20:57:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/directed_mst_minimum_cost_arborescence.test.cpp
  - test/graph/offline_dynamic_connectivity.test.cpp
  - test/graph/directed_mst.test.cpp
documentation_of: data_structures/rollback_disjoint_set.hpp
layout: document
redirect_from:
- /library/data_structures/rollback_disjoint_set.hpp
- /library/data_structures/rollback_disjoint_set.hpp.html
title: data_structures/rollback_disjoint_set.hpp
---
