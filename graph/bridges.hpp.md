---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/bridges.test.cpp
    title: test/graph/bridges.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/bridges.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <utility>\n#include <vector>\n\nstd::vector<std::pair<int, int>> find_bridges(const\
    \ auto &g) {\n    auto n = (int)g.size();\n    auto timer = 0;\n    std::vector<int>\
    \ visited(n, false), tin(n, -1), low(n, -1);\n    std::vector<std::pair<int, int>>\
    \ bridges;\n    auto dfs = [&](auto self, int u, int p) -> void {\n        visited[u]\
    \ = true;\n        tin[u] = low[u] = timer++;\n        bool parent_skipped = false;\n\
    \        for (int v : g[u]) {\n            if (v == p && !parent_skipped) {\n\
    \                parent_skipped = true;\n                continue;\n         \
    \   }\n            if (visited[v]) {\n                low[u] = std::min(low[u],\
    \ tin[v]);\n            } else {\n                self(self, v, u);\n        \
    \        low[u] = std::min(low[u], low[v]);\n                if (tin[u] < low[v])\
    \ {\n                    bridges.emplace_back(u, v);\n                }\n    \
    \        }\n        }\n    };\n    for (int i = 0; i < n; ++i) {\n        if (!visited[i])\
    \ {\n            dfs(dfs, i, -1);\n        }\n    }\n    return bridges;\n}\n\n\
    \n"
  code: "#ifndef BRIDGES_HPP\n#define BRIDGES_HPP\n\n#include <algorithm>\n#include\
    \ <utility>\n#include <vector>\n\nstd::vector<std::pair<int, int>> find_bridges(const\
    \ auto &g) {\n    auto n = (int)g.size();\n    auto timer = 0;\n    std::vector<int>\
    \ visited(n, false), tin(n, -1), low(n, -1);\n    std::vector<std::pair<int, int>>\
    \ bridges;\n    auto dfs = [&](auto self, int u, int p) -> void {\n        visited[u]\
    \ = true;\n        tin[u] = low[u] = timer++;\n        bool parent_skipped = false;\n\
    \        for (int v : g[u]) {\n            if (v == p && !parent_skipped) {\n\
    \                parent_skipped = true;\n                continue;\n         \
    \   }\n            if (visited[v]) {\n                low[u] = std::min(low[u],\
    \ tin[v]);\n            } else {\n                self(self, v, u);\n        \
    \        low[u] = std::min(low[u], low[v]);\n                if (tin[u] < low[v])\
    \ {\n                    bridges.emplace_back(u, v);\n                }\n    \
    \        }\n        }\n    };\n    for (int i = 0; i < n; ++i) {\n        if (!visited[i])\
    \ {\n            dfs(dfs, i, -1);\n        }\n    }\n    return bridges;\n}\n\n\
    #endif // BRIDGES_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/bridges.hpp
  requiredBy: []
  timestamp: '2026-01-06 20:06:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/bridges.test.cpp
documentation_of: graph/bridges.hpp
layout: document
title: Bridges
---
### Source
+ [Finding bridges in a graph in $O(N+M)$ ](https://cp-algorithms.com/graph/bridge-searching.html)
