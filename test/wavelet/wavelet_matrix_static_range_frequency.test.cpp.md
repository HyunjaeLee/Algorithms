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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_frequency
    links:
    - https://judge.yosupo.jp/problem/static_range_frequency
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../wavelet/wavelet_matrix.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\
    \n\n#include \"../wavelet/wavelet_matrix.hpp\"\n#include <bits/stdc++.h>\n\nint\
    \ main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin\
    \ >> N >> Q;\n    std::vector<int> v(N);\n    for (auto &x : v) {\n        std::cin\
    \ >> x;\n    }\n    v.push_back(0); // Wavelet matrix requires non-empty vector\n\
    \    wavelet_matrix<int> wm(std::move(v));\n    while (Q--) {\n        int l,\
    \ r, x;\n        std::cin >> l >> r >> x;\n        std::cout << wm.rank(l, r,\
    \ x) << '\\n';\n    }\n}\n"
  dependsOn:
  - wavelet/wavelet_matrix.hpp
  isVerificationFile: true
  path: test/wavelet/wavelet_matrix_static_range_frequency.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/wavelet/wavelet_matrix_static_range_frequency.test.cpp
layout: document
redirect_from:
- /verify/test/wavelet/wavelet_matrix_static_range_frequency.test.cpp
- /verify/test/wavelet/wavelet_matrix_static_range_frequency.test.cpp.html
title: test/wavelet/wavelet_matrix_static_range_frequency.test.cpp
---
