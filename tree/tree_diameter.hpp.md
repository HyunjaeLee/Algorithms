---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/tree/tree_diameter.test.cpp
    title: test/tree/tree_diameter.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/tree_diameter.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\n// requires non-negative edge weights\n// return\
    \ (diameter, path)\n// for an unweighted tree, centers are path[d / 2] and path[(d\
    \ + 1) / 2]\ntemplate <typename T> auto tree_diameter(const auto &g) {\n    assert(0\
    \ < g.size());\n    auto n = int(g.size());\n    std::vector<int> parent(n, -1);\n\
    \    std::vector<T> depth(n);\n    auto dfs = [&](int x) {\n        std::vector<int>\
    \ st;\n        st.push_back(x);\n        parent[x] = -1;\n        depth[x] = 0;\n\
    \        while (!st.empty()) {\n            auto u = st.back();\n            st.pop_back();\n\
    \            for (auto [v, w]: g[u]) {\n                if (v != parent[u]) {\n\
    \                    st.push_back(v);\n                    parent[v] = u;\n  \
    \                  depth[v] = depth[u] + w;\n                }\n            }\n\
    \        }\n        auto it = std::ranges::max_element(depth);\n        auto r\
    \ = int(it - depth.begin());\n        return std::pair(r, *it);\n    };\n    auto\
    \ x = dfs(0).first;\n    auto [y, d] = dfs(x);\n    std::vector<int> path;\n \
    \   for (auto u = y; ~u; u = parent[u]) {\n        path.push_back(u);\n    }\n\
    \    return std::pair(d, path);\n}\n\n\n"
  code: "#ifndef TREE_DIAMETER_HPP\n#define TREE_DIAMETER_HPP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// requires non-negative edge weights\n\
    // return (diameter, path)\n// for an unweighted tree, centers are path[d / 2]\
    \ and path[(d + 1) / 2]\ntemplate <typename T> auto tree_diameter(const auto &g)\
    \ {\n    assert(0 < g.size());\n    auto n = int(g.size());\n    std::vector<int>\
    \ parent(n, -1);\n    std::vector<T> depth(n);\n    auto dfs = [&](int x) {\n\
    \        std::vector<int> st;\n        st.push_back(x);\n        parent[x] = -1;\n\
    \        depth[x] = 0;\n        while (!st.empty()) {\n            auto u = st.back();\n\
    \            st.pop_back();\n            for (auto [v, w]: g[u]) {\n         \
    \       if (v != parent[u]) {\n                    st.push_back(v);\n        \
    \            parent[v] = u;\n                    depth[v] = depth[u] + w;\n  \
    \              }\n            }\n        }\n        auto it = std::ranges::max_element(depth);\n\
    \        auto r = int(it - depth.begin());\n        return std::pair(r, *it);\n\
    \    };\n    auto x = dfs(0).first;\n    auto [y, d] = dfs(x);\n    std::vector<int>\
    \ path;\n    for (auto u = y; ~u; u = parent[u]) {\n        path.push_back(u);\n\
    \    }\n    return std::pair(d, path);\n}\n\n#endif // TREE_DIAMETER_HPP"
  dependsOn: []
  isVerificationFile: false
  path: tree/tree_diameter.hpp
  requiredBy: []
  timestamp: '2026-10-12 17:31:27+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/tree/tree_diameter.test.cpp
documentation_of: tree/tree_diameter.hpp
layout: document
redirect_from:
- /library/tree/tree_diameter.hpp
- /library/tree/tree_diameter.hpp.html
title: tree/tree_diameter.hpp
---
