---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dp/diameter_dfs.test.cpp
    title: test/dp/diameter_dfs.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/dp/reroot_dfs.test.cpp
    title: test/dp/reroot_dfs.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"dp/reroot_dfs.hpp\"\n\n\n\n#include <vector>\n\n/*\n   \
    \ vector<vector<pair<int, EdgeWeight>>> g;\n    struct Subtree {};\n    struct\
    \ Children {};\n    auto rake = [&](Children l, Children r) -> Children {};\n\
    \    auto add_edge = [&](Subtree d, EdgeWeight w) -> Children {};\n    auto add_vertex\
    \ = [&](Children d, int i) -> Subtree {};\n    auto e = []() -> Children {};\n\
    */\n\nauto reroot_dfs(const auto &g, auto rake, auto add_edge, auto add_vertex,\
    \ auto e) {\n    using Children = decltype(e());\n    using Subtree = decltype(add_vertex(e(),\
    \ 0));\n    std::vector<Subtree> dp(g.size());\n    auto dfs0 = [&](auto &&self,\
    \ int u, int p) -> Subtree {\n        Children sum = e();\n        for (auto [v,\
    \ w] : g[u]) {\n            if (v != p) {\n                sum = rake(sum, add_edge(self(self,\
    \ v, u), w));\n            }\n        }\n        return dp[u] = add_vertex(sum,\
    \ u);\n    };\n    auto dfs1 = [&](auto &&self, int u, int p) -> void {\n    \
    \    std::vector<Children> pref{e()};\n        for (auto [v, w] : g[u]) {\n  \
    \          pref.push_back(rake(pref.back(), add_edge(dp[v], w)));\n        }\n\
    \        Children suff = e();\n        for (auto i = int(g[u].size()) - 1; 0 <=\
    \ i; --i) {\n            auto [v, w] = g[u][i];\n            auto x = add_edge(dp[v],\
    \ w);\n            if (v != p) {\n                dp[u] = add_vertex(rake(pref[i],\
    \ suff), u);\n                self(self, v, u);\n            }\n            suff\
    \ = rake(x, suff);\n        }\n        dp[u] = add_vertex(suff, u);\n    };\n\
    \    dfs0(dfs0, 0, 0);\n    dfs1(dfs1, 0, 0);\n    return dp;\n}\n\n\n"
  code: "#ifndef REROOT_DFS_HPP\n#define REROOT_DFS_HPP\n\n#include <vector>\n\n/*\n\
    \    vector<vector<pair<int, EdgeWeight>>> g;\n    struct Subtree {};\n    struct\
    \ Children {};\n    auto rake = [&](Children l, Children r) -> Children {};\n\
    \    auto add_edge = [&](Subtree d, EdgeWeight w) -> Children {};\n    auto add_vertex\
    \ = [&](Children d, int i) -> Subtree {};\n    auto e = []() -> Children {};\n\
    */\n\nauto reroot_dfs(const auto &g, auto rake, auto add_edge, auto add_vertex,\
    \ auto e) {\n    using Children = decltype(e());\n    using Subtree = decltype(add_vertex(e(),\
    \ 0));\n    std::vector<Subtree> dp(g.size());\n    auto dfs0 = [&](auto &&self,\
    \ int u, int p) -> Subtree {\n        Children sum = e();\n        for (auto [v,\
    \ w] : g[u]) {\n            if (v != p) {\n                sum = rake(sum, add_edge(self(self,\
    \ v, u), w));\n            }\n        }\n        return dp[u] = add_vertex(sum,\
    \ u);\n    };\n    auto dfs1 = [&](auto &&self, int u, int p) -> void {\n    \
    \    std::vector<Children> pref{e()};\n        for (auto [v, w] : g[u]) {\n  \
    \          pref.push_back(rake(pref.back(), add_edge(dp[v], w)));\n        }\n\
    \        Children suff = e();\n        for (auto i = int(g[u].size()) - 1; 0 <=\
    \ i; --i) {\n            auto [v, w] = g[u][i];\n            auto x = add_edge(dp[v],\
    \ w);\n            if (v != p) {\n                dp[u] = add_vertex(rake(pref[i],\
    \ suff), u);\n                self(self, v, u);\n            }\n            suff\
    \ = rake(x, suff);\n        }\n        dp[u] = add_vertex(suff, u);\n    };\n\
    \    dfs0(dfs0, 0, 0);\n    dfs1(dfs1, 0, 0);\n    return dp;\n}\n\n#endif //\
    \ REROOT_DFS_HPP"
  dependsOn: []
  isVerificationFile: false
  path: dp/reroot_dfs.hpp
  requiredBy: []
  timestamp: '2026-10-26 19:01:10+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dp/reroot_dfs.test.cpp
  - test/dp/diameter_dfs.test.cpp
documentation_of: dp/reroot_dfs.hpp
layout: document
redirect_from:
- /library/dp/reroot_dfs.hpp
- /library/dp/reroot_dfs.hpp.html
title: dp/reroot_dfs.hpp
---
