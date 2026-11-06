---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: dp/rerooting.hpp
    title: Rerooting
  - icon: ':question:'
    path: math/modint.hpp
    title: math/modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tree_path_composite_sum
    links:
    - https://judge.yosupo.jp/problem/tree_path_composite_sum
  bundledCode: "#line 1 \"test/dp/rerooting.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n\n#line 1 \"dp/rerooting.hpp\"\n\n\n\n#include <ranges>\n#include <vector>\n\
    \n/*\n    vector<vector<pair<int, EdgeWeight>>> g;\n    struct Subtree {};\n \
    \   struct Children {};\n    auto rake = [&](Children l, Children r) -> Children\
    \ {};\n    auto add_edge = [&](Subtree d, EdgeWeight w) -> Children {};\n    auto\
    \ add_vertex = [&](Children d, int i) -> Subtree {};\n    auto e = []() -> Children\
    \ {};\n*/\n\nauto rerooting(const auto &g, auto rake, auto add_edge, auto add_vertex,\
    \ auto e) {\n    auto n = int(g.size());\n    using Children = decltype(e());\n\
    \    using Subtree = decltype(add_vertex(e(), 0));\n    std::vector<Subtree> dp(n),\
    \ dp_parent(n);\n    std::vector<int> bfs_order, parent(n, -1);\n    std::vector<Children>\
    \ pref(n + 1);\n    bfs_order.reserve(n);\n    for (auto root = 0; root < n; ++root)\
    \ {\n        if (~parent[root]) {\n            continue;\n        }\n        parent[root]\
    \ = root;\n        bfs_order.clear();\n        bfs_order.push_back(root);\n  \
    \      auto q = bfs_order.cbegin();\n        while (q != bfs_order.cend()) {\n\
    \            auto u = *q++;\n            for (auto [v, w] : g[u]) {\n        \
    \        if (v != parent[u]) {\n                    parent[v] = u;\n         \
    \           bfs_order.push_back(v);\n                }\n            }\n      \
    \  }\n        for (auto u : bfs_order | std::views::reverse) {\n            Children\
    \ sum = e();\n            for (auto [v, w] : g[u]) {\n                if (v !=\
    \ parent[u]) {\n                    sum = rake(sum, add_edge(dp[v], w));\n   \
    \             }\n            }\n            dp[u] = add_vertex(sum, u);\n    \
    \    }\n        for (auto u : bfs_order) {\n            auto i = 0;\n        \
    \    pref[0] = e();\n            for (auto [v, w] : g[u]) {\n                auto\
    \ state = (v == parent[u]) ? dp_parent[u] : dp[v];\n                pref[i + 1]\
    \ = rake(pref[i], add_edge(state, w));\n                ++i;\n            }\n\
    \            Children suff = e();\n            for (auto [v, w] : g[u] | std::views::reverse)\
    \ {\n                if (v != parent[u]) {\n                    Children except_child\
    \ = rake(pref[i - 1], suff);\n                    dp_parent[v] = add_vertex(except_child,\
    \ u);\n                }\n                auto state = (v == parent[u]) ? dp_parent[u]\
    \ : dp[v];\n                suff = rake(add_edge(state, w), suff);\n         \
    \       --i;\n            }\n            dp[u] = add_vertex(suff, u);\n      \
    \  }\n    }\n    return dp;\n}\n\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <concepts>\n#include <iostream>\n#include <limits>\n#include\
    \ <type_traits>\n#include <utility>\n\ntemplate <std::signed_integral auto mod>\
    \ struct modint {\n    using T = decltype(mod);\n    static_assert(0 < mod &&\
    \ mod <= std::numeric_limits<T>::max() / 2 + 1);\n    constexpr modint() : v(0)\
    \ {}\n    constexpr modint(std::integral auto x) : v(T((x % mod + mod) % mod))\
    \ {}\n    constexpr modint &operator+=(modint o) {\n        v = (v + o.v) % mod;\n\
    \        return *this;\n    }\n    constexpr modint &operator-=(modint o) {\n\
    \        v = (v - o.v + mod) % mod;\n        return *this;\n    }\n    constexpr\
    \ modint &operator*=(modint o) {\n        static_assert(sizeof(T) <= sizeof(long\
    \ long));\n        using U = std::conditional_t<sizeof(T) <= sizeof(int), long\
    \ long, __int128>;\n        v = T(U(v) * o.v % mod);\n        return *this;\n\
    \    }\n    constexpr modint &operator/=(modint o) { return *this *= o.inv();\
    \ }\n    constexpr modint operator-() const { return -v; }\n    constexpr modint\
    \ operator+() const { return *this; }\n    friend constexpr modint operator+(modint\
    \ l, modint r) { return l += r; }\n    friend constexpr modint operator-(modint\
    \ l, modint r) { return l -= r; }\n    friend constexpr modint operator*(modint\
    \ l, modint r) { return l *= r; }\n    friend constexpr modint operator/(modint\
    \ l, modint r) { return l /= r; }\n    friend bool operator==(modint, modint)\
    \ = default;\n    constexpr modint pow(std::integral auto n) const {\n       \
    \ assert(0 <= n);\n        modint x = *this, r = 1;\n        for (; n; x *= x,\
    \ n /= 2) {\n            if (n & 1) {\n                r *= x;\n            }\n\
    \        }\n        return r;\n    }\n    constexpr modint inv() const {\n   \
    \     T a = v, b = mod, s = 1, t = 0;\n        while (b) {\n            T q =\
    \ a / b;\n            std::swap(a -= b * q, b);\n            std::swap(s -= t\
    \ * q, t);\n        }\n        assert(a == 1);\n        return s;\n    }\n   \
    \ constexpr T val() const { return v; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, modint a) { return os << a.v; }\n    friend std::istream &operator>>(std::istream\
    \ &is, modint &a) {\n        long long x;\n        is >> x;\n        a = x;\n\
    \        return is;\n    }\n\nprivate:\n    T v;\n};\n\nusing modint998244353\
    \ = modint<998244353>;\nusing modint1000000007 = modint<1000000007>;\n\n\n#line\
    \ 5 \"test/dp/rerooting.test.cpp\"\n#include <bits/stdc++.h>\n\nusing Z = modint998244353;\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N;\n    std::cin\
    \ >> N;\n    using EdgeWeight = std::pair<int, int>;\n    std::vector<std::vector<std::pair<int,\
    \ EdgeWeight>>> g(N);\n    std::vector<int> a(N);\n    std::copy_n(std::istream_iterator<int>(std::cin),\
    \ N, a.begin());\n    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b,\
    \ c;\n        std::cin >> u >> v >> b >> c;\n        g[u].emplace_back(v, std::pair{b,\
    \ c});\n        g[v].emplace_back(u, std::pair{b, c});\n    }\n    using Subtree\
    \ = std::pair<Z, int>;\n    using Child = std::pair<Z, int>;\n    auto rake =\
    \ [&](Child l, Child r) -> Child { return {l.first + r.first, l.second + r.second};\
    \ };\n    auto add_edge = [&](Subtree d, EdgeWeight w) -> Child {\n        return\
    \ {w.first * d.first + Z::raw(w.second) * d.second, d.second};\n    };\n    auto\
    \ add_vertex = [&](Child d, int i) -> Subtree { return {d.first + a[i], d.second\
    \ + 1}; };\n    auto e = []() -> Child { return {0, 0}; };\n    auto dp = rerooting(g,\
    \ rake, add_edge, add_vertex, e);\n    for (auto [sum, cnt] : dp) {\n        std::cout\
    \ << sum.val() << ' ';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n\n#include \"dp/rerooting.hpp\"\n#include \"math/modint.hpp\"\n#include <bits/stdc++.h>\n\
    \nusing Z = modint998244353;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    using EdgeWeight = std::pair<int, int>;\n\
    \    std::vector<std::vector<std::pair<int, EdgeWeight>>> g(N);\n    std::vector<int>\
    \ a(N);\n    std::copy_n(std::istream_iterator<int>(std::cin), N, a.begin());\n\
    \    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b, c;\n        std::cin\
    \ >> u >> v >> b >> c;\n        g[u].emplace_back(v, std::pair{b, c});\n     \
    \   g[v].emplace_back(u, std::pair{b, c});\n    }\n    using Subtree = std::pair<Z,\
    \ int>;\n    using Child = std::pair<Z, int>;\n    auto rake = [&](Child l, Child\
    \ r) -> Child { return {l.first + r.first, l.second + r.second}; };\n    auto\
    \ add_edge = [&](Subtree d, EdgeWeight w) -> Child {\n        return {w.first\
    \ * d.first + Z::raw(w.second) * d.second, d.second};\n    };\n    auto add_vertex\
    \ = [&](Child d, int i) -> Subtree { return {d.first + a[i], d.second + 1}; };\n\
    \    auto e = []() -> Child { return {0, 0}; };\n    auto dp = rerooting(g, rake,\
    \ add_edge, add_vertex, e);\n    for (auto [sum, cnt] : dp) {\n        std::cout\
    \ << sum.val() << ' ';\n    }\n}\n"
  dependsOn:
  - dp/rerooting.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: test/dp/rerooting.test.cpp
  requiredBy: []
  timestamp: '2026-11-06 14:29:39+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/dp/rerooting.test.cpp
layout: document
redirect_from:
- /verify/test/dp/rerooting.test.cpp
- /verify/test/dp/rerooting.test.cpp.html
title: test/dp/rerooting.test.cpp
---
