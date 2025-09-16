---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lca/tarjan_offline_lca.hpp
    title: lca/tarjan_offline_lca.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../lca/tarjan_offline_lca.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"../lca/tarjan_offline_lca.hpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<std::vector<int>> adj(N);\n\
    \    for (auto i = 1; i < N; ++i) {\n        int p;\n        std::cin >> p;\n\
    \        adj[p].push_back(i);\n    }\n    std::vector<std::pair<int, int>> queries(Q);\n\
    \    for (auto &[u, v] : queries) {\n        std::cin >> u >> v;\n    }\n    tarjan_offline_lca\
    \ lca(adj, 0, queries);\n    auto result = lca.lca();\n    for (auto x : result)\
    \ {\n        std::cout << x << '\\n';\n    }\n}\n"
  dependsOn:
  - lca/tarjan_offline_lca.hpp
  isVerificationFile: true
  path: test/lca/tarjan_offline_lca.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/lca/tarjan_offline_lca.test.cpp
layout: document
redirect_from:
- /verify/test/lca/tarjan_offline_lca.test.cpp
- /verify/test/lca/tarjan_offline_lca.test.cpp.html
title: test/lca/tarjan_offline_lca.test.cpp
---
