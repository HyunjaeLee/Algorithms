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
    \nauto rerooting(const auto &g,   // Graph\n               auto op,         //\
    \ (PathState, PathState) -> PathState\n               auto to_path,    // (TreeState,\
    \ EdgeWeight) -> PathState\n               auto to_subtree, // (PathState, NodeWeight)\
    \ -> TreeState\n               auto e           // PathState (Identity)\n) {\n\
    \    int n = g.size();\n    using PathState = decltype(e);\n    using TreeState\
    \ = decltype(to_subtree(e, g.node_weight(0)));\n    std::vector<TreeState> dp(n),\
    \ dp_parent(n);\n    std::vector<int> q, parent(n, -1);\n    std::vector<PathState>\
    \ pref(n + 1);\n    q.reserve(n);\n    for (int root = 0; root < n; ++root) {\n\
    \        if (~parent[root]) {\n            continue;\n        }\n        parent[root]\
    \ = root;\n        q.clear();\n        q.push_back(root);\n        auto it = q.cbegin();\n\
    \        while (it != q.cend()) {\n            int u = *it++;\n            for\
    \ (auto [v, w] : g[u]) {\n                if (v != parent[u]) {\n            \
    \        parent[v] = u;\n                    q.push_back(v);\n               \
    \ }\n            }\n        }\n        for (auto u : q | std::views::reverse)\
    \ {\n            PathState merged = e;\n            for (auto [v, w] : g[u]) {\n\
    \                if (v != parent[u]) {\n                    merged = op(merged,\
    \ to_path(dp[v], w));\n                }\n            }\n            dp[u] = to_subtree(merged,\
    \ g.node_weight(u));\n        }\n        for (auto u : q) {\n            int i\
    \ = 0;\n            pref[0] = e;\n            for (auto [v, w] : g[u]) {\n   \
    \             auto state = v == parent[u] ? dp_parent[u] : dp[v];\n          \
    \      pref[i + 1] = op(pref[i], to_path(state, w));\n                ++i;\n \
    \           }\n            auto suff = e;\n            for (auto [v, w] : g[u]\
    \ | std::views::reverse) {\n                if (v != parent[u]) {\n          \
    \          PathState except_child = op(pref[i - 1], suff);\n                 \
    \   dp_parent[v] = to_subtree(except_child, g.node_weight(u));\n             \
    \   }\n                auto state = v == parent[u] ? dp_parent[u] : dp[v];\n \
    \               suff = op(to_path(state, w), suff);\n                --i;\n  \
    \          }\n            dp[u] = to_subtree(suff, g.node_weight(u));\n      \
    \  }\n    }\n    return dp;\n}\n\n\n"
  code: "#ifndef REROOTING_HPP\n#define REROOTING_HPP\n\n#include <ranges>\n#include\
    \ <vector>\n\nauto rerooting(const auto &g,   // Graph\n               auto op,\
    \         // (PathState, PathState) -> PathState\n               auto to_path,\
    \    // (TreeState, EdgeWeight) -> PathState\n               auto to_subtree,\
    \ // (PathState, NodeWeight) -> TreeState\n               auto e           //\
    \ PathState (Identity)\n) {\n    int n = g.size();\n    using PathState = decltype(e);\n\
    \    using TreeState = decltype(to_subtree(e, g.node_weight(0)));\n    std::vector<TreeState>\
    \ dp(n), dp_parent(n);\n    std::vector<int> q, parent(n, -1);\n    std::vector<PathState>\
    \ pref(n + 1);\n    q.reserve(n);\n    for (int root = 0; root < n; ++root) {\n\
    \        if (~parent[root]) {\n            continue;\n        }\n        parent[root]\
    \ = root;\n        q.clear();\n        q.push_back(root);\n        auto it = q.cbegin();\n\
    \        while (it != q.cend()) {\n            int u = *it++;\n            for\
    \ (auto [v, w] : g[u]) {\n                if (v != parent[u]) {\n            \
    \        parent[v] = u;\n                    q.push_back(v);\n               \
    \ }\n            }\n        }\n        for (auto u : q | std::views::reverse)\
    \ {\n            PathState merged = e;\n            for (auto [v, w] : g[u]) {\n\
    \                if (v != parent[u]) {\n                    merged = op(merged,\
    \ to_path(dp[v], w));\n                }\n            }\n            dp[u] = to_subtree(merged,\
    \ g.node_weight(u));\n        }\n        for (auto u : q) {\n            int i\
    \ = 0;\n            pref[0] = e;\n            for (auto [v, w] : g[u]) {\n   \
    \             auto state = v == parent[u] ? dp_parent[u] : dp[v];\n          \
    \      pref[i + 1] = op(pref[i], to_path(state, w));\n                ++i;\n \
    \           }\n            auto suff = e;\n            for (auto [v, w] : g[u]\
    \ | std::views::reverse) {\n                if (v != parent[u]) {\n          \
    \          PathState except_child = op(pref[i - 1], suff);\n                 \
    \   dp_parent[v] = to_subtree(except_child, g.node_weight(u));\n             \
    \   }\n                auto state = v == parent[u] ? dp_parent[u] : dp[v];\n \
    \               suff = op(to_path(state, w), suff);\n                --i;\n  \
    \          }\n            dp[u] = to_subtree(suff, g.node_weight(u));\n      \
    \  }\n    }\n    return dp;\n}\n\n#endif // REROOTING_HPP"
  dependsOn: []
  isVerificationFile: false
  path: dp/rerooting.hpp
  requiredBy: []
  timestamp: '2026-01-04 01:29:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dp/rerooting.test.cpp
documentation_of: dp/rerooting.hpp
layout: document
redirect_from:
- /library/dp/rerooting.hpp
- /library/dp/rerooting.hpp.html
title: dp/rerooting.hpp
---
