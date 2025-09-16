---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: heavy_light_decomposition/heavy_light_decomposition.hpp
    title: Heavy-Light Decomposition
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "#line 1 \"test/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\n\
    \n#line 1 \"heavy_light_decomposition/heavy_light_decomposition.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include <vector>\n\
    \nstruct heavy_light_decomposition {\n    heavy_light_decomposition(const std::vector<std::vector<int>>\
    \ &graph,\n                              int root)\n        : n_(static_cast<int>(graph.size())),\
    \ timer_(0), graph_(graph),\n          size_(n_, 1), depth_(n_), parent_(n_, -1),\
    \ top_(n_), in_(n_),\n          out_(n_) {\n        assert(0 <= root && root <\
    \ n_);\n        top_[root] = root;\n        dfs_size(root);\n        dfs_hld(root);\n\
    \    }\n    template <typename Function> void access_node(int u, Function f) {\n\
    \        assert(0 <= u && u < n_);\n        f(in_[u]);\n    }\n    template <typename\
    \ Function>\n    std::enable_if_t<\n        std::is_same_v<std::invoke_result_t<Function,\
    \ int, int>, void>, void>\n    access_path(int u, int v, bool include_lca, Function\
    \ f) const {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        while\
    \ (top_[u] != top_[v]) {\n            if (depth_[top_[u]] < depth_[top_[v]]) {\n\
    \                std::swap(u, v);\n            }\n            f(in_[top_[u]],\
    \ in_[u] + 1);\n            u = parent_[top_[u]];\n        }\n        if (depth_[u]\
    \ > depth_[v]) {\n            std::swap(u, v);\n        }\n        if (include_lca)\
    \ {\n            f(in_[u], in_[v] + 1);\n        } else {\n            f(in_[u]\
    \ + 1, in_[v] + 1);\n        }\n    }\n    template <typename Function>\n    std::enable_if_t<\n\
    \        std::is_same_v<std::invoke_result_t<Function, int, int, bool>, void>,\n\
    \        void>\n    access_path(int u, int v, bool include_lca, Function f) const\
    \ {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        bool u_to_lca\
    \ = true;\n        while (top_[u] != top_[v]) {\n            if (depth_[top_[u]]\
    \ < depth_[top_[v]]) {\n                std::swap(u, v);\n                u_to_lca\
    \ = !u_to_lca;\n            }\n            f(in_[top_[u]], in_[u] + 1, u_to_lca);\n\
    \            u = parent_[top_[u]];\n        }\n        if (depth_[u] > depth_[v])\
    \ {\n            std::swap(u, v);\n        } else {\n            u_to_lca = !u_to_lca;\n\
    \        }\n        if (include_lca) {\n            f(in_[u], in_[v] + 1, u_to_lca);\n\
    \        } else {\n            f(in_[u] + 1, in_[v] + 1, u_to_lca);\n        }\n\
    \    }\n    template <typename Function>\n    void access_subtree(int u, bool\
    \ include_root, Function f) const {\n        assert(0 <= u && u < n_);\n     \
    \   if (include_root) {\n            f(in_[u], out_[u]);\n        } else {\n \
    \           f(in_[u] + 1, out_[u]);\n        }\n    }\n    int lca(int u, int\
    \ v) const {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        while\
    \ (top_[u] != top_[v]) {\n            if (depth_[top_[u]] < depth_[top_[v]]) {\n\
    \                std::swap(u, v);\n            }\n            u = parent_[top_[u]];\n\
    \        }\n        if (depth_[u] > depth_[v]) {\n            std::swap(u, v);\n\
    \        }\n        return u;\n    }\n\nprivate:\n    void dfs_size(int u) {\n\
    \        auto it = std::find(graph_[u].begin(), graph_[u].end(), parent_[u]);\n\
    \        if (it != graph_[u].end()) {\n            graph_[u].erase(it);\n    \
    \    }\n        for (auto &v : graph_[u]) {\n            depth_[v] = depth_[u]\
    \ + 1;\n            parent_[v] = u;\n            dfs_size(v);\n            size_[u]\
    \ += size_[v];\n            if (size_[v] > size_[graph_[u][0]]) {\n          \
    \      std::swap(v, graph_[u][0]);\n            }\n        }\n    }\n    void\
    \ dfs_hld(int u) {\n        in_[u] = timer_++;\n        for (auto v : graph_[u])\
    \ {\n            top_[v] = (v == graph_[u][0] ? top_[u] : v);\n            dfs_hld(v);\n\
    \        }\n        out_[u] = timer_;\n    }\n    int n_, timer_;\n    std::vector<std::vector<int>>\
    \ graph_;\n    std::vector<int> size_, depth_, parent_, top_, in_, out_;\n};\n\
    \n\n#line 4 \"test/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp\"\
    \n#include <atcoder/fenwicktree>\n#include <bits/stdc++.h>\n\nint main() {\n \
    \   std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >> N >>\
    \ Q;\n    std::vector<int> a(N);\n    for (auto &x : a) {\n        std::cin >>\
    \ x;\n    }\n    std::vector<std::vector<int>> adj(N);\n    for (auto i = 1; i\
    \ < N; ++i) {\n        int p;\n        std::cin >> p;\n        adj[p].push_back(i);\n\
    \    }\n    heavy_light_decomposition hld(adj, 0);\n    atcoder::fenwick_tree<long\
    \ long> ft(N);\n    for (auto i = 0; i < N; ++i) {\n        hld.access_node(i,\
    \ [&](auto x) { ft.add(x, a[i]); });\n    }\n    for (auto i = 0; i < Q; ++i)\
    \ {\n        int t, u;\n        std::cin >> t >> u;\n        if (t == 0) {\n \
    \           long long val;\n            std::cin >> val;\n            hld.access_node(u,\
    \ [&](auto x) { ft.add(x, val); });\n        } else {\n            auto ans =\
    \ 0LL;\n            hld.access_subtree(u, true,\n                            \
    \   [&](auto l, auto r) { ans = ft.sum(l, r); });\n            std::cout << ans\
    \ << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n\n#include \"heavy_light_decomposition/heavy_light_decomposition.hpp\"\n#include\
    \ <atcoder/fenwicktree>\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> a(N);\n    for (auto\
    \ &x : a) {\n        std::cin >> x;\n    }\n    std::vector<std::vector<int>>\
    \ adj(N);\n    for (auto i = 1; i < N; ++i) {\n        int p;\n        std::cin\
    \ >> p;\n        adj[p].push_back(i);\n    }\n    heavy_light_decomposition hld(adj,\
    \ 0);\n    atcoder::fenwick_tree<long long> ft(N);\n    for (auto i = 0; i < N;\
    \ ++i) {\n        hld.access_node(i, [&](auto x) { ft.add(x, a[i]); });\n    }\n\
    \    for (auto i = 0; i < Q; ++i) {\n        int t, u;\n        std::cin >> t\
    \ >> u;\n        if (t == 0) {\n            long long val;\n            std::cin\
    \ >> val;\n            hld.access_node(u, [&](auto x) { ft.add(x, val); });\n\
    \        } else {\n            auto ans = 0LL;\n            hld.access_subtree(u,\
    \ true,\n                               [&](auto l, auto r) { ans = ft.sum(l,\
    \ r); });\n            std::cout << ans << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - heavy_light_decomposition/heavy_light_decomposition.hpp
  isVerificationFile: true
  path: test/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
layout: document
redirect_from:
- /verify/test/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
- /verify/test/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp.html
title: test/heavy_light_decomposition/vertex_add_subtree_sum.test.cpp
---
