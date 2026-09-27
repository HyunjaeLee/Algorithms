---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/link_cut_tree/link_cut_tree.test.cpp
    title: test/link_cut_tree/link_cut_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"link_cut_tree/link_cut_tree.hpp\"\n\n\n\n#include <cassert>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\ntemplate <typename\
    \ S, auto op, auto e, auto toggle> struct link_cut_tree {\n    link_cut_tree(int\
    \ n)\n        : n_(n), left_(n, -1), right_(n, -1), parent_(n, -1), data_(n, e()),\
    \ sum_(n, e()),\n          reversed_(n, false) {}\n    int access(int u) {\n \
    \       assert(0 <= u && u < n_);\n        auto result = -1;\n        for (auto\
    \ cur = u; ~cur; cur = parent_[cur]) {\n            splay(cur);\n            right_[cur]\
    \ = result;\n            update(cur);\n            result = cur;\n        }\n\
    \        splay(u);\n        return result;\n    }\n    void make_root(int u) {\n\
    \        assert(0 <= u && u < n_);\n        access(u);\n        reverse(u);\n\
    \        push(u);\n    }\n    void link(int u, int p) {\n        assert(0 <= u\
    \ && u < n_ && 0 <= p && p < n_);\n        make_root(u);\n        access(p);\n\
    \        parent_[u] = p;\n        right_[p] = u;\n        update(p);\n    }\n\
    \    void cut(int u) {\n        assert(0 <= u && u < n_);\n        access(u);\n\
    \        auto p = left_[u];\n        left_[u] = -1;\n        update(u);\n    \
    \    parent_[p] = -1;\n    }\n    void cut(int u, int v) {\n        assert(0 <=\
    \ u && u < n_ && 0 <= v && v < n_);\n        make_root(u);\n        cut(v);\n\
    \    }\n    int lca(int u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v\
    \ && v < n_);\n        access(u);\n        return access(v);\n    }\n    void\
    \ set(int u, S x) {\n        assert(0 <= u && u < n_);\n        access(u);\n \
    \       data_[u] = x;\n        update(u);\n    }\n    S get(int u) {\n       \
    \ assert(0 <= u && u < n_);\n        access(u);\n        return data_[u];\n  \
    \  }\n    S prod(int u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v &&\
    \ v < n_);\n        make_root(u);\n        access(v);\n        return sum_[v];\n\
    \    }\n    bool connected(int u, int v) {\n        assert(0 <= u && u < n_ &&\
    \ 0 <= v && v < n_);\n        access(u);\n        access(v);\n        return u\
    \ == v || ~parent_[u];\n    }\n\nprivate:\n    bool is_root(int u) const {\n \
    \       auto p = parent_[u];\n        return !~p || (left_[p] != u && right_[p]\
    \ != u);\n    }\n    void update(int u) {\n        if (~u) {\n            sum_[u]\
    \ = data_[u];\n            if (auto v = left_[u]; ~v) {\n                sum_[u]\
    \ = op(sum_[v], sum_[u]);\n            }\n            if (auto v = right_[u];\
    \ ~v) {\n                sum_[u] = op(sum_[u], sum_[v]);\n            }\n    \
    \    }\n    }\n    void reverse(int u) {\n        if (~u) {\n            std::swap(left_[u],\
    \ right_[u]);\n            reversed_[u] = !reversed_[u];\n            sum_[u]\
    \ = toggle(sum_[u]);\n        }\n    }\n    void push(int u) {\n        if (~u)\
    \ {\n            if (reversed_[u]) {\n                reverse(left_[u]);\n   \
    \             reverse(right_[u]);\n                reversed_[u] = false;\n   \
    \         }\n        }\n    }\n    void rotate_right(int u) {\n        auto p\
    \ = parent_[u];\n        auto g = parent_[p];\n        if (left_[p] = right_[u];\
    \ ~left_[p]) {\n            parent_[right_[u]] = p;\n        }\n        right_[u]\
    \ = p;\n        parent_[p] = u;\n        update(p);\n        update(u);\n    \
    \    if (parent_[u] = g; ~parent_[u]) {\n            if (left_[g] == p) {\n  \
    \              left_[g] = u;\n            }\n            if (right_[g] == p) {\n\
    \                right_[g] = u;\n            }\n            update(g);\n     \
    \   }\n    }\n    void rotate_left(int u) {\n        auto p = parent_[u];\n  \
    \      auto g = parent_[p];\n        if (right_[p] = left_[u]; ~right_[p]) {\n\
    \            parent_[left_[u]] = p;\n        }\n        left_[u] = p;\n      \
    \  parent_[p] = u;\n        update(p);\n        update(u);\n        if (parent_[u]\
    \ = g; ~parent_[u]) {\n            if (left_[g] == p) {\n                left_[g]\
    \ = u;\n            }\n            if (right_[g] == p) {\n                right_[g]\
    \ = u;\n            }\n            update(g);\n        }\n    }\n    void splay(int\
    \ u) {\n        push(u);\n        while (!is_root(u)) {\n            auto p =\
    \ parent_[u];\n            if (is_root(p)) {\n                push(p);\n     \
    \           push(u);\n                if (left_[p] == u) {\n                 \
    \   rotate_right(u);\n                } else {\n                    rotate_left(u);\n\
    \                }\n            } else {\n                auto g = parent_[p];\n\
    \                push(g);\n                push(p);\n                push(u);\n\
    \                if (left_[g] == p) {\n                    if (left_[p] == u)\
    \ {\n                        rotate_right(p);\n                        rotate_right(u);\n\
    \                    } else {\n                        rotate_left(u);\n     \
    \                   rotate_right(u);\n                    }\n                }\
    \ else {\n                    if (right_[p] == u) {\n                        rotate_left(p);\n\
    \                        rotate_left(u);\n                    } else {\n     \
    \                   rotate_right(u);\n                        rotate_left(u);\n\
    \                    }\n                }\n            }\n        }\n    }\n \
    \   int n_;\n    std::vector<int> left_, right_, parent_;\n    std::vector<S>\
    \ data_, sum_;\n    std::vector<char> reversed_;\n};\n\n\n"
  code: "#ifndef LINK_CUT_TREE_HPP\n#define LINK_CUT_TREE_HPP\n\n#include <cassert>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\ntemplate <typename\
    \ S, auto op, auto e, auto toggle> struct link_cut_tree {\n    link_cut_tree(int\
    \ n)\n        : n_(n), left_(n, -1), right_(n, -1), parent_(n, -1), data_(n, e()),\
    \ sum_(n, e()),\n          reversed_(n, false) {}\n    int access(int u) {\n \
    \       assert(0 <= u && u < n_);\n        auto result = -1;\n        for (auto\
    \ cur = u; ~cur; cur = parent_[cur]) {\n            splay(cur);\n            right_[cur]\
    \ = result;\n            update(cur);\n            result = cur;\n        }\n\
    \        splay(u);\n        return result;\n    }\n    void make_root(int u) {\n\
    \        assert(0 <= u && u < n_);\n        access(u);\n        reverse(u);\n\
    \        push(u);\n    }\n    void link(int u, int p) {\n        assert(0 <= u\
    \ && u < n_ && 0 <= p && p < n_);\n        make_root(u);\n        access(p);\n\
    \        parent_[u] = p;\n        right_[p] = u;\n        update(p);\n    }\n\
    \    void cut(int u) {\n        assert(0 <= u && u < n_);\n        access(u);\n\
    \        auto p = left_[u];\n        left_[u] = -1;\n        update(u);\n    \
    \    parent_[p] = -1;\n    }\n    void cut(int u, int v) {\n        assert(0 <=\
    \ u && u < n_ && 0 <= v && v < n_);\n        make_root(u);\n        cut(v);\n\
    \    }\n    int lca(int u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v\
    \ && v < n_);\n        access(u);\n        return access(v);\n    }\n    void\
    \ set(int u, S x) {\n        assert(0 <= u && u < n_);\n        access(u);\n \
    \       data_[u] = x;\n        update(u);\n    }\n    S get(int u) {\n       \
    \ assert(0 <= u && u < n_);\n        access(u);\n        return data_[u];\n  \
    \  }\n    S prod(int u, int v) {\n        assert(0 <= u && u < n_ && 0 <= v &&\
    \ v < n_);\n        make_root(u);\n        access(v);\n        return sum_[v];\n\
    \    }\n    bool connected(int u, int v) {\n        assert(0 <= u && u < n_ &&\
    \ 0 <= v && v < n_);\n        access(u);\n        access(v);\n        return u\
    \ == v || ~parent_[u];\n    }\n\nprivate:\n    bool is_root(int u) const {\n \
    \       auto p = parent_[u];\n        return !~p || (left_[p] != u && right_[p]\
    \ != u);\n    }\n    void update(int u) {\n        if (~u) {\n            sum_[u]\
    \ = data_[u];\n            if (auto v = left_[u]; ~v) {\n                sum_[u]\
    \ = op(sum_[v], sum_[u]);\n            }\n            if (auto v = right_[u];\
    \ ~v) {\n                sum_[u] = op(sum_[u], sum_[v]);\n            }\n    \
    \    }\n    }\n    void reverse(int u) {\n        if (~u) {\n            std::swap(left_[u],\
    \ right_[u]);\n            reversed_[u] = !reversed_[u];\n            sum_[u]\
    \ = toggle(sum_[u]);\n        }\n    }\n    void push(int u) {\n        if (~u)\
    \ {\n            if (reversed_[u]) {\n                reverse(left_[u]);\n   \
    \             reverse(right_[u]);\n                reversed_[u] = false;\n   \
    \         }\n        }\n    }\n    void rotate_right(int u) {\n        auto p\
    \ = parent_[u];\n        auto g = parent_[p];\n        if (left_[p] = right_[u];\
    \ ~left_[p]) {\n            parent_[right_[u]] = p;\n        }\n        right_[u]\
    \ = p;\n        parent_[p] = u;\n        update(p);\n        update(u);\n    \
    \    if (parent_[u] = g; ~parent_[u]) {\n            if (left_[g] == p) {\n  \
    \              left_[g] = u;\n            }\n            if (right_[g] == p) {\n\
    \                right_[g] = u;\n            }\n            update(g);\n     \
    \   }\n    }\n    void rotate_left(int u) {\n        auto p = parent_[u];\n  \
    \      auto g = parent_[p];\n        if (right_[p] = left_[u]; ~right_[p]) {\n\
    \            parent_[left_[u]] = p;\n        }\n        left_[u] = p;\n      \
    \  parent_[p] = u;\n        update(p);\n        update(u);\n        if (parent_[u]\
    \ = g; ~parent_[u]) {\n            if (left_[g] == p) {\n                left_[g]\
    \ = u;\n            }\n            if (right_[g] == p) {\n                right_[g]\
    \ = u;\n            }\n            update(g);\n        }\n    }\n    void splay(int\
    \ u) {\n        push(u);\n        while (!is_root(u)) {\n            auto p =\
    \ parent_[u];\n            if (is_root(p)) {\n                push(p);\n     \
    \           push(u);\n                if (left_[p] == u) {\n                 \
    \   rotate_right(u);\n                } else {\n                    rotate_left(u);\n\
    \                }\n            } else {\n                auto g = parent_[p];\n\
    \                push(g);\n                push(p);\n                push(u);\n\
    \                if (left_[g] == p) {\n                    if (left_[p] == u)\
    \ {\n                        rotate_right(p);\n                        rotate_right(u);\n\
    \                    } else {\n                        rotate_left(u);\n     \
    \                   rotate_right(u);\n                    }\n                }\
    \ else {\n                    if (right_[p] == u) {\n                        rotate_left(p);\n\
    \                        rotate_left(u);\n                    } else {\n     \
    \                   rotate_right(u);\n                        rotate_left(u);\n\
    \                    }\n                }\n            }\n        }\n    }\n \
    \   int n_;\n    std::vector<int> left_, right_, parent_;\n    std::vector<S>\
    \ data_, sum_;\n    std::vector<char> reversed_;\n};\n\n#endif // LINK_CUT_TREE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: link_cut_tree/link_cut_tree.hpp
  requiredBy: []
  timestamp: '2026-01-04 02:17:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/link_cut_tree/link_cut_tree.test.cpp
  - test/link_cut_tree/dynamic_tree_vertex_set_path_composite.test.cpp
documentation_of: link_cut_tree/link_cut_tree.hpp
layout: document
redirect_from:
- /library/link_cut_tree/link_cut_tree.hpp
- /library/link_cut_tree/link_cut_tree.hpp.html
title: link_cut_tree/link_cut_tree.hpp
---
