---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/enumerate_triangles.test.cpp
    title: test/graph/enumerate_triangles.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/enumerate_triangles.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <utility>\n#include <vector>\n\n// O(n + m * sqrt(m))\nvoid enumerate_triangles(int\
    \ n, const std::vector<std::pair<int, int>> &edges, auto f) {\n    std::vector<int>\
    \ deg(n);\n    for (auto [u, v] : edges) {\n        ++deg[u];\n        ++deg[v];\n\
    \    }\n    std::vector<std::vector<int>> g(n);\n    for (auto [u, v] : edges)\
    \ {\n        if (std::pair(deg[u], u) < std::pair(deg[v], v)) {\n            std::swap(u,\
    \ v);\n        }\n        g[u].push_back(v);\n    }\n    std::vector<int> color(n,\
    \ -1);\n    for (auto i = 0; i < n; ++i) {\n        for (auto j : g[i]) {\n  \
    \          color[j] = i;\n        }\n        for (auto j : g[i]) {\n         \
    \   for (auto k : g[j]) {\n                if (color[k] == i) {\n            \
    \        f(i, j, k);\n                }\n            }\n        }\n    }\n}\n\n\
    \n"
  code: "#ifndef ENUMERATE_TRIANGLES_HPP\n#define ENUMERATE_TRIANGLES_HPP\n\n#include\
    \ <algorithm>\n#include <utility>\n#include <vector>\n\n// O(n + m * sqrt(m))\n\
    void enumerate_triangles(int n, const std::vector<std::pair<int, int>> &edges,\
    \ auto f) {\n    std::vector<int> deg(n);\n    for (auto [u, v] : edges) {\n \
    \       ++deg[u];\n        ++deg[v];\n    }\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (auto [u, v] : edges) {\n        if (std::pair(deg[u], u) < std::pair(deg[v],\
    \ v)) {\n            std::swap(u, v);\n        }\n        g[u].push_back(v);\n\
    \    }\n    std::vector<int> color(n, -1);\n    for (auto i = 0; i < n; ++i) {\n\
    \        for (auto j : g[i]) {\n            color[j] = i;\n        }\n       \
    \ for (auto j : g[i]) {\n            for (auto k : g[j]) {\n                if\
    \ (color[k] == i) {\n                    f(i, j, k);\n                }\n    \
    \        }\n        }\n    }\n}\n\n#endif // ENUMERATE_TRIANGLES_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/enumerate_triangles.hpp
  requiredBy: []
  timestamp: '2026-10-14 18:10:34+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/enumerate_triangles.test.cpp
documentation_of: graph/enumerate_triangles.hpp
layout: document
redirect_from:
- /library/graph/enumerate_triangles.hpp
- /library/graph/enumerate_triangles.hpp.html
title: graph/enumerate_triangles.hpp
---
