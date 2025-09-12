---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lca/lca_tree.hpp
    title: LCA Tree
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
  bundledCode: "#line 1 \"test/lca_tree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\
    \n\n#line 1 \"lca/lca_tree.hpp\"\n\n\n\n#include <algorithm>\n#include <bit>\n\
    #include <cassert>\n#include <queue>\n#include <vector>\n\nstruct lca_tree {\n\
    \    lca_tree(const std::vector<std::vector<int>> &adj, int root)\n        : n_(static_cast<int>(adj.size())),\
    \ root_(root),\n          lg_(std::bit_width(static_cast<unsigned>(n_)) - 1),\n\
    \          table_((lg_ + 1) * n_), depth_(n_) {\n        depth_[root_] = 0;\n\
    \        table_[root_] = root_;\n        std::queue<int> q;\n        q.emplace(root_);\n\
    \        while (!q.empty()) {\n            auto u = q.front();\n            q.pop();\n\
    \            for (auto v : adj[u]) {\n                if (v != table_[u]) {\n\
    \                    depth_[v] = depth_[u] + 1;\n                    table_[v]\
    \ = u;\n                    q.emplace(v);\n                }\n            }\n\
    \        }\n        for (auto i = 1; i <= lg_; ++i) {\n            for (auto u\
    \ = 0; u < n_; ++u) {\n                auto parent = table_[(i - 1) * n_ + u];\n\
    \                table_[i * n_ + u] = table_[(i - 1) * n_ + parent];\n       \
    \     }\n        }\n    }\n    int kth_parent(int u, int k) const {\n        assert(0\
    \ <= u && u < n_ && 0 <= k);\n        for (auto i = 0; i <= lg_; ++i) {\n    \
    \        if ((k >> i) & 1) {\n                u = table_[i * n_ + u];\n      \
    \      }\n        }\n        return u;\n    }\n    int lca(int u, int v) const\
    \ {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        if (depth_[u]\
    \ < depth_[v]) {\n            std::swap(u, v);\n        }\n        u = kth_parent(u,\
    \ depth_[u] - depth_[v]);\n        if (u == v) {\n            return u;\n    \
    \    }\n        for (auto i = lg_; i >= 0; i--) {\n            if (table_[i *\
    \ n_ + u] != table_[i * n_ + v]) {\n                u = table_[i * n_ + u];\n\
    \                v = table_[i * n_ + v];\n            }\n        }\n        return\
    \ table_[u];\n    }\n    int distance(int u, int v) const {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        return depth_[u] + depth_[v] -\
    \ 2 * depth_[lca(u, v)];\n    }\n    int jump(int u, int v, int k) const {\n \
    \       assert(0 <= u && u < n_ && 0 <= v && v < n_ && 0 <= k);\n        auto\
    \ l = lca(u, v);\n        auto ul = depth_[u] - depth_[l];\n        auto vl =\
    \ depth_[v] - depth_[l];\n        if (ul + vl < k) {\n            return -1;\n\
    \        }\n        if (k <= ul) {\n            return kth_parent(u, k);\n   \
    \     } else {\n            return kth_parent(v, ul + vl - k);\n        }\n  \
    \  }\n    const int n_, root_, lg_;\n    std::vector<int> table_, depth_;\n};\n\
    \n\n#line 4 \"test/lca_tree.test.cpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >>\
    \ N >> Q;\n    std::vector<std::vector<int>> adj(N);\n    for (auto i = 1; i <\
    \ N; ++i) {\n        int p;\n        std::cin >> p;\n        adj[p].push_back(i);\n\
    \    }\n    lca_tree tree(adj, 0);\n    for (int i = 0; i < Q; ++i) {\n      \
    \  int u, v;\n        std::cin >> u >> v;\n        std::cout << tree.lca(u, v)\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"../lca/lca_tree.hpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<std::vector<int>> adj(N);\n\
    \    for (auto i = 1; i < N; ++i) {\n        int p;\n        std::cin >> p;\n\
    \        adj[p].push_back(i);\n    }\n    lca_tree tree(adj, 0);\n    for (int\
    \ i = 0; i < Q; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n     \
    \   std::cout << tree.lca(u, v) << '\\n';\n    }\n}\n"
  dependsOn:
  - lca/lca_tree.hpp
  isVerificationFile: true
  path: test/lca_tree.test.cpp
  requiredBy: []
  timestamp: '2025-09-12 21:56:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/lca_tree.test.cpp
layout: document
redirect_from:
- /verify/test/lca_tree.test.cpp
- /verify/test/lca_tree.test.cpp.html
title: test/lca_tree.test.cpp
---
