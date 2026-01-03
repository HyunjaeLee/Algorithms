---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: random/splitmix64.hpp
    title: splitmix64
  - icon: ':heavy_check_mark:'
    path: random/xoshiro256starstar.hpp
    title: xoshiro256**
  - icon: ':heavy_check_mark:'
    path: treap/treap_set.hpp
    title: treap/treap_set.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_A
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../random/xoshiro256starstar.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_A\"\
    \n\n#include \"../random/xoshiro256starstar.hpp\"\n#include \"../treap/treap_set.hpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int q;\n    std::cin >> q;\n    treap_set<int, xoshiro256starstar> s;\n \
    \   while (q--) {\n        int t, x;\n        std::cin >> t >> x;\n        if\
    \ (t == 0) {\n            s.insert(x);\n            std::cout << s.size() << '\\\
    n';\n        } else {\n            std::cout << (s.contains(x) ? 1 : 0) << '\\\
    n';\n        }\n    }\n}\n"
  dependsOn:
  - random/xoshiro256starstar.hpp
  - random/splitmix64.hpp
  - treap/treap_set.hpp
  isVerificationFile: true
  path: test/treap/treap_set.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/treap/treap_set.test.cpp
layout: document
redirect_from:
- /verify/test/treap/treap_set.test.cpp
- /verify/test/treap/treap_set.test.cpp.html
title: test/treap/treap_set.test.cpp
---
