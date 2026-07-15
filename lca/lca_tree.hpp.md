---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lca/lca_tree.test.cpp
    title: test/lca/lca_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/lca/lca_tree_jump.test.cpp
    title: test/lca/lca_tree_jump.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lca/lca_tree.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <bit>\n#include <cassert>\n#include <queue>\n#include <vector>\n\nstruct lca_tree\
    \ {\n    lca_tree(const std::vector<std::vector<int>> &adj, int root)\n      \
    \  : n_(static_cast<int>(adj.size())), root_(root),\n          lg_(std::bit_width(static_cast<unsigned>(n_))\
    \ - 1),\n          table_((lg_ + 1) * n_), depth_(n_) {\n        depth_[root_]\
    \ = 0;\n        table_[root_] = root_;\n        std::queue<int> q;\n        q.emplace(root_);\n\
    \        while (!q.empty()) {\n            auto u = q.front();\n            q.pop();\n\
    \            for (auto v : adj[u]) {\n                if (v != table_[u]) {\n\
    \                    depth_[v] = depth_[u] + 1;\n                    table_[v]\
    \ = u;\n                    q.emplace(v);\n                }\n            }\n\
    \        }\n        for (auto i = 1; i <= lg_; ++i) {\n            for (auto u\
    \ = 0; u < n_; ++u) {\n                auto parent = table_[(i - 1) * n_ + u];\n\
    \                table_[i * n_ + u] = table_[(i - 1) * n_ + parent];\n       \
    \     }\n        }\n    }\n    int kth_parent(int u, int k) const {\n        assert(0\
    \ <= u && u < n_ && 0 <= k);\n        for (auto i = 0; i <= lg_; ++i) {\n    \
    \        if ((k >> i) & 1) {\n                u = table_[i * n_ + u];\n      \
    \      }\n        }\n        return u;\n    }\n    int lca(int u, int v) const\
    \ {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        if (depth_[u]\
    \ < depth_[v]) {\n            std::swap(u, v);\n        }\n        u = kth_parent(u,\
    \ depth_[u] - depth_[v]);\n        if (u == v) {\n            return u;\n    \
    \    }\n        for (auto i = lg_; i >= 0; i--) {\n            if (table_[i *\
    \ n_ + u] != table_[i * n_ + v]) {\n                u = table_[i * n_ + u];\n\
    \                v = table_[i * n_ + v];\n            }\n        }\n        return\
    \ table_[u];\n    }\n    int distance(int u, int v) const {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        return depth_[u] + depth_[v] -\
    \ 2 * depth_[lca(u, v)];\n    }\n    int jump(int u, int v, int k) const {\n \
    \       assert(0 <= u && u < n_ && 0 <= v && v < n_ && 0 <= k);\n        auto\
    \ l = lca(u, v);\n        auto ul = depth_[u] - depth_[l];\n        auto vl =\
    \ depth_[v] - depth_[l];\n        if (ul + vl < k) {\n            return -1;\n\
    \        }\n        if (k <= ul) {\n            return kth_parent(u, k);\n   \
    \     } else {\n            return kth_parent(v, ul + vl - k);\n        }\n  \
    \  }\n    const int n_, root_, lg_;\n    std::vector<int> table_, depth_;\n};\n\
    \n\n"
  code: "#ifndef LCA_TREE_HPP\n#define LCA_TREE_HPP\n\n#include <algorithm>\n#include\
    \ <bit>\n#include <cassert>\n#include <queue>\n#include <vector>\n\nstruct lca_tree\
    \ {\n    lca_tree(const std::vector<std::vector<int>> &adj, int root)\n      \
    \  : n_(static_cast<int>(adj.size())), root_(root),\n          lg_(std::bit_width(static_cast<unsigned>(n_))\
    \ - 1),\n          table_((lg_ + 1) * n_), depth_(n_) {\n        depth_[root_]\
    \ = 0;\n        table_[root_] = root_;\n        std::queue<int> q;\n        q.emplace(root_);\n\
    \        while (!q.empty()) {\n            auto u = q.front();\n            q.pop();\n\
    \            for (auto v : adj[u]) {\n                if (v != table_[u]) {\n\
    \                    depth_[v] = depth_[u] + 1;\n                    table_[v]\
    \ = u;\n                    q.emplace(v);\n                }\n            }\n\
    \        }\n        for (auto i = 1; i <= lg_; ++i) {\n            for (auto u\
    \ = 0; u < n_; ++u) {\n                auto parent = table_[(i - 1) * n_ + u];\n\
    \                table_[i * n_ + u] = table_[(i - 1) * n_ + parent];\n       \
    \     }\n        }\n    }\n    int kth_parent(int u, int k) const {\n        assert(0\
    \ <= u && u < n_ && 0 <= k);\n        for (auto i = 0; i <= lg_; ++i) {\n    \
    \        if ((k >> i) & 1) {\n                u = table_[i * n_ + u];\n      \
    \      }\n        }\n        return u;\n    }\n    int lca(int u, int v) const\
    \ {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        if (depth_[u]\
    \ < depth_[v]) {\n            std::swap(u, v);\n        }\n        u = kth_parent(u,\
    \ depth_[u] - depth_[v]);\n        if (u == v) {\n            return u;\n    \
    \    }\n        for (auto i = lg_; i >= 0; i--) {\n            if (table_[i *\
    \ n_ + u] != table_[i * n_ + v]) {\n                u = table_[i * n_ + u];\n\
    \                v = table_[i * n_ + v];\n            }\n        }\n        return\
    \ table_[u];\n    }\n    int distance(int u, int v) const {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        return depth_[u] + depth_[v] -\
    \ 2 * depth_[lca(u, v)];\n    }\n    int jump(int u, int v, int k) const {\n \
    \       assert(0 <= u && u < n_ && 0 <= v && v < n_ && 0 <= k);\n        auto\
    \ l = lca(u, v);\n        auto ul = depth_[u] - depth_[l];\n        auto vl =\
    \ depth_[v] - depth_[l];\n        if (ul + vl < k) {\n            return -1;\n\
    \        }\n        if (k <= ul) {\n            return kth_parent(u, k);\n   \
    \     } else {\n            return kth_parent(v, ul + vl - k);\n        }\n  \
    \  }\n    const int n_, root_, lg_;\n    std::vector<int> table_, depth_;\n};\n\
    \n#endif // LCA_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: lca/lca_tree.hpp
  requiredBy: []
  timestamp: '2025-09-12 21:56:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lca/lca_tree.test.cpp
  - test/lca/lca_tree_jump.test.cpp
documentation_of: lca/lca_tree.hpp
layout: document
title: LCA Tree
---

# LCA Tree

## Overview

The `lca_tree` is a data structure designed to find the **Lowest Common Ancestor (LCA)** of any two nodes in a tree. This implementation utilizes the **Binary Lifting** technique.

Key functionalities include:
* Finding the $k$-th ancestor of a given node.
* Finding the Lowest Common Ancestor (LCA) of two nodes.
* Calculating the distance between two nodes.
* Finding a specific node on the path between two other nodes.

---

## Constructor

`lca_tree(const std::vector<std::vector<int>>& adj, int root)`

* **Description**: Constructs the `lca_tree` from an adjacency list `adj` and a specified `root` node.
* **Constraints**:
    * The graph given by `adj` must be a tree.
    * `adj.size()` = $N$.
    * $0 \le \text{root} < N$.
* **Time Complexity**: $O(N \log N)$, where $N$ is the number of nodes.

---

## Member Functions

#### `int kth_parent(int u, int k)`

* **Description**: Returns the $k$-th ancestor of node `u`.
* **Constraints**:
    * $0 \le u < N$
    * $0 \le k$
* **Time Complexity**: $O(\log N)$

#### `int lca(int u, int v)`

* **Description**: Returns the Lowest Common Ancestor of nodes `u` and `v`.
* **Constraints**:
    * $0 \le u < N$
    * $0 \le v < N$
* **Time Complexity**: $O(\log N)$

---

#### `int distance(int u, int v)`

* **Description**: Returns the distance between nodes `u` and `v`.
* **Constraints**:
    * $0 \le u < N$
    * $0 \le v < N$
* **Time Complexity**: $O(\log N)$

---

#### `int jump(int u, int v, int k)`

* **Description**: Returns the node that is $k$ steps away from `u` on the simple path to `v`. If the path length is less than `k`, it returns `-1`.
* **Constraints**:
    * $0 \le u < N$
    * $0 \le v < N$
    * $0 \le k$
* **Time Complexity**: $O(\log N)$
