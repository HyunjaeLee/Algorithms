---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/potentialized_offline_dynamic_connectivity.hpp
    title: graph/potentialized_offline_dynamic_connectivity.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structures/consistent_trading.test.cpp
    title: test/data_structures/consistent_trading.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/jag_regional_2022_i.test.cpp
    title: test/graph/jag_regional_2022_i.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/graph/odd_trip_plans.test.cpp
    title: test/graph/odd_trip_plans.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structures/potentialized_rollback_dsu.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <vector>\n\
    \n// A is an abelian group\ntemplate <typename A> struct PotentializedRollbackDSU\
    \ {\n    explicit PotentializedRollbackDSU(int n)\n        : n_(n), valid_(true),\
    \ parent_or_size_(n, -1), potential_(n, A::e()) {}\n    int leader(int u) const\
    \ { return parent_or_size_[u] < 0 ? u : leader(parent_or_size_[u]); }\n    //\
    \ returns p_u\n    A potential(int u) const {\n        return parent_or_size_[u]\
    \ < 0 ? A::e()\n                                      : A::op(potential_[u], potential(parent_or_size_[u]));\n\
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
    };\n\n\n"
  code: "#ifndef POTENTIALIZED_ROLLBACK_DSU\n#define POTENTIALIZED_ROLLBACK_DSU\n\n\
    #include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <vector>\n\
    \n// A is an abelian group\ntemplate <typename A> struct PotentializedRollbackDSU\
    \ {\n    explicit PotentializedRollbackDSU(int n)\n        : n_(n), valid_(true),\
    \ parent_or_size_(n, -1), potential_(n, A::e()) {}\n    int leader(int u) const\
    \ { return parent_or_size_[u] < 0 ? u : leader(parent_or_size_[u]); }\n    //\
    \ returns p_u\n    A potential(int u) const {\n        return parent_or_size_[u]\
    \ < 0 ? A::e()\n                                      : A::op(potential_[u], potential(parent_or_size_[u]));\n\
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
    };\n\n#endif // POTENTIALIZED_ROLLBACK_DSU"
  dependsOn: []
  isVerificationFile: false
  path: data_structures/potentialized_rollback_dsu.hpp
  requiredBy:
  - graph/potentialized_offline_dynamic_connectivity.hpp
  timestamp: '2026-02-03 20:57:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/graph/odd_trip_plans.test.cpp
  - test/graph/jag_regional_2022_i.test.cpp
  - test/data_structures/consistent_trading.test.cpp
documentation_of: data_structures/potentialized_rollback_dsu.hpp
layout: document
redirect_from:
- /library/data_structures/potentialized_rollback_dsu.hpp
- /library/data_structures/potentialized_rollback_dsu.hpp.html
title: data_structures/potentialized_rollback_dsu.hpp
---
