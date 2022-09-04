---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segment_tree/segtree_beats.hpp
    title: Segtree Beats
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
  bundledCode: "#line 1 \"test/segtree_beats.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#line 1 \"segment_tree/segtree_beats.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename S, typename Op, typename\
    \ E, typename F, typename Mapping,\n          typename Composition, typename Id>\n\
    struct segtree_beats {\n    segtree_beats(const std::vector<S> &data, Op op, E\
    \ e, Mapping mapping,\n                      Composition composition, Id id)\n\
    \        : op_(op), e_(e), mapping_(mapping), composition_(composition), id_(id),\n\
    \          n_(static_cast<int>(data.size())),\n          log_(std::__lg(std::max(n_\
    \ - 1, 1)) + 1), size_(1 << log_),\n          data_(2 * size_, e_()), lazy_(size_,\
    \ id_()) {\n        for (auto i = 0; i < n_; ++i) {\n            data_[size_ +\
    \ i] = data[i];\n        }\n        for (auto i = size_ - 1; i >= 1; --i) {\n\
    \            update(i);\n        }\n    }\n    void set(int pos, S x) {\n    \
    \    assert(0 <= pos && pos < n_);\n        pos += size_;\n        for (auto i\
    \ = log_; i >= 1; --i) {\n            push(pos >> i);\n        }\n        data_[pos]\
    \ = x;\n        for (auto i = 1; i <= log_; ++i) {\n            update(pos >>\
    \ i);\n        }\n    }\n    S get(int pos) {\n        assert(0 <= pos && pos\
    \ < n_);\n        pos += size_;\n        for (auto i = log_; i >= 1; --i) {\n\
    \            push(pos >> i);\n        }\n        return data_[pos];\n    }\n \
    \   S prod(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n   \
    \     if (l == r)\n            return e_();\n        l += size_;\n        r +=\
    \ size_;\n        for (auto i = log_; i >= 1; --i) {\n            if (((l >> i)\
    \ << i) != l) {\n                push(l >> i);\n            }\n            if\
    \ (((r >> i) << i) != r) {\n                push((r - 1) >> i);\n            }\n\
    \        }\n        S sml = e_(), smr = e_();\n        while (l < r) {\n     \
    \       if (l & 1) {\n                sml = op_(sml, data_[l++]);\n          \
    \  }\n            if (r & 1) {\n                smr = op_(data_[--r], smr);\n\
    \            }\n            l >>= 1;\n            r >>= 1;\n        }\n      \
    \  return op_(sml, smr);\n    }\n    S all_prod() { return data_[1]; }\n    void\
    \ apply(int pos, F f) {\n        assert(0 <= pos && pos < n_);\n        pos +=\
    \ size_;\n        for (auto i = log_; i >= 1; --i) {\n            push(pos >>\
    \ i);\n        }\n        data_[pos] = mapping(f, data_[pos]);\n        for (auto\
    \ i = 1; i <= log_; ++i) {\n            update(pos >> i);\n        }\n    }\n\
    \    void apply(int l, int r, F f) {\n        assert(0 <= l && l <= r && r <=\
    \ n_);\n        if (l == r) {\n            return;\n        }\n        l += size_;\n\
    \        r += size_;\n        for (auto i = log_; i >= 1; --i) {\n           \
    \ if (((l >> i) << i) != l) {\n                push(l >> i);\n            }\n\
    \            if (((r >> i) << i) != r) {\n                push((r - 1) >> i);\n\
    \            }\n        }\n        int l2 = l, r2 = r;\n        while (l < r)\
    \ {\n            if (l & 1) {\n                all_apply(l++, f);\n          \
    \  }\n            if (r & 1) {\n                all_apply(--r, f);\n         \
    \   }\n            l >>= 1;\n            r >>= 1;\n        }\n        l = l2;\n\
    \        r = r2;\n        for (auto i = 1; i <= log_; ++i) {\n            if (((l\
    \ >> i) << i) != l) {\n                update(l >> i);\n            }\n      \
    \      if (((r >> i) << i) != r) {\n                update((r - 1) >> i);\n  \
    \          }\n        }\n    }\n\nprivate:\n    void update(int node) {\n    \
    \    data_[node] = op_(data_[2 * node], data_[2 * node + 1]);\n    }\n    void\
    \ all_apply(int node, F f) {\n        data_[node] = mapping_(f, data_[node]);\n\
    \        if (node < size_) {\n            lazy_[node] = composition_(f, lazy_[node]);\n\
    \            if (data_[node].fail) {\n                push(node);\n          \
    \      update(node);\n            }\n        }\n    }\n    void push(int node)\
    \ {\n        all_apply(2 * node, lazy_[node]);\n        all_apply(2 * node + 1,\
    \ lazy_[node]);\n        lazy_[node] = id_();\n    }\n    Op op_;\n    E e_;\n\
    \    Mapping mapping_;\n    Composition composition_;\n    Id id_;\n    const\
    \ int n_, log_, size_;\n    std::vector<S> data_;\n    std::vector<F> lazy_;\n\
    };\n\ntemplate <typename S, typename Op, typename E, typename Mapping,\n     \
    \     typename Composition, typename Id>\nsegtree_beats(const std::vector<S> &data,\
    \ Op op, E e, Mapping mapping,\n                  Composition composition, Id\
    \ id)\n    -> segtree_beats<S, Op, E, std::invoke_result_t<Id>, Mapping,\n   \
    \                      Composition, Id>;\n\n\n#line 4 \"test/segtree_beats.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nstruct S {\n    long long max, max2, min, min2,\
    \ sum;\n    int max_count, min_count, size;\n    bool fail;\n};\n\nstruct F {\n\
    \    long long upper, lower, sum;\n};\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<S> v(N);\n    constexpr\
    \ auto inf = static_cast<long long>(1e18);\n    for (auto &s : v) {\n        long\
    \ long x;\n        std::cin >> x;\n        s.max = s.min = s.sum = x;\n      \
    \  s.max_count = s.min_count = s.size = 1;\n        s.max2 = -inf;\n        s.min2\
    \ = inf;\n        s.fail = false;\n    }\n    auto op = [](S a, S b) -> S {\n\
    \        S ret{};\n        if (a.max < b.max) {\n            ret.max = b.max;\n\
    \            ret.max2 = std::max(a.max, b.max2);\n            ret.max_count =\
    \ b.max_count;\n        } else if (b.max < a.max) {\n            ret.max = a.max;\n\
    \            ret.max2 = std::max(a.max2, b.max);\n            ret.max_count =\
    \ a.max_count;\n        } else {\n            ret.max = a.max;\n            ret.max2\
    \ = std::max(a.max2, b.max2);\n            ret.max_count = a.max_count + b.max_count;\n\
    \        }\n        if (a.min < b.min) {\n            ret.min = a.min;\n     \
    \       ret.min2 = std::min(a.min2, b.min);\n            ret.min_count = a.min_count;\n\
    \        } else if (b.min < a.min) {\n            ret.min = b.min;\n         \
    \   ret.min2 = std::min(a.min, b.min2);\n            ret.min_count = b.min_count;\n\
    \        } else {\n            ret.min = a.min;\n            ret.min2 = std::min(a.min2,\
    \ b.min2);\n            ret.min_count = a.min_count + b.min_count;\n        }\n\
    \        ret.sum = a.sum + b.sum;\n        ret.size = a.size + b.size;\n     \
    \   return ret;\n    };\n    auto e = []() -> S { return {-inf, -inf, inf, inf,\
    \ 0, 0, 0, 0, false}; };\n    auto mapping = [](F f, S x) -> S {\n        x.max\
    \ += f.sum;\n        x.max2 += f.sum;\n        x.min += f.sum;\n        x.min2\
    \ += f.sum;\n        x.sum += f.sum * x.size;\n        if (x.max <= f.lower) {\n\
    \            return {f.lower, -1,     f.lower, -1,   f.lower * x.size,\n     \
    \               x.size,  x.size, x.size,  false};\n        }\n        if (f.upper\
    \ <= x.min) {\n            return {f.upper, -1,     f.upper, -1,   f.upper * x.size,\n\
    \                    x.size,  x.size, x.size,  false};\n        }\n        if\
    \ (x.max2 < f.upper && f.upper < x.max) {\n            x.sum -= (x.max - f.upper)\
    \ * x.max_count;\n            x.max = f.upper;\n        } else if (f.upper <=\
    \ x.max2) {\n            x.fail = true;\n            return x;\n        }\n  \
    \      if (x.max < x.min) {\n            x.min = x.max;\n        } else if (x.max\
    \ < x.min2) {\n            x.min2 = x.max;\n        }\n        if (x.min < f.lower\
    \ && f.lower < x.min2) {\n            x.sum += (f.lower - x.min) * x.min_count;\n\
    \            x.min = f.lower;\n        } else if (x.min2 <= f.lower) {\n     \
    \       x.fail = true;\n            return x;\n        }\n        if (x.max <\
    \ x.min) {\n            x.max = x.min;\n        } else if (x.max2 < x.min) {\n\
    \            x.max2 = x.min;\n        }\n        return x;\n    };\n    auto composition\
    \ = [](F f, F g) -> F {\n        g.upper += f.sum;\n        g.lower += f.sum;\n\
    \        g.sum += f.sum;\n        g.upper = std::min(f.upper, g.upper);\n    \
    \    if (g.upper < g.lower) {\n            g.lower = g.upper;\n        }\n   \
    \     g.lower = std::max(f.lower, g.lower);\n        if (g.upper < g.lower) {\n\
    \            g.upper = g.lower;\n        }\n        return g;\n    };\n    auto\
    \ id = []() -> F { return {inf, -inf, 0}; };\n    segtree_beats seg(v, op, e,\
    \ mapping, composition, id);\n    for (auto i = 0; i < Q; ++i) {\n        int\
    \ q, l, r;\n        std::cin >> q >> l >> r;\n        auto b = 0LL;\n        if\
    \ (q != 3)\n            std::cin >> b;\n        switch (q) {\n        case 0:\n\
    \            seg.apply(l, r, {b, -inf, 0});\n            break;\n        case\
    \ 1:\n            seg.apply(l, r, {inf, b, 0});\n            break;\n        case\
    \ 2:\n            seg.apply(l, r, {inf, -inf, b});\n            break;\n     \
    \   case 3:\n            std::cout << seg.prod(l, r).sum << '\\n';\n         \
    \   break;\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#include \"../segment_tree/segtree_beats.hpp\"\n#include <bits/stdc++.h>\n\
    \nstruct S {\n    long long max, max2, min, min2, sum;\n    int max_count, min_count,\
    \ size;\n    bool fail;\n};\n\nstruct F {\n    long long upper, lower, sum;\n\
    };\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n    std::vector<S> v(N);\n    constexpr auto inf = static_cast<long\
    \ long>(1e18);\n    for (auto &s : v) {\n        long long x;\n        std::cin\
    \ >> x;\n        s.max = s.min = s.sum = x;\n        s.max_count = s.min_count\
    \ = s.size = 1;\n        s.max2 = -inf;\n        s.min2 = inf;\n        s.fail\
    \ = false;\n    }\n    auto op = [](S a, S b) -> S {\n        S ret{};\n     \
    \   if (a.max < b.max) {\n            ret.max = b.max;\n            ret.max2 =\
    \ std::max(a.max, b.max2);\n            ret.max_count = b.max_count;\n       \
    \ } else if (b.max < a.max) {\n            ret.max = a.max;\n            ret.max2\
    \ = std::max(a.max2, b.max);\n            ret.max_count = a.max_count;\n     \
    \   } else {\n            ret.max = a.max;\n            ret.max2 = std::max(a.max2,\
    \ b.max2);\n            ret.max_count = a.max_count + b.max_count;\n        }\n\
    \        if (a.min < b.min) {\n            ret.min = a.min;\n            ret.min2\
    \ = std::min(a.min2, b.min);\n            ret.min_count = a.min_count;\n     \
    \   } else if (b.min < a.min) {\n            ret.min = b.min;\n            ret.min2\
    \ = std::min(a.min, b.min2);\n            ret.min_count = b.min_count;\n     \
    \   } else {\n            ret.min = a.min;\n            ret.min2 = std::min(a.min2,\
    \ b.min2);\n            ret.min_count = a.min_count + b.min_count;\n        }\n\
    \        ret.sum = a.sum + b.sum;\n        ret.size = a.size + b.size;\n     \
    \   return ret;\n    };\n    auto e = []() -> S { return {-inf, -inf, inf, inf,\
    \ 0, 0, 0, 0, false}; };\n    auto mapping = [](F f, S x) -> S {\n        x.max\
    \ += f.sum;\n        x.max2 += f.sum;\n        x.min += f.sum;\n        x.min2\
    \ += f.sum;\n        x.sum += f.sum * x.size;\n        if (x.max <= f.lower) {\n\
    \            return {f.lower, -1,     f.lower, -1,   f.lower * x.size,\n     \
    \               x.size,  x.size, x.size,  false};\n        }\n        if (f.upper\
    \ <= x.min) {\n            return {f.upper, -1,     f.upper, -1,   f.upper * x.size,\n\
    \                    x.size,  x.size, x.size,  false};\n        }\n        if\
    \ (x.max2 < f.upper && f.upper < x.max) {\n            x.sum -= (x.max - f.upper)\
    \ * x.max_count;\n            x.max = f.upper;\n        } else if (f.upper <=\
    \ x.max2) {\n            x.fail = true;\n            return x;\n        }\n  \
    \      if (x.max < x.min) {\n            x.min = x.max;\n        } else if (x.max\
    \ < x.min2) {\n            x.min2 = x.max;\n        }\n        if (x.min < f.lower\
    \ && f.lower < x.min2) {\n            x.sum += (f.lower - x.min) * x.min_count;\n\
    \            x.min = f.lower;\n        } else if (x.min2 <= f.lower) {\n     \
    \       x.fail = true;\n            return x;\n        }\n        if (x.max <\
    \ x.min) {\n            x.max = x.min;\n        } else if (x.max2 < x.min) {\n\
    \            x.max2 = x.min;\n        }\n        return x;\n    };\n    auto composition\
    \ = [](F f, F g) -> F {\n        g.upper += f.sum;\n        g.lower += f.sum;\n\
    \        g.sum += f.sum;\n        g.upper = std::min(f.upper, g.upper);\n    \
    \    if (g.upper < g.lower) {\n            g.lower = g.upper;\n        }\n   \
    \     g.lower = std::max(f.lower, g.lower);\n        if (g.upper < g.lower) {\n\
    \            g.upper = g.lower;\n        }\n        return g;\n    };\n    auto\
    \ id = []() -> F { return {inf, -inf, 0}; };\n    segtree_beats seg(v, op, e,\
    \ mapping, composition, id);\n    for (auto i = 0; i < Q; ++i) {\n        int\
    \ q, l, r;\n        std::cin >> q >> l >> r;\n        auto b = 0LL;\n        if\
    \ (q != 3)\n            std::cin >> b;\n        switch (q) {\n        case 0:\n\
    \            seg.apply(l, r, {b, -inf, 0});\n            break;\n        case\
    \ 1:\n            seg.apply(l, r, {inf, b, 0});\n            break;\n        case\
    \ 2:\n            seg.apply(l, r, {inf, -inf, b});\n            break;\n     \
    \   case 3:\n            std::cout << seg.prod(l, r).sum << '\\n';\n         \
    \   break;\n        }\n    }\n}\n"
  dependsOn:
  - segment_tree/segtree_beats.hpp
  isVerificationFile: true
  path: test/segtree_beats.test.cpp
  requiredBy: []
  timestamp: '2022-09-04 07:55:00+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segtree_beats.test.cpp
layout: document
redirect_from:
- /verify/test/segtree_beats.test.cpp
- /verify/test/segtree_beats.test.cpp.html
title: test/segtree_beats.test.cpp
---
