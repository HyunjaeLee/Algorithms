---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/havel_hakimi.test.cpp
    title: test/graph/havel_hakimi.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - "https://en.wikipedia.org/wiki/Havel\u2013Hakimi_algorithm"
  bundledCode: "#line 1 \"graph/havel_hakimi.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <optional>\n#include <queue>\n#include <span>\n#include <utility>\n#include\
    \ <vector>\n\n// https://en.wikipedia.org/wiki/Havel\u2013Hakimi_algorithm\n//\
    \ O(N + M log N)\nstd::optional<std::vector<std::pair<int, int>>> havel_hakimi(std::vector<int>\
    \ deg) {\n    auto n = int(deg.size());\n    std::priority_queue<std::pair<int,\
    \ int>> pq;\n    for (auto i = 0; i < n; ++i) {\n        assert(0 <= deg[i]);\n\
    \        if (0 < deg[i]) {\n            pq.emplace(deg[i], i);\n        }\n  \
    \  }\n    std::vector<std::pair<int, int>> edges;\n    while (!pq.empty()) {\n\
    \        auto [k, u] = pq.top();\n        pq.pop();\n        if (int(pq.size())\
    \ < k) {\n            return std::nullopt;\n        }\n        for (auto i = 0;\
    \ i < k; ++i) {\n            auto [d, v] = pq.top();\n            pq.pop();\n\
    \            --deg[v];\n            edges.emplace_back(u, v);\n        }\n   \
    \     for (auto [_, v] : std::span(edges).last(k)) {\n            if (0 < deg[v])\
    \ {\n                pq.emplace(deg[v], v);\n            }\n        }\n    }\n\
    \    return edges;\n}\n\n\n"
  code: "#ifndef HAVEL_HAKIMI_HPP\n#define HAVEL_HAKIMI_HPP\n\n#include <cassert>\n\
    #include <optional>\n#include <queue>\n#include <span>\n#include <utility>\n#include\
    \ <vector>\n\n// https://en.wikipedia.org/wiki/Havel\u2013Hakimi_algorithm\n//\
    \ O(N + M log N)\nstd::optional<std::vector<std::pair<int, int>>> havel_hakimi(std::vector<int>\
    \ deg) {\n    auto n = int(deg.size());\n    std::priority_queue<std::pair<int,\
    \ int>> pq;\n    for (auto i = 0; i < n; ++i) {\n        assert(0 <= deg[i]);\n\
    \        if (0 < deg[i]) {\n            pq.emplace(deg[i], i);\n        }\n  \
    \  }\n    std::vector<std::pair<int, int>> edges;\n    while (!pq.empty()) {\n\
    \        auto [k, u] = pq.top();\n        pq.pop();\n        if (int(pq.size())\
    \ < k) {\n            return std::nullopt;\n        }\n        for (auto i = 0;\
    \ i < k; ++i) {\n            auto [d, v] = pq.top();\n            pq.pop();\n\
    \            --deg[v];\n            edges.emplace_back(u, v);\n        }\n   \
    \     for (auto [_, v] : std::span(edges).last(k)) {\n            if (0 < deg[v])\
    \ {\n                pq.emplace(deg[v], v);\n            }\n        }\n    }\n\
    \    return edges;\n}\n\n#endif // HAVEL_HAKIMI_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/havel_hakimi.hpp
  requiredBy: []
  timestamp: '2026-10-29 17:02:14+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/havel_hakimi.test.cpp
documentation_of: graph/havel_hakimi.hpp
layout: document
redirect_from:
- /library/graph/havel_hakimi.hpp
- /library/graph/havel_hakimi.hpp.html
title: graph/havel_hakimi.hpp
---
