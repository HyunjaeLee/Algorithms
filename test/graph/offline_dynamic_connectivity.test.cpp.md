---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: disjoint_set/rollback_disjoint_set.hpp
    title: disjoint_set/rollback_disjoint_set.hpp
  - icon: ':heavy_check_mark:'
    path: graph/offline_dynamic_connectivity.hpp
    title: graph/offline_dynamic_connectivity.hpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../disjoint_set/rollback_disjoint_set.hpp:\
    \ line -1: no such header\n"
  code: "#include <clocale>\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2235\"\
    \n\n#include \"../disjoint_set/rollback_disjoint_set.hpp\"\n#include \"../graph/offline_dynamic_connectivity.hpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int n, k;\n    std::cin >> n >> k;\n    offline_dynamic_connectivity<rollback_disjoint_set>\
    \ dc(n);\n    std::vector<std::pair<int, int>> q;\n    dc.reserve(k);\n    q.reserve(k);\n\
    \    while (k--) {\n        int t, u, v;\n        std::cin >> t >> u >> v;\n \
    \       switch (t) {\n        case 1:\n        case 2:\n            dc.toggle_edge(u,\
    \ v);\n            break;\n        case 3:\n            q.emplace_back(u, v);\n\
    \            dc.snapshot();\n            break;\n        }\n    }\n    auto result\
    \ = dc.solve([&](const auto &dsu, int i) {\n        auto [u, v] = q[i];\n    \
    \    return dsu.same(u, v);\n    });\n    for (auto b : result) {\n        std::cout\
    \ << (b ? \"YES\\n\" : \"NO\\n\");\n    }\n}\n"
  dependsOn:
  - disjoint_set/rollback_disjoint_set.hpp
  - graph/offline_dynamic_connectivity.hpp
  isVerificationFile: true
  path: test/graph/offline_dynamic_connectivity.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/graph/offline_dynamic_connectivity.test.cpp
layout: document
redirect_from:
- /verify/test/graph/offline_dynamic_connectivity.test.cpp
- /verify/test/graph/offline_dynamic_connectivity.test.cpp.html
title: test/graph/offline_dynamic_connectivity.test.cpp
---
