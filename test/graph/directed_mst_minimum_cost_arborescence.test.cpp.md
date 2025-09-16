---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: disjoint_set/rollback_disjoint_set.hpp
    title: disjoint_set/rollback_disjoint_set.hpp
  - icon: ':heavy_check_mark:'
    path: graph/directed_mst.hpp
    title: graph/directed_mst.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B
  bundledCode: "#line 1 \"test/graph/directed_mst_minimum_cost_arborescence.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B\"\
    \n\n#line 1 \"graph/directed_mst.hpp\"\n\n\n\n#line 1 \"disjoint_set/rollback_disjoint_set.hpp\"\
    \n\n\n\n#include <cassert>\n#include <stack>\n#include <utility>\n#include <vector>\n\
    \nstruct rollback_disjoint_set {\n    explicit rollback_disjoint_set(int n) :\
    \ n_(n), parent_or_size_(n, -1) {}\n    int find(int u) const {\n        return\
    \ parent_or_size_[u] < 0 ? u : find(parent_or_size_[u]);\n    }\n    bool merge(int\
    \ u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n       \
    \ u = find(u);\n        v = find(v);\n        if (u == v) {\n            return\
    \ false;\n        }\n        if (-parent_or_size_[u] < -parent_or_size_[v]) {\n\
    \            std::swap(u, v);\n        }\n        history_.emplace(v, parent_or_size_[v]);\n\
    \        parent_or_size_[u] += parent_or_size_[v];\n        parent_or_size_[v]\
    \ = u;\n        return true;\n    }\n    bool same(int u, int v) const {\n   \
    \     assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        return find(u) ==\
    \ find(v);\n    }\n    int size(int u) const {\n        assert(0 <= u && u < n_);\n\
    \        return -parent_or_size_[find(u)];\n    }\n    void rollback() {\n   \
    \     assert(!history_.empty());\n        auto [v, val] = history_.top();\n  \
    \      auto u = parent_or_size_[v];\n        parent_or_size_[v] = val;\n     \
    \   parent_or_size_[u] -= val;\n        history_.pop();\n    }\n    void rollback(int\
    \ count) {\n        for (auto i = 0; i < count; ++i) {\n            rollback();\n\
    \        }\n    }\n\nprivate:\n    int n_;\n    std::vector<int> parent_or_size_;\n\
    \    std::stack<std::pair<int, int>> history_;\n};\n\n\n#line 8 \"graph/directed_mst.hpp\"\
    \n\ntemplate <typename Cost> struct directed_mst {\n    explicit directed_mst(int\
    \ n) : n_(n), heap_(n_, -1) {}\n\n    void add_edge(int from, int to, Cost cost)\
    \ {\n        assert(0 <= from && from < n_ && 0 <= to && to < n_);\n        auto\
    \ id = static_cast<int>(from_.size());\n        from_.push_back(from);\n     \
    \   to_.push_back(to);\n        cost_.push_back(cost);\n        left_.push_back(-1);\n\
    \        right_.push_back(-1);\n        lazy_.push_back(Cost{});\n        heap_[to]\
    \ = merge(heap_[to], id);\n    }\n\n    std::pair<Cost, std::vector<int>> run(int\
    \ root) {\n        rollback_disjoint_set dsu(n_);\n        Cost result{};\n  \
    \      std::vector<int> seen(n_, -1), path(n_), queue(n_), in(n_, -1);\n     \
    \   seen[root] = root;\n        std::vector<std::pair<int, std::vector<int>>>\
    \ cycles;\n        for (auto s = 0; s < n_; ++s) {\n            auto u = s, pos\
    \ = 0, w = -1;\n            while (!~seen[u]) {\n                if (!~heap_[u])\
    \ {\n                    return {-1, {}};\n                }\n               \
    \ push(heap_[u]);\n                auto e = heap_[u];\n                result\
    \ += cost_[e];\n                lazy_[heap_[u]] -= cost_[e];\n               \
    \ heap_[u] = pop(heap_[u]);\n                queue[pos] = e;\n               \
    \ path[pos++] = u;\n                seen[u] = s;\n                u = dsu.find(from_[e]);\n\
    \                if (seen[u] == s) {\n                    auto cycle = -1;\n \
    \                   auto end = pos;\n                    do {\n              \
    \          w = path[--pos];\n                        cycle = merge(cycle, heap_[w]);\n\
    \                    } while (dsu.merge(u, w));\n                    u = dsu.find(u);\n\
    \                    heap_[u] = cycle;\n                    seen[u] = -1;\n  \
    \                  cycles.emplace_back(u,\n                                  \
    \      std::vector<int>(queue.begin() + pos,\n                               \
    \                          queue.begin() + end));\n                }\n       \
    \     }\n            for (auto i = 0; i < pos; ++i) {\n                in[dsu.find(to_[queue[i]])]\
    \ = queue[i];\n            }\n        }\n        for (auto it = cycles.rbegin();\
    \ it != cycles.rend(); ++it) {\n            auto &[u, comp] = *it;\n         \
    \   auto count = static_cast<int>(comp.size()) - 1;\n            dsu.rollback(count);\n\
    \            auto in_edge = in[u];\n            for (auto e : comp) {\n      \
    \          in[dsu.find(to_[e])] = e;\n            }\n            in[dsu.find(to_[in_edge])]\
    \ = in_edge;\n        }\n        std::vector<int> parent;\n        parent.reserve(n_);\n\
    \        for (auto i : in) {\n            parent.push_back(~i ? from_[i] : -1);\n\
    \        }\n        return {result, parent};\n    }\n\nprivate:\n    void push(int\
    \ u) {\n        cost_[u] += lazy_[u];\n        if (auto l = left_[u]; ~l) {\n\
    \            lazy_[l] += lazy_[u];\n        }\n        if (auto r = right_[u];\
    \ ~r) {\n            lazy_[r] += lazy_[u];\n        }\n        lazy_[u] = 0;\n\
    \    }\n    int merge(int u, int v) {\n        if (!~u || !~v) {\n           \
    \ return ~u ? u : v;\n        }\n        push(u);\n        push(v);\n        if\
    \ (cost_[u] > cost_[v]) {\n            std::swap(u, v);\n        }\n        right_[u]\
    \ = merge(v, right_[u]);\n        std::swap(left_[u], right_[u]);\n        return\
    \ u;\n    }\n    int pop(int u) {\n        push(u);\n        return merge(left_[u],\
    \ right_[u]);\n    }\n    const int n_;\n    std::vector<int> from_, to_, left_,\
    \ right_, heap_;\n    std::vector<Cost> cost_, lazy_;\n};\n\n\n#line 4 \"test/graph/directed_mst_minimum_cost_arborescence.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int V, E, r;\n    std::cin >> V >> E >> r;\n    directed_mst<int> dmst(V);\n\
    \    for (auto i = 0; i < E; ++i) {\n        int s, t, w;\n        std::cin >>\
    \ s >> t >> w;\n        dmst.add_edge(s, t, w);\n    }\n    auto [ans, p] = dmst.run(r);\n\
    \    std::cout << ans << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B\"\
    \n\n#include \"graph/directed_mst.hpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int V, E, r;\n    std::cin\
    \ >> V >> E >> r;\n    directed_mst<int> dmst(V);\n    for (auto i = 0; i < E;\
    \ ++i) {\n        int s, t, w;\n        std::cin >> s >> t >> w;\n        dmst.add_edge(s,\
    \ t, w);\n    }\n    auto [ans, p] = dmst.run(r);\n    std::cout << ans << '\\\
    n';\n}\n"
  dependsOn:
  - graph/directed_mst.hpp
  - disjoint_set/rollback_disjoint_set.hpp
  isVerificationFile: true
  path: test/graph/directed_mst_minimum_cost_arborescence.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/directed_mst_minimum_cost_arborescence.test.cpp
layout: document
redirect_from:
- /verify/test/graph/directed_mst_minimum_cost_arborescence.test.cpp
- /verify/test/graph/directed_mst_minimum_cost_arborescence.test.cpp.html
title: test/graph/directed_mst_minimum_cost_arborescence.test.cpp
---
