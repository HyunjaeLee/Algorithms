---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/enumerate_triangles.hpp
    title: graph/enumerate_triangles.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_triangles
    links:
    - https://judge.yosupo.jp/problem/enumerate_triangles
  bundledCode: "#line 1 \"test/graph/enumerate_triangles.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/enumerate_triangles\"\n\n#line 1 \"graph/enumerate_triangles.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <utility>\n#include <vector>\n\n// O(n\
    \ + m * sqrt(m))\nvoid enumerate_triangles(int n, const std::vector<std::pair<int,\
    \ int>> &edges, auto f) {\n    std::vector<int> deg(n);\n    for (auto [u, v]\
    \ : edges) {\n        ++deg[u];\n        ++deg[v];\n    }\n    std::vector<std::vector<int>>\
    \ g(n);\n    for (auto [u, v] : edges) {\n        if (std::pair(deg[u], u) < std::pair(deg[v],\
    \ v)) {\n            std::swap(u, v);\n        }\n        g[u].push_back(v);\n\
    \    }\n    std::vector<int> color(n, -1);\n    for (auto i = 0; i < n; ++i) {\n\
    \        for (auto j : g[i]) {\n            color[j] = i;\n        }\n       \
    \ for (auto j : g[i]) {\n            for (auto k : g[j]) {\n                if\
    \ (color[k] == i) {\n                    f(i, j, k);\n                }\n    \
    \        }\n        }\n    }\n}\n\n\n#line 4 \"test/graph/enumerate_triangles.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, M;\n    std::cin >> N >> M;\n    std::vector<int> A(N);\n    for (auto\
    \ &x : A) {\n        std::cin >> x;\n    }\n    std::vector<std::pair<int, int>>\
    \ E(M);\n    for (auto &[u, v] : E) {\n        std::cin >> u >> v;\n    }\n  \
    \  __int128 sum = 0;\n    auto f = [&](int i, int j, int k) { sum += __int128(A[i])\
    \ * A[j] * A[k]; };\n    enumerate_triangles(N, E, f);\n    auto ans = int(sum\
    \ % 998244353);\n    std::cout << ans << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_triangles\"\n\
    \n#include \"graph/enumerate_triangles.hpp\"\n#include <bits/stdc++.h>\n\nint\
    \ main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, M;\n    std::cin\
    \ >> N >> M;\n    std::vector<int> A(N);\n    for (auto &x : A) {\n        std::cin\
    \ >> x;\n    }\n    std::vector<std::pair<int, int>> E(M);\n    for (auto &[u,\
    \ v] : E) {\n        std::cin >> u >> v;\n    }\n    __int128 sum = 0;\n    auto\
    \ f = [&](int i, int j, int k) { sum += __int128(A[i]) * A[j] * A[k]; };\n   \
    \ enumerate_triangles(N, E, f);\n    auto ans = int(sum % 998244353);\n    std::cout\
    \ << ans << \"\\n\";\n}\n"
  dependsOn:
  - graph/enumerate_triangles.hpp
  isVerificationFile: true
  path: test/graph/enumerate_triangles.test.cpp
  requiredBy: []
  timestamp: '2026-10-14 18:10:34+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/enumerate_triangles.test.cpp
layout: document
redirect_from:
- /verify/test/graph/enumerate_triangles.test.cpp
- /verify/test/graph/enumerate_triangles.test.cpp.html
title: test/graph/enumerate_triangles.test.cpp
---
