---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"heavy_light_decomposition/heavy_light_decomposition.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include\
    \ <vector>\n\nstruct heavy_light_decomposition {\n    heavy_light_decomposition(const\
    \ std::vector<std::vector<int>> &graph,\n                              int root)\n\
    \        : n_(static_cast<int>(graph.size())), timer_(0), graph_(graph),\n   \
    \       size_(n_, 1), depth_(n_), parent_(n_, -1), top_(n_), in_(n_), out_(n_)\
    \ {\n        assert(0 <= root && root < n_);\n        top_[root] = root;\n   \
    \     dfs_size(root);\n        dfs_hld(root);\n    }\n    explicit heavy_light_decomposition(\n\
    \        const std::vector<std::vector<int>> &graph)\n        : n_(static_cast<int>(graph.size())),\
    \ timer_(0), graph_(graph),\n          size_(n_, 1), depth_(n_), parent_(n_, -1),\
    \ top_(n_), in_(n_), out_(n_) {\n        for (auto i = 0; i < n_; ++i) {\n   \
    \         if (!~parent_[i]) {\n                top_[i] = i;\n                dfs_size(i);\n\
    \                dfs_hld(i);\n            }\n        }\n    }\n    template <typename\
    \ Function> void access_node(int u, Function f) {\n        assert(0 <= u && u\
    \ < n_);\n        f(in_[u]);\n    }\n    template <typename Function>\n    std::enable_if_t<\n\
    \        std::is_same_v<std::invoke_result_t<Function, int, int>, void>, void>\n\
    \    access_path(int u, int v, bool include_lca, Function f) const {\n       \
    \ assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        while (top_[u] != top_[v])\
    \ {\n            if (depth_[top_[u]] < depth_[top_[v]]) {\n                std::swap(u,\
    \ v);\n            }\n            f(in_[top_[u]], in_[u] + 1);\n            u\
    \ = parent_[top_[u]];\n        }\n        if (depth_[u] > depth_[v]) {\n     \
    \       std::swap(u, v);\n        }\n        if (include_lca) {\n            f(in_[u],\
    \ in_[v] + 1);\n        } else {\n            f(in_[u] + 1, in_[v] + 1);\n   \
    \     }\n    }\n    template <typename Function>\n    std::enable_if_t<\n    \
    \    std::is_same_v<std::invoke_result_t<Function, int, int, bool>, void>,\n \
    \       void>\n    access_path(int u, int v, bool include_lca, Function f) const\
    \ {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        bool forward\
    \ = true;\n        while (top_[u] != top_[v]) {\n            if (depth_[top_[u]]\
    \ < depth_[top_[v]]) {\n                std::swap(u, v);\n                forward\
    \ = !forward;\n            }\n            f(in_[top_[u]], in_[u] + 1, forward);\n\
    \            u = parent_[top_[u]];\n        }\n        if (depth_[u] > depth_[v])\
    \ {\n            std::swap(u, v);\n            forward = !forward;\n        }\n\
    \        if (include_lca) {\n            f(in_[u], in_[v] + 1, forward);\n   \
    \     } else {\n            f(in_[u] + 1, in_[v] + 1, forward);\n        }\n \
    \   }\n    template <typename Function>\n    void access_subtree(int u, bool include_root,\
    \ Function f) const {\n        assert(0 <= u && u < n_);\n        if (include_root)\
    \ {\n            f(in_[u], out_[u]);\n        } else {\n            f(in_[u] +\
    \ 1, out_[u]);\n        }\n    }\n    int lca(int u, int v) const {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        while (top_[u] != top_[v]) {\n\
    \            if (depth_[top_[u]] < depth_[top_[v]]) {\n                std::swap(u,\
    \ v);\n            }\n            u = parent_[top_[u]];\n        }\n        if\
    \ (depth_[u] > depth_[v]) {\n            std::swap(u, v);\n        }\n       \
    \ return u;\n    }\n\nprivate:\n    void dfs_size(int u) {\n        auto it =\
    \ std::find(graph_[u].begin(), graph_[u].end(), parent_[u]);\n        if (it !=\
    \ graph_[u].end()) {\n            graph_[u].erase(it);\n        }\n        for\
    \ (auto &v : graph_[u]) {\n            depth_[v] = depth_[u] + 1;\n          \
    \  parent_[v] = u;\n            dfs_size(v);\n            size_[u] += size_[v];\n\
    \            if (size_[v] > size_[graph_[u][0]]) {\n                std::swap(v,\
    \ graph_[u][0]);\n            }\n        }\n    }\n    void dfs_hld(int u) {\n\
    \        in_[u] = timer_++;\n        for (auto v : graph_[u]) {\n            top_[v]\
    \ = (v == graph_[u][0] ? top_[u] : v);\n            dfs_hld(v);\n        }\n \
    \       out_[u] = timer_;\n    }\n    int n_, timer_;\n    std::vector<std::vector<int>>\
    \ graph_;\n    std::vector<int> size_, depth_, parent_, top_, in_, out_;\n};\n\
    \n\n"
  code: "#ifndef HEAVY_LIGHT_DECOMPOSITION\n#define HEAVY_LIGHT_DECOMPOSITION\n\n\
    #include <algorithm>\n#include <cassert>\n#include <type_traits>\n#include <vector>\n\
    \nstruct heavy_light_decomposition {\n    heavy_light_decomposition(const std::vector<std::vector<int>>\
    \ &graph,\n                              int root)\n        : n_(static_cast<int>(graph.size())),\
    \ timer_(0), graph_(graph),\n          size_(n_, 1), depth_(n_), parent_(n_, -1),\
    \ top_(n_), in_(n_), out_(n_) {\n        assert(0 <= root && root < n_);\n   \
    \     top_[root] = root;\n        dfs_size(root);\n        dfs_hld(root);\n  \
    \  }\n    explicit heavy_light_decomposition(\n        const std::vector<std::vector<int>>\
    \ &graph)\n        : n_(static_cast<int>(graph.size())), timer_(0), graph_(graph),\n\
    \          size_(n_, 1), depth_(n_), parent_(n_, -1), top_(n_), in_(n_), out_(n_)\
    \ {\n        for (auto i = 0; i < n_; ++i) {\n            if (!~parent_[i]) {\n\
    \                top_[i] = i;\n                dfs_size(i);\n                dfs_hld(i);\n\
    \            }\n        }\n    }\n    template <typename Function> void access_node(int\
    \ u, Function f) {\n        assert(0 <= u && u < n_);\n        f(in_[u]);\n  \
    \  }\n    template <typename Function>\n    std::enable_if_t<\n        std::is_same_v<std::invoke_result_t<Function,\
    \ int, int>, void>, void>\n    access_path(int u, int v, bool include_lca, Function\
    \ f) const {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        while\
    \ (top_[u] != top_[v]) {\n            if (depth_[top_[u]] < depth_[top_[v]]) {\n\
    \                std::swap(u, v);\n            }\n            f(in_[top_[u]],\
    \ in_[u] + 1);\n            u = parent_[top_[u]];\n        }\n        if (depth_[u]\
    \ > depth_[v]) {\n            std::swap(u, v);\n        }\n        if (include_lca)\
    \ {\n            f(in_[u], in_[v] + 1);\n        } else {\n            f(in_[u]\
    \ + 1, in_[v] + 1);\n        }\n    }\n    template <typename Function>\n    std::enable_if_t<\n\
    \        std::is_same_v<std::invoke_result_t<Function, int, int, bool>, void>,\n\
    \        void>\n    access_path(int u, int v, bool include_lca, Function f) const\
    \ {\n        assert(0 <= u && u < n_ && 0 <= v && v < n_);\n        bool forward\
    \ = true;\n        while (top_[u] != top_[v]) {\n            if (depth_[top_[u]]\
    \ < depth_[top_[v]]) {\n                std::swap(u, v);\n                forward\
    \ = !forward;\n            }\n            f(in_[top_[u]], in_[u] + 1, forward);\n\
    \            u = parent_[top_[u]];\n        }\n        if (depth_[u] > depth_[v])\
    \ {\n            std::swap(u, v);\n            forward = !forward;\n        }\n\
    \        if (include_lca) {\n            f(in_[u], in_[v] + 1, forward);\n   \
    \     } else {\n            f(in_[u] + 1, in_[v] + 1, forward);\n        }\n \
    \   }\n    template <typename Function>\n    void access_subtree(int u, bool include_root,\
    \ Function f) const {\n        assert(0 <= u && u < n_);\n        if (include_root)\
    \ {\n            f(in_[u], out_[u]);\n        } else {\n            f(in_[u] +\
    \ 1, out_[u]);\n        }\n    }\n    int lca(int u, int v) const {\n        assert(0\
    \ <= u && u < n_ && 0 <= v && v < n_);\n        while (top_[u] != top_[v]) {\n\
    \            if (depth_[top_[u]] < depth_[top_[v]]) {\n                std::swap(u,\
    \ v);\n            }\n            u = parent_[top_[u]];\n        }\n        if\
    \ (depth_[u] > depth_[v]) {\n            std::swap(u, v);\n        }\n       \
    \ return u;\n    }\n\nprivate:\n    void dfs_size(int u) {\n        auto it =\
    \ std::find(graph_[u].begin(), graph_[u].end(), parent_[u]);\n        if (it !=\
    \ graph_[u].end()) {\n            graph_[u].erase(it);\n        }\n        for\
    \ (auto &v : graph_[u]) {\n            depth_[v] = depth_[u] + 1;\n          \
    \  parent_[v] = u;\n            dfs_size(v);\n            size_[u] += size_[v];\n\
    \            if (size_[v] > size_[graph_[u][0]]) {\n                std::swap(v,\
    \ graph_[u][0]);\n            }\n        }\n    }\n    void dfs_hld(int u) {\n\
    \        in_[u] = timer_++;\n        for (auto v : graph_[u]) {\n            top_[v]\
    \ = (v == graph_[u][0] ? top_[u] : v);\n            dfs_hld(v);\n        }\n \
    \       out_[u] = timer_;\n    }\n    int n_, timer_;\n    std::vector<std::vector<int>>\
    \ graph_;\n    std::vector<int> size_, depth_, parent_, top_, in_, out_;\n};\n\
    \n#endif // HEAVY_LIGHT_DECOMPOSITION"
  dependsOn: []
  isVerificationFile: false
  path: heavy_light_decomposition/heavy_light_decomposition.hpp
  requiredBy: []
  timestamp: '2022-09-08 16:54:03+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: heavy_light_decomposition/heavy_light_decomposition.hpp
layout: document
title: Heavy-light Decomposition
---
