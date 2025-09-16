---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/dominator_tree.test.cpp
    title: test/graph/dominator_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/dominator_tree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <vector>\n\nstruct dominator_tree\
    \ {\n    explicit dominator_tree(int n)\n        : n_(n), parent_(n), idom_(n,\
    \ -1), sdom_(n, -1), dsu_(n), label_(n),\n          graph_(n), rev_graph_(n) {\n\
    \        order_.reserve(n);\n        std::iota(dsu_.begin(), dsu_.end(), 0);\n\
    \        std::iota(label_.begin(), label_.end(), 0);\n    }\n    void add_edge(int\
    \ from, int to) {\n        assert(0 <= from && from < n_ && 0 <= to && to < n_);\n\
    \        graph_[from].push_back(to);\n        rev_graph_[to].push_back(from);\n\
    \    }\n    void run(int root) {\n        assert(0 <= root && root < n_);\n  \
    \      dfs(root);\n        std::vector<std::vector<int>> bucket(n_);\n       \
    \ std::vector<int> x(n_);\n        for (auto i = static_cast<int>(order_.size())\
    \ - 1; i >= 0; --i) {\n            auto u = order_[i];\n            for (auto\
    \ v : rev_graph_[u]) {\n                if (~sdom_[v]) {\n                   \
    \ sdom_[u] = std::min(sdom_[u], sdom_[eval(v)]);\n                }\n        \
    \    }\n            bucket[order_[sdom_[u]]].push_back(u);\n            for (auto\
    \ v : bucket[parent_[u]]) {\n                x[v] = eval(v);\n            }\n\
    \            bucket[parent_[u]].clear();\n            link(parent_[u], u);\n \
    \       }\n        for (auto i = 1; i < static_cast<int>(order_.size()); ++i)\
    \ {\n            auto u = order_[i], v = x[u];\n            idom_[u] = (sdom_[u]\
    \ == sdom_[v] ? sdom_[u] : idom_[v]);\n        }\n        for (auto i = 1; i <\
    \ static_cast<int>(order_.size()); ++i) {\n            auto u = order_[i];\n \
    \           idom_[u] = order_[idom_[u]];\n        }\n        idom_[root] = root;\n\
    \    }\n    int operator[](int u) const {\n        assert(0 <= u && u < n_);\n\
    \        return idom_[u];\n    }\n\nprivate:\n    void dfs(int u) {\n        sdom_[u]\
    \ = static_cast<int>(order_.size());\n        order_.push_back(u);\n        for\
    \ (auto v : graph_[u]) {\n            if (!~sdom_[v]) {\n                parent_[v]\
    \ = u;\n                dfs(v);\n            }\n        }\n    }\n    int find(int\
    \ u) {\n        if (dsu_[u] == u) {\n            return u;\n        }\n      \
    \  auto root = find(dsu_[u]);\n        if (sdom_[label_[u]] > sdom_[label_[dsu_[u]]])\
    \ {\n            label_[u] = label_[dsu_[u]];\n        }\n        return dsu_[u]\
    \ = root;\n    }\n    int eval(int u) {\n        find(u);\n        return label_[u];\n\
    \    }\n    void link(int u, int v) { dsu_[v] = u; }\n    int n_;\n    std::vector<int>\
    \ order_, parent_, idom_, sdom_, dsu_, label_;\n    std::vector<std::vector<int>>\
    \ graph_, rev_graph_;\n};\n\n\n"
  code: "#ifndef DOMINATOR_TREE_HPP\n#define DOMINATOR_TREE_HPP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <vector>\n\nstruct dominator_tree\
    \ {\n    explicit dominator_tree(int n)\n        : n_(n), parent_(n), idom_(n,\
    \ -1), sdom_(n, -1), dsu_(n), label_(n),\n          graph_(n), rev_graph_(n) {\n\
    \        order_.reserve(n);\n        std::iota(dsu_.begin(), dsu_.end(), 0);\n\
    \        std::iota(label_.begin(), label_.end(), 0);\n    }\n    void add_edge(int\
    \ from, int to) {\n        assert(0 <= from && from < n_ && 0 <= to && to < n_);\n\
    \        graph_[from].push_back(to);\n        rev_graph_[to].push_back(from);\n\
    \    }\n    void run(int root) {\n        assert(0 <= root && root < n_);\n  \
    \      dfs(root);\n        std::vector<std::vector<int>> bucket(n_);\n       \
    \ std::vector<int> x(n_);\n        for (auto i = static_cast<int>(order_.size())\
    \ - 1; i >= 0; --i) {\n            auto u = order_[i];\n            for (auto\
    \ v : rev_graph_[u]) {\n                if (~sdom_[v]) {\n                   \
    \ sdom_[u] = std::min(sdom_[u], sdom_[eval(v)]);\n                }\n        \
    \    }\n            bucket[order_[sdom_[u]]].push_back(u);\n            for (auto\
    \ v : bucket[parent_[u]]) {\n                x[v] = eval(v);\n            }\n\
    \            bucket[parent_[u]].clear();\n            link(parent_[u], u);\n \
    \       }\n        for (auto i = 1; i < static_cast<int>(order_.size()); ++i)\
    \ {\n            auto u = order_[i], v = x[u];\n            idom_[u] = (sdom_[u]\
    \ == sdom_[v] ? sdom_[u] : idom_[v]);\n        }\n        for (auto i = 1; i <\
    \ static_cast<int>(order_.size()); ++i) {\n            auto u = order_[i];\n \
    \           idom_[u] = order_[idom_[u]];\n        }\n        idom_[root] = root;\n\
    \    }\n    int operator[](int u) const {\n        assert(0 <= u && u < n_);\n\
    \        return idom_[u];\n    }\n\nprivate:\n    void dfs(int u) {\n        sdom_[u]\
    \ = static_cast<int>(order_.size());\n        order_.push_back(u);\n        for\
    \ (auto v : graph_[u]) {\n            if (!~sdom_[v]) {\n                parent_[v]\
    \ = u;\n                dfs(v);\n            }\n        }\n    }\n    int find(int\
    \ u) {\n        if (dsu_[u] == u) {\n            return u;\n        }\n      \
    \  auto root = find(dsu_[u]);\n        if (sdom_[label_[u]] > sdom_[label_[dsu_[u]]])\
    \ {\n            label_[u] = label_[dsu_[u]];\n        }\n        return dsu_[u]\
    \ = root;\n    }\n    int eval(int u) {\n        find(u);\n        return label_[u];\n\
    \    }\n    void link(int u, int v) { dsu_[v] = u; }\n    int n_;\n    std::vector<int>\
    \ order_, parent_, idom_, sdom_, dsu_, label_;\n    std::vector<std::vector<int>>\
    \ graph_, rev_graph_;\n};\n\n#endif // DOMINATOR_TREE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/dominator_tree.hpp
  requiredBy: []
  timestamp: '2022-11-22 05:54:44+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/dominator_tree.test.cpp
documentation_of: graph/dominator_tree.hpp
layout: document
redirect_from:
- /library/graph/dominator_tree.hpp
- /library/graph/dominator_tree.hpp.html
title: graph/dominator_tree.hpp
---
