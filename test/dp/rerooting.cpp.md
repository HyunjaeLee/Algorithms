---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: dp/rerooting.hpp
    title: dp/rerooting.hpp
  - icon: ':warning:'
    path: graph/csr_graph.hpp
    title: graph/csr_graph.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"test/dp/rerooting.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#line 1 \"dp/rerooting.hpp\"\n\n\n\n#include <vector>\n\nauto rerooting(const\
    \ auto &g,   // Graph\n               auto op,         // (PathState, PathState)\
    \ -> PathState\n               auto to_path,    // (TreeState, EdgeWeight) ->\
    \ PathState\n               auto to_subtree, // (PathState, NodeWeight) -> TreeState\n\
    \               auto e           // PathState (Identity)\n) {\n    int n = g.size();\n\
    \    using PathState = decltype(e);\n    using TreeState = decltype(to_subtree(e,\
    \ g.node_weight(0)));\n    std::vector<TreeState> dp(n), dp_parent(n);\n    std::vector<int>\
    \ q, parent(n, -1);\n    std::vector<PathState> pref(n + 1);\n    q.reserve(n);\n\
    \    for (int root = 0; root < n; ++root) {\n        if (~parent[root]) {\n  \
    \          continue;\n        }\n        parent[root] = root;\n        q.clear();\n\
    \        q.push_back(root);\n        auto it = q.cbegin();\n        while (it\
    \ != q.cend()) {\n            int u = *it++;\n            for (auto [v, w] : g[u])\
    \ {\n                if (v != parent[u]) {\n                    parent[v] = u;\n\
    \                    q.push_back(v);\n                }\n            }\n     \
    \   }\n        for (auto u : q | std::views::reverse) {\n            PathState\
    \ merged = e;\n            for (auto [v, w] : g[u]) {\n                if (v !=\
    \ parent[u]) {\n                    merged = op(merged, to_path(dp[v], w));\n\
    \                }\n            }\n            dp[u] = to_subtree(merged, g.node_weight(u));\n\
    \        }\n        for (auto u : q) {\n            int i = 0;\n            pref[0]\
    \ = e;\n            for (auto [v, w] : g[u]) {\n                auto state = v\
    \ == parent[u] ? dp_parent[u] : dp[v];\n                pref[i + 1] = op(pref[i],\
    \ to_path(state, w));\n                ++i;\n            }\n            auto suff\
    \ = e;\n            for (auto [v, w] : g[u] | std::views::reverse) {\n       \
    \         if (v != parent[u]) {\n                    PathState except_child =\
    \ op(pref[i - 1], suff);\n                    dp_parent[v] = to_subtree(except_child,\
    \ g.node_weight(u));\n                }\n                auto state = v == parent[u]\
    \ ? dp_parent[u] : dp[v];\n                suff = op(to_path(state, w), suff);\n\
    \                --i;\n            }\n            dp[u] = to_subtree(suff, g.node_weight(u));\n\
    \        }\n    }\n    return dp;\n}\n\n\n#line 1 \"graph/csr_graph.hpp\"\n\n\n\
    \n#include <cassert>\n#include <ranges>\n#include <type_traits>\n#include <utility>\n\
    #include <variant>\n#line 10 \"graph/csr_graph.hpp\"\n\ntemplate <typename NodeWeight\
    \ = std::monostate, typename EdgeWeight = std::monostate>\nstruct CSRGraph {\n\
    \    static constexpr bool HasNodeWeight = !std::is_same_v<NodeWeight, std::monostate>;\n\
    \    CSRGraph(int n) : n_(n), start_(n + 1) {\n        if constexpr (HasNodeWeight)\
    \ {\n            nodes_.resize(n_);\n        }\n    }\n    void set_node(int u,\
    \ NodeWeight w) {\n        assert(0 <= u && u < n_);\n        if constexpr (HasNodeWeight)\
    \ {\n            nodes_[u] = w;\n        }\n    }\n    NodeWeight node_weight(int\
    \ u) const {\n        assert(0 <= u && u < n_);\n        if constexpr (HasNodeWeight)\
    \ {\n            return nodes_[u];\n        } else {\n            return {};\n\
    \        }\n    }\n    void add_edge(int u, int v, EdgeWeight w = {}) {\n    \
    \    assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        raw_edges_.push_back({u,\
    \ v, w});\n    }\n    void build_undirected() {\n        assert(!built_);\n  \
    \      edges_.resize(2 * raw_edges_.size());\n        for (const auto &e : raw_edges_)\
    \ {\n            ++start_[e.u + 1];\n            ++start_[e.v + 1];\n        }\n\
    \        for (int i = 0; i < n_; ++i) {\n            start_[i + 1] += start_[i];\n\
    \        }\n        auto counter = start_;\n        for (const auto &e : raw_edges_)\
    \ {\n            edges_[counter[e.u]++] = {e.v, e.w};\n            edges_[counter[e.v]++]\
    \ = {e.u, e.w};\n        }\n        std::vector<RawEdge>().swap(raw_edges_);\n\
    \        built_ = true;\n    }\n    void build_directed() {\n        assert(!built_);\n\
    \        edges_.resize(raw_edges_.size());\n        for (const auto &e : raw_edges_)\
    \ {\n            ++start_[e.u + 1];\n        }\n        for (int i = 0; i < n_;\
    \ ++i) {\n            start_[i + 1] += start_[i];\n        }\n        auto counter\
    \ = start_;\n        for (const auto &e : raw_edges_) {\n            edges_[counter[e.u]++]\
    \ = {e.v, e.w};\n        }\n        std::vector<RawEdge>().swap(raw_edges_);\n\
    \        built_ = true;\n    }\n    auto operator[](int u) const {\n        assert(built_);\n\
    \        assert(0 <= u && u < n_);\n        constexpr auto f = [](Edge e) { return\
    \ std::pair(e.to, e.w); };\n        return std::ranges::subrange(edges_.begin()\
    \ + start_[u], edges_.begin() + start_[u + 1]) |\n               std::views::transform(f);\n\
    \    }\n    int size() const { return n_; }\n    struct Edge {\n        int to;\n\
    \        [[no_unique_address]] EdgeWeight w;\n    };\n    struct RawEdge {\n \
    \       int u, v;\n        [[no_unique_address]] EdgeWeight w;\n    };\n    int\
    \ n_;\n    bool built_ = false;\n    std::vector<Edge> edges_;\n    std::vector<int>\
    \ start_;\n    std::vector<RawEdge> raw_edges_;\n    std::vector<NodeWeight> nodes_;\n\
    };\n\n\n#line 5 \"test/dp/rerooting.cpp\"\n#include <atcoder/modint>\n#include\
    \ <bits/stdc++.h>\n\nusing mint = atcoder::modint998244353;\n\nint main() {\n\
    \    std::cin.tie(0)->sync_with_stdio(0);\n    int N;\n    std::cin >> N;\n  \
    \  CSRGraph<int, std::pair<int, int>> g(N);\n    for (auto i = 0; i < N; ++i)\
    \ {\n        int a;\n        std::cin >> a;\n        g.set_node(i, a);\n    }\n\
    \    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b, c;\n        std::cin\
    \ >> u >> v >> b >> c;\n        g.add_edge(u, v, {b, c});\n    }\n    g.build_undirected();\n\
    \    using State = std::pair<mint, int>;\n    auto op = [](State a, State b) ->\
    \ State { return {a.first + b.first, a.second + b.second}; };\n    auto to_path\
    \ = [](State x, auto e) -> State {\n        return {e.first * x.first + mint::raw(e.second)\
    \ * x.second, x.second};\n    };\n    auto to_subtree = [](State x, int v) ->\
    \ State { return {x.first + v, x.second + 1}; };\n    State e{0, 0};\n    auto\
    \ dp = rerooting(g, op, to_path, to_subtree, e);\n    for (auto [sum, cnt] : dp)\
    \ {\n        std::cout << sum.val() << ' ';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"dp/rerooting.hpp\"\n#include \"graph/csr_graph.hpp\"\n#include\
    \ <atcoder/modint>\n#include <bits/stdc++.h>\n\nusing mint = atcoder::modint998244353;\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N;\n    std::cin\
    \ >> N;\n    CSRGraph<int, std::pair<int, int>> g(N);\n    for (auto i = 0; i\
    \ < N; ++i) {\n        int a;\n        std::cin >> a;\n        g.set_node(i, a);\n\
    \    }\n    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b, c;\n    \
    \    std::cin >> u >> v >> b >> c;\n        g.add_edge(u, v, {b, c});\n    }\n\
    \    g.build_undirected();\n    using State = std::pair<mint, int>;\n    auto\
    \ op = [](State a, State b) -> State { return {a.first + b.first, a.second + b.second};\
    \ };\n    auto to_path = [](State x, auto e) -> State {\n        return {e.first\
    \ * x.first + mint::raw(e.second) * x.second, x.second};\n    };\n    auto to_subtree\
    \ = [](State x, int v) -> State { return {x.first + v, x.second + 1}; };\n   \
    \ State e{0, 0};\n    auto dp = rerooting(g, op, to_path, to_subtree, e);\n  \
    \  for (auto [sum, cnt] : dp) {\n        std::cout << sum.val() << ' ';\n    }\n\
    }\n"
  dependsOn:
  - dp/rerooting.hpp
  - graph/csr_graph.hpp
  isVerificationFile: false
  path: test/dp/rerooting.cpp
  requiredBy: []
  timestamp: '2026-01-04 01:20:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: test/dp/rerooting.cpp
layout: document
redirect_from:
- /library/test/dp/rerooting.cpp
- /library/test/dp/rerooting.cpp.html
title: test/dp/rerooting.cpp
---
