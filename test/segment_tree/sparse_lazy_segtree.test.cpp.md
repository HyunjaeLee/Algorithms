---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/modint.hpp
    title: math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: segment_tree/sparse_lazy_segtree.hpp
    title: segment_tree/sparse_lazy_segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum_large_array
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum_large_array
  bundledCode: "#line 1 \"test/segment_tree/sparse_lazy_segtree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum_large_array\"\
    \n\n#line 1 \"segment_tree/sparse_lazy_segtree.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <cstdint>\n#include <vector>\n\n// https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/sparse_lazy_segment_tree.hpp\n\
    template <typename IndexType, // type of index\n          typename S,        \
    \ // type of element\n          auto op,            // S op(S a, S b)\n      \
    \    auto e,             // S e()\n          typename F,         // type of operator\
    \ which acts on S\n          auto mapping,       // S mapping(F f, S x, IndexType\
    \ l, IndexType r)\n          auto composition,   // F composition(F f, F g)\n\
    \          auto id,            // F id()\n          auto init = [](IndexType,\n\
    \                         IndexType) { return e(); } // initializes product of\
    \ segment [l, r)\n          >\nstruct sparse_lazy_segtree {\n    using index_type\
    \ = IndexType;\n    using value_type = S;\n    using operator_type = F;\n\nprivate:\n\
    \    using pool_index_type = uint32_t;\n\n    struct Node {\n        pool_index_type\
    \ ch[2]{0, 0};\n        value_type dat;\n        operator_type laz;\n        Node(const\
    \ value_type &dat_) : dat(dat_), laz(id()) {}\n    };\n\n    static inline std::vector<Node>\
    \ pool{Node{e()}};\n\n    static pool_index_type new_node(const value_type &dat)\
    \ {\n        const pool_index_type res = static_cast<pool_index_type>(pool.size());\n\
    \        return pool.emplace_back(dat), res;\n    }\n\npublic:\n    sparse_lazy_segtree()\
    \ : sparse_lazy_segtree(0) {}\n    explicit sparse_lazy_segtree(IndexType n_)\
    \ : n(n_), root(new_node(init(0, n))) {}\n\n    static void reserve(int siz) {\
    \ pool.reserve(siz); }\n\n    value_type get(index_type i) const {\n        assert(0\
    \ <= i and i < n);\n        operator_type f = id();\n        pool_index_type cur\
    \ = root;\n        for (std::array<index_type, 2> lr{0, n}; cur and lr[1] - lr[0]\
    \ > 1;) {\n            index_type m = lr[0] + (lr[1] - lr[0]) / 2;\n         \
    \   bool b = i >= m;\n            f = composition(f, pool[cur].laz);\n       \
    \     cur = pool[cur].ch[b], lr[not b] = m;\n        }\n        return mapping(f,\
    \ cur ? pool[cur].dat : init(i, i + 1), i, i + 1);\n    }\n    template <typename\
    \ Fun> void apply_fun(index_type i, Fun &&fun) {\n        assert(0 <= i and i\
    \ < n);\n        static std::vector<pool_index_type> path;\n        pool_index_type\
    \ cur = root;\n        for (std::array<index_type, 2> lr{0, n}; lr[1] - lr[0]\
    \ > 1;) {\n            path.push_back(cur);\n            index_type m = lr[0]\
    \ + (lr[1] - lr[0]) / 2;\n            bool b = i >= m;\n            push(cur,\
    \ lr[0], lr[1]);\n            cur = pool[cur].ch[b], lr[not b] = m;\n        }\n\
    \        pool[cur].dat = fun(pool[cur].dat);\n        while (path.size())\n  \
    \          update(path.back()), path.pop_back();\n    }\n    void set(index_type\
    \ i, const value_type &val) {\n        apply_fun(i, [&val](const value_type &)\
    \ { return val; });\n    }\n    void apply(index_type i, const operator_type &f)\
    \ {\n        apply_fun(i, [&f, i](const value_type &val) { return mapping(f, val,\
    \ i, i + 1); });\n    }\n\n    value_type operator()(index_type l, index_type\
    \ r) {\n        assert(0 <= l and l <= r and r <= n);\n        if (l == r)\n \
    \           return e();\n        return query(root, l, r, 0, n);\n    }\n    value_type\
    \ prod(index_type l, index_type r) { return (*this)(l, r); }\n    value_type all_prod()\
    \ { return pool[root].dat; }\n\n    void apply(index_type l, index_type r, const\
    \ operator_type &f) {\n        assert(0 <= l and l <= r and r <= n);\n       \
    \ if (l == r)\n            return;\n        apply(root, f, l, r, 0, n);\n    }\n\
    \    void apply_all(const operator_type &f) { apply_all(root, f, 0, n); }\n\n\
    private:\n    index_type n;\n    pool_index_type root;\n\n    pool_index_type\
    \ get_or_create_child(pool_index_type node, int index, index_type tl,\n      \
    \                                  index_type tr) {\n        if (pool[node].ch[index])\n\
    \            return pool[node].ch[index];\n        const pool_index_type ch =\
    \ new_node(init(tl, tr));\n        return pool[node].ch[index] = ch;\n    }\n\n\
    \    void apply_all(pool_index_type node, const operator_type &f, index_type tl,\
    \ index_type tr) {\n        pool[node].dat = mapping(f, pool[node].dat, tl, tr);\n\
    \        pool[node].laz = composition(f, pool[node].laz);\n    }\n    void push(pool_index_type\
    \ node, index_type tl, index_type tr) {\n        const index_type tm = tl + (tr\
    \ - tl) / 2;\n        const operator_type laz = pool[node].laz;\n        apply_all(get_or_create_child(node,\
    \ 0, tl, tm), laz, tl, tm);\n        apply_all(get_or_create_child(node, 1, tm,\
    \ tr), laz, tm, tr);\n        pool[node].laz = id();\n    }\n\n    void update(pool_index_type\
    \ node) {\n        pool_index_type lch = pool[node].ch[0], rch = pool[node].ch[1];\n\
    \        pool[node].dat = op(pool[lch].dat, pool[rch].dat);\n    }\n\n    value_type\
    \ query(pool_index_type node, index_type ql, index_type qr, index_type tl,\n \
    \                    index_type tr) {\n        if (tr <= ql or qr <= tl)\n   \
    \         return e();\n        if (ql <= tl and tr <= qr)\n            return\
    \ pool[node].dat;\n        push(node, tl, tr);\n        const index_type tm =\
    \ tl + (tr - tl) / 2;\n        return op(query(pool[node].ch[0], ql, qr, tl, tm),\
    \ query(pool[node].ch[1], ql, qr, tm, tr));\n    }\n\n    void apply(pool_index_type\
    \ node, const operator_type &f, index_type ql, index_type qr,\n              \
    \ index_type tl, index_type tr) {\n        if (tr <= ql or qr <= tl)\n       \
    \     return;\n        if (ql <= tl and tr <= qr)\n            return apply_all(node,\
    \ f, tl, tr);\n        const index_type tm = tl + (tr - tl) / 2;\n        push(node,\
    \ tl, tr);\n        apply(pool[node].ch[0], f, ql, qr, tl, tm), apply(pool[node].ch[1],\
    \ f, ql, qr, tm, tr);\n        update(node);\n    }\n};\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 5 \"math/modint.hpp\"\n#include <concepts>\n#include <iostream>\n\
    #include <limits>\n#include <type_traits>\n#include <utility>\n\ntemplate <std::signed_integral\
    \ auto mod> struct modint {\n    using T = decltype(mod);\n    static_assert(0\
    \ < mod && mod <= std::numeric_limits<T>::max() / 2 + 1);\n    constexpr modint()\
    \ : v(0) {}\n    constexpr modint(std::integral auto x) : v(T((x % mod + mod)\
    \ % mod)) {}\n    constexpr modint &operator+=(modint o) {\n        v = (v + o.v)\
    \ % mod;\n        return *this;\n    }\n    constexpr modint &operator-=(modint\
    \ o) {\n        v = (v - o.v + mod) % mod;\n        return *this;\n    }\n   \
    \ constexpr modint &operator*=(modint o) {\n        static_assert(sizeof(T) <=\
    \ sizeof(long long));\n        using U = std::conditional_t<sizeof(T) <= sizeof(int),\
    \ long long, __int128>;\n        v = T(U(v) * o.v % mod);\n        return *this;\n\
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
    \ 5 \"test/segment_tree/sparse_lazy_segtree.test.cpp\"\n#include <bits/stdc++.h>\n\
    \nusing Z = modint998244353;\n\nusing S = Z;\n\nS op(S a, S b) { return a + b;\
    \ }\n\nS e() { return 0; }\n\nusing F = std::pair<Z, Z>;\n\nS mapping(F f, S x,\
    \ int l, int r) {\n    auto [a, b] = f;\n    return a * x + b * (r - l);\n}\n\n\
    F composition(F f, F g) {\n    auto [a, b] = f;\n    auto [c, d] = g;\n    return\
    \ {a * c, a * d + b};\n}\n\nF id() { return {1, 0}; }\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    sparse_lazy_segtree<int, S, op, e,\
    \ F, mapping, composition, id> seg(N);\n    while (Q--) {\n        int t, l, r;\n\
    \        std::cin >> t >> l >> r;\n        if (t == 0) {\n            int b, c;\n\
    \            std::cin >> b >> c;\n            seg.apply(l, r, {b, c});\n     \
    \   } else {\n            auto ans = seg.prod(l, r);\n            std::cout <<\
    \ ans.val() << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum_large_array\"\
    \n\n#include \"segment_tree/sparse_lazy_segtree.hpp\"\n#include \"math/modint.hpp\"\
    \n#include <bits/stdc++.h>\n\nusing Z = modint998244353;\n\nusing S = Z;\n\nS\
    \ op(S a, S b) { return a + b; }\n\nS e() { return 0; }\n\nusing F = std::pair<Z,\
    \ Z>;\n\nS mapping(F f, S x, int l, int r) {\n    auto [a, b] = f;\n    return\
    \ a * x + b * (r - l);\n}\n\nF composition(F f, F g) {\n    auto [a, b] = f;\n\
    \    auto [c, d] = g;\n    return {a * c, a * d + b};\n}\n\nF id() { return {1,\
    \ 0}; }\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N,\
    \ Q;\n    std::cin >> N >> Q;\n    sparse_lazy_segtree<int, S, op, e, F, mapping,\
    \ composition, id> seg(N);\n    while (Q--) {\n        int t, l, r;\n        std::cin\
    \ >> t >> l >> r;\n        if (t == 0) {\n            int b, c;\n            std::cin\
    \ >> b >> c;\n            seg.apply(l, r, {b, c});\n        } else {\n       \
    \     auto ans = seg.prod(l, r);\n            std::cout << ans.val() << \"\\n\"\
    ;\n        }\n    }\n}\n"
  dependsOn:
  - segment_tree/sparse_lazy_segtree.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: test/segment_tree/sparse_lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-11-06 14:29:39+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segment_tree/sparse_lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/test/segment_tree/sparse_lazy_segtree.test.cpp
- /verify/test/segment_tree/sparse_lazy_segtree.test.cpp.html
title: test/segment_tree/sparse_lazy_segtree.test.cpp
---
