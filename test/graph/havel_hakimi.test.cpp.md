---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/havel_hakimi.hpp
    title: graph/havel_hakimi.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/4003
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/4003
  bundledCode: "#line 1 \"test/graph/havel_hakimi.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/4003\"\
    \n\n#line 1 \"graph/havel_hakimi.hpp\"\n\n\n\n#include <cassert>\n#include <optional>\n\
    #include <queue>\n#include <span>\n#include <utility>\n#include <vector>\n\n//\
    \ https://en.wikipedia.org/wiki/Havel\u2013Hakimi_algorithm\n// O(N + M log N)\n\
    std::optional<std::vector<std::pair<int, int>>> havel_hakimi(std::vector<int>\
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
    \    return edges;\n}\n\n\n#line 4 \"test/graph/havel_hakimi.test.cpp\"\n#include\
    \ <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<int> deg(N);\n    for (auto &d\
    \ : deg) {\n        std::cin >> d;\n    }\n    std::cout << (havel_hakimi(deg)\
    \ ? \"Yes\\n\" : \"No\\n\");\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/4003\"\n\n#include\
    \ \"graph/havel_hakimi.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<int> deg(N);\n    for (auto &d\
    \ : deg) {\n        std::cin >> d;\n    }\n    std::cout << (havel_hakimi(deg)\
    \ ? \"Yes\\n\" : \"No\\n\");\n}\n"
  dependsOn:
  - graph/havel_hakimi.hpp
  isVerificationFile: true
  path: test/graph/havel_hakimi.test.cpp
  requiredBy: []
  timestamp: '2026-10-29 17:02:14+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/havel_hakimi.test.cpp
layout: document
redirect_from:
- /verify/test/graph/havel_hakimi.test.cpp
- /verify/test/graph/havel_hakimi.test.cpp.html
title: test/graph/havel_hakimi.test.cpp
---
