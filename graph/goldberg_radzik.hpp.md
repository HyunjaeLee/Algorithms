---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/graph/goldberg_radzik.test.cpp
    title: test/graph/goldberg_radzik.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/sssp.test.cpp
    title: test/graph/sssp.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/goldberg_radzik.hpp\"\n\n\n\n#include <limits>\n#include\
    \ <ranges>\n#include <tuple>\n#include <utility>\n#include <vector>\n\ntemplate\
    \ <typename T, T inf = std::numeric_limits<T>::max() / 2>\nstd::tuple<bool, std::vector<T>,\
    \ std::vector<int>> goldberg_radzik(const auto &g, int src) {\n    auto n = int(g.size());\n\
    \    std::vector<T> dist(n, inf);\n    dist[src] = 0;\n    std::vector<int> cur{src},\
    \ nxt, order, parent(n, -1);\n    std::vector<int> state(n); // -t: in stack/labeled,\
    \ t: visited\n    for (auto t = 1; !cur.empty(); ++t) {\n        order.clear();\n\
    \        auto dfs = [&](auto &&self, int u) {\n            if (state[u] == t ||\
    \ state[u] == -t)\n                return state[u] == t;\n            state[u]\
    \ = -t;\n            for (auto [v, w] : g[u]) {\n                if (dist[v] <=\
    \ dist[u] + w)\n                    continue;\n                dist[v] = dist[u]\
    \ + w;\n                parent[v] = u;\n                if (!self(self, v))\n\
    \                    return false;\n            }\n            state[u] = t;\n\
    \            order.push_back(u);\n            return true;\n        };\n     \
    \   for (auto u : cur) {\n            if (state[u] == t)\n                continue;\n\
    \            auto can_relax = false;\n            for (auto [v, w] : g[u]) {\n\
    \                if (dist[u] + w < dist[v]) {\n                    can_relax =\
    \ true;\n                    break;\n                }\n            }\n      \
    \      if (can_relax && !dfs(dfs, u)) {\n                return {false, {}, {}};\n\
    \            }\n        }\n        nxt.clear();\n        for (auto u : order |\
    \ std::views::reverse) {\n            for (auto [v, w] : g[u]) {\n           \
    \     if (dist[v] <= dist[u] + w)\n                    continue;\n           \
    \     dist[v] = dist[u] + w;\n                parent[v] = u;\n               \
    \ if (state[v] != -t) {\n                    state[v] = -t;\n                \
    \    nxt.push_back(v);\n                }\n            }\n        }\n        std::swap(cur,\
    \ nxt);\n    }\n    return {true, std::move(dist), std::move(parent)};\n}\n\n\n"
  code: "#ifndef GOLDBERG_RADZIK_HPP\n#define GOLDBERG_RADZIK_HPP\n\n#include <limits>\n\
    #include <ranges>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    template <typename T, T inf = std::numeric_limits<T>::max() / 2>\nstd::tuple<bool,\
    \ std::vector<T>, std::vector<int>> goldberg_radzik(const auto &g, int src) {\n\
    \    auto n = int(g.size());\n    std::vector<T> dist(n, inf);\n    dist[src]\
    \ = 0;\n    std::vector<int> cur{src}, nxt, order, parent(n, -1);\n    std::vector<int>\
    \ state(n); // -t: in stack/labeled, t: visited\n    for (auto t = 1; !cur.empty();\
    \ ++t) {\n        order.clear();\n        auto dfs = [&](auto &&self, int u) {\n\
    \            if (state[u] == t || state[u] == -t)\n                return state[u]\
    \ == t;\n            state[u] = -t;\n            for (auto [v, w] : g[u]) {\n\
    \                if (dist[v] <= dist[u] + w)\n                    continue;\n\
    \                dist[v] = dist[u] + w;\n                parent[v] = u;\n    \
    \            if (!self(self, v))\n                    return false;\n        \
    \    }\n            state[u] = t;\n            order.push_back(u);\n         \
    \   return true;\n        };\n        for (auto u : cur) {\n            if (state[u]\
    \ == t)\n                continue;\n            auto can_relax = false;\n    \
    \        for (auto [v, w] : g[u]) {\n                if (dist[u] + w < dist[v])\
    \ {\n                    can_relax = true;\n                    break;\n     \
    \           }\n            }\n            if (can_relax && !dfs(dfs, u)) {\n \
    \               return {false, {}, {}};\n            }\n        }\n        nxt.clear();\n\
    \        for (auto u : order | std::views::reverse) {\n            for (auto [v,\
    \ w] : g[u]) {\n                if (dist[v] <= dist[u] + w)\n                \
    \    continue;\n                dist[v] = dist[u] + w;\n                parent[v]\
    \ = u;\n                if (state[v] != -t) {\n                    state[v] =\
    \ -t;\n                    nxt.push_back(v);\n                }\n            }\n\
    \        }\n        std::swap(cur, nxt);\n    }\n    return {true, std::move(dist),\
    \ std::move(parent)};\n}\n\n#endif // GOLDBERG_RADZIK_HPP"
  dependsOn: []
  isVerificationFile: false
  path: graph/goldberg_radzik.hpp
  requiredBy: []
  timestamp: '2026-10-12 17:50:32+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/sssp.test.cpp
  - test/graph/goldberg_radzik.test.cpp
documentation_of: graph/goldberg_radzik.hpp
layout: document
redirect_from:
- /library/graph/goldberg_radzik.hpp
- /library/graph/goldberg_radzik.hpp.html
title: graph/goldberg_radzik.hpp
---
