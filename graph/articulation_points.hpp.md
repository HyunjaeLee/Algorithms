---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/articulation_points.test.cpp
    title: test/graph/articulation_points.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/articulation_points.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\nstd::vector<int> find_cutpoints(const auto &g) {\n    auto\
    \ n = (int)g.size();\n    auto timer = 0;\n    std::vector<int> visited(n), tin(n,\
    \ -1), low(n, -1);\n    std::vector<int> cutpoints;\n    auto dfs = [&](auto self,\
    \ int u, int p) -> void {\n        visited[u] = true;\n        tin[u] = low[u]\
    \ = timer++;\n        auto children = 0;\n        auto is_cutpoint = false;\n\
    \        for (auto v : g[u]) {\n            if (v == p) {\n                continue;\n\
    \            }\n            if (visited[v]) {\n                low[u] = std::min(low[u],\
    \ tin[v]);\n            } else {\n                self(self, v, u);\n        \
    \        low[u] = std::min(low[u], low[v]);\n                is_cutpoint |= (tin[u]\
    \ <= low[v] && p != -1);\n                ++children;\n            }\n       \
    \ }\n        is_cutpoint |= (p == -1 && 1 < children);\n        if (is_cutpoint)\
    \ {\n            cutpoints.push_back(u);\n        }\n    };\n    for (auto i =\
    \ 0; i < n; ++i) {\n        if (!visited[i]) {\n            dfs(dfs, i, -1);\n\
    \        }\n    }\n    return cutpoints;\n}\n\n\n"
  code: "#ifndef ARTICULATION_POINTS_HPP\n#define ARTICULATION_POINTS_HPP\n\n#include\
    \ <algorithm>\n#include <vector>\n\nstd::vector<int> find_cutpoints(const auto\
    \ &g) {\n    auto n = (int)g.size();\n    auto timer = 0;\n    std::vector<int>\
    \ visited(n), tin(n, -1), low(n, -1);\n    std::vector<int> cutpoints;\n    auto\
    \ dfs = [&](auto self, int u, int p) -> void {\n        visited[u] = true;\n \
    \       tin[u] = low[u] = timer++;\n        auto children = 0;\n        auto is_cutpoint\
    \ = false;\n        for (auto v : g[u]) {\n            if (v == p) {\n       \
    \         continue;\n            }\n            if (visited[v]) {\n          \
    \      low[u] = std::min(low[u], tin[v]);\n            } else {\n            \
    \    self(self, v, u);\n                low[u] = std::min(low[u], low[v]);\n \
    \               is_cutpoint |= (tin[u] <= low[v] && p != -1);\n              \
    \  ++children;\n            }\n        }\n        is_cutpoint |= (p == -1 && 1\
    \ < children);\n        if (is_cutpoint) {\n            cutpoints.push_back(u);\n\
    \        }\n    };\n    for (auto i = 0; i < n; ++i) {\n        if (!visited[i])\
    \ {\n            dfs(dfs, i, -1);\n        }\n    }\n    return cutpoints;\n}\n\
    \n#endif // ARTICULATION_POINTS_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/articulation_points.hpp
  requiredBy: []
  timestamp: '2026-01-09 14:45:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/articulation_points.test.cpp
documentation_of: graph/articulation_points.hpp
layout: document
title: Articulation Points
---
### Source
+ [Finding articulation points in a graph in $O(N+M)$](https://cp-algorithms.com/graph/cutpoints.html)
