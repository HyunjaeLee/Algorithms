---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/csr_graph.hpp
    title: graph/csr_graph.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "#line 1 \"test/graph/dijkstra.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\
    \n\n#line 1 \"graph/csr_graph.hpp\"\n\n\n\n#include <cassert>\n#include <ranges>\n\
    #include <vector>\n\ntemplate <typename EdgeWeight = int> struct CSRGraph {\n\
    \    struct Edge {\n        int u;\n        int v;\n        EdgeWeight w;\n  \
    \      int i;\n    };\n    CSRGraph(int n) : n_(n) {}\n    void add_edge(int u,\
    \ int v, EdgeWeight w = 1) {\n        assert(!built_);\n        assert(0 <= u\
    \ && u < n_ && 0 <= v && v < n_);\n        auto i = int(edges_.size());\n    \
    \    edges_.push_back({u, v, w, i});\n    }\n    void build_undirected() {\n \
    \       assert(!built_);\n        start_.assign(n_ + 1, 0);\n        csr_.resize(2\
    \ * edges_.size());\n        for (const auto &e : edges_) {\n            ++start_[e.u\
    \ + 1];\n            ++start_[e.v + 1];\n        }\n        for (int i = 0; i\
    \ < n_; ++i) {\n            start_[i + 1] += start_[i];\n        }\n        auto\
    \ pos = start_;\n        for (const auto &e : edges_) {\n            csr_[pos[e.u]++]\
    \ = {e.u, e.v, e.w, e.i};\n            csr_[pos[e.v]++] = {e.v, e.u, e.w, e.i};\n\
    \        }\n        built_ = true;\n    }\n    void build_directed() {\n     \
    \   assert(!built_);\n        start_.assign(n_ + 1, 0);\n        csr_.resize(edges_.size());\n\
    \        for (const auto &e : edges_) {\n            ++start_[e.u + 1];\n    \
    \    }\n        for (int i = 0; i < n_; ++i) {\n            start_[i + 1] += start_[i];\n\
    \        }\n        auto pos = start_;\n        for (const auto &e : edges_) {\n\
    \            csr_[pos[e.u]++] = e;\n        }\n        built_ = true;\n    }\n\
    \    auto operator[](int u) const {\n        assert(built_);\n        assert(0\
    \ <= u && u < n_);\n        return std::ranges::subrange(csr_.begin() + start_[u],\
    \ csr_.begin() + start_[u + 1]);\n    }\n    int size() const { return n_; }\n\
    \nprivate:\n    int n_;\n    bool built_ = false;\n    std::vector<Edge> edges_;\n\
    \    std::vector<Edge> csr_;\n    std::vector<int> start_;\n};\n\n\n#line 4 \"\
    test/graph/dijkstra.test.cpp\"\n#include <bits/stdc++.h>\n\nint main() {\n   \
    \ std::cin.tie(0)->sync_with_stdio(0);\n    int n, m, s, t;\n    std::cin >> n\
    \ >> m >> s >> t;\n    CSRGraph<long long> g(n);\n    for (auto i = 0; i < m;\
    \ ++i) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n        g.add_edge(u,\
    \ v, w);\n    }\n    g.build_directed();\n    using S = std::pair<long long, int>;\n\
    \    std::vector<int> parent(n, -1);\n    std::vector<long long> dist(n, std::numeric_limits<long\
    \ long>::max());\n    std::priority_queue<S, std::vector<S>, std::greater<>> pq;\n\
    \    dist[s] = 0;\n    pq.emplace(dist[s], s);\n    while (!pq.empty()) {\n  \
    \      auto [d, u] = pq.top();\n        pq.pop();\n        if (d != dist[u]) {\n\
    \            continue;\n        }\n        for (auto [v, w] : g[u]) {\n      \
    \      if (d + w < dist[v]) {\n                parent[v] = u;\n              \
    \  dist[v] = d + w;\n                pq.emplace(dist[v], v);\n            }\n\
    \        }\n    }\n    if (dist[t] == std::numeric_limits<long long>::max()) {\n\
    \        std::cout << -1;\n    } else {\n        std::vector<int> ans;\n     \
    \   for (auto u = t; u != s; u = parent[u]) {\n            ans.push_back(u);\n\
    \        }\n        auto X = dist[t];\n        auto Y = (int)ans.size();\n   \
    \     ans.push_back(s);\n        std::cout << X << \" \" << Y << \"\\n\";\n  \
    \      for (auto i = Y; 0 < i; --i) {\n            std::cout << ans[i] << \" \"\
    \ << ans[i - 1] << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n\n#include\
    \ \"graph/csr_graph.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int n, m, s, t;\n    std::cin >> n >> m >> s >> t;\n    CSRGraph<long long>\
    \ g(n);\n    for (auto i = 0; i < m; ++i) {\n        int u, v, w;\n        std::cin\
    \ >> u >> v >> w;\n        g.add_edge(u, v, w);\n    }\n    g.build_directed();\n\
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
  timestamp: '2026-08-12 07:38:15+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/graph/dijkstra.test.cpp
layout: document
redirect_from:
- /verify/test/graph/dijkstra.test.cpp
- /verify/test/graph/dijkstra.test.cpp.html
title: test/graph/dijkstra.test.cpp
---
