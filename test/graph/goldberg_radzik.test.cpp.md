---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/csr_graph.hpp
    title: graph/csr_graph.hpp
  - icon: ':heavy_check_mark:'
    path: graph/goldberg_radzik.hpp
    title: graph/goldberg_radzik.hpp
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
  bundledCode: "#line 1 \"test/graph/goldberg_radzik.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/shortest_path\"\n\n#line 1 \"graph/goldberg_radzik.hpp\"\
    \n\n\n\n#include <limits>\n#include <ranges>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\ntemplate <typename T, T inf = std::numeric_limits<T>::max()\
    \ / 2>\nstd::tuple<bool, std::vector<T>, std::vector<int>> goldberg_radzik(const\
    \ auto &g, int src) {\n    auto n = int(g.size());\n    std::vector<T> dist(n,\
    \ inf);\n    dist[src] = 0;\n    std::vector<int> cur{src}, nxt, order, parent(n,\
    \ -1);\n    std::vector<int> state(n); // -t: in stack/labeled, t: complete\n\
    \    for (auto t = 1; !cur.empty(); ++t) {\n        order.clear();\n        auto\
    \ dfs = [&](auto &&self, int u) {\n            if (state[u] == t || state[u] ==\
    \ -t)\n                return state[u] == t;\n            state[u] = -t;\n   \
    \         for (auto [v, w] : g[u]) {\n                if (dist[v] <= dist[u] +\
    \ w)\n                    continue;\n                dist[v] = dist[u] + w;\n\
    \                parent[v] = u;\n                if (!self(self, v))\n       \
    \             return false;\n            }\n            state[u] = t;\n      \
    \      order.push_back(u);\n            return true;\n        };\n        for\
    \ (auto u : cur) {\n            if (state[u] == t)\n                continue;\n\
    \            auto can_relax = false;\n            for (auto [v, w] : g[u]) {\n\
    \                if (dist[u] + w < dist[v]) {\n                    can_relax =\
    \ true;\n                    break;\n                }\n            }\n      \
    \      if (can_relax && !dfs(dfs, u)) {\n                return {false, {}, {}};\n\
    \            }\n        }\n        nxt.clear();\n        for (auto u : order |\
    \ std::views::reverse) {\n            for (auto [v, w] : g[u]) {\n           \
    \     if (dist[v] <= dist[u] + w)\n                    continue;\n           \
    \     dist[v] = dist[u] + w;\n                parent[v] = u;\n               \
    \ if (state[v] != -t) {\n                    state[v] = -t;\n                \
    \    nxt.push_back(v);\n                }\n            }\n        }\n        std::swap(cur,\
    \ nxt);\n    }\n    return {true, std::move(dist), std::move(parent)};\n}\n\n\n\
    #line 1 \"graph/csr_graph.hpp\"\n\n\n\n#include <cassert>\n#line 7 \"graph/csr_graph.hpp\"\
    \n\ntemplate <typename T> struct csr_graph {\n    csr_graph(int n) : n_(n) {}\n\
    \    void add_edge(int u, int v, T w) {\n        assert(!built_);\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        edges_.push_back({u, v, w});\n\
    \    }\n    void build() {\n        assert(!built_);\n        start_.assign(n_\
    \ + 1, 0);\n        csr_.resize(edges_.size());\n        for (auto [u, v, w] :\
    \ edges_) {\n            ++start_[u + 1];\n        }\n        for (int i = 0;\
    \ i < n_; ++i) {\n            start_[i + 1] += start_[i];\n        }\n       \
    \ auto pos = start_;\n        for (auto [u, v, w] : edges_) {\n            csr_[pos[u]++]\
    \ = {v, w};\n        }\n        built_ = true;\n    }\n    auto operator[](int\
    \ u) const {\n        assert(built_);\n        assert(0 <= u && u < n_);\n   \
    \     return std::ranges::subrange(csr_.begin() + start_[u], csr_.begin() + start_[u\
    \ + 1]);\n    }\n    int size() const { return n_; }\n\nprivate:\n    int n_;\n\
    \    bool built_ = false;\n    std::vector<std::tuple<int, int, T>> edges_;\n\
    \    std::vector<std::pair<int, T>> csr_;\n    std::vector<int> start_;\n};\n\n\
    \n#line 5 \"test/graph/goldberg_radzik.test.cpp\"\n#include <bits/stdc++.h>\n\n\
    int main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, M, S, T;\n\
    \    std::cin >> N >> M >> S >> T;\n    csr_graph<int> g(N);\n    for (auto i\
    \ = 0; i < M; ++i) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n\
    \        g.add_edge(u, v, w);\n    }\n    g.build();\n    constexpr auto inf =\
    \ std::numeric_limits<long long>::max() / 2;\n    auto [ok, dist, parent] = goldberg_radzik<long\
    \ long, inf>(g, S);\n    std::vector<int> path;\n    for (auto x = T; x != -1;\
    \ x = parent[x]) {\n        path.push_back(x);\n    }\n    if (inf <= dist[T])\
    \ {\n        std::cout << \"-1\\n\";\n    } else {\n        auto X = dist[T];\n\
    \        auto Y = int(path.size()) - 1;\n        std::cout << X << \" \" << Y\
    \ << \"\\n\";\n        for (auto i = Y; 0 < i; --i) {\n            std::cout <<\
    \ path[i] << \" \" << path[i - 1] << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n\n#include\
    \ \"graph/goldberg_radzik.hpp\"\n#include \"graph/csr_graph.hpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, M, S, T;\n\
    \    std::cin >> N >> M >> S >> T;\n    csr_graph<int> g(N);\n    for (auto i\
    \ = 0; i < M; ++i) {\n        int u, v, w;\n        std::cin >> u >> v >> w;\n\
    \        g.add_edge(u, v, w);\n    }\n    g.build();\n    constexpr auto inf =\
    \ std::numeric_limits<long long>::max() / 2;\n    auto [ok, dist, parent] = goldberg_radzik<long\
    \ long, inf>(g, S);\n    std::vector<int> path;\n    for (auto x = T; x != -1;\
    \ x = parent[x]) {\n        path.push_back(x);\n    }\n    if (inf <= dist[T])\
    \ {\n        std::cout << \"-1\\n\";\n    } else {\n        auto X = dist[T];\n\
    \        auto Y = int(path.size()) - 1;\n        std::cout << X << \" \" << Y\
    \ << \"\\n\";\n        for (auto i = Y; 0 < i; --i) {\n            std::cout <<\
    \ path[i] << \" \" << path[i - 1] << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - graph/goldberg_radzik.hpp
  - graph/csr_graph.hpp
  isVerificationFile: true
  path: test/graph/goldberg_radzik.test.cpp
  requiredBy: []
  timestamp: '2026-10-12 17:31:27+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/goldberg_radzik.test.cpp
layout: document
redirect_from:
- /verify/test/graph/goldberg_radzik.test.cpp
- /verify/test/graph/goldberg_radzik.test.cpp.html
title: test/graph/goldberg_radzik.test.cpp
---
