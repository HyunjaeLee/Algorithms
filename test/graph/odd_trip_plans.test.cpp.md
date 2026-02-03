---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structures/potentialized_rollback_dsu.hpp
    title: data_structures/potentialized_rollback_dsu.hpp
  - icon: ':heavy_check_mark:'
    path: graph/potentialized_offline_dynamic_connectivity.hpp
    title: graph/potentialized_offline_dynamic_connectivity.hpp
  - icon: ':heavy_check_mark:'
    path: monoids/xor.hpp
    title: monoids/xor.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/3622
    links:
    - https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/3622
  bundledCode: "#line 1 \"test/graph/odd_trip_plans.test.cpp\"\n#define PROBLEM \"\
    https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/3622\"\n\n#line\
    \ 1 \"graph/potentialized_offline_dynamic_connectivity.hpp\"\n\n\n\n#line 1 \"\
    data_structures/potentialized_rollback_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <tuple>\n#include <vector>\n\n// A is an abelian\
    \ group\ntemplate <typename A> struct PotentializedRollbackDSU {\n    explicit\
    \ PotentializedRollbackDSU(int n)\n        : n_(n), valid_(true), parent_or_size_(n,\
    \ -1), potential_(n, A::e()) {}\n    int leader(int u) const { return parent_or_size_[u]\
    \ < 0 ? u : leader(parent_or_size_[u]); }\n    // returns p_u\n    A potential(int\
    \ u) const {\n        return parent_or_size_[u] < 0 ? A::e()\n               \
    \                       : A::op(potential_[u], potential(parent_or_size_[u]));\n\
    \    }\n    // returns p_v - p_u\n    A diff(int u, int v) const {\n        auto\
    \ p_u = potential(u);\n        auto p_v = potential(v);\n        return A::op(p_v,\
    \ A::inv(p_u));\n    }\n    // returns history accumulation count for offline\
    \ dynamic connectivity\n    // p_u + w = p_v\n    int merge(int u, int v, A w)\
    \ {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        auto p_v =\
    \ A::op(A::op(potential(u), w), A::inv(potential(v)));\n        u = leader(u);\n\
    \        v = leader(v);\n        if (u == v) {\n            history_.emplace_back(-1,\
    \ 0, valid_);\n            if (!(p_v == A::e())) {\n                valid_ = false;\n\
    \            }\n            return 1;\n        }\n        // insert tree v into\
    \ tree u\n        if (-parent_or_size_[u] < -parent_or_size_[v]) {\n         \
    \   std::swap(u, v);\n            p_v = A::inv(p_v);\n        }\n        history_.emplace_back(v,\
    \ parent_or_size_[v], valid_);\n        parent_or_size_[u] += parent_or_size_[v];\n\
    \        parent_or_size_[v] = u;\n        potential_[v] = p_v;\n        return\
    \ 1;\n    }\n    bool same(int u, int v) const {\n        assert(0 <= u && u <\
    \ n_ && 0 <= v && v < n_);\n        return leader(u) == leader(v);\n    }\n  \
    \  int size(int u) const {\n        assert(0 <= u && u < n_);\n        return\
    \ -parent_or_size_[leader(u)];\n    }\n    void rollback() {\n        assert(!history_.empty());\n\
    \        auto [v, size, valid] = history_.back();\n        if (~v) {\n       \
    \     auto u = parent_or_size_[v];\n            parent_or_size_[v] = size;\n \
    \           parent_or_size_[u] -= size;\n            potential_[v] = A::e();\n\
    \        } else {\n            valid_ = valid;\n        }\n        history_.pop_back();\n\
    \    }\n    void rollback(int count) {\n        for (auto i = 0; i < count; ++i)\
    \ {\n            rollback();\n        }\n    }\n    bool is_valid() const { return\
    \ valid_; }\n\nprivate:\n    int n_;\n    bool valid_;\n    std::vector<int> parent_or_size_;\n\
    \    std::vector<A> potential_;\n    std::vector<std::tuple<int, int, bool>> history_;\n\
    };\n\n\n#line 7 \"graph/potentialized_offline_dynamic_connectivity.hpp\"\n#include\
    \ <ranges>\n#line 10 \"graph/potentialized_offline_dynamic_connectivity.hpp\"\n\
    \n// A is an abelian group\ntemplate <typename A> struct PotentializedOfflineDynamicConnectivity\
    \ {\n    explicit PotentializedOfflineDynamicConnectivity(int n) : n_(n), timer_(0)\
    \ {}\n    void toggle_edge(int u, int v, A w) {\n        assert(0 <= u && u <\
    \ n_ && 0 <= v && v < n_);\n        if (u > v) {\n            std::swap(u, v);\n\
    \            w = A::inv(w);\n        }\n        edges_.emplace_back(u, v, timer_,\
    \ w);\n    }\n    int snapshot() { return timer_++; }\n    void reserve(int n)\
    \ { edges_.reserve(n); }\n    void solve(auto f) {\n        auto k = timer_;\n\
    \        if (k == 0) {\n            return;\n        }\n        auto comp = [](const\
    \ auto &a, const auto &b) {\n            const auto &[u1, v1, t1, w1] = a;\n \
    \           const auto &[u2, v2, t2, w2] = b;\n            return std::tie(u1,\
    \ v1, t1) < std::tie(u2, v2, t2);\n        };\n        std::ranges::sort(edges_,\
    \ comp);\n        std::vector<std::vector<int>> segment(2 * k);\n        const\
    \ auto E = int(edges_.size());\n        for (auto i = 0; i < E; ++i) {\n     \
    \       auto [u, v, l, w] = edges_[i];\n            auto r = k;\n            if\
    \ (i + 1 < E && u == std::get<0>(edges_[i + 1]) && v == std::get<1>(edges_[i +\
    \ 1])) {\n                r = std::get<2>(edges_[++i]);\n            }\n     \
    \       l += k;\n            r += k;\n            while (l < r) {\n          \
    \      if (l & 1) {\n                    segment[l++].emplace_back(i);\n     \
    \           }\n                if (r & 1) {\n                    segment[--r].emplace_back(i);\n\
    \                }\n                l >>= 1;\n                r >>= 1;\n     \
    \       }\n        }\n        PotentializedRollbackDSU<A> dsu(n_);\n        auto\
    \ dfs = [&](auto self, int node) -> void {\n            auto count = 0;\n    \
    \        for (auto i : segment[node]) {\n                auto &&[u, v, _, w] =\
    \ edges_[i];\n                count += dsu.merge(u, v, w);\n            }\n  \
    \          if (node < k) {\n                self(self, 2 * node);\n          \
    \      self(self, 2 * node + 1);\n            } else {\n                f(dsu,\
    \ node - k);\n            }\n            dsu.rollback(count);\n        };\n  \
    \      dfs(dfs, 1);\n    }\n\nprivate:\n    int n_, timer_;\n    std::vector<std::tuple<int,\
    \ int, int, A>> edges_;\n};\n\n\n#line 1 \"monoids/xor.hpp\"\n\n\n\n// Xor Abelian\
    \ Group\ntemplate <typename T> struct Xor {\n    T val;\n    static Xor op(Xor\
    \ a, Xor b) { return {a.val ^ b.val}; }\n    static Xor e() { return {0}; }\n\
    \    static Xor inv(Xor x) { return x; }\n    friend bool operator==(const Xor\
    \ &a, const Xor &b) { return a.val == b.val; }\n};\n\n\n#line 5 \"test/graph/odd_trip_plans.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, M, Q;\n    std::cin >> N >> M >> Q;\n    using A = Xor<int>;\n   \
    \ PotentializedOfflineDynamicConnectivity<A> dc(N);\n    for (auto i = 0; i <\
    \ M; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        --u, --v;\n\
    \        dc.toggle_edge(u, v, A{1});\n    }\n    std::vector<std::pair<int, int>>\
    \ query;\n    for (auto i = 0; i < Q; ++i) {\n        int t, u, v;\n        std::cin\
    \ >> t >> u >> v;\n        --u, --v;\n        if (t == 1) {\n            dc.toggle_edge(u,\
    \ v, A{1});\n        } else {\n            dc.snapshot();\n            query.emplace_back(u,\
    \ v);\n        }\n    }\n    std::vector<char> ans(query.size());\n    dc.solve([&](const\
    \ auto &dsu, int i) {\n        auto [u, v] = query[i];\n        auto is_bipartite\
    \ = dsu.is_valid();\n        auto ok = dsu.size(0) == N && (!is_bipartite || dsu.diff(u,\
    \ v) == A{(N ^ 1) & 1});\n        ans[i] = ok;\n    });\n    for (auto ok : ans)\
    \ {\n        std::cout << (ok ? \"Yes\" : \"No\") << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/3622\"\
    \n\n#include \"graph/potentialized_offline_dynamic_connectivity.hpp\"\n#include\
    \ \"monoids/xor.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, M, Q;\n    std::cin >> N >> M >> Q;\n    using A = Xor<int>;\n   \
    \ PotentializedOfflineDynamicConnectivity<A> dc(N);\n    for (auto i = 0; i <\
    \ M; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n        --u, --v;\n\
    \        dc.toggle_edge(u, v, A{1});\n    }\n    std::vector<std::pair<int, int>>\
    \ query;\n    for (auto i = 0; i < Q; ++i) {\n        int t, u, v;\n        std::cin\
    \ >> t >> u >> v;\n        --u, --v;\n        if (t == 1) {\n            dc.toggle_edge(u,\
    \ v, A{1});\n        } else {\n            dc.snapshot();\n            query.emplace_back(u,\
    \ v);\n        }\n    }\n    std::vector<char> ans(query.size());\n    dc.solve([&](const\
    \ auto &dsu, int i) {\n        auto [u, v] = query[i];\n        auto is_bipartite\
    \ = dsu.is_valid();\n        auto ok = dsu.size(0) == N && (!is_bipartite || dsu.diff(u,\
    \ v) == A{(N ^ 1) & 1});\n        ans[i] = ok;\n    });\n    for (auto ok : ans)\
    \ {\n        std::cout << (ok ? \"Yes\" : \"No\") << \"\\n\";\n    }\n}\n"
  dependsOn:
  - graph/potentialized_offline_dynamic_connectivity.hpp
  - data_structures/potentialized_rollback_dsu.hpp
  - monoids/xor.hpp
  isVerificationFile: true
  path: test/graph/odd_trip_plans.test.cpp
  requiredBy: []
  timestamp: '2026-02-03 20:57:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/odd_trip_plans.test.cpp
layout: document
redirect_from:
- /verify/test/graph/odd_trip_plans.test.cpp
- /verify/test/graph/odd_trip_plans.test.cpp.html
title: test/graph/odd_trip_plans.test.cpp
---
