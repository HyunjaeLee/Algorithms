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
  bundledCode: "#line 1 \"splay/splay_set.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <vector>\n\ntemplate <typename Key, typename Compare = std::less<Key>> struct\
    \ splay_set {\n    splay_set() : root_(-1), comp_(Compare()) {}\n    bool insert(const\
    \ Key &key) {\n        if (!~root_) {\n            root_ = new_node(key);\n  \
    \          return true;\n        }\n        auto u = root_, p = -1;\n        while\
    \ (~u) {\n            if (comp_(key, key_[u])) {\n                p = u;\n   \
    \             u = left_[u];\n            } else if (comp_(key_[u], key)) {\n \
    \               p = u;\n                u = right_[u];\n            } else {\n\
    \                break;\n            }\n        }\n        bool created = false;\n\
    \        if (!~u) {\n            created = true;\n            u = new_node(key);\n\
    \            parent_[u] = p;\n            (comp_(key, key_[p]) ? left_[p] : right_[p])\
    \ = u;\n        }\n        splay(u);\n        return created;\n    }\n    bool\
    \ erase(const Key &key) {\n        if (!~find(key)) {\n            return false;\n\
    \        }\n        auto l = left_[root_];\n        auto r = right_[root_];\n\
    \        if (~l && ~r) {\n            root_ = l;\n            parent_[l] = -1;\n\
    \            auto u = l;\n            while (~right_[u]) {\n                u\
    \ = right_[u];\n            }\n            right_[u] = r;\n            parent_[r]\
    \ = u;\n            update(u);\n            splay(u);\n        } else if (~l)\
    \ {\n            parent_[l] = -1;\n            root_ = l;\n        } else if (~r)\
    \ {\n            parent_[r] = -1;\n            root_ = r;\n        } else {\n\
    \            root_ = -1;\n        }\n        return true;\n    }\n    bool contains(const\
    \ Key &key) { return static_cast<bool>(~find(key)); }\n    int size() const {\
    \ return size(root_); }\n    template <typename Function> void for_each(Function\
    \ f) const {\n        for_each(root_, f);\n    }\n\nprivate:\n    void rotate(int\
    \ u) {\n        auto p = parent_[u];\n        auto b = -1;\n        if (u == left_[p])\
    \ {\n            left_[p] = b = right_[u];\n            right_[u] = p;\n     \
    \   } else {\n            right_[p] = b = left_[u];\n            left_[u] = p;\n\
    \        }\n        parent_[u] = parent_[p];\n        parent_[p] = u;\n      \
    \  if (~b) {\n            parent_[b] = p;\n        }\n        (~parent_[u]\n \
    \            ? (p == left_[parent_[u]] ? left_[parent_[u]] : right_[parent_[u]])\n\
    \             : root_) = u;\n        update(p);\n        update(u);\n    }\n \
    \   void splay(int u) {\n        if (!~u) {\n            return;\n        }\n\
    \        while (~parent_[u]) {\n            auto p = parent_[u];\n           \
    \ auto g = parent_[p];\n            if (~g) {\n                rotate(((u == left_[p])\
    \ == (p == left_[g])) ? p : u);\n            }\n            rotate(u);\n     \
    \   }\n        return;\n    }\n    void update(int u) {\n        if (~u) {\n \
    \           size_[u] = 1 + size(left_[u]) + size(right_[u]);\n        }\n    }\n\
    \    int new_node(const Key &key) {\n        auto u = static_cast<int>(key_.size());\n\
    \        key_.push_back(key);\n        size_.push_back(1);\n        left_.push_back(-1);\n\
    \        right_.push_back(-1);\n        parent_.push_back(-1);\n        return\
    \ u;\n    }\n    int find(const Key &key) {\n        auto u = root_, p = -1;\n\
    \        while (~u) {\n            if (comp_(key, key_[u])) {\n              \
    \  p = u;\n                u = left_[u];\n            } else if (comp_(key_[u],\
    \ key)) {\n                p = u;\n                u = right_[u];\n          \
    \  } else {\n                break;\n            }\n        }\n        splay(~u\
    \ ? u : p);\n        return u;\n    }\n    template <typename Function> void for_each(int\
    \ u, Function f) const {\n        if (~u) {\n            for_each(left_[u], f);\n\
    \            f(key_[u]);\n            for_each(right_[u], f);\n        }\n   \
    \ }\n    int size(int u) const { return ~u ? size_[u] : 0; }\n    std::vector<Key>\
    \ key_;\n    std::vector<int> size_, left_, right_, parent_;\n    int root_;\n\
    \    Compare comp_;\n};\n\n\n"
  code: "#ifndef SPLAY_SET_HPP\n#define SPLAY_SET_HPP\n\n#include <functional>\n#include\
    \ <vector>\n\ntemplate <typename Key, typename Compare = std::less<Key>> struct\
    \ splay_set {\n    splay_set() : root_(-1), comp_(Compare()) {}\n    bool insert(const\
    \ Key &key) {\n        if (!~root_) {\n            root_ = new_node(key);\n  \
    \          return true;\n        }\n        auto u = root_, p = -1;\n        while\
    \ (~u) {\n            if (comp_(key, key_[u])) {\n                p = u;\n   \
    \             u = left_[u];\n            } else if (comp_(key_[u], key)) {\n \
    \               p = u;\n                u = right_[u];\n            } else {\n\
    \                break;\n            }\n        }\n        bool created = false;\n\
    \        if (!~u) {\n            created = true;\n            u = new_node(key);\n\
    \            parent_[u] = p;\n            (comp_(key, key_[p]) ? left_[p] : right_[p])\
    \ = u;\n        }\n        splay(u);\n        return created;\n    }\n    bool\
    \ erase(const Key &key) {\n        if (!~find(key)) {\n            return false;\n\
    \        }\n        auto l = left_[root_];\n        auto r = right_[root_];\n\
    \        if (~l && ~r) {\n            root_ = l;\n            parent_[l] = -1;\n\
    \            auto u = l;\n            while (~right_[u]) {\n                u\
    \ = right_[u];\n            }\n            right_[u] = r;\n            parent_[r]\
    \ = u;\n            update(u);\n            splay(u);\n        } else if (~l)\
    \ {\n            parent_[l] = -1;\n            root_ = l;\n        } else if (~r)\
    \ {\n            parent_[r] = -1;\n            root_ = r;\n        } else {\n\
    \            root_ = -1;\n        }\n        return true;\n    }\n    bool contains(const\
    \ Key &key) { return static_cast<bool>(~find(key)); }\n    int size() const {\
    \ return size(root_); }\n    template <typename Function> void for_each(Function\
    \ f) const {\n        for_each(root_, f);\n    }\n\nprivate:\n    void rotate(int\
    \ u) {\n        auto p = parent_[u];\n        auto b = -1;\n        if (u == left_[p])\
    \ {\n            left_[p] = b = right_[u];\n            right_[u] = p;\n     \
    \   } else {\n            right_[p] = b = left_[u];\n            left_[u] = p;\n\
    \        }\n        parent_[u] = parent_[p];\n        parent_[p] = u;\n      \
    \  if (~b) {\n            parent_[b] = p;\n        }\n        (~parent_[u]\n \
    \            ? (p == left_[parent_[u]] ? left_[parent_[u]] : right_[parent_[u]])\n\
    \             : root_) = u;\n        update(p);\n        update(u);\n    }\n \
    \   void splay(int u) {\n        if (!~u) {\n            return;\n        }\n\
    \        while (~parent_[u]) {\n            auto p = parent_[u];\n           \
    \ auto g = parent_[p];\n            if (~g) {\n                rotate(((u == left_[p])\
    \ == (p == left_[g])) ? p : u);\n            }\n            rotate(u);\n     \
    \   }\n        return;\n    }\n    void update(int u) {\n        if (~u) {\n \
    \           size_[u] = 1 + size(left_[u]) + size(right_[u]);\n        }\n    }\n\
    \    int new_node(const Key &key) {\n        auto u = static_cast<int>(key_.size());\n\
    \        key_.push_back(key);\n        size_.push_back(1);\n        left_.push_back(-1);\n\
    \        right_.push_back(-1);\n        parent_.push_back(-1);\n        return\
    \ u;\n    }\n    int find(const Key &key) {\n        auto u = root_, p = -1;\n\
    \        while (~u) {\n            if (comp_(key, key_[u])) {\n              \
    \  p = u;\n                u = left_[u];\n            } else if (comp_(key_[u],\
    \ key)) {\n                p = u;\n                u = right_[u];\n          \
    \  } else {\n                break;\n            }\n        }\n        splay(~u\
    \ ? u : p);\n        return u;\n    }\n    template <typename Function> void for_each(int\
    \ u, Function f) const {\n        if (~u) {\n            for_each(left_[u], f);\n\
    \            f(key_[u]);\n            for_each(right_[u], f);\n        }\n   \
    \ }\n    int size(int u) const { return ~u ? size_[u] : 0; }\n    std::vector<Key>\
    \ key_;\n    std::vector<int> size_, left_, right_, parent_;\n    int root_;\n\
    \    Compare comp_;\n};\n\n#endif // SPLAY_SET_HPP"
  dependsOn: []
  isVerificationFile: false
  path: splay/splay_set.hpp
  requiredBy: []
  timestamp: '2022-09-11 18:08:14+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: splay/splay_set.hpp
layout: document
redirect_from:
- /library/splay/splay_set.hpp
- /library/splay/splay_set.hpp.html
title: splay/splay_set.hpp
---
