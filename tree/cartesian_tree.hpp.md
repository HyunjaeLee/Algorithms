---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/tree/cartesian_tree.test.cpp
    title: test/tree/cartesian_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/cartesian_tree.hpp\"\n\n\n\n#include <vector>\n\nstd::vector<int>\
    \ cartesian_tree(const std::vector<int> &a) {\n    const auto n = int(a.size());\n\
    \    std::vector<int> parent(n, -1), st;\n    for (auto i = 0; i < n; ++i) {\n\
    \        auto v = -1;\n        while (!st.empty() && a[i] < a[st.back()]) {\n\
    \            v = st.back();\n            st.pop_back();\n        }\n        if\
    \ (!st.empty()) {\n            parent[i] = st.back();\n        }\n        if (~v)\
    \ {\n            parent[v] = i;\n        }\n        st.push_back(i);\n    }\n\
    \    return parent;\n}\n\n\n"
  code: "#ifndef CARTESIAN_TREE_HPP\n#define CARTESIAN_TREE_HPP\n\n#include <vector>\n\
    \nstd::vector<int> cartesian_tree(const std::vector<int> &a) {\n    const auto\
    \ n = int(a.size());\n    std::vector<int> parent(n, -1), st;\n    for (auto i\
    \ = 0; i < n; ++i) {\n        auto v = -1;\n        while (!st.empty() && a[i]\
    \ < a[st.back()]) {\n            v = st.back();\n            st.pop_back();\n\
    \        }\n        if (!st.empty()) {\n            parent[i] = st.back();\n \
    \       }\n        if (~v) {\n            parent[v] = i;\n        }\n        st.push_back(i);\n\
    \    }\n    return parent;\n}\n\n#endif // CARTESIAN_TREE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: tree/cartesian_tree.hpp
  requiredBy: []
  timestamp: '2026-03-17 14:01:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/tree/cartesian_tree.test.cpp
documentation_of: tree/cartesian_tree.hpp
layout: document
title: Cartesian Tree
---

+ [Cartesian Tree - OI Wiki](https://en.oi-wiki.org/ds/cartesian-tree/)
