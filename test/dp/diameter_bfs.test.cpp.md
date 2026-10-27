---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: dp/rerooting.hpp
    title: Rerooting
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tree_diameter
    links:
    - https://judge.yosupo.jp/problem/tree_diameter
  bundledCode: "#line 1 \"test/dp/diameter_bfs.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\
    \n\n#line 1 \"dp/rerooting.hpp\"\n\n\n\n#include <ranges>\n#include <vector>\n\
    \n/*\n    vector<vector<pair<int, EdgeWeight>>> g;\n    struct Subtree {};\n \
    \   struct Children {};\n    auto rake = [&](Children l, Children r) -> Children\
    \ {};\n    auto add_edge = [&](Subtree d, EdgeWeight w) -> Children {};\n    auto\
    \ add_vertex = [&](Children d, int i) -> Subtree {};\n    auto e = []() -> Children\
    \ {};\n*/\n\nauto rerooting(const auto &g, auto rake, auto add_edge, auto add_vertex,\
    \ auto e) {\n    auto n = int(g.size());\n    using Children = decltype(e());\n\
    \    using Subtree = decltype(add_vertex(e(), 0));\n    std::vector<Subtree> dp(n),\
    \ dp_parent(n);\n    std::vector<int> bfs_order, parent(n, -1);\n    std::vector<Children>\
    \ pref(n + 1);\n    bfs_order.reserve(n);\n    for (auto root = 0; root < n; ++root)\
    \ {\n        if (~parent[root]) {\n            continue;\n        }\n        parent[root]\
    \ = root;\n        bfs_order.clear();\n        bfs_order.push_back(root);\n  \
    \      auto q = bfs_order.cbegin();\n        while (q != bfs_order.cend()) {\n\
    \            auto u = *q++;\n            for (auto [v, w] : g[u]) {\n        \
    \        if (v != parent[u]) {\n                    parent[v] = u;\n         \
    \           bfs_order.push_back(v);\n                }\n            }\n      \
    \  }\n        for (auto u : bfs_order | std::views::reverse) {\n            Children\
    \ sum = e();\n            for (auto [v, w] : g[u]) {\n                if (v !=\
    \ parent[u]) {\n                    sum = rake(sum, add_edge(dp[v], w));\n   \
    \             }\n            }\n            dp[u] = add_vertex(sum, u);\n    \
    \    }\n        for (auto u : bfs_order) {\n            auto i = 0;\n        \
    \    pref[0] = e();\n            for (auto [v, w] : g[u]) {\n                auto\
    \ state = (v == parent[u]) ? dp_parent[u] : dp[v];\n                pref[i + 1]\
    \ = rake(pref[i], add_edge(state, w));\n                ++i;\n            }\n\
    \            Children suff = e();\n            for (auto [v, w] : g[u] | std::views::reverse)\
    \ {\n                if (v != parent[u]) {\n                    Children except_child\
    \ = rake(pref[i - 1], suff);\n                    dp_parent[v] = add_vertex(except_child,\
    \ u);\n                }\n                auto state = (v == parent[u]) ? dp_parent[u]\
    \ : dp[v];\n                suff = rake(add_edge(state, w), suff);\n         \
    \       --i;\n            }\n            dp[u] = add_vertex(suff, u);\n      \
    \  }\n    }\n    return dp;\n}\n\n\n#line 4 \"test/dp/diameter_bfs.test.cpp\"\n\
    #include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<std::vector<std::pair<int, int>>>\
    \ g(N);\n    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, w;\n      \
    \  std::cin >> u >> v >> w;\n        g[u].emplace_back(v, w);\n        g[v].emplace_back(u,\
    \ w);\n    }\n    auto rake = [&](long long l, long long r) -> long long { return\
    \ std::max(l, r); };\n    auto add_edge = [&](long long d, int w) -> long long\
    \ { return d + w; };\n    auto add_vertex = [&](long long d, int) -> long long\
    \ { return d; };\n    auto e = []() -> long long { return 0; };\n    auto dp =\
    \ rerooting(g, rake, add_edge, add_vertex, e);\n    auto root = 0;\n    for (auto\
    \ i = 0; i < N; ++i) {\n        if (dp[root] < dp[i]) {\n            root = i;\n\
    \        }\n    }\n    std::vector<int> parent(N, -1);\n    std::vector<long long>\
    \ depth(N);\n    auto dfs = [&](auto &&self, int u) -> void {\n        for (auto\
    \ [v, w] : g[u]) {\n            if (v == parent[u]) {\n                continue;\n\
    \            }\n            parent[v] = u;\n            depth[v] = depth[u] +\
    \ w;\n            self(self, v);\n        }\n    };\n    dfs(dfs, root);\n   \
    \ auto u = 0;\n    for (auto i = 0; i < N; ++i) {\n        if (depth[u] < depth[i])\
    \ {\n            u = i;\n        }\n    }\n    std::vector<int> path;\n    while\
    \ (u != -1) {\n        path.push_back(u);\n        u = parent[u];\n    }\n   \
    \ std::cout << dp[root] << \" \" << path.size() << \"\\n\";\n    for (auto v :\
    \ path) {\n        std::cout << v << \" \";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\n\n#include\
    \ \"dp/rerooting.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<std::vector<std::pair<int, int>>>\
    \ g(N);\n    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, w;\n      \
    \  std::cin >> u >> v >> w;\n        g[u].emplace_back(v, w);\n        g[v].emplace_back(u,\
    \ w);\n    }\n    auto rake = [&](long long l, long long r) -> long long { return\
    \ std::max(l, r); };\n    auto add_edge = [&](long long d, int w) -> long long\
    \ { return d + w; };\n    auto add_vertex = [&](long long d, int) -> long long\
    \ { return d; };\n    auto e = []() -> long long { return 0; };\n    auto dp =\
    \ rerooting(g, rake, add_edge, add_vertex, e);\n    auto root = 0;\n    for (auto\
    \ i = 0; i < N; ++i) {\n        if (dp[root] < dp[i]) {\n            root = i;\n\
    \        }\n    }\n    std::vector<int> parent(N, -1);\n    std::vector<long long>\
    \ depth(N);\n    auto dfs = [&](auto &&self, int u) -> void {\n        for (auto\
    \ [v, w] : g[u]) {\n            if (v == parent[u]) {\n                continue;\n\
    \            }\n            parent[v] = u;\n            depth[v] = depth[u] +\
    \ w;\n            self(self, v);\n        }\n    };\n    dfs(dfs, root);\n   \
    \ auto u = 0;\n    for (auto i = 0; i < N; ++i) {\n        if (depth[u] < depth[i])\
    \ {\n            u = i;\n        }\n    }\n    std::vector<int> path;\n    while\
    \ (u != -1) {\n        path.push_back(u);\n        u = parent[u];\n    }\n   \
    \ std::cout << dp[root] << \" \" << path.size() << \"\\n\";\n    for (auto v :\
    \ path) {\n        std::cout << v << \" \";\n    }\n}\n"
  dependsOn:
  - dp/rerooting.hpp
  isVerificationFile: true
  path: test/dp/diameter_bfs.test.cpp
  requiredBy: []
  timestamp: '2026-10-27 11:04:08+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dp/diameter_bfs.test.cpp
layout: document
redirect_from:
- /verify/test/dp/diameter_bfs.test.cpp
- /verify/test/dp/diameter_bfs.test.cpp.html
title: test/dp/diameter_bfs.test.cpp
---
