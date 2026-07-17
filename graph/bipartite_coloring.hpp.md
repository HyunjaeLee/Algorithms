---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/aoj1404.test.cpp
    title: test/graph/aoj1404.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/bipartite_coloring.hpp\"\n\n\n\n#include <optional>\n\
    #include <queue>\n#include <vector>\n\nstd::optional<std::vector<int>> bipartite_coloring(const\
    \ std::vector<std::vector<int>> &g) {\n    auto n = int(g.size());\n    std::vector<int>\
    \ color(n, -1);\n    for (auto i = 0; i < n; ++i) {\n        if (color[i] != -1)\
    \ {\n            continue;\n        }\n        std::queue<int> q;\n        q.push(i);\n\
    \        color[i] = 0;\n        while (!q.empty()) {\n            auto u = q.front();\n\
    \            q.pop();\n            for (auto v : g[u]) {\n                if (color[v]\
    \ == -1) {\n                    q.push(v);\n                    color[v] = color[u]\
    \ ^ 1;\n                } else if (color[v] == color[u]) {\n                 \
    \   return std::nullopt;\n                }\n            }\n        }\n    }\n\
    \    return color;\n}\n\n\n"
  code: "#ifndef BIPARTITE_COLORING_HPP\n#define BIPARTITE_COLORING_HPP\n\n#include\
    \ <optional>\n#include <queue>\n#include <vector>\n\nstd::optional<std::vector<int>>\
    \ bipartite_coloring(const std::vector<std::vector<int>> &g) {\n    auto n = int(g.size());\n\
    \    std::vector<int> color(n, -1);\n    for (auto i = 0; i < n; ++i) {\n    \
    \    if (color[i] != -1) {\n            continue;\n        }\n        std::queue<int>\
    \ q;\n        q.push(i);\n        color[i] = 0;\n        while (!q.empty()) {\n\
    \            auto u = q.front();\n            q.pop();\n            for (auto\
    \ v : g[u]) {\n                if (color[v] == -1) {\n                    q.push(v);\n\
    \                    color[v] = color[u] ^ 1;\n                } else if (color[v]\
    \ == color[u]) {\n                    return std::nullopt;\n                }\n\
    \            }\n        }\n    }\n    return color;\n}\n\n#endif // BIPARTITE_COLORING_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/bipartite_coloring.hpp
  requiredBy: []
  timestamp: '2026-07-17 16:10:27+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/aoj1404.test.cpp
documentation_of: graph/bipartite_coloring.hpp
layout: document
redirect_from:
- /library/graph/bipartite_coloring.hpp
- /library/graph/bipartite_coloring.hpp.html
title: graph/bipartite_coloring.hpp
---
