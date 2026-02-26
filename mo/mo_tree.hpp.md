---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: mo/hilbert_mo.hpp
    title: mo/hilbert_mo.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/mo/aoj0489.test.cpp
    title: test/mo/aoj0489.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/mo/aoj2270.test.cpp
    title: test/mo/aoj2270.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"mo/mo_tree.hpp\"\n\n\n\n#line 1 \"mo/hilbert_mo.hpp\"\n\n\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <vector>\n\
    \nstruct HilbertMo {\n    HilbertMo(int n) : n_(n), log_(std::bit_width(unsigned(n)))\
    \ {}\n    void add(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n\
    \        auto index = int(queries_.size());\n        auto order = hilbert_order(l,\
    \ r);\n        queries_.push_back({l, r, index, order});\n    }\n    void solve(auto\
    \ add, auto remove, auto eval) { solve(add, add, remove, remove, eval); }\n  \
    \  void solve(auto add_left, auto add_right, auto remove_left, auto remove_right,\
    \ auto eval) {\n        sort(queries_.begin(), queries_.end());\n        auto\
    \ l = 0, r = 0;\n        for (auto [left, right, index, order] : queries_) {\n\
    \            while (left < l) {\n                add_left(--l);\n            }\n\
    \            while (r < right) {\n                add_right(r++);\n          \
    \  }\n            while (l < left) {\n                remove_left(l++);\n    \
    \        }\n            while (right < r) {\n                remove_right(--r);\n\
    \            }\n            eval(index);\n        }\n    }\n\nprivate:\n    struct\
    \ query {\n        int left, right, index;\n        long long order;\n       \
    \ bool operator<(const query &other) const { return order < other.order; }\n \
    \   };\n    long long hilbert_order(int x, int y) const {\n        long long d\
    \ = 0;\n        for (int s = 1 << log_; s > 0; s >>= 1) {\n            bool rx\
    \ = x & s, ry = y & s;\n            d = (d << 2) | ((rx * 3) ^ ry);\n        \
    \    if (!ry) {\n                if (rx) {\n                    x = ~x;\n    \
    \                y = ~y;\n                }\n                std::swap(x, y);\n\
    \            }\n        }\n        return d;\n    }\n    std::vector<query> queries_;\n\
    \    const int n_, log_;\n};\n\n\n#line 7 \"mo/mo_tree.hpp\"\n#include <utility>\n\
    #line 9 \"mo/mo_tree.hpp\"\n\nstruct MoTree {\n    explicit MoTree(const std::vector<std::vector<int>>\
    \ &adj)\n        : n_(int(adj.size())), in_(n_), tour_(2 * n_), top_(n_), parent_(n_),\
    \ mo_(2 * n_) {\n        auto timer = 0;\n        std::vector<int> size(n_, 1),\
    \ heavy(n_, -1);\n        auto dfs = [&](auto &&self, int u) -> void {\n     \
    \       for (auto v : adj[u]) {\n                if (v != parent_[u]) {\n    \
    \                parent_[v] = u;\n                    self(self, v);\n       \
    \             size[u] += size[v];\n                    if (heavy[u] == -1 || size[heavy[u]]\
    \ < size[v]) {\n                        heavy[u] = v;\n                    }\n\
    \                }\n            }\n        };\n        auto hld = [&](auto &&self,\
    \ int u) -> void {\n            in_[u] = timer;\n            tour_[timer++] =\
    \ u;\n            for (auto v : adj[u]) {\n                if (v != parent_[u])\
    \ {\n                    top_[v] = (v == heavy[u]) ? top_[u] : v;\n          \
    \          self(self, v);\n                }\n            }\n            tour_[timer++]\
    \ = u;\n        };\n        dfs(dfs, 0);\n        hld(hld, 0);\n    }\n    int\
    \ lca(int u, int v) const {\n        assert(0 <= u && u < n_ && 0 <= v && v <=\
    \ n_);\n        while (top_[u] != top_[v]) {\n            if (in_[top_[u]] < in_[top_[v]])\
    \ {\n                std::swap(u, v);\n            }\n            u = parent_[top_[u]];\n\
    \        }\n        return (in_[u] < in_[v]) ? u : v;\n    }\n    void add(int\
    \ u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v && v <= n_);\n      \
    \  lca_.push_back(lca(u, v));\n        auto [l, r] = std::minmax(in_[u], in_[v]);\n\
    \        mo_.add(l + 1, r + 1);\n    }\n    void solve(auto add, auto remove,\
    \ auto eval) {\n        std::vector<bool> contains(n_);\n        auto toggle =\
    \ [&](int i) {\n            auto u = tour_[i];\n            if (contains[u]) {\n\
    \                remove(u);\n            } else {\n                add(u);\n \
    \           }\n            contains[u].flip();\n        };\n        auto eval_lca\
    \ = [&](int i) {\n            toggle(in_[lca_[i]]);\n            eval(i);\n  \
    \          toggle(in_[lca_[i]]);\n        };\n        mo_.solve(toggle, toggle,\
    \ eval_lca);\n    }\n\nprivate:\n    int n_;\n    std::vector<int> in_, tour_,\
    \ top_, parent_, lca_;\n    HilbertMo mo_;\n};\n\n\n"
  code: "#ifndef MO_TREE_HPP\n#define MO_TREE_HPP\n\n#include \"mo/hilbert_mo.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \nstruct MoTree {\n    explicit MoTree(const std::vector<std::vector<int>> &adj)\n\
    \        : n_(int(adj.size())), in_(n_), tour_(2 * n_), top_(n_), parent_(n_),\
    \ mo_(2 * n_) {\n        auto timer = 0;\n        std::vector<int> size(n_, 1),\
    \ heavy(n_, -1);\n        auto dfs = [&](auto &&self, int u) -> void {\n     \
    \       for (auto v : adj[u]) {\n                if (v != parent_[u]) {\n    \
    \                parent_[v] = u;\n                    self(self, v);\n       \
    \             size[u] += size[v];\n                    if (heavy[u] == -1 || size[heavy[u]]\
    \ < size[v]) {\n                        heavy[u] = v;\n                    }\n\
    \                }\n            }\n        };\n        auto hld = [&](auto &&self,\
    \ int u) -> void {\n            in_[u] = timer;\n            tour_[timer++] =\
    \ u;\n            for (auto v : adj[u]) {\n                if (v != parent_[u])\
    \ {\n                    top_[v] = (v == heavy[u]) ? top_[u] : v;\n          \
    \          self(self, v);\n                }\n            }\n            tour_[timer++]\
    \ = u;\n        };\n        dfs(dfs, 0);\n        hld(hld, 0);\n    }\n    int\
    \ lca(int u, int v) const {\n        assert(0 <= u && u < n_ && 0 <= v && v <=\
    \ n_);\n        while (top_[u] != top_[v]) {\n            if (in_[top_[u]] < in_[top_[v]])\
    \ {\n                std::swap(u, v);\n            }\n            u = parent_[top_[u]];\n\
    \        }\n        return (in_[u] < in_[v]) ? u : v;\n    }\n    void add(int\
    \ u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v && v <= n_);\n      \
    \  lca_.push_back(lca(u, v));\n        auto [l, r] = std::minmax(in_[u], in_[v]);\n\
    \        mo_.add(l + 1, r + 1);\n    }\n    void solve(auto add, auto remove,\
    \ auto eval) {\n        std::vector<bool> contains(n_);\n        auto toggle =\
    \ [&](int i) {\n            auto u = tour_[i];\n            if (contains[u]) {\n\
    \                remove(u);\n            } else {\n                add(u);\n \
    \           }\n            contains[u].flip();\n        };\n        auto eval_lca\
    \ = [&](int i) {\n            toggle(in_[lca_[i]]);\n            eval(i);\n  \
    \          toggle(in_[lca_[i]]);\n        };\n        mo_.solve(toggle, toggle,\
    \ eval_lca);\n    }\n\nprivate:\n    int n_;\n    std::vector<int> in_, tour_,\
    \ top_, parent_, lca_;\n    HilbertMo mo_;\n};\n\n#endif // MO_TREE_HPP"
  dependsOn:
  - mo/hilbert_mo.hpp
  isVerificationFile: false
  path: mo/mo_tree.hpp
  requiredBy: []
  timestamp: '2026-02-26 17:56:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/mo/aoj0489.test.cpp
  - test/mo/aoj2270.test.cpp
documentation_of: mo/mo_tree.hpp
layout: document
redirect_from:
- /library/mo/mo_tree.hpp
- /library/mo/mo_tree.hpp.html
title: mo/mo_tree.hpp
---
