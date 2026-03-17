---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/cartesian_tree.hpp
    title: Cartesian Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"test/tree/cartesian_tree.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#line 1 \"tree/cartesian_tree.hpp\"\
    \n\n\n\n#include <vector>\n\nstd::vector<int> cartesian_tree(const std::vector<int>\
    \ &a) {\n    const auto n = int(a.size());\n    std::vector<int> parent(n, -1),\
    \ st;\n    for (auto i = 0; i < n; ++i) {\n        auto v = -1;\n        while\
    \ (!st.empty() && a[i] < a[st.back()]) {\n            v = st.back();\n       \
    \     st.pop_back();\n        }\n        if (!st.empty()) {\n            parent[i]\
    \ = st.back();\n        }\n        if (~v) {\n            parent[v] = i;\n   \
    \     }\n        st.push_back(i);\n    }\n    return parent;\n}\n\n\n#line 4 \"\
    test/tree/cartesian_tree.test.cpp\"\n#include <bits/stdc++.h>\n\nint main() {\n\
    \    std::cin.tie(0)->sync_with_stdio(0);\n    int N;\n    std::cin >> N;\n  \
    \  std::vector<int> A(N);\n    copy_n(std::istream_iterator<int>(std::cin), N,\
    \ A.begin());\n    auto parent = cartesian_tree(A);\n    for (auto i = 0; i <\
    \ N; ++i) {\n        std::cout << (~parent[i] ? parent[i] : i) << \" \";\n   \
    \ }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include\
    \ \"tree/cartesian_tree.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N;\n    std::cin >> N;\n    std::vector<int> A(N);\n    copy_n(std::istream_iterator<int>(std::cin),\
    \ N, A.begin());\n    auto parent = cartesian_tree(A);\n    for (auto i = 0; i\
    \ < N; ++i) {\n        std::cout << (~parent[i] ? parent[i] : i) << \" \";\n \
    \   }\n}\n"
  dependsOn:
  - tree/cartesian_tree.hpp
  isVerificationFile: true
  path: test/tree/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2026-03-17 14:01:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/tree/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/test/tree/cartesian_tree.test.cpp
- /verify/test/tree/cartesian_tree.test.cpp.html
title: test/tree/cartesian_tree.test.cpp
---
