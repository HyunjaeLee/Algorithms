---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dynamic_connectivity.hpp
    title: graph/dynamic_connectivity.hpp
  - icon: ':heavy_check_mark:'
    path: random/splitmix64.hpp
    title: splitmix64
  - icon: ':heavy_check_mark:'
    path: random/xoshiro256starstar.hpp
    title: xoshiro256**
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../graph/dynamic_connectivity.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235\"\
    \n\n#include \"../graph/dynamic_connectivity.hpp\"\n#include <bits/stdc++.h>\n\
    \nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int n, k;\n    std::cin\
    \ >> n >> k;\n    dynamic_connectivity dc(n);\n    for (auto i = 0; i < k; ++i)\
    \ {\n        int q, u, v;\n        std::cin >> q >> u >> v;\n        switch (q)\
    \ {\n        case 1:\n            dc.link(u, v);\n            break;\n       \
    \ case 2:\n            dc.cut(u, v);\n            break;\n        case 3:\n  \
    \          std::cout << (dc.connected(u, v) ? \"YES\\n\" : \"NO\\n\");\n     \
    \       break;\n        }\n    }\n}\n"
  dependsOn:
  - graph/dynamic_connectivity.hpp
  - random/xoshiro256starstar.hpp
  - random/splitmix64.hpp
  isVerificationFile: true
  path: test/graph/dynamic_connectivity.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/dynamic_connectivity.test.cpp
layout: document
redirect_from:
- /verify/test/graph/dynamic_connectivity.test.cpp
- /verify/test/graph/dynamic_connectivity.test.cpp.html
title: test/graph/dynamic_connectivity.test.cpp
---
