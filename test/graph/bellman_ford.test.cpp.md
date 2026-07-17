---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.hpp
    title: graph/bellman_ford.hpp
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
  bundledCode: "#line 1 \"test/graph/bellman_ford.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B\"\
    \n\n#line 1 \"graph/bellman_ford.hpp\"\n\n\n\n#include <algorithm>\n#include <limits>\n\
    #include <tuple>\n#include <vector>\n\ntemplate <typename T, T inf = std::numeric_limits<T>::max()\
    \ / 2>\nstd::vector<T> bellman_ford(int n, const std::vector<std::tuple<int, int,\
    \ T>> &edges, int src) {\n    std::vector<T> dist(n, inf);\n    dist[src] = 0;\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto [u, v, w] : edges) {\n\
    \            if (dist[u] < inf && dist[u] + w < dist[v]) {\n                dist[v]\
    \ = (i < n - 1) ? std::max(-inf, dist[u] + w) : -inf;\n            }\n       \
    \ }\n    }\n    for (auto i = 0; i < n; ++i) {\n        for (auto [u, v, w] :\
    \ edges) {\n            if (dist[u] == -inf) {\n                dist[v] = -inf;\n\
    \            }\n        }\n    }\n    return dist;\n}\n\n\n#line 4 \"test/graph/bellman_ford.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, M, S;\n    std::cin >> N >> M >> S;\n    constexpr auto inf = std::numeric_limits<int>::max()\
    \ / 2;\n    std::vector<std::tuple<int, int, int>> edges(M);\n    for (auto &[u,\
    \ v, w] : edges) {\n        std::cin >> u >> v >> w;\n    }\n    auto dist = bellman_ford(N,\
    \ edges, S);\n    for (auto i = 0; i < N; ++i) {\n        if (dist[i] == -inf)\
    \ {\n            std::cout << \"NEGATIVE CYCLE\\n\";\n            return 0;\n\
    \        }\n    }\n    for (auto i = 0; i < N; ++i) {\n        if (dist[i] ==\
    \ inf) {\n            std::cout << \"INF\\n\";\n        } else {\n           \
    \ std::cout << dist[i] << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B\"\n\n\
    #include \"graph/bellman_ford.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n\
    \    std::cin.tie(0)->sync_with_stdio(0);\n    int N, M, S;\n    std::cin >> N\
    \ >> M >> S;\n    constexpr auto inf = std::numeric_limits<int>::max() / 2;\n\
    \    std::vector<std::tuple<int, int, int>> edges(M);\n    for (auto &[u, v, w]\
    \ : edges) {\n        std::cin >> u >> v >> w;\n    }\n    auto dist = bellman_ford(N,\
    \ edges, S);\n    for (auto i = 0; i < N; ++i) {\n        if (dist[i] == -inf)\
    \ {\n            std::cout << \"NEGATIVE CYCLE\\n\";\n            return 0;\n\
    \        }\n    }\n    for (auto i = 0; i < N; ++i) {\n        if (dist[i] ==\
    \ inf) {\n            std::cout << \"INF\\n\";\n        } else {\n           \
    \ std::cout << dist[i] << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - graph/bellman_ford.hpp
  isVerificationFile: true
  path: test/graph/bellman_ford.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 10:26:14+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/bellman_ford.test.cpp
layout: document
redirect_from:
- /verify/test/graph/bellman_ford.test.cpp
- /verify/test/graph/bellman_ford.test.cpp.html
title: test/graph/bellman_ford.test.cpp
---
