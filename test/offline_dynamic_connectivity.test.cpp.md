---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: disjoint_set/rollback_disjoint_set.hpp
    title: disjoint_set/rollback_disjoint_set.hpp
  - icon: ':heavy_check_mark:'
    path: graph/offline_dynamic_connectivity.hpp
    title: graph/offline_dynamic_connectivity.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235
  bundledCode: "#line 1 \"test/offline_dynamic_connectivity.test.cpp\"\n#include <clocale>\n\
    #define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235\"\
    \n\n#line 1 \"disjoint_set/rollback_disjoint_set.hpp\"\n\n\n\n#include <cassert>\n\
    #include <stack>\n#include <utility>\n#include <vector>\n\nstruct rollback_disjoint_set\
    \ {\n    explicit rollback_disjoint_set(int n) : n_(n), parent_or_size_(n, -1)\
    \ {}\n    int find(int u) const {\n        return parent_or_size_[u] < 0 ? u :\
    \ find(parent_or_size_[u]);\n    }\n    bool merge(int u, int v) {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        u = find(u);\n        v = find(v);\n\
    \        if (u == v) {\n            return false;\n        }\n        if (-parent_or_size_[u]\
    \ < -parent_or_size_[v]) {\n            std::swap(u, v);\n        }\n        history_.emplace(v,\
    \ parent_or_size_[v]);\n        parent_or_size_[u] += parent_or_size_[v];\n  \
    \      parent_or_size_[v] = u;\n        return true;\n    }\n    bool same(int\
    \ u, int v) const {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n \
    \       return find(u) == find(v);\n    }\n    int size(int u) const {\n     \
    \   assert(0 <= u && u < n_);\n        return -parent_or_size_[find(u)];\n   \
    \ }\n    void rollback() {\n        assert(!history_.empty());\n        auto [v,\
    \ val] = history_.top();\n        auto u = parent_or_size_[v];\n        parent_or_size_[v]\
    \ = val;\n        parent_or_size_[u] -= val;\n        history_.pop();\n    }\n\
    \    void rollback(int count) {\n        for (auto i = 0; i < count; ++i) {\n\
    \            rollback();\n        }\n    }\n\nprivate:\n    int n_;\n    std::vector<int>\
    \ parent_or_size_;\n    std::stack<std::pair<int, int>> history_;\n};\n\n\n#line\
    \ 1 \"graph/offline_dynamic_connectivity.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#line 7 \"graph/offline_dynamic_connectivity.hpp\"\n#include <type_traits>\n\
    #line 10 \"graph/offline_dynamic_connectivity.hpp\"\n\ntemplate <typename DisjointSet>\
    \ struct offline_dynamic_connectivity {\n    explicit offline_dynamic_connectivity(int\
    \ n) : n_(n), timer_(0) {}\n    void toggle_edge(int u, int v) {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        if (u > v) {\n            std::swap(u,\
    \ v);\n        }\n        edges_.push_back({u, v, timer_});\n    }\n    int snapshot()\
    \ { return timer_++; }\n    void reserve(int n) { edges_.reserve(n); }\n    template\
    \ <typename Function>\n    std::vector<std::invoke_result_t<Function, DisjointSet,\
    \ int>>\n    solve(Function f) {\n        auto k = timer_;\n        if (k == 0)\
    \ {\n            return {};\n        }\n        std::sort(edges_.begin(), edges_.end());\n\
    \        std::vector<std::vector<std::pair<int, int>>> segment(2 * k);\n     \
    \   auto edges_size = static_cast<int>(edges_.size());\n        for (auto i =\
    \ 0; i < edges_size; ++i) {\n            auto [u, v, l] = edges_[i];\n       \
    \     auto r = k;\n            if (i + 1 < edges_size && u == edges_[i + 1][0]\
    \ &&\n                v == edges_[i + 1][1]) {\n                r = edges_[++i][2];\n\
    \            }\n            l += k;\n            r += k;\n            while (l\
    \ < r) {\n                if (l & 1) {\n                    segment[l++].push_back({u,\
    \ v});\n                }\n                if (r & 1) {\n                    segment[--r].push_back({u,\
    \ v});\n                }\n                l >>= 1;\n                r >>= 1;\n\
    \            }\n        }\n        DisjointSet dsu(n_);\n        std::vector<std::invoke_result_t<Function,\
    \ DisjointSet, int>> result(k);\n        auto dfs = [&](auto self, int node) ->\
    \ void {\n            auto count = 0;\n            for (auto [u, v] : segment[node])\
    \ {\n                if (dsu.merge(u, v)) {\n                    ++count;\n  \
    \              }\n            }\n            if (node < k) {\n               \
    \ self(self, 2 * node);\n                self(self, 2 * node + 1);\n         \
    \   } else {\n                result[node - k] = f(dsu, node - k);\n         \
    \   }\n            dsu.rollback(count);\n        };\n        dfs(dfs, 1);\n  \
    \      return result;\n    }\n\nprivate:\n    int n_, timer_;\n    std::vector<std::array<int,\
    \ 3>> edges_;\n};\n\n\n#line 6 \"test/offline_dynamic_connectivity.test.cpp\"\n\
    #include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int n, k;\n    std::cin >> n >> k;\n    offline_dynamic_connectivity<rollback_disjoint_set>\
    \ dc(n);\n    std::vector<std::pair<int, int>> q;\n    dc.reserve(k);\n    q.reserve(k);\n\
    \    while (k--) {\n        int t, u, v;\n        std::cin >> t >> u >> v;\n \
    \       switch (t) {\n        case 1:\n        case 2:\n            dc.toggle_edge(u,\
    \ v);\n            break;\n        case 3:\n            q.emplace_back(u, v);\n\
    \            dc.snapshot();\n            break;\n        }\n    }\n    auto result\
    \ = dc.solve([&](const auto &dsu, int i) {\n        auto [u, v] = q[i];\n    \
    \    return dsu.same(u, v);\n    });\n    for (auto b : result) {\n        std::cout\
    \ << (b ? \"YES\\n\" : \"NO\\n\");\n    }\n}\n"
  code: "#include <clocale>\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235\"\
    \n\n#include \"../disjoint_set/rollback_disjoint_set.hpp\"\n#include \"../graph/offline_dynamic_connectivity.hpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int n, k;\n    std::cin >> n >> k;\n    offline_dynamic_connectivity<rollback_disjoint_set>\
    \ dc(n);\n    std::vector<std::pair<int, int>> q;\n    dc.reserve(k);\n    q.reserve(k);\n\
    \    while (k--) {\n        int t, u, v;\n        std::cin >> t >> u >> v;\n \
    \       switch (t) {\n        case 1:\n        case 2:\n            dc.toggle_edge(u,\
    \ v);\n            break;\n        case 3:\n            q.emplace_back(u, v);\n\
    \            dc.snapshot();\n            break;\n        }\n    }\n    auto result\
    \ = dc.solve([&](const auto &dsu, int i) {\n        auto [u, v] = q[i];\n    \
    \    return dsu.same(u, v);\n    });\n    for (auto b : result) {\n        std::cout\
    \ << (b ? \"YES\\n\" : \"NO\\n\");\n    }\n}\n"
  dependsOn:
  - disjoint_set/rollback_disjoint_set.hpp
  - graph/offline_dynamic_connectivity.hpp
  isVerificationFile: true
  path: test/offline_dynamic_connectivity.test.cpp
  requiredBy: []
  timestamp: '2022-09-30 17:14:09+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/offline_dynamic_connectivity.test.cpp
layout: document
redirect_from:
- /verify/test/offline_dynamic_connectivity.test.cpp
- /verify/test/offline_dynamic_connectivity.test.cpp.html
title: test/offline_dynamic_connectivity.test.cpp
---
