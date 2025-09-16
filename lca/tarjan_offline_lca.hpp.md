---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lca/tarjan_offline_lca.test.cpp
    title: test/lca/tarjan_offline_lca.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lca/tarjan_offline_lca.hpp\"\n\n\n\n#include <utility>\n\
    #include <vector>\n\nstruct dsu {\n    dsu(int n) : parent_or_size(n, -1) {}\n\
    \    int find(int u) {\n        return parent_or_size[u] < 0\n               \
    \    ? u\n                   : parent_or_size[u] = find(parent_or_size[u]);\n\
    \    }\n    void merge(int u, int v) {\n        u = find(u);\n        v = find(v);\n\
    \        if (u != v) {\n            if (-parent_or_size[u] < -parent_or_size[v])\
    \ {\n                std::swap(u, v);\n            }\n            parent_or_size[u]\
    \ += parent_or_size[v];\n            parent_or_size[v] = u;\n        }\n    }\n\
    \nprivate:\n    std::vector<int> parent_or_size;\n};\n\nstruct tarjan_offline_lca\
    \ {\n    tarjan_offline_lca(const std::vector<std::vector<int>> &graph, int root,\n\
    \                       const std::vector<std::pair<int, int>> &queries)\n   \
    \     : graph_(graph), root_(root), queries_(graph.size()),\n          result_(queries.size()),\
    \ ancestor_(graph.size()), color_(graph.size()),\n          d_(graph.size()) {\n\
    \        auto q = static_cast<int>(queries.size());\n        for (auto i = 0;\
    \ i < q; ++i) {\n            auto [u, v] = queries[i];\n            queries_[u].push_back({v,\
    \ i});\n            queries_[v].push_back({u, i});\n        }\n    }\n    std::vector<int>\
    \ lca() {\n        lca(root_, root_);\n        return result_;\n    }\n\nprivate:\n\
    \    void lca(int u, int parent) {\n        ancestor_[d_.find(u)] = u;\n     \
    \   for (auto v : graph_[u])\n            if (v != parent) {\n               \
    \ lca(v, u);\n                d_.merge(u, v);\n                ancestor_[d_.find(u)]\
    \ = u;\n            }\n        color_[u] = 1;\n        for (auto [v, i] : queries_[u])\
    \ {\n            if (color_[v]) {\n                result_[i] = ancestor_[d_.find(v)];\n\
    \            }\n        }\n    }\n    std::vector<std::vector<int>> graph_;\n\
    \    int root_;\n    std::vector<std::vector<std::pair<int, int>>> queries_;\n\
    \    std::vector<int> result_, ancestor_;\n    std::vector<char> color_;\n   \
    \ dsu d_;\n};\n\n\n"
  code: "#ifndef TARJAN_OFFLINE_LCA_HPP\n#define TARJAN_OFFLINE_LCA_HPP\n\n#include\
    \ <utility>\n#include <vector>\n\nstruct dsu {\n    dsu(int n) : parent_or_size(n,\
    \ -1) {}\n    int find(int u) {\n        return parent_or_size[u] < 0\n      \
    \             ? u\n                   : parent_or_size[u] = find(parent_or_size[u]);\n\
    \    }\n    void merge(int u, int v) {\n        u = find(u);\n        v = find(v);\n\
    \        if (u != v) {\n            if (-parent_or_size[u] < -parent_or_size[v])\
    \ {\n                std::swap(u, v);\n            }\n            parent_or_size[u]\
    \ += parent_or_size[v];\n            parent_or_size[v] = u;\n        }\n    }\n\
    \nprivate:\n    std::vector<int> parent_or_size;\n};\n\nstruct tarjan_offline_lca\
    \ {\n    tarjan_offline_lca(const std::vector<std::vector<int>> &graph, int root,\n\
    \                       const std::vector<std::pair<int, int>> &queries)\n   \
    \     : graph_(graph), root_(root), queries_(graph.size()),\n          result_(queries.size()),\
    \ ancestor_(graph.size()), color_(graph.size()),\n          d_(graph.size()) {\n\
    \        auto q = static_cast<int>(queries.size());\n        for (auto i = 0;\
    \ i < q; ++i) {\n            auto [u, v] = queries[i];\n            queries_[u].push_back({v,\
    \ i});\n            queries_[v].push_back({u, i});\n        }\n    }\n    std::vector<int>\
    \ lca() {\n        lca(root_, root_);\n        return result_;\n    }\n\nprivate:\n\
    \    void lca(int u, int parent) {\n        ancestor_[d_.find(u)] = u;\n     \
    \   for (auto v : graph_[u])\n            if (v != parent) {\n               \
    \ lca(v, u);\n                d_.merge(u, v);\n                ancestor_[d_.find(u)]\
    \ = u;\n            }\n        color_[u] = 1;\n        for (auto [v, i] : queries_[u])\
    \ {\n            if (color_[v]) {\n                result_[i] = ancestor_[d_.find(v)];\n\
    \            }\n        }\n    }\n    std::vector<std::vector<int>> graph_;\n\
    \    int root_;\n    std::vector<std::vector<std::pair<int, int>>> queries_;\n\
    \    std::vector<int> result_, ancestor_;\n    std::vector<char> color_;\n   \
    \ dsu d_;\n};\n\n#endif // TARJAN_OFFLINE_LCA_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: lca/tarjan_offline_lca.hpp
  requiredBy: []
  timestamp: '2022-09-04 17:18:59+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lca/tarjan_offline_lca.test.cpp
documentation_of: lca/tarjan_offline_lca.hpp
layout: document
redirect_from:
- /library/lca/tarjan_offline_lca.hpp
- /library/lca/tarjan_offline_lca.hpp.html
title: lca/tarjan_offline_lca.hpp
---
