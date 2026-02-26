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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.11.14/x64/lib/python3.11/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.11.14/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.11.14/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/opt/hostedtoolcache/Python/3.11.14/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../segment_tree/segtree_beats.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM                                                         \
    \       \\\n    \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#include \"../segment_tree/segtree_beats.hpp\"\n#include <bits/stdc++.h>\n\
    \nstruct S {\n    long long max, max2, min, min2, sum;\n    int max_count, min_count,\
    \ size;\n};\n\nstruct F {\n    long long upper, lower, sum;\n};\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >>\
    \ N >> Q;\n    std::vector<S> v(N);\n    constexpr auto inf = static_cast<long\
    \ long>(1e18);\n    for (auto &s : v) {\n        long long x;\n        std::cin\
    \ >> x;\n        s.max = s.min = s.sum = x;\n        s.max_count = s.min_count\
    \ = s.size = 1;\n        s.max2 = -inf;\n        s.min2 = inf;\n    }\n    auto\
    \ op = [](S a, S b) -> S {\n        S ret{};\n        if (a.max < b.max) {\n \
    \           ret.max = b.max;\n            ret.max2 = std::max(a.max, b.max2);\n\
    \            ret.max_count = b.max_count;\n        } else if (b.max < a.max) {\n\
    \            ret.max = a.max;\n            ret.max2 = std::max(a.max2, b.max);\n\
    \            ret.max_count = a.max_count;\n        } else {\n            ret.max\
    \ = a.max;\n            ret.max2 = std::max(a.max2, b.max2);\n            ret.max_count\
    \ = a.max_count + b.max_count;\n        }\n        if (a.min < b.min) {\n    \
    \        ret.min = a.min;\n            ret.min2 = std::min(a.min2, b.min);\n \
    \           ret.min_count = a.min_count;\n        } else if (b.min < a.min) {\n\
    \            ret.min = b.min;\n            ret.min2 = std::min(a.min, b.min2);\n\
    \            ret.min_count = b.min_count;\n        } else {\n            ret.min\
    \ = a.min;\n            ret.min2 = std::min(a.min2, b.min2);\n            ret.min_count\
    \ = a.min_count + b.min_count;\n        }\n        ret.sum = a.sum + b.sum;\n\
    \        ret.size = a.size + b.size;\n        return ret;\n    };\n    auto e\
    \ = []() -> S { return {-inf, -inf, inf, inf, 0, 0, 0, 0}; };\n    auto mapping\
    \ = [](F f, S x) -> std::pair<S, bool> {\n        x.max += f.sum;\n        x.max2\
    \ += f.sum;\n        x.min += f.sum;\n        x.min2 += f.sum;\n        x.sum\
    \ += f.sum * x.size;\n        if (x.max <= f.lower) {\n            return {{f.lower,\
    \ -1, f.lower, -1, f.lower * x.size, x.size, x.size,\n                     x.size},\n\
    \                    true};\n        }\n        if (f.upper <= x.min) {\n    \
    \        return {{f.upper, -1, f.upper, -1, f.upper * x.size, x.size, x.size,\n\
    \                     x.size},\n                    true};\n        }\n      \
    \  if (x.max2 < f.upper && f.upper < x.max) {\n            x.sum -= (x.max - f.upper)\
    \ * x.max_count;\n            x.max = f.upper;\n        } else if (f.upper <=\
    \ x.max2) {\n            return {x, false};\n        }\n        if (x.max < x.min)\
    \ {\n            x.min = x.max;\n        } else if (x.max < x.min2) {\n      \
    \      x.min2 = x.max;\n        }\n        if (x.min < f.lower && f.lower < x.min2)\
    \ {\n            x.sum += (f.lower - x.min) * x.min_count;\n            x.min\
    \ = f.lower;\n        } else if (x.min2 <= f.lower) {\n            return {x,\
    \ false};\n        }\n        if (x.max < x.min) {\n            x.max = x.min;\n\
    \        } else if (x.max2 < x.min) {\n            x.max2 = x.min;\n        }\n\
    \        return {x, true};\n    };\n    auto composition = [](F f, F g) -> F {\n\
    \        g.upper += f.sum;\n        g.lower += f.sum;\n        g.sum += f.sum;\n\
    \        g.upper = std::min(f.upper, g.upper);\n        if (g.upper < g.lower)\
    \ {\n            g.lower = g.upper;\n        }\n        g.lower = std::max(f.lower,\
    \ g.lower);\n        if (g.upper < g.lower) {\n            g.upper = g.lower;\n\
    \        }\n        return g;\n    };\n    auto id = []() -> F { return {inf,\
    \ -inf, 0}; };\n    segtree_beats seg(v, op, e, mapping, composition, id);\n \
    \   for (auto i = 0; i < Q; ++i) {\n        int q, l, r;\n        std::cin >>\
    \ q >> l >> r;\n        auto b = 0LL;\n        if (q != 3)\n            std::cin\
    \ >> b;\n        switch (q) {\n        case 0:\n            seg.apply(l, r, {b,\
    \ -inf, 0});\n            break;\n        case 1:\n            seg.apply(l, r,\
    \ {inf, b, 0});\n            break;\n        case 2:\n            seg.apply(l,\
    \ r, {inf, -inf, b});\n            break;\n        case 3:\n            std::cout\
    \ << seg.prod(l, r).sum << '\\n';\n            break;\n        }\n    }\n}\n"
  dependsOn:
  - segment_tree/segtree_beats.hpp
  isVerificationFile: true
  path: test/segment_tree/segtree_beats.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segment_tree/segtree_beats.test.cpp
layout: document
redirect_from:
- /verify/test/segment_tree/segtree_beats.test.cpp
- /verify/test/segment_tree/segtree_beats.test.cpp.html
title: test/segment_tree/segtree_beats.test.cpp
---
