---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/auxiliary_tree.hpp
    title: graph/auxiliary_tree.hpp
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
    PROBLEM: https://yukicoder.me/problems/no/901
    links:
    - https://yukicoder.me/problems/no/901
  bundledCode: "#line 1 \"test/graph/yuki901.test.cpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/901\"\
    \n\n#line 1 \"graph/auxiliary_tree.hpp\"\n\n\n\n#line 1 \"heavy_light_decomposition/heavy_light_decomposition.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include\
    \ <vector>\n\nstruct heavy_light_decomposition {\n    heavy_light_decomposition(const\
    \ std::vector<std::vector<int>> &graph, int root)\n        : n_(int(graph.size())),\
    \ timer_(0), graph_(graph), size_(n_, 1), depth_(n_), parent_(n_, -1), top_(n_),\
    \ in_(n_),\n          out_(n_) {\n        assert(0 <= root && root < n_);\n  \
    \      top_[root] = root;\n        dfs_size(root);\n        dfs_hld(root);\n \
    \   }\n    template <typename Function> void access_node(int u, Function f) const\
    \ {\n        assert(0 <= u && u < n_);\n        f(in_[u]);\n    }\n    template\
    \ <typename Function>\n    std::enable_if_t<std::is_same_v<std::invoke_result_t<Function,\
    \ int, int>, void>, void>\n    access_path(int u, int v, bool include_lca, Function\
    \ f) const {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        while\
    \ (top_[u] != top_[v]) {\n            if (depth_[top_[u]] < depth_[top_[v]]) {\n\
    \                std::swap(u, v);\n            }\n            f(in_[top_[u]],\
    \ in_[u] + 1);\n            u = parent_[top_[u]];\n        }\n        if (depth_[u]\
    \ > depth_[v]) {\n            std::swap(u, v);\n        }\n        if (include_lca)\
    \ {\n            f(in_[u], in_[v] + 1);\n        } else {\n            f(in_[u]\
    \ + 1, in_[v] + 1);\n        }\n    }\n    template <typename Function>\n    std::enable_if_t<std::is_same_v<std::invoke_result_t<Function,\
    \ int, int, bool>, void>, void>\n    access_path(int u, int v, bool include_lca,\
    \ Function f) const {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n\
    \        bool u_to_lca = true;\n        while (top_[u] != top_[v]) {\n       \
    \     if (depth_[top_[u]] < depth_[top_[v]]) {\n                std::swap(u, v);\n\
    \                u_to_lca = !u_to_lca;\n            }\n            f(in_[top_[u]],\
    \ in_[u] + 1, u_to_lca);\n            u = parent_[top_[u]];\n        }\n     \
    \   if (depth_[u] > depth_[v]) {\n            std::swap(u, v);\n        } else\
    \ {\n            u_to_lca = !u_to_lca;\n        }\n        if (include_lca) {\n\
    \            f(in_[u], in_[v] + 1, u_to_lca);\n        } else {\n            f(in_[u]\
    \ + 1, in_[v] + 1, u_to_lca);\n        }\n    }\n    template <typename Function>\
    \ void access_subtree(int u, bool include_root, Function f) const {\n        assert(0\
    \ <= u && u < n_);\n        if (include_root) {\n            f(in_[u], out_[u]);\n\
    \        } else {\n            f(in_[u] + 1, out_[u]);\n        }\n    }\n   \
    \ int lca(int u, int v) const {\n        assert(0 <= u && u < n_ && 0 <= v &&\
    \ v < n_);\n        while (top_[u] != top_[v]) {\n            if (depth_[top_[u]]\
    \ < depth_[top_[v]]) {\n                std::swap(u, v);\n            }\n    \
    \        u = parent_[top_[u]];\n        }\n        if (depth_[u] > depth_[v])\
    \ {\n            std::swap(u, v);\n        }\n        return u;\n    }\n    int\
    \ in(int u) const {\n        assert(0 <= u && u < n_);\n        return in_[u];\n\
    \    }\n    int out(int u) const {\n        assert(0 <= u && u < n_);\n      \
    \  return out_[u];\n    }\n    int depth(int u) const {\n        assert(0 <= u\
    \ && u < n_);\n        return depth_[u];\n    };\n\nprivate:\n    void dfs_size(int\
    \ u) {\n        for (auto &v : graph_[u]) {\n            if (v != parent_[u])\
    \ {\n                depth_[v] = depth_[u] + 1;\n                parent_[v] =\
    \ u;\n                dfs_size(v);\n                size_[u] += size_[v];\n  \
    \              if (size_[graph_[u][0]] < size_[v] || graph_[u][0] == parent_[u])\
    \ {\n                    std::swap(graph_[u][0], v);\n                }\n    \
    \        }\n        }\n    }\n    void dfs_hld(int u) {\n        in_[u] = timer_++;\n\
    \        for (auto v : graph_[u]) {\n            if (v != parent_[u]) {\n    \
    \            top_[v] = (v == graph_[u][0] ? top_[u] : v);\n                dfs_hld(v);\n\
    \            }\n        }\n        out_[u] = timer_;\n    }\n    const int n_;\n\
    \    int timer_;\n    std::vector<std::vector<int>> graph_;\n    std::vector<int>\
    \ size_, depth_, parent_, top_, in_, out_;\n};\n\n\n#line 6 \"graph/auxiliary_tree.hpp\"\
    \n#include <utility>\n#line 8 \"graph/auxiliary_tree.hpp\"\n\nstruct AuxiliaryTree\
    \ {\n    AuxiliaryTree(const std::vector<std::vector<int>> &graph, int root) :\
    \ hld_(graph, root) {}\n    std::vector<std::pair<int, int>> get(std::vector<int>\
    \ x) const {\n        if (x.empty()) {\n            return {};\n        }\n  \
    \      std::ranges::sort(x, {}, [&](int u) { return hld_.in(u); });\n        const\
    \ auto m = int(x.size());\n        for (auto i = 1; i < m; i++) {\n          \
    \  x.push_back(hld_.lca(x[i - 1], x[i]));\n        }\n        std::ranges::sort(x,\
    \ {}, [&](int u) { return hld_.in(u); });\n        auto r = std::ranges::unique(x);\n\
    \        x.erase(r.begin(), r.end());\n        const auto n = int(x.size());\n\
    \        std::vector<int> st;\n        std::vector<std::pair<int, int>> dfs_order(n);\n\
    \        st.push_back(x[0]);\n        dfs_order[0] = {x[0], -1};\n        for\
    \ (auto i = 1; i < n; ++i) {\n            auto v = x[i];\n            while (!st.empty())\
    \ {\n                auto u = st.back();\n                if (hld_.in(u) <= hld_.in(v)\
    \ && hld_.in(v) < hld_.out(u)) {\n                    break;\n               \
    \ } else {\n                    st.pop_back();\n                }\n          \
    \  }\n            auto parent = st.back();\n            dfs_order[i] = {v, parent};\n\
    \            st.push_back(v);\n        }\n        return dfs_order;\n    }\n \
    \   const heavy_light_decomposition &hld() const { return hld_; }\n\nprivate:\n\
    \    const heavy_light_decomposition hld_;\n};\n\n\n#line 4 \"test/graph/yuki901.test.cpp\"\
    \n#include <bits/stdc++.h>\nusing i64 = long long;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<std::vector<std::pair<int, i64>>>\
    \ adj(N);\n    std::vector<std::vector<int>> g(N);\n    for (auto i = 0; i < N\
    \ - 1; ++i) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n      \
    \  adj[u].emplace_back(v, w);\n        adj[v].emplace_back(u, w);\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    std::vector<i64> dist(N);\n    auto dfs\
    \ = [&](auto &&self, int u, int p) -> void {\n        for (auto [v, w] : adj[u])\
    \ {\n            if (v != p) {\n                dist[v] = dist[u] + w;\n     \
    \           self(self, v, u);\n            }\n        }\n    };\n    dfs(dfs,\
    \ 0, 0);\n    AuxiliaryTree aux(g, 0);\n    int Q;\n    std::cin >> Q;\n    while\
    \ (Q--) {\n        int k;\n        std::cin >> k;\n        std::vector<int> x(k);\n\
    \        std::copy_n(std::istream_iterator<int>(std::cin), k, x.begin());\n  \
    \      i64 ans = 0;\n        for (auto [u, p] : aux.get(move(x)) | std::views::drop(1))\
    \ {\n            ans += dist[u] - dist[p];\n        }\n        std::cout << ans\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/901\"\n\n#include \"graph/auxiliary_tree.hpp\"\
    \n#include <bits/stdc++.h>\nusing i64 = long long;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<std::vector<std::pair<int, i64>>>\
    \ adj(N);\n    std::vector<std::vector<int>> g(N);\n    for (auto i = 0; i < N\
    \ - 1; ++i) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n      \
    \  adj[u].emplace_back(v, w);\n        adj[v].emplace_back(u, w);\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n    std::vector<i64> dist(N);\n    auto dfs\
    \ = [&](auto &&self, int u, int p) -> void {\n        for (auto [v, w] : adj[u])\
    \ {\n            if (v != p) {\n                dist[v] = dist[u] + w;\n     \
    \           self(self, v, u);\n            }\n        }\n    };\n    dfs(dfs,\
    \ 0, 0);\n    AuxiliaryTree aux(g, 0);\n    int Q;\n    std::cin >> Q;\n    while\
    \ (Q--) {\n        int k;\n        std::cin >> k;\n        std::vector<int> x(k);\n\
    \        std::copy_n(std::istream_iterator<int>(std::cin), k, x.begin());\n  \
    \      i64 ans = 0;\n        for (auto [u, p] : aux.get(move(x)) | std::views::drop(1))\
    \ {\n            ans += dist[u] - dist[p];\n        }\n        std::cout << ans\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/auxiliary_tree.hpp
  - heavy_light_decomposition/heavy_light_decomposition.hpp
  isVerificationFile: true
  path: test/graph/yuki901.test.cpp
  requiredBy: []
  timestamp: '2026-02-28 16:36:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/yuki901.test.cpp
layout: document
redirect_from:
- /verify/test/graph/yuki901.test.cpp
- /verify/test/graph/yuki901.test.cpp.html
title: test/graph/yuki901.test.cpp
---
