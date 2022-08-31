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
  bundledCode: "#line 1 \"treap/implicit_treap.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cassert>\n#include <initializer_list>\n#include <vector>\n\ntemplate <typename\
    \ T, typename Generator> struct implicit_treap {\n    implicit_treap() = default;\n\
    \    explicit implicit_treap(typename Generator::result_type seed)\n        :\
    \ gen_(seed) {}\n    // Split into [0, pos), [pos, inf)\n    std::array<int, 2>\
    \ split(int u, int pos) {\n        if (!~u) {\n            return {-1, -1};\n\
    \        }\n        if (size(nodes_[u].children[0]) < pos) {\n            auto\
    \ [left, right] = split(nodes_[u].children[1],\n                             \
    \          pos - size(nodes_[u].children[0]) - 1);\n            nodes_[u].children[1]\
    \ = left;\n            return {update(u), right};\n        } else {\n        \
    \    auto [left, right] = split(nodes_[u].children[0], pos);\n            nodes_[u].children[0]\
    \ = right;\n            return {left, update(u)};\n        }\n    }\n    // Split\
    \ into [0, pos[0]), [pos[0], pos[1]),\n    // ..., [pos[n-2], pos[n-1]), [pos[n-1],\
    \ inf)\n    std::vector<int> split(int u, std::initializer_list<int> ilist) {\n\
    \        auto n = static_cast<int>(ilist.size());\n        assert(n > 0);\n  \
    \      assert(~u);\n        std::vector<int> result(n + 1), pos(ilist);\n    \
    \    result[0] = u;\n        for (auto i = n - 1; i >= 1; --i) {\n           \
    \ pos[i] -= pos[i - 1];\n        }\n        for (auto i = 0; i < n; ++i) {\n \
    \           auto [left, right] = split(result[i], pos[i]);\n            result[i]\
    \ = left;\n            result[i + 1] = right;\n        }\n        return result;\n\
    \    }\n    int merge(int u, int v) {\n        if (!~u || !~v) {\n           \
    \ return ~u ? u : v;\n        }\n        if (nodes_[u].priority < nodes_[v].priority)\
    \ {\n            nodes_[u].children[1] = merge(nodes_[u].children[1], v);\n  \
    \          return update(u);\n        } else {\n            nodes_[v].children[0]\
    \ = merge(u, nodes_[v].children[0]);\n            return update(v);\n        }\n\
    \    }\n    int merge(std::initializer_list<int> ilist) {\n        auto u = -1;\n\
    \        for (auto v : ilist) {\n            u = merge(u, v);\n        }\n   \
    \     return u;\n    }\n    // Inserts value before pos\n    int insert(int u,\
    \ int pos, const T &value) {\n        assert(0 <= pos && pos <= size(u));\n  \
    \      auto v = static_cast<int>(nodes_.size());\n        nodes_.emplace_back(value,\
    \ gen_());\n        auto [left, right] = split(u, pos);\n        return merge({left,\
    \ v, right});\n    }\n    int push_back(int u, const T &value) {\n        auto\
    \ v = static_cast<int>(nodes_.size());\n        nodes_.emplace_back(value, gen_());\n\
    \        return merge(u, v);\n    }\n    T &get(int u, int pos) {\n        assert(!~nodes_[u].parent);\n\
    \        assert(0 <= pos && pos < size(u));\n        while (~u) {\n          \
    \  if (size(nodes_[u].children[0]) < pos) {\n                pos -= size(nodes_[u].children[0])\
    \ + 1;\n                u = nodes_[u].children[1];\n            } else if (pos\
    \ < size(nodes_[u].children[0])) {\n                u = nodes_[u].children[0];\n\
    \            } else {\n                break;\n            }\n        }\n    \
    \    assert(~u);\n        return nodes_[u].value;\n    }\n    void reserve(std::vector<int>::size_type\
    \ n) { nodes_.reserve(n); }\n    int size(int u) const { return ~u ? nodes_[u].subtree_size\
    \ : 0; }\n    template <typename Function> void for_each(int u, Function f) const\
    \ {\n        if (~u) {\n            for_each(nodes_[u].children[0], f);\n    \
    \        f(nodes_[u].value);\n            for_each(nodes_[u].children[1], f);\n\
    \        }\n    }\n\nprivate:\n    int update(int u) {\n        if (!~u) {\n \
    \           return u;\n        }\n        nodes_[u].parent = -1;\n        nodes_[u].subtree_size\
    \ = 1;\n        for (auto v : nodes_[u].children) {\n            if (~v) {\n \
    \               nodes_[v].parent = u;\n                nodes_[u].subtree_size\
    \ += nodes_[v].subtree_size;\n            }\n        }\n        return u;\n  \
    \  }\n    struct node {\n        node(const T &value, typename Generator::result_type\
    \ priority)\n            : value(value), priority(priority) {}\n        T value;\n\
    \        typename Generator::result_type priority;\n        int parent = -1;\n\
    \        int subtree_size = 1;\n        std::array<int, 2> children{-1, -1};\n\
    \    };\n    Generator gen_;\n    std::vector<node> nodes_;\n};\n\n\n"
  code: "#ifndef IMPLICIT_TREAP_HPP\n#define IMPLICIT_TREAP_HPP\n\n#include <array>\n\
    #include <cassert>\n#include <initializer_list>\n#include <vector>\n\ntemplate\
    \ <typename T, typename Generator> struct implicit_treap {\n    implicit_treap()\
    \ = default;\n    explicit implicit_treap(typename Generator::result_type seed)\n\
    \        : gen_(seed) {}\n    // Split into [0, pos), [pos, inf)\n    std::array<int,\
    \ 2> split(int u, int pos) {\n        if (!~u) {\n            return {-1, -1};\n\
    \        }\n        if (size(nodes_[u].children[0]) < pos) {\n            auto\
    \ [left, right] = split(nodes_[u].children[1],\n                             \
    \          pos - size(nodes_[u].children[0]) - 1);\n            nodes_[u].children[1]\
    \ = left;\n            return {update(u), right};\n        } else {\n        \
    \    auto [left, right] = split(nodes_[u].children[0], pos);\n            nodes_[u].children[0]\
    \ = right;\n            return {left, update(u)};\n        }\n    }\n    // Split\
    \ into [0, pos[0]), [pos[0], pos[1]),\n    // ..., [pos[n-2], pos[n-1]), [pos[n-1],\
    \ inf)\n    std::vector<int> split(int u, std::initializer_list<int> ilist) {\n\
    \        auto n = static_cast<int>(ilist.size());\n        assert(n > 0);\n  \
    \      assert(~u);\n        std::vector<int> result(n + 1), pos(ilist);\n    \
    \    result[0] = u;\n        for (auto i = n - 1; i >= 1; --i) {\n           \
    \ pos[i] -= pos[i - 1];\n        }\n        for (auto i = 0; i < n; ++i) {\n \
    \           auto [left, right] = split(result[i], pos[i]);\n            result[i]\
    \ = left;\n            result[i + 1] = right;\n        }\n        return result;\n\
    \    }\n    int merge(int u, int v) {\n        if (!~u || !~v) {\n           \
    \ return ~u ? u : v;\n        }\n        if (nodes_[u].priority < nodes_[v].priority)\
    \ {\n            nodes_[u].children[1] = merge(nodes_[u].children[1], v);\n  \
    \          return update(u);\n        } else {\n            nodes_[v].children[0]\
    \ = merge(u, nodes_[v].children[0]);\n            return update(v);\n        }\n\
    \    }\n    int merge(std::initializer_list<int> ilist) {\n        auto u = -1;\n\
    \        for (auto v : ilist) {\n            u = merge(u, v);\n        }\n   \
    \     return u;\n    }\n    // Inserts value before pos\n    int insert(int u,\
    \ int pos, const T &value) {\n        assert(0 <= pos && pos <= size(u));\n  \
    \      auto v = static_cast<int>(nodes_.size());\n        nodes_.emplace_back(value,\
    \ gen_());\n        auto [left, right] = split(u, pos);\n        return merge({left,\
    \ v, right});\n    }\n    int push_back(int u, const T &value) {\n        auto\
    \ v = static_cast<int>(nodes_.size());\n        nodes_.emplace_back(value, gen_());\n\
    \        return merge(u, v);\n    }\n    T &get(int u, int pos) {\n        assert(!~nodes_[u].parent);\n\
    \        assert(0 <= pos && pos < size(u));\n        while (~u) {\n          \
    \  if (size(nodes_[u].children[0]) < pos) {\n                pos -= size(nodes_[u].children[0])\
    \ + 1;\n                u = nodes_[u].children[1];\n            } else if (pos\
    \ < size(nodes_[u].children[0])) {\n                u = nodes_[u].children[0];\n\
    \            } else {\n                break;\n            }\n        }\n    \
    \    assert(~u);\n        return nodes_[u].value;\n    }\n    void reserve(std::vector<int>::size_type\
    \ n) { nodes_.reserve(n); }\n    int size(int u) const { return ~u ? nodes_[u].subtree_size\
    \ : 0; }\n    template <typename Function> void for_each(int u, Function f) const\
    \ {\n        if (~u) {\n            for_each(nodes_[u].children[0], f);\n    \
    \        f(nodes_[u].value);\n            for_each(nodes_[u].children[1], f);\n\
    \        }\n    }\n\nprivate:\n    int update(int u) {\n        if (!~u) {\n \
    \           return u;\n        }\n        nodes_[u].parent = -1;\n        nodes_[u].subtree_size\
    \ = 1;\n        for (auto v : nodes_[u].children) {\n            if (~v) {\n \
    \               nodes_[v].parent = u;\n                nodes_[u].subtree_size\
    \ += nodes_[v].subtree_size;\n            }\n        }\n        return u;\n  \
    \  }\n    struct node {\n        node(const T &value, typename Generator::result_type\
    \ priority)\n            : value(value), priority(priority) {}\n        T value;\n\
    \        typename Generator::result_type priority;\n        int parent = -1;\n\
    \        int subtree_size = 1;\n        std::array<int, 2> children{-1, -1};\n\
    \    };\n    Generator gen_;\n    std::vector<node> nodes_;\n};\n\n#endif // IMPLICIT_TREAP_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: treap/implicit_treap.hpp
  requiredBy: []
  timestamp: '2022-08-31 18:46:27+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: treap/implicit_treap.hpp
layout: document
redirect_from:
- /library/treap/implicit_treap.hpp
- /library/treap/implicit_treap.hpp.html
title: treap/implicit_treap.hpp
---
