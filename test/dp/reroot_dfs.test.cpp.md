---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: dp/reroot_dfs.hpp
    title: dp/reroot_dfs.hpp
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
  bundledCode: "#line 1 \"test/dp/reroot_dfs.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n\n#line 1 \"dp/reroot_dfs.hpp\"\n\n\n\n#include <vector>\n\n/*\n    vector<vector<pair<int,\
    \ EdgeWeight>>> g;\n    struct Subtree {};\n    struct Children {};\n    auto\
    \ rake = [&](Children l, Children r) -> Children {};\n    auto add_edge = [&](Subtree\
    \ d, EdgeWeight w) -> Children {};\n    auto add_vertex = [&](Children d, int\
    \ i) -> Subtree {};\n    auto e = []() -> Children {};\n*/\n\nauto reroot_dfs(const\
    \ auto &g, auto rake, auto add_edge, auto add_vertex, auto e) {\n    using Children\
    \ = decltype(e());\n    using Subtree = decltype(add_vertex(e(), 0));\n    std::vector<Subtree>\
    \ dp(g.size());\n    auto dfs0 = [&](auto &&self, int u, int p) -> Subtree {\n\
    \        Children sum = e();\n        for (auto [v, w] : g[u]) {\n           \
    \ if (v != p) {\n                sum = rake(sum, add_edge(self(self, v, u), w));\n\
    \            }\n        }\n        return dp[u] = add_vertex(sum, u);\n    };\n\
    \    auto dfs1 = [&](auto &&self, int u, int p) -> void {\n        std::vector<Children>\
    \ pref{e()};\n        for (auto [v, w] : g[u]) {\n            pref.push_back(rake(pref.back(),\
    \ add_edge(dp[v], w)));\n        }\n        Children suff = e();\n        for\
    \ (auto i = int(g[u].size()) - 1; 0 <= i; --i) {\n            auto [v, w] = g[u][i];\n\
    \            auto x = add_edge(dp[v], w);\n            if (v != p) {\n       \
    \         dp[u] = add_vertex(rake(pref[i], suff), u);\n                self(self,\
    \ v, u);\n            }\n            suff = rake(x, suff);\n        }\n      \
    \  dp[u] = add_vertex(suff, u);\n    };\n    dfs0(dfs0, 0, 0);\n    dfs1(dfs1,\
    \ 0, 0);\n    return dp;\n}\n\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <iostream>\n#include <limits>\n#include <type_traits>\n\
    #include <utility>\n\ntemplate <std::signed_integral auto mod> struct modint {\n\
    \    using T = decltype(mod);\n    static_assert(0 < mod && mod <= std::numeric_limits<T>::max()\
    \ / 2 + 1);\n    constexpr modint() : v(0) {}\n    constexpr modint(std::integral\
    \ auto x) : v(T((x % mod + mod) % mod)) {}\n    constexpr modint &operator+=(modint\
    \ o) {\n        v = (v + o.v) % mod;\n        return *this;\n    }\n    constexpr\
    \ modint &operator-=(modint o) {\n        v = (v - o.v + mod) % mod;\n       \
    \ return *this;\n    }\n    constexpr modint &operator*=(modint o) {\n       \
    \ static_assert(sizeof(T) <= sizeof(long long));\n        using U = std::conditional_t<sizeof(T)\
    \ <= sizeof(int), long long, __int128>;\n        v = T(U(v) * o.v % mod);\n  \
    \      return *this;\n    }\n    constexpr modint &operator/=(modint o) { return\
    \ *this *= o.inv(); }\n    constexpr modint operator-() const { return -v; }\n\
    \    constexpr modint operator+() const { return *this; }\n    friend constexpr\
    \ modint operator+(modint l, modint r) { return l += r; }\n    friend constexpr\
    \ modint operator-(modint l, modint r) { return l -= r; }\n    friend constexpr\
    \ modint operator*(modint l, modint r) { return l *= r; }\n    friend constexpr\
    \ modint operator/(modint l, modint r) { return l /= r; }\n    friend bool operator==(modint,\
    \ modint) = default;\n    constexpr modint pow(std::integral auto n) const {\n\
    \        assert(0 <= n);\n        modint x = *this, r = 1;\n        for (; n;\
    \ x *= x, n /= 2) {\n            if (n & 1) {\n                r *= x;\n     \
    \       }\n        }\n        return r;\n    }\n    constexpr modint inv() const\
    \ {\n        T a = v, b = mod, s = 1, t = 0;\n        while (b) {\n          \
    \  T q = a / b;\n            std::swap(a -= b * q, b);\n            std::swap(s\
    \ -= t * q, t);\n        }\n        assert(a == 1);\n        return s;\n    }\n\
    \    constexpr T val() const { return v; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, modint a) { return os << a.v; }\n    friend std::istream &operator>>(std::istream\
    \ &is, modint &a) {\n        long long x;\n        is >> x;\n        a = x;\n\
    \        return is;\n    }\n\nprivate:\n    T v;\n};\n\nusing modint998244353\
    \ = modint<998244353>;\nusing modint1000000007 = modint<1000000007>;\n\n\n#line\
    \ 5 \"test/dp/reroot_dfs.test.cpp\"\n#include <bits/stdc++.h>\n\nusing Z = modint998244353;\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N;\n    std::cin\
    \ >> N;\n    using EdgeWeight = std::pair<int, int>;\n    std::vector<std::vector<std::pair<int,\
    \ EdgeWeight>>> g(N);\n    std::vector<int> a(N);\n    for (auto i = 0; i < N;\
    \ ++i) {\n        std::cin >> a[i];\n    }\n    for (auto i = 0; i < N - 1; ++i)\
    \ {\n        int u, v, b, c;\n        std::cin >> u >> v >> b >> c;\n        g[u].push_back({v,\
    \ {b, c}});\n        g[v].push_back({u, {b, c}});\n    }\n    using Subtree =\
    \ std::pair<Z, int>;\n    using Children = std::pair<Z, int>;\n    auto rake =\
    \ [&](Children l, Children r) -> Children {\n        return {l.first + r.first,\
    \ l.second + r.second};\n    };\n    auto add_edge = [&](Subtree d, EdgeWeight\
    \ w) -> Children {\n        return {w.first * d.first + Z::raw(w.second) * d.second,\
    \ d.second};\n    };\n    auto add_vertex = [&](Children d, int i) -> Subtree\
    \ { return {d.first + a[i], d.second + 1}; };\n    auto e = []() -> Children {\
    \ return {0, 0}; };\n    auto dp = reroot_dfs(g, rake, add_edge, add_vertex, e);\n\
    \    for (auto [sum, cnt] : dp) {\n        std::cout << sum.val() << ' ';\n  \
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n\n#include \"dp/reroot_dfs.hpp\"\n#include \"math/modint.hpp\"\n#include <bits/stdc++.h>\n\
    \nusing Z = modint998244353;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    using EdgeWeight = std::pair<int, int>;\n\
    \    std::vector<std::vector<std::pair<int, EdgeWeight>>> g(N);\n    std::vector<int>\
    \ a(N);\n    for (auto i = 0; i < N; ++i) {\n        std::cin >> a[i];\n    }\n\
    \    for (auto i = 0; i < N - 1; ++i) {\n        int u, v, b, c;\n        std::cin\
    \ >> u >> v >> b >> c;\n        g[u].push_back({v, {b, c}});\n        g[v].push_back({u,\
    \ {b, c}});\n    }\n    using Subtree = std::pair<Z, int>;\n    using Children\
    \ = std::pair<Z, int>;\n    auto rake = [&](Children l, Children r) -> Children\
    \ {\n        return {l.first + r.first, l.second + r.second};\n    };\n    auto\
    \ add_edge = [&](Subtree d, EdgeWeight w) -> Children {\n        return {w.first\
    \ * d.first + Z::raw(w.second) * d.second, d.second};\n    };\n    auto add_vertex\
    \ = [&](Children d, int i) -> Subtree { return {d.first + a[i], d.second + 1};\
    \ };\n    auto e = []() -> Children { return {0, 0}; };\n    auto dp = reroot_dfs(g,\
    \ rake, add_edge, add_vertex, e);\n    for (auto [sum, cnt] : dp) {\n        std::cout\
    \ << sum.val() << ' ';\n    }\n}\n"
  dependsOn:
  - dp/reroot_dfs.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: test/dp/reroot_dfs.test.cpp
  requiredBy: []
  timestamp: '2026-11-06 14:29:39+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/dp/reroot_dfs.test.cpp
layout: document
redirect_from:
- /verify/test/dp/reroot_dfs.test.cpp
- /verify/test/dp/reroot_dfs.test.cpp.html
title: test/dp/reroot_dfs.test.cpp
---
