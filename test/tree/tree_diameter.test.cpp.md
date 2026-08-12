---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/csr_graph.hpp
    title: graph/csr_graph.hpp
  - icon: ':heavy_check_mark:'
    path: tree/tree_diameter.hpp
    title: tree/tree_diameter.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tree_diameter
    links:
    - https://judge.yosupo.jp/problem/tree_diameter
  bundledCode: "#line 1 \"test/tree/tree_diameter.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\
    \n#include <graph/csr_graph.hpp>\n#include <tree/tree_diameter.hpp>\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\n\nint main() {\n    cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    cin >> N;\n    CSRGraph<long long> g(N);\n    for (auto i = 0;\
    \ i < N - 1; ++i) {\n        int u, v, w;\n        cin >> u >> v >> w;\n     \
    \   g.add_edge(u, v, w);\n    }\n    g.build_undirected();\n    auto [d, path]\
    \ = tree_diameter(g);\n    cout << d << \" \" << path.size() << \"\\n\";\n   \
    \ for (auto u : path) {\n        cout << u << \" \";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\n#include\
    \ <graph/csr_graph.hpp>\n#include <tree/tree_diameter.hpp>\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nint main() {\n    cin.tie(0)->sync_with_stdio(0);\n  \
    \  int N;\n    cin >> N;\n    CSRGraph<long long> g(N);\n    for (auto i = 0;\
    \ i < N - 1; ++i) {\n        int u, v, w;\n        cin >> u >> v >> w;\n     \
    \   g.add_edge(u, v, w);\n    }\n    g.build_undirected();\n    auto [d, path]\
    \ = tree_diameter(g);\n    cout << d << \" \" << path.size() << \"\\n\";\n   \
    \ for (auto u : path) {\n        cout << u << \" \";\n    }\n}\n"
  dependsOn:
  - graph/csr_graph.hpp
  - tree/tree_diameter.hpp
  isVerificationFile: true
  path: test/tree/tree_diameter.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 07:38:15+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/tree/tree_diameter.test.cpp
layout: document
redirect_from:
- /verify/test/tree/tree_diameter.test.cpp
- /verify/test/tree/tree_diameter.test.cpp.html
title: test/tree/tree_diameter.test.cpp
---
