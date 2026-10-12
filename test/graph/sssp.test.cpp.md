---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/goldberg_radzik.hpp
    title: graph/goldberg_radzik.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B
  bundledCode: "#line 1 \"test/graph/sssp.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B\"\
    \n\n#line 1 \"graph/goldberg_radzik.hpp\"\n\n\n\n#include <limits>\n#include <ranges>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\ntemplate <typename\
    \ T, T inf = std::numeric_limits<T>::max() / 2>\nstd::tuple<bool, std::vector<T>,\
    \ std::vector<int>> goldberg_radzik(const auto &g, int src) {\n    auto n = int(g.size());\n\
    \    std::vector<T> dist(n, inf);\n    dist[src] = 0;\n    std::vector<int> cur{src},\
    \ nxt, order, parent(n, -1);\n    std::vector<int> state(n); // -t: in stack/labeled,\
    \ t: visited\n    for (auto t = 1; !cur.empty(); ++t) {\n        order.clear();\n\
    \        auto dfs = [&](auto &&self, int u) {\n            if (state[u] == t ||\
    \ state[u] == -t) {\n                return state[u] == t;\n            }\n  \
    \          state[u] = -t;\n            for (auto [v, w] : g[u]) {\n          \
    \      if (dist[v] <= dist[u] + w) {\n                    continue;\n        \
    \        }\n                dist[v] = dist[u] + w;\n                parent[v]\
    \ = u;\n                if (!self(self, v)) {\n                    return false;\n\
    \                }\n            }\n            state[u] = t;\n            order.push_back(u);\n\
    \            return true;\n        };\n        for (auto u : cur) {\n        \
    \    if (state[u] == t) {\n                continue;\n            }\n        \
    \    auto can_relax = false;\n            for (auto [v, w] : g[u]) {\n       \
    \         if (dist[u] + w < dist[v]) {\n                    can_relax = true;\n\
    \                    break;\n                }\n            }\n            if\
    \ (can_relax && !dfs(dfs, u)) {\n                return {false, {}, {}};\n   \
    \         }\n        }\n        nxt.clear();\n        for (auto u : order | std::views::reverse)\
    \ {\n            for (auto [v, w] : g[u]) {\n                if (dist[v] <= dist[u]\
    \ + w) {\n                    continue;\n                }\n                dist[v]\
    \ = dist[u] + w;\n                parent[v] = u;\n                if (state[v]\
    \ != -t) {\n                    state[v] = -t;\n                    nxt.push_back(v);\n\
    \                }\n            }\n        }\n        std::swap(cur, nxt);\n \
    \   }\n    return {true, std::move(dist), std::move(parent)};\n}\n\n\n#line 4\
    \ \"test/graph/sssp.test.cpp\"\n#include <bits/stdc++.h>\n\nint main() {\n   \
    \ std::cin.tie(0)->sync_with_stdio(0);\n    int N, M, S;\n    std::cin >> N >>\
    \ M >> S;\n    constexpr auto inf = std::numeric_limits<int>::max() / 2;\n   \
    \ std::vector<std::vector<std::pair<int, int>>> g(N);\n    for (auto i = 0; i\
    \ < M; ++i) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n      \
    \  g[u].emplace_back(v, w);\n    }\n    auto [ok, dist, parent] = goldberg_radzik<int,\
    \ inf>(g, S);\n    if (!ok) {\n        std::cout << \"NEGATIVE CYCLE\\n\";\n \
    \       return 0;\n    }\n    for (auto i = 0; i < N; ++i) {\n        if (dist[i]\
    \ == inf) {\n            std::cout << \"INF\\n\";\n        } else {\n        \
    \    std::cout << dist[i] << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B\"\n\n\
    #include \"graph/goldberg_radzik.hpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, M, S;\n    std::cin\
    \ >> N >> M >> S;\n    constexpr auto inf = std::numeric_limits<int>::max() /\
    \ 2;\n    std::vector<std::vector<std::pair<int, int>>> g(N);\n    for (auto i\
    \ = 0; i < M; ++i) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n\
    \        g[u].emplace_back(v, w);\n    }\n    auto [ok, dist, parent] = goldberg_radzik<int,\
    \ inf>(g, S);\n    if (!ok) {\n        std::cout << \"NEGATIVE CYCLE\\n\";\n \
    \       return 0;\n    }\n    for (auto i = 0; i < N; ++i) {\n        if (dist[i]\
    \ == inf) {\n            std::cout << \"INF\\n\";\n        } else {\n        \
    \    std::cout << dist[i] << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - graph/goldberg_radzik.hpp
  isVerificationFile: true
  path: test/graph/sssp.test.cpp
  requiredBy: []
  timestamp: '2026-10-12 17:57:57+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/sssp.test.cpp
layout: document
redirect_from:
- /verify/test/graph/sssp.test.cpp
- /verify/test/graph/sssp.test.cpp.html
title: test/graph/sssp.test.cpp
---
