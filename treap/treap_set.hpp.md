---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/treap_set.test.cpp
    title: test/treap_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"treap/treap_set.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename Key, typename Generator>\
    \ struct treap_set {\n    treap_set() = default;\n    explicit treap_set(typename\
    \ Generator::result_type seed) : gen_(seed) {}\n    bool insert(const Key &key)\
    \ {\n        if (contains(key)) {\n            return false;\n        }\n    \
    \    auto [left, right] = split(root_, key);\n        auto u = static_cast<int>(nodes_.size());\n\
    \        nodes_.emplace_back(key, gen_());\n        root_ = merge(merge(left,\
    \ u), right);\n        return true;\n    }\n    bool erase(const Key &key) {\n\
    \        if (!contains(key)) {\n            return false;\n        }\n       \
    \ root_ = erase(root_, key);\n        return true;\n    }\n    void reserve(int\
    \ n) {\n        nodes_.reserve(static_cast<std::vector<int>::size_type>(n));\n\
    \    }\n    const Key &find_by_order(int order) const {\n        assert(0 <= order\
    \ && order < size());\n        auto u = find_by_order(root_, order);\n       \
    \ assert(~u);\n        return nodes_[u].key;\n    }\n    int order_of_key(const\
    \ Key &key) const { return order_of_key(root_, key); }\n    bool contains(const\
    \ Key &key) const { return ~find(root_, key); }\n    int size() const { return\
    \ size(root_); }\n    template <typename Function> void for_each(Function f) const\
    \ {\n        for_each(root_, f);\n    }\n\nprivate:\n    // for all x in left\
    \ tree: x < key\n    // for all x in right tree: x >= key\n    std::array<int,\
    \ 2> split(int u, const Key &key) {\n        if (!~u) {\n            return {-1,\
    \ -1};\n        }\n        if (nodes_[u].key < key) {\n            auto [left,\
    \ right] = split(nodes_[u].children[1], key);\n            nodes_[u].children[1]\
    \ = left;\n            return {update(u), right};\n        } else {\n        \
    \    auto [left, right] = split(nodes_[u].children[0], key);\n            nodes_[u].children[0]\
    \ = right;\n            return {left, update(u)};\n        }\n    }\n    int merge(int\
    \ u, int v) {\n        if (!~u || !~v) {\n            return ~u ? u : v;\n   \
    \     }\n        if (nodes_[u].priority < nodes_[v].priority) {\n            nodes_[u].children[1]\
    \ = merge(nodes_[u].children[1], v);\n            return update(u);\n        }\
    \ else {\n            nodes_[v].children[0] = merge(u, nodes_[v].children[0]);\n\
    \            return update(v);\n        }\n    }\n    int update(int u) {\n  \
    \      if (!~u) {\n            return u;\n        }\n        nodes_[u].subtree_size\
    \ = 1;\n        for (auto v : nodes_[u].children) {\n            if (~v) {\n \
    \               nodes_[u].subtree_size += nodes_[v].subtree_size;\n          \
    \  }\n        }\n        return u;\n    }\n    int find(int u, const Key &key)\
    \ const {\n        while (~u) {\n            if (nodes_[u].key < key) {\n    \
    \            u = nodes_[u].children[1];\n            } else if (key < nodes_[u].key)\
    \ {\n                u = nodes_[u].children[0];\n            } else {\n      \
    \          break;\n            }\n        }\n        return u;\n    }\n    int\
    \ erase(int u, const Key &key) {\n        if (!~u) {\n            return -1;\n\
    \        }\n        if (nodes_[u].key < key) {\n            nodes_[u].children[1]\
    \ = erase(nodes_[u].children[1], key);\n            return update(u);\n      \
    \  } else if (key < nodes_[u].key) {\n            nodes_[u].children[0] = erase(nodes_[u].children[0],\
    \ key);\n            return update(u);\n        } else {\n            return merge(nodes_[u].children[0],\
    \ nodes_[u].children[1]);\n        }\n    }\n    int find_by_order(int u, int\
    \ order) const {\n        while (~u) {\n            if (size(nodes_[u].children[0])\
    \ < order) {\n                order -= size(nodes_[u].children[0]) + 1;\n    \
    \            u = nodes_[u].children[1];\n            } else if (order < size(nodes_[u].children[0]))\
    \ {\n                u = nodes_[u].children[0];\n            } else {\n      \
    \          break;\n            }\n        }\n        return u;\n    }\n    int\
    \ order_of_key(int u, const Key &key) const {\n        auto order = 0;\n     \
    \   while (~u) {\n            if (nodes_[u].key < key) {\n                order\
    \ += size(nodes_[u].children[0]) + 1;\n                u = nodes_[u].children[1];\n\
    \            } else {\n                u = nodes_[u].children[0];\n          \
    \  }\n        }\n        return order;\n    }\n    int size(int u) const { return\
    \ ~u ? nodes_[u].subtree_size : 0; }\n    template <typename Function> void for_each(int\
    \ u, Function f) const {\n        if (~u) {\n            for_each(nodes_[u].children[0],\
    \ f);\n            f(nodes_[u].key);\n            for_each(nodes_[u].children[1],\
    \ f);\n        }\n    }\n    struct node {\n        node(const Key &key, typename\
    \ Generator::result_type priority)\n            : key(key), priority(priority)\
    \ {}\n        Key key;\n        typename Generator::result_type priority;\n  \
    \      std::array<int, 2> children{-1, -1};\n        int subtree_size = 1;\n \
    \   };\n    Generator gen_;\n    std::vector<node> nodes_;\n    int root_ = -1;\n\
    };\n\n\n"
  code: "#ifndef TREAP_SET_HPP\n#define TREAP_SET_HPP\n\n#include <array>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename Key, typename Generator>\
    \ struct treap_set {\n    treap_set() = default;\n    explicit treap_set(typename\
    \ Generator::result_type seed) : gen_(seed) {}\n    bool insert(const Key &key)\
    \ {\n        if (contains(key)) {\n            return false;\n        }\n    \
    \    auto [left, right] = split(root_, key);\n        auto u = static_cast<int>(nodes_.size());\n\
    \        nodes_.emplace_back(key, gen_());\n        root_ = merge(merge(left,\
    \ u), right);\n        return true;\n    }\n    bool erase(const Key &key) {\n\
    \        if (!contains(key)) {\n            return false;\n        }\n       \
    \ root_ = erase(root_, key);\n        return true;\n    }\n    void reserve(int\
    \ n) {\n        nodes_.reserve(static_cast<std::vector<int>::size_type>(n));\n\
    \    }\n    const Key &find_by_order(int order) const {\n        assert(0 <= order\
    \ && order < size());\n        auto u = find_by_order(root_, order);\n       \
    \ assert(~u);\n        return nodes_[u].key;\n    }\n    int order_of_key(const\
    \ Key &key) const { return order_of_key(root_, key); }\n    bool contains(const\
    \ Key &key) const { return ~find(root_, key); }\n    int size() const { return\
    \ size(root_); }\n    template <typename Function> void for_each(Function f) const\
    \ {\n        for_each(root_, f);\n    }\n\nprivate:\n    // for all x in left\
    \ tree: x < key\n    // for all x in right tree: x >= key\n    std::array<int,\
    \ 2> split(int u, const Key &key) {\n        if (!~u) {\n            return {-1,\
    \ -1};\n        }\n        if (nodes_[u].key < key) {\n            auto [left,\
    \ right] = split(nodes_[u].children[1], key);\n            nodes_[u].children[1]\
    \ = left;\n            return {update(u), right};\n        } else {\n        \
    \    auto [left, right] = split(nodes_[u].children[0], key);\n            nodes_[u].children[0]\
    \ = right;\n            return {left, update(u)};\n        }\n    }\n    int merge(int\
    \ u, int v) {\n        if (!~u || !~v) {\n            return ~u ? u : v;\n   \
    \     }\n        if (nodes_[u].priority < nodes_[v].priority) {\n            nodes_[u].children[1]\
    \ = merge(nodes_[u].children[1], v);\n            return update(u);\n        }\
    \ else {\n            nodes_[v].children[0] = merge(u, nodes_[v].children[0]);\n\
    \            return update(v);\n        }\n    }\n    int update(int u) {\n  \
    \      if (!~u) {\n            return u;\n        }\n        nodes_[u].subtree_size\
    \ = 1;\n        for (auto v : nodes_[u].children) {\n            if (~v) {\n \
    \               nodes_[u].subtree_size += nodes_[v].subtree_size;\n          \
    \  }\n        }\n        return u;\n    }\n    int find(int u, const Key &key)\
    \ const {\n        while (~u) {\n            if (nodes_[u].key < key) {\n    \
    \            u = nodes_[u].children[1];\n            } else if (key < nodes_[u].key)\
    \ {\n                u = nodes_[u].children[0];\n            } else {\n      \
    \          break;\n            }\n        }\n        return u;\n    }\n    int\
    \ erase(int u, const Key &key) {\n        if (!~u) {\n            return -1;\n\
    \        }\n        if (nodes_[u].key < key) {\n            nodes_[u].children[1]\
    \ = erase(nodes_[u].children[1], key);\n            return update(u);\n      \
    \  } else if (key < nodes_[u].key) {\n            nodes_[u].children[0] = erase(nodes_[u].children[0],\
    \ key);\n            return update(u);\n        } else {\n            return merge(nodes_[u].children[0],\
    \ nodes_[u].children[1]);\n        }\n    }\n    int find_by_order(int u, int\
    \ order) const {\n        while (~u) {\n            if (size(nodes_[u].children[0])\
    \ < order) {\n                order -= size(nodes_[u].children[0]) + 1;\n    \
    \            u = nodes_[u].children[1];\n            } else if (order < size(nodes_[u].children[0]))\
    \ {\n                u = nodes_[u].children[0];\n            } else {\n      \
    \          break;\n            }\n        }\n        return u;\n    }\n    int\
    \ order_of_key(int u, const Key &key) const {\n        auto order = 0;\n     \
    \   while (~u) {\n            if (nodes_[u].key < key) {\n                order\
    \ += size(nodes_[u].children[0]) + 1;\n                u = nodes_[u].children[1];\n\
    \            } else {\n                u = nodes_[u].children[0];\n          \
    \  }\n        }\n        return order;\n    }\n    int size(int u) const { return\
    \ ~u ? nodes_[u].subtree_size : 0; }\n    template <typename Function> void for_each(int\
    \ u, Function f) const {\n        if (~u) {\n            for_each(nodes_[u].children[0],\
    \ f);\n            f(nodes_[u].key);\n            for_each(nodes_[u].children[1],\
    \ f);\n        }\n    }\n    struct node {\n        node(const Key &key, typename\
    \ Generator::result_type priority)\n            : key(key), priority(priority)\
    \ {}\n        Key key;\n        typename Generator::result_type priority;\n  \
    \      std::array<int, 2> children{-1, -1};\n        int subtree_size = 1;\n \
    \   };\n    Generator gen_;\n    std::vector<node> nodes_;\n    int root_ = -1;\n\
    };\n\n#endif // TREAP_SET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: treap/treap_set.hpp
  requiredBy: []
  timestamp: '2022-08-31 18:46:27+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/treap_set.test.cpp
documentation_of: treap/treap_set.hpp
layout: document
redirect_from:
- /library/treap/treap_set.hpp
- /library/treap/treap_set.hpp.html
title: treap/treap_set.hpp
---
