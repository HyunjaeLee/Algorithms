---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: link_cut_tree/link_cut_tree.hpp
    title: link_cut_tree/link_cut_tree.hpp
  - icon: ':heavy_check_mark:'
    path: monoids/affine_monoid.hpp
    title: monoids/affine_monoid.hpp
  - icon: ':heavy_check_mark:'
    path: monoids/reversible_monoid.hpp
    title: monoids/reversible_monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
  bundledCode: "#line 1 \"test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n\n#line 1 \"link_cut_tree/link_cut_tree.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\ntemplate <typename S,\
    \ auto op, auto e, auto toggle> struct link_cut_tree {\n    link_cut_tree(int\
    \ n)\n        : n_(n), left_(n, -1), right_(n, -1), parent_(n, -1), data_(n, e()),\
    \ sum_(n, e()),\n          reversed_(n, false) {}\n    int access(int u) {\n \
    \       assert(0 <= u && u < n_);\n        auto result = -1;\n        for (auto\
    \ cur = u; ~cur; cur = parent_[cur]) {\n            splay(cur);\n            right_[cur]\
    \ = result;\n            update(cur);\n            result = cur;\n        }\n\
    \        splay(u);\n        return result;\n    }\n    void make_root(int u) {\n\
    \        assert(0 <= u && u < n_);\n        access(u);\n        reverse(u);\n\
    \        push(u);\n    }\n    void link(int u, int p) {\n        assert(0 <= u\
    \ && u < n_ && 0 <= p && p < n_);\n        make_root(u);\n        access(p);\n\
    \        parent_[u] = p;\n        right_[p] = u;\n        update(p);\n    }\n\
    \    void cut(int u) {\n        assert(0 <= u && u < n_);\n        access(u);\n\
    \        auto p = left_[u];\n        left_[u] = -1;\n        update(u);\n    \
    \    parent_[p] = -1;\n    }\n    void cut(int u, int v) {\n        assert(0 <=\
    \ u && u < n_ && 0 <= v && v < n_);\n        make_root(u);\n        cut(v);\n\
    \    }\n    int lca(int u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v\
    \ && v < n_);\n        access(u);\n        return access(v);\n    }\n    void\
    \ set(int u, S x) {\n        assert(0 <= u && u < n_);\n        access(u);\n \
    \       data_[u] = x;\n        update(u);\n    }\n    S get(int u) {\n       \
    \ assert(0 <= u && u < n_);\n        access(u);\n        return data_[u];\n  \
    \  }\n    S prod(int u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v &&\
    \ v < n_);\n        make_root(u);\n        access(v);\n        return sum_[v];\n\
    \    }\n    bool connected(int u, int v) {\n        assert(0 <= u && u < n_ &&\
    \ 0 <= v && v < n_);\n        access(u);\n        access(v);\n        return u\
    \ == v || ~parent_[u];\n    }\n\nprivate:\n    bool is_root(int u) const {\n \
    \       auto p = parent_[u];\n        return !~p || (left_[p] != u && right_[p]\
    \ != u);\n    }\n    void update(int u) {\n        if (~u) {\n            sum_[u]\
    \ = data_[u];\n            if (auto v = left_[u]; ~v) {\n                sum_[u]\
    \ = op(sum_[v], sum_[u]);\n            }\n            if (auto v = right_[u];\
    \ ~v) {\n                sum_[u] = op(sum_[u], sum_[v]);\n            }\n    \
    \    }\n    }\n    void reverse(int u) {\n        if (~u) {\n            std::swap(left_[u],\
    \ right_[u]);\n            reversed_[u] = !reversed_[u];\n            sum_[u]\
    \ = toggle(sum_[u]);\n        }\n    }\n    void push(int u) {\n        if (~u)\
    \ {\n            if (reversed_[u]) {\n                reverse(left_[u]);\n   \
    \             reverse(right_[u]);\n                reversed_[u] = false;\n   \
    \         }\n        }\n    }\n    void rotate_right(int u) {\n        auto p\
    \ = parent_[u];\n        auto g = parent_[p];\n        if (left_[p] = right_[u];\
    \ ~left_[p]) {\n            parent_[right_[u]] = p;\n        }\n        right_[u]\
    \ = p;\n        parent_[p] = u;\n        update(p);\n        update(u);\n    \
    \    if (parent_[u] = g; ~parent_[u]) {\n            if (left_[g] == p) {\n  \
    \              left_[g] = u;\n            }\n            if (right_[g] == p) {\n\
    \                right_[g] = u;\n            }\n            update(g);\n     \
    \   }\n    }\n    void rotate_left(int u) {\n        auto p = parent_[u];\n  \
    \      auto g = parent_[p];\n        if (right_[p] = left_[u]; ~right_[p]) {\n\
    \            parent_[left_[u]] = p;\n        }\n        left_[u] = p;\n      \
    \  parent_[p] = u;\n        update(p);\n        update(u);\n        if (parent_[u]\
    \ = g; ~parent_[u]) {\n            if (left_[g] == p) {\n                left_[g]\
    \ = u;\n            }\n            if (right_[g] == p) {\n                right_[g]\
    \ = u;\n            }\n            update(g);\n        }\n    }\n    void splay(int\
    \ u) {\n        push(u);\n        while (!is_root(u)) {\n            auto p =\
    \ parent_[u];\n            if (is_root(p)) {\n                push(p);\n     \
    \           push(u);\n                if (left_[p] == u) {\n                 \
    \   rotate_right(u);\n                } else {\n                    rotate_left(u);\n\
    \                }\n            } else {\n                auto g = parent_[p];\n\
    \                push(g);\n                push(p);\n                push(u);\n\
    \                if (left_[g] == p) {\n                    if (left_[p] == u)\
    \ {\n                        rotate_right(p);\n                        rotate_right(u);\n\
    \                    } else {\n                        rotate_left(u);\n     \
    \                   rotate_right(u);\n                    }\n                }\
    \ else {\n                    if (right_[p] == u) {\n                        rotate_left(p);\n\
    \                        rotate_left(u);\n                    } else {\n     \
    \                   rotate_right(u);\n                        rotate_left(u);\n\
    \                    }\n                }\n            }\n        }\n    }\n \
    \   int n_;\n    std::vector<int> left_, right_, parent_;\n    std::vector<S>\
    \ data_, sum_;\n    std::vector<char> reversed_;\n};\n\n\n#line 1 \"monoids/affine_monoid.hpp\"\
    \n\n\n\ntemplate <typename Z> struct AffineMonoid {\n    static AffineMonoid op(AffineMonoid\
    \ f, AffineMonoid g) {\n        auto [a, b] = f;\n        auto [c, d] = g;\n \
    \       return {a * c, b * c + d};\n    }\n    static AffineMonoid e() { return\
    \ {1, 0}; }\n    Z a, b;\n};\n\n\n#line 1 \"monoids/reversible_monoid.hpp\"\n\n\
    \n\ntemplate <typename M> struct ReversibleMonoid {\n    ReversibleMonoid(M x)\
    \ : val(x), rev(x) {}\n    ReversibleMonoid(M x, M y) : val(x), rev(y) {}\n  \
    \  static ReversibleMonoid op(ReversibleMonoid l, ReversibleMonoid r) {\n    \
    \    return {M::op(l.val, r.val), M::op(r.rev, l.rev)};\n    }\n    static ReversibleMonoid\
    \ e() { return {M::e(), M::e()}; }\n    static ReversibleMonoid toggle(ReversibleMonoid\
    \ x) { return {x.rev, x.val}; }\n    M val, rev;\n};\n\n\n#line 6 \"test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp\"\
    \n#include <atcoder/modint>\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    using mint = atcoder::modint998244353;\n\
    \    using M = AffineMonoid<mint>;\n    using S = ReversibleMonoid<M>;\n    link_cut_tree<S,\
    \ S::op, S::e, S::toggle> lct(N);\n    for (auto i = 0; i < N; ++i) {\n      \
    \  int a, b;\n        std::cin >> a >> b;\n        lct.set(i, M{a, b});\n    }\n\
    \    for (auto i = 0; i < N - 1; ++i) {\n        int u, v;\n        std::cin >>\
    \ u >> v;\n        lct.link(u, v);\n    }\n    while (Q--) {\n        int t;\n\
    \        std::cin >> t;\n        if (t == 0) {\n            int u, v, w, x;\n\
    \            std::cin >> u >> v >> w >> x;\n            lct.cut(u, v);\n     \
    \       lct.link(w, x);\n        } else if (t == 1) {\n            int p, c, d;\n\
    \            std::cin >> p >> c >> d;\n            lct.set(p, M{c, d});\n    \
    \    } else {\n            int u, v, x;\n            std::cin >> u >> v >> x;\n\
    \            auto [a, b] = lct.prod(u, v).val;\n            auto ans = a * x +\
    \ b;\n            std::cout << ans.val() << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite\"\
    \n\n#include \"link_cut_tree/link_cut_tree.hpp\"\n#include \"monoids/affine_monoid.hpp\"\
    \n#include \"monoids/reversible_monoid.hpp\"\n#include <atcoder/modint>\n#include\
    \ <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    using mint = atcoder::modint998244353;\n\
    \    using M = AffineMonoid<mint>;\n    using S = ReversibleMonoid<M>;\n    link_cut_tree<S,\
    \ S::op, S::e, S::toggle> lct(N);\n    for (auto i = 0; i < N; ++i) {\n      \
    \  int a, b;\n        std::cin >> a >> b;\n        lct.set(i, M{a, b});\n    }\n\
    \    for (auto i = 0; i < N - 1; ++i) {\n        int u, v;\n        std::cin >>\
    \ u >> v;\n        lct.link(u, v);\n    }\n    while (Q--) {\n        int t;\n\
    \        std::cin >> t;\n        if (t == 0) {\n            int u, v, w, x;\n\
    \            std::cin >> u >> v >> w >> x;\n            lct.cut(u, v);\n     \
    \       lct.link(w, x);\n        } else if (t == 1) {\n            int p, c, d;\n\
    \            std::cin >> p >> c >> d;\n            lct.set(p, M{c, d});\n    \
    \    } else {\n            int u, v, x;\n            std::cin >> u >> v >> x;\n\
    \            auto [a, b] = lct.prod(u, v).val;\n            auto ans = a * x +\
    \ b;\n            std::cout << ans.val() << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - link_cut_tree/link_cut_tree.hpp
  - monoids/affine_monoid.hpp
  - monoids/reversible_monoid.hpp
  isVerificationFile: true
  path: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2026-01-04 02:17:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
- /verify/test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp.html
title: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
---
