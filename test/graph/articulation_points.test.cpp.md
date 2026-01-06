---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/articulation_points.hpp
    title: Articulation Points
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A
  bundledCode: "#line 1 \"test/graph/articulation_points.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A\"\n\n#line 1 \"graph/articulation_points.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <vector>\n\nstd::vector<int> find_cutpoints(const\
    \ auto &g) {\n    auto n = (int)g.size();\n    auto timer = 0;\n    std::vector<int>\
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
    \        }\n    };\n    for (int i = 0; i < n; ++i) {\n        if (!visited[i])\
    \ {\n            dfs(dfs, i, -1);\n        }\n    }\n    return cutpoints;\n}\n\
    \n\n#line 4 \"test/graph/articulation_points.test.cpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int n, m;\n    std::cin\
    \ >> n >> m;\n    std::vector<std::vector<int>> g(n);\n    for (auto i = 0; i\
    \ < m; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    auto cutpoints = find_cutpoints(g);\n\
    \    std::ranges::sort(cutpoints);\n    std::ranges::copy(cutpoints, std::ostream_iterator<int>(std::cout,\
    \ \"\\n\"));\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A\"\n\n\
    #include \"graph/articulation_points.hpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int n, m;\n    std::cin >>\
    \ n >> m;\n    std::vector<std::vector<int>> g(n);\n    for (auto i = 0; i < m;\
    \ ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    auto cutpoints = find_cutpoints(g);\n\
    \    std::ranges::sort(cutpoints);\n    std::ranges::copy(cutpoints, std::ostream_iterator<int>(std::cout,\
    \ \"\\n\"));\n}\n"
  dependsOn:
  - graph/articulation_points.hpp
  isVerificationFile: true
  path: test/graph/articulation_points.test.cpp
  requiredBy: []
  timestamp: '2026-01-06 20:06:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/articulation_points.test.cpp
layout: document
redirect_from:
- /verify/test/graph/articulation_points.test.cpp
- /verify/test/graph/articulation_points.test.cpp.html
title: test/graph/articulation_points.test.cpp
---
