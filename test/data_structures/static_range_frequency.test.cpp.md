---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structures/csr.hpp
    title: data_structures/csr.hpp
  - icon: ':heavy_check_mark:'
    path: data_structures/static_range_frequency.hpp
    title: data_structures/static_range_frequency.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_frequency
    links:
    - https://judge.yosupo.jp/problem/static_range_frequency
  bundledCode: "#line 1 \"test/data_structures/static_range_frequency.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\n\n\
    #line 1 \"data_structures/static_range_frequency.hpp\"\n\n\n\n#line 1 \"data_structures/csr.hpp\"\
    \n\n\n\n#include <cassert>\n#include <ranges>\n#include <utility>\n#include <vector>\n\
    \ntemplate <typename T> struct csr {\n    explicit csr(int n) : n_(n) {}\n   \
    \ void add(int i, T x) {\n        assert(!built_);\n        assert(0 <= i && i\
    \ < n_);\n        buf_.emplace_back(i, x);\n    }\n    void build() {\n      \
    \  assert(!built_);\n        ptr_.assign(n_ + 2, 0);\n        csr_.resize(buf_.size());\n\
    \        for (auto [i, x] : buf_) {\n            ++ptr_[i + 2];\n        }\n \
    \       for (int i = 0; i < n_; ++i) {\n            ptr_[i + 1] += ptr_[i];\n\
    \        }\n        for (auto [i, x] : buf_) {\n            csr_[ptr_[i + 1]++]\
    \ = x;\n        }\n        built_ = true;\n    }\n    auto operator[](int i) {\n\
    \        assert(built_);\n        assert(0 <= i && i < n_);\n        return std::ranges::subrange(csr_.begin()\
    \ + ptr_[i], csr_.begin() + ptr_[i + 1]);\n    }\n    auto operator[](int i) const\
    \ {\n        assert(built_);\n        assert(0 <= i && i < n_);\n        return\
    \ std::ranges::subrange(csr_.begin() + ptr_[i], csr_.begin() + ptr_[i + 1]);\n\
    \    }\n    int size() const { return n_; }\n\nprivate:\n    int n_;\n    bool\
    \ built_ = false;\n    std::vector<std::pair<int, T>> buf_;\n    std::vector<T>\
    \ csr_;\n    std::vector<int> ptr_;\n};\n\n\n#line 5 \"data_structures/static_range_frequency.hpp\"\
    \n#include <algorithm>\n#line 8 \"data_structures/static_range_frequency.hpp\"\
    \n\ntemplate <typename T> struct static_range_frequency {\n    explicit static_range_frequency(const\
    \ std::vector<T> &a)\n        : n(int(a.size())), v(compress(a)), f(int(v.size()))\
    \ {\n        for (auto i = 0; i < n; ++i) {\n            auto c = int(std::ranges::lower_bound(v,\
    \ a[i]) - v.begin());\n            f.add(c, i);\n        }\n        f.build();\n\
    \    }\n    int query(int l, int r, T x) const { // [l, r)\n        assert(0 <=\
    \ l && l <= r && r <= n);\n        if (l == r) {\n            return 0;\n    \
    \    }\n        auto it = std::ranges::lower_bound(v, x);\n        if (it == v.end()\
    \ || *it != x) {\n            return 0;\n        }\n        auto c = int(it -\
    \ v.begin());\n        return int(std::ranges::lower_bound(f[c], r) - std::ranges::lower_bound(f[c],\
    \ l));\n    }\n\nprivate:\n    static std::vector<T> compress(std::vector<T> a)\
    \ {\n        std::ranges::sort(a);\n        auto [l, r] = std::ranges::unique(a);\n\
    \        a.erase(l, r);\n        return a;\n    }\n    int n;\n    std::vector<T>\
    \ v;\n    csr<int> f;\n};\n\n\n#line 4 \"test/data_structures/static_range_frequency.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<int> A(N);\n    for (auto\
    \ &x : A) {\n        std::cin >> x;\n    }\n    static_range_frequency<int> f(A);\n\
    \    while (Q--) {\n        int l, r, x;\n        std::cin >> l >> r >> x;\n \
    \       std::cout << f.query(l, r, x) << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\
    \n\n#include \"data_structures/static_range_frequency.hpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin\
    \ >> N >> Q;\n    std::vector<int> A(N);\n    for (auto &x : A) {\n        std::cin\
    \ >> x;\n    }\n    static_range_frequency<int> f(A);\n    while (Q--) {\n   \
    \     int l, r, x;\n        std::cin >> l >> r >> x;\n        std::cout << f.query(l,\
    \ r, x) << \"\\n\";\n    }\n}\n"
  dependsOn:
  - data_structures/static_range_frequency.hpp
  - data_structures/csr.hpp
  isVerificationFile: true
  path: test/data_structures/static_range_frequency.test.cpp
  requiredBy: []
  timestamp: '2026-10-14 13:04:34+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structures/static_range_frequency.test.cpp
layout: document
redirect_from:
- /verify/test/data_structures/static_range_frequency.test.cpp
- /verify/test/data_structures/static_range_frequency.test.cpp.html
title: test/data_structures/static_range_frequency.test.cpp
---
