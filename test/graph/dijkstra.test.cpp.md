---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/csr_graph.hpp
    title: graph/csr_graph.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "#line 1 \"test/graph/dijkstra.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\
    \n\n#line 1 \"graph/csr_graph.hpp\"\n\n\n\n#include <cassert>\n#include <ranges>\n\
    #include <type_traits>\n#include <utility>\n#include <variant>\n#include <vector>\n\
    \ntemplate <typename NodeWeight = std::monostate, typename EdgeWeight = std::monostate>\n\
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
    };\n\n\n#line 4 \"test/graph/dijkstra.test.cpp\"\n#include <bits/stdc++.h>\n\n\
    int main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int n, m, s, t;\n\
    \    std::cin >> n >> m >> s >> t;\n    CSRGraph<std::monostate, long long> g(n);\n\
    \    for (auto i = 0; i < m; ++i) {\n        int u, v, w;\n        std::cin >>\
    \ u >> v >> w;\n        g.add_edge(u, v, w);\n    }\n    g.build_directed();\n\
    \    using S = std::pair<long long, int>;\n    std::vector<int> parent(n, -1);\n\
    \    std::vector<long long> dist(n, std::numeric_limits<long long>::max());\n\
    \    std::priority_queue<S, std::vector<S>, std::greater<>> pq;\n    dist[s] =\
    \ 0;\n    pq.emplace(dist[s], s);\n    while (!pq.empty()) {\n        auto [d,\
    \ u] = pq.top();\n        pq.pop();\n        if (d != dist[u]) {\n           \
    \ continue;\n        }\n        for (auto [v, w] : g[u]) {\n            if (d\
    \ + w < dist[v]) {\n                parent[v] = u;\n                dist[v] =\
    \ d + w;\n                pq.emplace(dist[v], v);\n            }\n        }\n\
    \    }\n    if (dist[t] == std::numeric_limits<long long>::max()) {\n        std::cout\
    \ << -1;\n    } else {\n        std::vector<int> ans;\n        for (auto u = t;\
    \ u != s; u = parent[u]) {\n            ans.push_back(u);\n        }\n       \
    \ auto X = dist[t];\n        auto Y = (int)ans.size();\n        ans.push_back(s);\n\
    \        std::cout << X << \" \" << Y << \"\\n\";\n        for (auto i = Y; 0\
    \ < i; --i) {\n            std::cout << ans[i] << \" \" << ans[i - 1] << \"\\\
    n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n\n#include\
    \ \"graph/csr_graph.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int n, m, s, t;\n    std::cin >> n >> m >> s >> t;\n    CSRGraph<std::monostate,\
    \ long long> g(n);\n    for (auto i = 0; i < m; ++i) {\n        int u, v, w;\n\
    \        std::cin >> u >> v >> w;\n        g.add_edge(u, v, w);\n    }\n    g.build_directed();\n\
    \    using S = std::pair<long long, int>;\n    std::vector<int> parent(n, -1);\n\
    \    std::vector<long long> dist(n, std::numeric_limits<long long>::max());\n\
    \    std::priority_queue<S, std::vector<S>, std::greater<>> pq;\n    dist[s] =\
    \ 0;\n    pq.emplace(dist[s], s);\n    while (!pq.empty()) {\n        auto [d,\
    \ u] = pq.top();\n        pq.pop();\n        if (d != dist[u]) {\n           \
    \ continue;\n        }\n        for (auto [v, w] : g[u]) {\n            if (d\
    \ + w < dist[v]) {\n                parent[v] = u;\n                dist[v] =\
    \ d + w;\n                pq.emplace(dist[v], v);\n            }\n        }\n\
    \    }\n    if (dist[t] == std::numeric_limits<long long>::max()) {\n        std::cout\
    \ << -1;\n    } else {\n        std::vector<int> ans;\n        for (auto u = t;\
    \ u != s; u = parent[u]) {\n            ans.push_back(u);\n        }\n       \
    \ auto X = dist[t];\n        auto Y = (int)ans.size();\n        ans.push_back(s);\n\
    \        std::cout << X << \" \" << Y << \"\\n\";\n        for (auto i = Y; 0\
    \ < i; --i) {\n            std::cout << ans[i] << \" \" << ans[i - 1] << \"\\\
    n\";\n        }\n    }\n}\n"
  dependsOn:
  - graph/csr_graph.hpp
  isVerificationFile: true
  path: test/graph/dijkstra.test.cpp
  requiredBy: []
  timestamp: '2026-01-12 02:39:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/dijkstra.test.cpp
layout: document
redirect_from:
- /verify/test/graph/dijkstra.test.cpp
- /verify/test/graph/dijkstra.test.cpp.html
title: test/graph/dijkstra.test.cpp
---
