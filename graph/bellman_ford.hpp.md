---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/bellman_ford.test.cpp
    title: test/graph/bellman_ford.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/bellman_ford.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <limits>\n#include <tuple>\n#include <vector>\n\ntemplate <typename T, T inf\
    \ = std::numeric_limits<T>::max() / 2>\nstd::vector<T> bellman_ford(int n, const\
    \ std::vector<std::tuple<int, int, T>> &edges, int src) {\n    std::vector<T>\
    \ dist(n, inf);\n    dist[src] = 0;\n    for (auto i = 0; i < n; ++i) {\n    \
    \    for (auto [u, v, w] : edges) {\n            if (dist[u] < inf && dist[u]\
    \ + w < dist[v]) {\n                dist[v] = (i < n - 1) ? std::max(-inf, dist[u]\
    \ + w) : -inf;\n            }\n        }\n    }\n    for (auto i = 0; i < n; ++i)\
    \ {\n        for (auto [u, v, w] : edges) {\n            if (dist[u] == -inf)\
    \ {\n                dist[v] = -inf;\n            }\n        }\n    }\n    return\
    \ dist;\n}\n\n\n"
  code: "#ifndef BELLMAN_FORD_HPP\n#define BELLMAN_FORD_HPP\n\n#include <algorithm>\n\
    #include <limits>\n#include <tuple>\n#include <vector>\n\ntemplate <typename T,\
    \ T inf = std::numeric_limits<T>::max() / 2>\nstd::vector<T> bellman_ford(int\
    \ n, const std::vector<std::tuple<int, int, T>> &edges, int src) {\n    std::vector<T>\
    \ dist(n, inf);\n    dist[src] = 0;\n    for (auto i = 0; i < n; ++i) {\n    \
    \    for (auto [u, v, w] : edges) {\n            if (dist[u] < inf && dist[u]\
    \ + w < dist[v]) {\n                dist[v] = (i < n - 1) ? std::max(-inf, dist[u]\
    \ + w) : -inf;\n            }\n        }\n    }\n    for (auto i = 0; i < n; ++i)\
    \ {\n        for (auto [u, v, w] : edges) {\n            if (dist[u] == -inf)\
    \ {\n                dist[v] = -inf;\n            }\n        }\n    }\n    return\
    \ dist;\n}\n\n#endif // BELLMAN_FORD_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/bellman_ford.hpp
  requiredBy: []
  timestamp: '2026-07-17 10:26:14+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/bellman_ford.test.cpp
documentation_of: graph/bellman_ford.hpp
layout: document
redirect_from:
- /library/graph/bellman_ford.hpp
- /library/graph/bellman_ford.hpp.html
title: graph/bellman_ford.hpp
---
