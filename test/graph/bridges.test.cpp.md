---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bridges.hpp
    title: Bridges
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B
  bundledCode: "#line 1 \"test/graph/bridges.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B\"\
    \n\n#line 1 \"graph/bridges.hpp\"\n\n\n\n#include <algorithm>\n#include <utility>\n\
    #include <vector>\n\nstd::vector<std::pair<int, int>> find_bridges(const auto\
    \ &g) {\n    auto n = (int)g.size();\n    auto timer = 0;\n    std::vector<int>\
    \ visited(n, false), tin(n, -1), low(n, -1);\n    std::vector<std::pair<int, int>>\
    \ bridges;\n    auto dfs = [&](auto self, int u, int p) -> void {\n        visited[u]\
    \ = true;\n        tin[u] = low[u] = timer++;\n        bool parent_skipped = false;\n\
    \        for (auto v : g[u]) {\n            if (v == p && !parent_skipped) {\n\
    \                parent_skipped = true;\n                continue;\n         \
    \   }\n            if (visited[v]) {\n                low[u] = std::min(low[u],\
    \ tin[v]);\n            } else {\n                self(self, v, u);\n        \
    \        low[u] = std::min(low[u], low[v]);\n                if (tin[u] < low[v])\
    \ {\n                    bridges.emplace_back(u, v);\n                }\n    \
    \        }\n        }\n    };\n    for (auto i = 0; i < n; ++i) {\n        if\
    \ (!visited[i]) {\n            dfs(dfs, i, -1);\n        }\n    }\n    return\
    \ bridges;\n}\n\n\n#line 4 \"test/graph/bridges.test.cpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int n, m;\n    std::cin\
    \ >> n >> m;\n    std::vector<std::vector<int>> g(n);\n    for (auto i = 0; i\
    \ < m; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    auto bridges = find_bridges(g);\n    for\
    \ (auto &[u, v] : bridges) {\n        if (u > v) {\n            std::swap(u, v);\n\
    \        }\n    }\n    std::ranges::sort(bridges);\n    for (auto [u, v] : bridges)\
    \ {\n        std::cout << u << ' ' << v << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B\"\n\n\
    #include \"graph/bridges.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n   \
    \ std::cin.tie(0)->sync_with_stdio(0);\n    int n, m;\n    std::cin >> n >> m;\n\
    \    std::vector<std::vector<int>> g(n);\n    for (auto i = 0; i < m; ++i) {\n\
    \        int u, v;\n        std::cin >> u >> v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    auto bridges = find_bridges(g);\n    for\
    \ (auto &[u, v] : bridges) {\n        if (u > v) {\n            std::swap(u, v);\n\
    \        }\n    }\n    std::ranges::sort(bridges);\n    for (auto [u, v] : bridges)\
    \ {\n        std::cout << u << ' ' << v << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/bridges.hpp
  isVerificationFile: true
  path: test/graph/bridges.test.cpp
  requiredBy: []
  timestamp: '2026-01-09 14:45:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/bridges.test.cpp
layout: document
redirect_from:
- /verify/test/graph/bridges.test.cpp
- /verify/test/graph/bridges.test.cpp.html
title: test/graph/bridges.test.cpp
---
