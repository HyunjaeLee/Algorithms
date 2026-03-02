---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dp/rerooting.test.cpp
    title: test/dp/rerooting.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"dp/rerooting.hpp\"\n\n\n\n#include <ranges>\n#include <vector>\n\
    \n/*\n    vector<vector<pair<int, EdgeWeight>>> g;\n    struct Subtree {};\n \
    \   struct Child {};\n    auto rake = [&](Child l, Child r) -> Child {};\n   \
    \ auto add_edge = [&](Subtree d, EdgeWeight w) -> Child {};\n    auto add_vertex\
    \ = [&](Child d, int i) -> Subtree {};\n    auto e = []() -> Child {};\n*/\n\n\
    auto rerooting(const auto &g, auto rake, auto add_edge, auto add_vertex, auto\
    \ e) {\n    int n = g.size();\n    using Child = decltype(e());\n    using Subtree\
    \ = decltype(add_vertex(e(), 0));\n    std::vector<Subtree> dp(n), dp_parent(n);\n\
    \    std::vector<int> bfs_order, parent(n, -1);\n    std::vector<Child> pref(n\
    \ + 1);\n    bfs_order.reserve(n);\n    for (int root = 0; root < n; ++root) {\n\
    \        if (~parent[root]) {\n            continue;\n        }\n        parent[root]\
    \ = root;\n        bfs_order.clear();\n        bfs_order.push_back(root);\n  \
    \      auto q = bfs_order.cbegin();\n        while (q != bfs_order.cend()) {\n\
    \            int u = *q++;\n            for (auto [v, w] : g[u]) {\n         \
    \       if (v != parent[u]) {\n                    parent[v] = u;\n          \
    \          bfs_order.push_back(v);\n                }\n            }\n       \
    \ }\n        for (auto u : bfs_order | std::views::reverse) {\n            Child\
    \ sum = e();\n            for (auto [v, w] : g[u]) {\n                if (v !=\
    \ parent[u]) {\n                    sum = rake(sum, add_edge(dp[v], w));\n   \
    \             }\n            }\n            dp[u] = add_vertex(sum, u);\n    \
    \    }\n        for (auto u : bfs_order) {\n            auto i = 0;\n        \
    \    pref[0] = e();\n            for (auto [v, w] : g[u]) {\n                auto\
    \ state = (v == parent[u]) ? dp_parent[u] : dp[v];\n                pref[i + 1]\
    \ = rake(pref[i], add_edge(state, w));\n                ++i;\n            }\n\
    \            auto suff = e();\n            for (auto [v, w] : g[u] | std::views::reverse)\
    \ {\n                if (v != parent[u]) {\n                    Child except_child\
    \ = rake(pref[i - 1], suff);\n                    dp_parent[v] = add_vertex(except_child,\
    \ u);\n                }\n                auto state = (v == parent[u]) ? dp_parent[u]\
    \ : dp[v];\n                suff = rake(add_edge(state, w), suff);\n         \
    \       --i;\n            }\n            dp[u] = add_vertex(suff, u);\n      \
    \  }\n    }\n    return dp;\n}\n\n\n"
  code: "#ifndef REROOTING_HPP\n#define REROOTING_HPP\n\n#include <ranges>\n#include\
    \ <vector>\n\n/*\n    vector<vector<pair<int, EdgeWeight>>> g;\n    struct Subtree\
    \ {};\n    struct Child {};\n    auto rake = [&](Child l, Child r) -> Child {};\n\
    \    auto add_edge = [&](Subtree d, EdgeWeight w) -> Child {};\n    auto add_vertex\
    \ = [&](Child d, int i) -> Subtree {};\n    auto e = []() -> Child {};\n*/\n\n\
    auto rerooting(const auto &g, auto rake, auto add_edge, auto add_vertex, auto\
    \ e) {\n    int n = g.size();\n    using Child = decltype(e());\n    using Subtree\
    \ = decltype(add_vertex(e(), 0));\n    std::vector<Subtree> dp(n), dp_parent(n);\n\
    \    std::vector<int> bfs_order, parent(n, -1);\n    std::vector<Child> pref(n\
    \ + 1);\n    bfs_order.reserve(n);\n    for (int root = 0; root < n; ++root) {\n\
    \        if (~parent[root]) {\n            continue;\n        }\n        parent[root]\
    \ = root;\n        bfs_order.clear();\n        bfs_order.push_back(root);\n  \
    \      auto q = bfs_order.cbegin();\n        while (q != bfs_order.cend()) {\n\
    \            int u = *q++;\n            for (auto [v, w] : g[u]) {\n         \
    \       if (v != parent[u]) {\n                    parent[v] = u;\n          \
    \          bfs_order.push_back(v);\n                }\n            }\n       \
    \ }\n        for (auto u : bfs_order | std::views::reverse) {\n            Child\
    \ sum = e();\n            for (auto [v, w] : g[u]) {\n                if (v !=\
    \ parent[u]) {\n                    sum = rake(sum, add_edge(dp[v], w));\n   \
    \             }\n            }\n            dp[u] = add_vertex(sum, u);\n    \
    \    }\n        for (auto u : bfs_order) {\n            auto i = 0;\n        \
    \    pref[0] = e();\n            for (auto [v, w] : g[u]) {\n                auto\
    \ state = (v == parent[u]) ? dp_parent[u] : dp[v];\n                pref[i + 1]\
    \ = rake(pref[i], add_edge(state, w));\n                ++i;\n            }\n\
    \            auto suff = e();\n            for (auto [v, w] : g[u] | std::views::reverse)\
    \ {\n                if (v != parent[u]) {\n                    Child except_child\
    \ = rake(pref[i - 1], suff);\n                    dp_parent[v] = add_vertex(except_child,\
    \ u);\n                }\n                auto state = (v == parent[u]) ? dp_parent[u]\
    \ : dp[v];\n                suff = rake(add_edge(state, w), suff);\n         \
    \       --i;\n            }\n            dp[u] = add_vertex(suff, u);\n      \
    \  }\n    }\n    return dp;\n}\n\n#endif // REROOTING_HPP"
  dependsOn: []
  isVerificationFile: false
  path: dp/rerooting.hpp
  requiredBy: []
  timestamp: '2026-03-02 14:25:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dp/rerooting.test.cpp
documentation_of: dp/rerooting.hpp
layout: document
title: Rerooting
---
### Related Problems
+ [Tree Median](https://www.acmicpc.net/problem/7812)
+ [City Attractions](https://www.acmicpc.net/problem/14875)
+ [Tree Path Composite Sum](https://judge.yosupo.jp/problem/tree_path_composite_sum)
+ [Choosing Capital for Treeland](https://codeforces.com/contest/219/problem/D)
