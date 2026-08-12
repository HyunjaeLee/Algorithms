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
    PROBLEM: https://judge.yosupo.jp/problem/tree_path_composite_sum
    links:
    - https://judge.yosupo.jp/problem/tree_path_composite_sum
  bundledCode: "#line 1 \"test/dp/rerooting.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n\n#line 1 \"dp/rerooting.hpp\"\n\n\n\n#include <ranges>\n#include <vector>\n\
    \n/*\n    vector<vector<pair<int, EdgeWeight>>> g;\n    struct Subtree {};\n \
    \   struct Child {};\n    auto rake = [&](Child l, Child r) -> Child {};\n   \
    \ auto add_edge = [&](Subtree d, EdgeWeight w) -> Child {};\n    auto add_vertex\
    \ = [&](Child d, int i) -> Subtree {};\n    auto e = []() -> Child {};\n*/\n\n\
    auto rerooting(const auto &g, auto rake, auto add_edge, auto add_vertex, auto\
    \ e) {\n    auto n = int(g.size());\n    using Child = decltype(e());\n    using\
    \ Subtree = decltype(add_vertex(e(), 0));\n    std::vector<Subtree> dp(n), dp_parent(n);\n\
    \    std::vector<int> bfs_order, parent(n, -1);\n    std::vector<Child> pref(n\
    \ + 1);\n    bfs_order.reserve(n);\n    for (auto root = 0; root < n; ++root)\
    \ {\n        if (~parent[root]) {\n            continue;\n        }\n        parent[root]\
    \ = root;\n        bfs_order.clear();\n        bfs_order.push_back(root);\n  \
    \      auto q = bfs_order.cbegin();\n        while (q != bfs_order.cend()) {\n\
    \            auto u = *q++;\n            for (auto [v, w] : g[u]) {\n        \
    \        if (v != parent[u]) {\n                    parent[v] = u;\n         \
    \           bfs_order.push_back(v);\n                }\n            }\n      \
    \  }\n        for (auto u : bfs_order | std::views::reverse) {\n            Child\
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
    \  }\n    }\n    return dp;\n}\n\n\n#line 4 \"test/dp/rerooting.test.cpp\"\n#include\
    \ <atcoder/modint>\n#include <bits/stdc++.h>\n\nusing Z = atcoder::modint998244353;\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N;\n    std::cin\
    \ >> N;\n    using EdgeWeight = std::pair<int, int>;\n    std::vector<std::vector<std::pair<int,\
    \ EdgeWeight>>> g(N);\n    std::vector<int> a(N);\n    std::copy_n(std::istream_iterator<int>(std::cin),\
    \ N, a.begin());\n    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b,\
    \ c;\n        std::cin >> u >> v >> b >> c;\n        g[u].emplace_back(v, std::pair{b,\
    \ c});\n        g[v].emplace_back(u, std::pair{b, c});\n    }\n    using Subtree\
    \ = std::pair<Z, int>;\n    using Child = std::pair<Z, int>;\n    auto rake =\
    \ [&](Child l, Child r) -> Child { return {l.first + r.first, l.second + r.second};\
    \ };\n    auto add_edge = [&](Subtree d, EdgeWeight w) -> Child {\n        return\
    \ {w.first * d.first + Z::raw(w.second) * d.second, d.second};\n    };\n    auto\
    \ add_vertex = [&](Child d, int i) -> Subtree { return {d.first + a[i], d.second\
    \ + 1}; };\n    auto e = []() -> Child { return {0, 0}; };\n    auto dp = rerooting(g,\
    \ rake, add_edge, add_vertex, e);\n    for (auto [sum, cnt] : dp) {\n        std::cout\
    \ << sum.val() << ' ';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n\n#include \"dp/rerooting.hpp\"\n#include <atcoder/modint>\n#include <bits/stdc++.h>\n\
    \nusing Z = atcoder::modint998244353;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    using EdgeWeight = std::pair<int, int>;\n\
    \    std::vector<std::vector<std::pair<int, EdgeWeight>>> g(N);\n    std::vector<int>\
    \ a(N);\n    std::copy_n(std::istream_iterator<int>(std::cin), N, a.begin());\n\
    \    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b, c;\n        std::cin\
    \ >> u >> v >> b >> c;\n        g[u].emplace_back(v, std::pair{b, c});\n     \
    \   g[v].emplace_back(u, std::pair{b, c});\n    }\n    using Subtree = std::pair<Z,\
    \ int>;\n    using Child = std::pair<Z, int>;\n    auto rake = [&](Child l, Child\
    \ r) -> Child { return {l.first + r.first, l.second + r.second}; };\n    auto\
    \ add_edge = [&](Subtree d, EdgeWeight w) -> Child {\n        return {w.first\
    \ * d.first + Z::raw(w.second) * d.second, d.second};\n    };\n    auto add_vertex\
    \ = [&](Child d, int i) -> Subtree { return {d.first + a[i], d.second + 1}; };\n\
    \    auto e = []() -> Child { return {0, 0}; };\n    auto dp = rerooting(g, rake,\
    \ add_edge, add_vertex, e);\n    for (auto [sum, cnt] : dp) {\n        std::cout\
    \ << sum.val() << ' ';\n    }\n}\n"
  dependsOn:
  - dp/rerooting.hpp
  isVerificationFile: true
  path: test/dp/rerooting.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 07:38:15+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dp/rerooting.test.cpp
layout: document
redirect_from:
- /verify/test/dp/rerooting.test.cpp
- /verify/test/dp/rerooting.test.cpp.html
title: test/dp/rerooting.test.cpp
---
