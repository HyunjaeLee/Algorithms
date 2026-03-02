---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: dp/rerooting.hpp
    title: Rerooting
  - icon: ':question:'
    path: graph/csr_graph.hpp
    title: graph/csr_graph.hpp
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
    \  }\n    }\n    return dp;\n}\n\n\n#line 1 \"graph/csr_graph.hpp\"\n\n\n\n#include\
    \ <cassert>\n#line 6 \"graph/csr_graph.hpp\"\n#include <type_traits>\n#include\
    \ <utility>\n#include <variant>\n#line 10 \"graph/csr_graph.hpp\"\n\ntemplate\
    \ <typename EdgeWeight = std::monostate, typename NodeWeight = std::monostate>\n\
    struct CSRGraph {\n    static constexpr bool HasNodeWeight = !std::is_same_v<NodeWeight,\
    \ std::monostate>;\n    CSRGraph(int n) : n_(n), start_(n + 1) {\n        if constexpr\
    \ (HasNodeWeight) {\n            nodes_.resize(n_);\n        }\n    }\n    void\
    \ set_node(int u, NodeWeight w) {\n        assert(0 <= u && u < n_);\n       \
    \ if constexpr (HasNodeWeight) {\n            nodes_[u] = w;\n        }\n    }\n\
    \    NodeWeight node_weight(int u) const {\n        assert(0 <= u && u < n_);\n\
    \        if constexpr (HasNodeWeight) {\n            return nodes_[u];\n     \
    \   } else {\n            return {};\n        }\n    }\n    void add_edge(int\
    \ u, int v, EdgeWeight w = {}) {\n        assert(0 <= u && u < n_ && 0 <= v &&\
    \ v < n_);\n        raw_edges_.push_back({u, v, w});\n    }\n    void build_undirected()\
    \ {\n        assert(!built_);\n        edges_.resize(2 * raw_edges_.size());\n\
    \        for (const auto &e : raw_edges_) {\n            ++start_[e.u + 1];\n\
    \            ++start_[e.v + 1];\n        }\n        for (int i = 0; i < n_; ++i)\
    \ {\n            start_[i + 1] += start_[i];\n        }\n        auto counter\
    \ = start_;\n        for (const auto &e : raw_edges_) {\n            edges_[counter[e.u]++]\
    \ = {e.v, e.w};\n            edges_[counter[e.v]++] = {e.u, e.w};\n        }\n\
    \        std::vector<RawEdge>().swap(raw_edges_);\n        built_ = true;\n  \
    \  }\n    void build_directed() {\n        assert(!built_);\n        edges_.resize(raw_edges_.size());\n\
    \        for (const auto &e : raw_edges_) {\n            ++start_[e.u + 1];\n\
    \        }\n        for (int i = 0; i < n_; ++i) {\n            start_[i + 1]\
    \ += start_[i];\n        }\n        auto counter = start_;\n        for (const\
    \ auto &e : raw_edges_) {\n            edges_[counter[e.u]++] = {e.v, e.w};\n\
    \        }\n        std::vector<RawEdge>().swap(raw_edges_);\n        built_ =\
    \ true;\n    }\n    auto operator[](int u) const {\n        assert(built_);\n\
    \        assert(0 <= u && u < n_);\n        constexpr auto f = [](Edge e) { return\
    \ std::pair(e.to, e.w); };\n        return std::ranges::subrange(edges_.begin()\
    \ + start_[u], edges_.begin() + start_[u + 1]) |\n               std::views::transform(f);\n\
    \    }\n    int size() const { return n_; }\n    struct Edge {\n        int to;\n\
    \        [[no_unique_address]] EdgeWeight w;\n    };\n    struct RawEdge {\n \
    \       int u, v;\n        [[no_unique_address]] EdgeWeight w;\n    };\n    int\
    \ n_;\n    bool built_ = false;\n    std::vector<Edge> edges_;\n    std::vector<int>\
    \ start_;\n    std::vector<RawEdge> raw_edges_;\n    std::vector<NodeWeight> nodes_;\n\
    };\n\n\n#line 5 \"test/dp/rerooting.test.cpp\"\n#include <atcoder/modint>\n#include\
    \ <bits/stdc++.h>\n\nusing Z = atcoder::modint998244353;\n\nint main() {\n   \
    \ std::cin.tie(0)->sync_with_stdio(0);\n    int N;\n    std::cin >> N;\n    using\
    \ EdgeWeight = std::pair<int, int>;\n    CSRGraph<EdgeWeight> g(N);\n    std::vector<int>\
    \ a(N);\n    std::copy_n(std::istream_iterator<int>(std::cin), N, a.begin());\n\
    \    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b, c;\n        std::cin\
    \ >> u >> v >> b >> c;\n        g.add_edge(u, v, {b, c});\n    }\n    g.build_undirected();\n\
    \    using State = std::pair<Z, int>;\n    using Subtree = State;\n    using Child\
    \ = State;\n    auto rake = [&](Child l, Child r) -> Child { return {l.first +\
    \ r.first, l.second + r.second}; };\n    auto add_edge = [&](Subtree d, EdgeWeight\
    \ w) -> Child {\n        return {w.first * d.first + Z::raw(w.second) * d.second,\
    \ d.second};\n    };\n    auto add_vertex = [&](Child d, int i) -> Subtree { return\
    \ {d.first + a[i], d.second + 1}; };\n    auto e = []() -> Child { return {0,\
    \ 0}; };\n    auto dp = rerooting(g, rake, add_edge, add_vertex, e);\n    for\
    \ (auto [sum, cnt] : dp) {\n        std::cout << sum.val() << ' ';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n\n#include \"dp/rerooting.hpp\"\n#include \"graph/csr_graph.hpp\"\n#include\
    \ <atcoder/modint>\n#include <bits/stdc++.h>\n\nusing Z = atcoder::modint998244353;\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N;\n    std::cin\
    \ >> N;\n    using EdgeWeight = std::pair<int, int>;\n    CSRGraph<EdgeWeight>\
    \ g(N);\n    std::vector<int> a(N);\n    std::copy_n(std::istream_iterator<int>(std::cin),\
    \ N, a.begin());\n    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b,\
    \ c;\n        std::cin >> u >> v >> b >> c;\n        g.add_edge(u, v, {b, c});\n\
    \    }\n    g.build_undirected();\n    using State = std::pair<Z, int>;\n    using\
    \ Subtree = State;\n    using Child = State;\n    auto rake = [&](Child l, Child\
    \ r) -> Child { return {l.first + r.first, l.second + r.second}; };\n    auto\
    \ add_edge = [&](Subtree d, EdgeWeight w) -> Child {\n        return {w.first\
    \ * d.first + Z::raw(w.second) * d.second, d.second};\n    };\n    auto add_vertex\
    \ = [&](Child d, int i) -> Subtree { return {d.first + a[i], d.second + 1}; };\n\
    \    auto e = []() -> Child { return {0, 0}; };\n    auto dp = rerooting(g, rake,\
    \ add_edge, add_vertex, e);\n    for (auto [sum, cnt] : dp) {\n        std::cout\
    \ << sum.val() << ' ';\n    }\n}\n"
  dependsOn:
  - dp/rerooting.hpp
  - graph/csr_graph.hpp
  isVerificationFile: true
  path: test/dp/rerooting.test.cpp
  requiredBy: []
  timestamp: '2026-03-02 14:25:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dp/rerooting.test.cpp
layout: document
redirect_from:
- /verify/test/dp/rerooting.test.cpp
- /verify/test/dp/rerooting.test.cpp.html
title: test/dp/rerooting.test.cpp
---
