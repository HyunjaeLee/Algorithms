---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structures/potentialized_rollback_dsu.hpp
    title: data_structures/potentialized_rollback_dsu.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2971
    links:
    - https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2971
  bundledCode: "#line 1 \"test/data_structures/consistent_trading.test.cpp\"\n#define\
    \ PROBLEM \"https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2971\"\
    \n\n#line 1 \"data_structures/potentialized_rollback_dsu.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <tuple>\n#include <vector>\n\n// A\
    \ is an abelian group\ntemplate <typename A> struct PotentializedRollbackDSU {\n\
    \    explicit PotentializedRollbackDSU(int n)\n        : n_(n), valid_(true),\
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
    };\n\n\n#line 4 \"test/data_structures/consistent_trading.test.cpp\"\n#include\
    \ <bits/stdc++.h>\n\nusing i64 = long long;\nusing i128 = __int128;\n\nstruct\
    \ A {\n    static A op(A a, A b) { return {modmul(a.val, b.val)}; }\n    static\
    \ A e() { return {1}; }\n    static A inv(A x) { return {modpow(x.val, mod - 2)};\
    \ }\n    static i64 modmul(i64 a, i64 b) { return i64(i128(a) * b % mod); }\n\
    \    static i64 modpow(i64 x, i64 n) {\n        i64 r = 1;\n        while (n)\
    \ {\n            if (n & 1) {\n                r = modmul(r, x);\n           \
    \ }\n            x = modmul(x, x);\n            n >>= 1;\n        }\n        return\
    \ r;\n    }\n    bool operator==(const A &other) const { return val == other.val;\
    \ }\n    i64 val;\n    inline static i64 mod = (1LL << 61) - 1;\n};\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, M;\n    std::cin >>\
    \ N >> M;\n    PotentializedRollbackDSU<A> dsu(N);\n    for (auto i = 0; i < M;\
    \ ++i) {\n        int v, u, x;\n        std::cin >> v >> u >> x;\n        --u,\
    \ --v;\n        dsu.merge(u, v, A{x});\n    }\n    auto ans = dsu.is_valid() ?\
    \ \"Yes\" : \"No\";\n    std::cout << ans << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2971\"\
    \n\n#include \"data_structures/potentialized_rollback_dsu.hpp\"\n#include <bits/stdc++.h>\n\
    \nusing i64 = long long;\nusing i128 = __int128;\n\nstruct A {\n    static A op(A\
    \ a, A b) { return {modmul(a.val, b.val)}; }\n    static A e() { return {1}; }\n\
    \    static A inv(A x) { return {modpow(x.val, mod - 2)}; }\n    static i64 modmul(i64\
    \ a, i64 b) { return i64(i128(a) * b % mod); }\n    static i64 modpow(i64 x, i64\
    \ n) {\n        i64 r = 1;\n        while (n) {\n            if (n & 1) {\n  \
    \              r = modmul(r, x);\n            }\n            x = modmul(x, x);\n\
    \            n >>= 1;\n        }\n        return r;\n    }\n    bool operator==(const\
    \ A &other) const { return val == other.val; }\n    i64 val;\n    inline static\
    \ i64 mod = (1LL << 61) - 1;\n};\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, M;\n    std::cin >> N >> M;\n    PotentializedRollbackDSU<A> dsu(N);\n\
    \    for (auto i = 0; i < M; ++i) {\n        int v, u, x;\n        std::cin >>\
    \ v >> u >> x;\n        --u, --v;\n        dsu.merge(u, v, A{x});\n    }\n   \
    \ auto ans = dsu.is_valid() ? \"Yes\" : \"No\";\n    std::cout << ans << \"\\\
    n\";\n}\n"
  dependsOn:
  - data_structures/potentialized_rollback_dsu.hpp
  isVerificationFile: true
  path: test/data_structures/consistent_trading.test.cpp
  requiredBy: []
  timestamp: '2026-02-06 17:15:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structures/consistent_trading.test.cpp
layout: document
redirect_from:
- /verify/test/data_structures/consistent_trading.test.cpp
- /verify/test/data_structures/consistent_trading.test.cpp.html
title: test/data_structures/consistent_trading.test.cpp
---
