---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: dp/reroot_dfs.hpp
    title: dp/reroot_dfs.hpp
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
  bundledCode: "#line 1 \"test/dp/diameter_dfs.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\
    \n\n#line 1 \"dp/reroot_dfs.hpp\"\n\n\n\n#include <vector>\n\n/*\n    vector<vector<pair<int,\
    \ EdgeWeight>>> g;\n    struct Subtree {};\n    struct Children {};\n    auto\
    \ rake = [&](Children l, Children r) -> Children {};\n    auto add_edge = [&](Subtree\
    \ d, EdgeWeight w) -> Children {};\n    auto add_vertex = [&](Children d, int\
    \ i) -> Subtree {};\n    auto e = []() -> Children {};\n*/\n\nauto reroot_dfs(const\
    \ auto &g, auto rake, auto add_edge, auto add_vertex, auto e) {\n    using Children\
    \ = decltype(e());\n    using Subtree = decltype(add_vertex(e(), 0));\n    std::vector<Subtree>\
    \ dp(g.size());\n    auto dfs0 = [&](auto &&self, int u, int p) -> Subtree {\n\
    \        Children sum = e();\n        for (auto [v, w] : g[u]) {\n           \
    \ if (v != p) {\n                sum = rake(sum, add_edge(self(self, v, u), w));\n\
    \            }\n        }\n        return dp[u] = add_vertex(sum, u);\n    };\n\
    \    auto dfs1 = [&](auto &&self, int u, int p) -> void {\n        std::vector<Children>\
    \ pref{e()};\n        for (auto [v, w] : g[u]) {\n            pref.push_back(rake(pref.back(),\
    \ add_edge(dp[v], w)));\n        }\n        Children suff = e();\n        for\
    \ (auto i = int(g[u].size()) - 1; 0 <= i; --i) {\n            auto [v, w] = g[u][i];\n\
    \            auto x = add_edge(dp[v], w);\n            if (v != p) {\n       \
    \         dp[u] = add_vertex(rake(pref[i], suff), u);\n                self(self,\
    \ v, u);\n            }\n            suff = rake(x, suff);\n        }\n      \
    \  dp[u] = add_vertex(suff, u);\n    };\n    dfs0(dfs0, 0, 0);\n    dfs1(dfs1,\
    \ 0, 0);\n    return dp;\n}\n\n\n#line 4 \"test/dp/diameter_dfs.test.cpp\"\n#include\
    \ <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<std::vector<std::pair<int, int>>>\
    \ g(N);\n    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, w;\n      \
    \  std::cin >> u >> v >> w;\n        g[u].emplace_back(v, w);\n        g[v].emplace_back(u,\
    \ w);\n    }\n    auto rake = [&](long long l, long long r) -> long long { return\
    \ std::max(l, r); };\n    auto add_edge = [&](long long d, int w) -> long long\
    \ { return d + w; };\n    auto add_vertex = [&](long long d, int) -> long long\
    \ { return d; };\n    auto e = []() -> long long { return 0; };\n    auto dp =\
    \ reroot_dfs(g, rake, add_edge, add_vertex, e);\n    auto root = 0;\n    for (auto\
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
    \ \"dp/reroot_dfs.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<std::vector<std::pair<int, int>>>\
    \ g(N);\n    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, w;\n      \
    \  std::cin >> u >> v >> w;\n        g[u].emplace_back(v, w);\n        g[v].emplace_back(u,\
    \ w);\n    }\n    auto rake = [&](long long l, long long r) -> long long { return\
    \ std::max(l, r); };\n    auto add_edge = [&](long long d, int w) -> long long\
    \ { return d + w; };\n    auto add_vertex = [&](long long d, int) -> long long\
    \ { return d; };\n    auto e = []() -> long long { return 0; };\n    auto dp =\
    \ reroot_dfs(g, rake, add_edge, add_vertex, e);\n    auto root = 0;\n    for (auto\
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
  - dp/reroot_dfs.hpp
  isVerificationFile: true
  path: test/dp/diameter_dfs.test.cpp
  requiredBy: []
  timestamp: '2026-10-27 11:04:08+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dp/diameter_dfs.test.cpp
layout: document
redirect_from:
- /verify/test/dp/diameter_dfs.test.cpp
- /verify/test/dp/diameter_dfs.test.cpp.html
title: test/dp/diameter_dfs.test.cpp
---
