---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: wavelet/wavelet_matrix.hpp
    title: wavelet/wavelet_matrix.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/opt/hostedtoolcache/Python/3.14.2/x64/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../wavelet/wavelet_matrix.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../wavelet/wavelet_matrix.hpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >>\
    \ N >> Q;\n    std::vector<int> v(N);\n    for (auto &x : v) {\n        std::cin\
    \ >> x;\n    }\n    wavelet_matrix<int> wm(std::move(v));\n    while (Q--) {\n\
    \        int l, r, k;\n        std::cin >> l >> r >> k;\n        std::cout <<\
    \ wm.quantile(l, r, k) << '\\n';\n    }\n}\n"
  dependsOn:
  - wavelet/wavelet_matrix.hpp
  isVerificationFile: true
  path: test/wavelet/wavelet_matrix_range_kth_smallest.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/wavelet/wavelet_matrix_range_kth_smallest.test.cpp
layout: document
redirect_from:
- /verify/test/wavelet/wavelet_matrix_range_kth_smallest.test.cpp
- /verify/test/wavelet/wavelet_matrix_range_kth_smallest.test.cpp.html
title: test/wavelet/wavelet_matrix_range_kth_smallest.test.cpp
---
