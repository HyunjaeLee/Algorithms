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
  bundledCode: "#line 1 \"treap/lazy_implicit_treap.hpp\"\n\n\n\n#include <array>\n\
    #include <cassert>\n#include <initializer_list>\n#include <utility>\n#include\
    \ <vector>\n\ntemplate <typename S, S (*op)(S, S), S (*e)(), typename F, S (*mapping)(F,\
    \ S),\n          F (*composition)(F, F), F (*id)(), typename Generator>\nstruct\
    \ lazy_implicit_treap {\n    lazy_implicit_treap() = default;\n    explicit lazy_implicit_treap(typename\
    \ Generator::result_type seed)\n        : gen_(seed) {}\n    // Split into [0,\
    \ pos), [pos, inf)\n    std::array<int, 2> split(int u, int pos) {\n        if\
    \ (!~u) {\n            return {-1, -1};\n        }\n        push(u);\n       \
    \ if (size(nodes_[u].children[0]) < pos) {\n            auto [left, right] = split(nodes_[u].children[1],\n\
    \                                       pos - size(nodes_[u].children[0]) - 1);\n\
    \            nodes_[u].children[1] = left;\n            return {update(u), right};\n\
    \        } else {\n            auto [left, right] = split(nodes_[u].children[0],\
    \ pos);\n            nodes_[u].children[0] = right;\n            return {left,\
    \ update(u)};\n        }\n    }\n    // Split into [0, pos[0]), [pos[0], pos[1]),\n\
    \    // ..., [pos[n-2], pos[n-1]), [pos[n-1], inf)\n    std::vector<int> split(int\
    \ u, std::initializer_list<int> ilist) {\n        auto n = static_cast<int>(ilist.size());\n\
    \        assert(n > 0);\n        assert(~u);\n        std::vector<int> result(n\
    \ + 1), pos(ilist);\n        result[0] = u;\n        for (auto i = n - 1; i >=\
    \ 1; --i) {\n            pos[i] -= pos[i - 1];\n        }\n        for (auto i\
    \ = 0; i < n; ++i) {\n            auto [left, right] = split(result[i], pos[i]);\n\
    \            result[i] = left;\n            result[i + 1] = right;\n        }\n\
    \        return result;\n    }\n    int merge(int u, int v) {\n        if (!~u\
    \ || !~v) {\n            return ~u ? u : v;\n        }\n        if (nodes_[u].priority\
    \ < nodes_[v].priority) {\n            push(u);\n            nodes_[u].children[1]\
    \ = merge(nodes_[u].children[1], v);\n            return update(u);\n        }\
    \ else {\n            push(v);\n            nodes_[v].children[0] = merge(u, nodes_[v].children[0]);\n\
    \            return update(v);\n        }\n    }\n    int merge(std::initializer_list<int>\
    \ ilist) {\n        auto u = -1;\n        for (auto v : ilist) {\n           \
    \ u = merge(u, v);\n        }\n        return u;\n    }\n    // Inserts value\
    \ before pos\n    int insert(int u, int pos, const S &value) {\n        assert(0\
    \ <= pos && pos <= size(u));\n        auto v = static_cast<int>(nodes_.size());\n\
    \        nodes_.emplace_back(value, gen_());\n        auto [left, right] = split(u,\
    \ pos);\n        return merge({left, v, right});\n    }\n    int push_back(int\
    \ u, const S &value) {\n        auto v = static_cast<int>(nodes_.size());\n  \
    \      nodes_.emplace_back(value, gen_());\n        return merge(u, v);\n    }\n\
    \    int erase(int u, int pos) {\n        assert(0 <= pos && pos < size(u));\n\
    \        auto v = split(u, {pos, pos+1});\n        return merge(v[0], v[2]);\n\
    \    }\n    S get(int u, int pos) {\n        assert(~u && !~nodes_[u].parent);\n\
    \        assert(0 <= pos && pos < size(u));\n        while (~u) {\n          \
    \  push(u);\n            if (size(nodes_[u].children[0]) < pos) {\n          \
    \      pos -= size(nodes_[u].children[0]) + 1;\n                u = nodes_[u].children[1];\n\
    \            } else if (pos < size(nodes_[u].children[0])) {\n               \
    \ u = nodes_[u].children[0];\n            } else {\n                break;\n \
    \           }\n        }\n        assert(~u);\n        return nodes_[u].value;\n\
    \    }\n    int set(int u, int pos, S value) {\n        assert(0 <= pos && pos\
    \ < size(u));\n        auto v = split(u, {pos, pos + 1});\n        nodes_[v[1]].value\
    \ = value;\n        return merge({v[0], v[1], v[2]});\n    }\n    int apply(int\
    \ u, int pos, F f) { return apply(u, pos, pos + 1, f); }\n    int apply(int u,\
    \ int l, int r, F f) {\n        assert(0 <= l && l <= r && r <= size(u));\n  \
    \      auto v = split(u, {l, r});\n        all_apply(v[1], f);\n        return\
    \ merge({v[0], v[1], v[2]});\n    }\n    S all_prod(int u) const { return ~u ?\
    \ nodes_[u].subtree_sum : e(); }\n    std::pair<int, S> prod(int u, int l, int\
    \ r) {\n        auto v = split(u, {l, r});\n        auto result = all_prod(v[1]);\n\
    \        return {merge({v[0], v[1], v[2]}), result};\n    }\n    int reverse(int\
    \ u) {\n        if (~u) {\n            nodes_[u].reversed ^= true;\n        }\n\
    \        return u;\n    }\n    int reverse(int u, int l, int r) {\n        assert(0\
    \ <= l && l <= r && r <= size(u));\n        auto v = split(u, {l, r});\n     \
    \   reverse(v[1]);\n        return merge({v[0], v[1], v[2]});\n    }\n    void\
    \ reserve(std::vector<int>::size_type n) { nodes_.reserve(n); }\n    int size(int\
    \ u) const { return ~u ? nodes_[u].subtree_size : 0; }\n    template <typename\
    \ Function> void for_each(int u, Function f) {\n        if (~u) {\n          \
    \  push(u);\n            for_each(nodes_[u].children[0], f);\n            f(nodes_[u].value);\n\
    \            for_each(nodes_[u].children[1], f);\n        }\n    }\n\nprivate:\n\
    \    int update(int u) {\n        if (!~u) {\n            return u;\n        }\n\
    \        nodes_[u].parent = -1;\n        nodes_[u].subtree_size = 1;\n       \
    \ for (auto v : nodes_[u].children) {\n            if (~v) {\n               \
    \ nodes_[v].parent = u;\n                nodes_[u].subtree_size += nodes_[v].subtree_size;\n\
    \            }\n        }\n        nodes_[u].subtree_sum =\n                ~nodes_[u].children[0]\n\
    \                ? op(nodes_[nodes_[u].children[0]].subtree_sum, nodes_[u].value)\n\
    \                : nodes_[u].value;\n        nodes_[u].subtree_sum =\n       \
    \         ~nodes_[u].children[1]\n                ? op(nodes_[u].subtree_sum,\
    \ nodes_[nodes_[u].children[1]].subtree_sum)\n                : nodes_[u].subtree_sum;\n\
    \        return u;\n    }\n    void push(int u) {\n        if (!~u) {\n      \
    \      return;\n        }\n        all_apply(nodes_[u].children[0], nodes_[u].lazy);\n\
    \        all_apply(nodes_[u].children[1], nodes_[u].lazy);\n        nodes_[u].lazy\
    \ = id();\n        if (nodes_[u].reversed) {\n            for (auto v : nodes_[u].children)\
    \ {\n                if (~v) {\n                    nodes_[v].reversed ^= true;\n\
    \                }\n            }\n            std::swap(nodes_[u].children[0],\
    \ nodes_[u].children[1]);\n            nodes_[u].reversed = false;\n        }\n\
    \    }\n    void all_apply(int u, F f) {\n        if (~u) {\n            nodes_[u].value\
    \ = mapping(f, nodes_[u].value);\n            nodes_[u].subtree_sum = mapping(f,\
    \ nodes_[u].subtree_sum);\n            nodes_[u].lazy = composition(f, nodes_[u].lazy);\n\
    \        }\n    }\n    struct node {\n        node(const S &value_, typename Generator::result_type\
    \ priority_)\n            : value(value_), subtree_sum(value_), priority(priority_)\
    \ {}\n        S value;\n        S subtree_sum;\n        F lazy = id();\n     \
    \   typename Generator::result_type priority;\n        bool reversed = false;\n\
    \        int parent = -1;\n        int subtree_size = 1;\n        std::array<int,\
    \ 2> children{-1, -1};\n    };\n    Generator gen_;\n    std::vector<node> nodes_;\n\
    };\n\n\n"
  code: "#ifndef LAZY_IMPLICIT_TREAP\n#define LAZY_IMPLICIT_TREAP\n\n#include <array>\n\
    #include <cassert>\n#include <initializer_list>\n#include <utility>\n#include\
    \ <vector>\n\ntemplate <typename S, S (*op)(S, S), S (*e)(), typename F, S (*mapping)(F,\
    \ S),\n          F (*composition)(F, F), F (*id)(), typename Generator>\nstruct\
    \ lazy_implicit_treap {\n    lazy_implicit_treap() = default;\n    explicit lazy_implicit_treap(typename\
    \ Generator::result_type seed)\n        : gen_(seed) {}\n    // Split into [0,\
    \ pos), [pos, inf)\n    std::array<int, 2> split(int u, int pos) {\n        if\
    \ (!~u) {\n            return {-1, -1};\n        }\n        push(u);\n       \
    \ if (size(nodes_[u].children[0]) < pos) {\n            auto [left, right] = split(nodes_[u].children[1],\n\
    \                                       pos - size(nodes_[u].children[0]) - 1);\n\
    \            nodes_[u].children[1] = left;\n            return {update(u), right};\n\
    \        } else {\n            auto [left, right] = split(nodes_[u].children[0],\
    \ pos);\n            nodes_[u].children[0] = right;\n            return {left,\
    \ update(u)};\n        }\n    }\n    // Split into [0, pos[0]), [pos[0], pos[1]),\n\
    \    // ..., [pos[n-2], pos[n-1]), [pos[n-1], inf)\n    std::vector<int> split(int\
    \ u, std::initializer_list<int> ilist) {\n        auto n = static_cast<int>(ilist.size());\n\
    \        assert(n > 0);\n        assert(~u);\n        std::vector<int> result(n\
    \ + 1), pos(ilist);\n        result[0] = u;\n        for (auto i = n - 1; i >=\
    \ 1; --i) {\n            pos[i] -= pos[i - 1];\n        }\n        for (auto i\
    \ = 0; i < n; ++i) {\n            auto [left, right] = split(result[i], pos[i]);\n\
    \            result[i] = left;\n            result[i + 1] = right;\n        }\n\
    \        return result;\n    }\n    int merge(int u, int v) {\n        if (!~u\
    \ || !~v) {\n            return ~u ? u : v;\n        }\n        if (nodes_[u].priority\
    \ < nodes_[v].priority) {\n            push(u);\n            nodes_[u].children[1]\
    \ = merge(nodes_[u].children[1], v);\n            return update(u);\n        }\
    \ else {\n            push(v);\n            nodes_[v].children[0] = merge(u, nodes_[v].children[0]);\n\
    \            return update(v);\n        }\n    }\n    int merge(std::initializer_list<int>\
    \ ilist) {\n        auto u = -1;\n        for (auto v : ilist) {\n           \
    \ u = merge(u, v);\n        }\n        return u;\n    }\n    // Inserts value\
    \ before pos\n    int insert(int u, int pos, const S &value) {\n        assert(0\
    \ <= pos && pos <= size(u));\n        auto v = static_cast<int>(nodes_.size());\n\
    \        nodes_.emplace_back(value, gen_());\n        auto [left, right] = split(u,\
    \ pos);\n        return merge({left, v, right});\n    }\n    int push_back(int\
    \ u, const S &value) {\n        auto v = static_cast<int>(nodes_.size());\n  \
    \      nodes_.emplace_back(value, gen_());\n        return merge(u, v);\n    }\n\
    \    int erase(int u, int pos) {\n        assert(0 <= pos && pos < size(u));\n\
    \        auto v = split(u, {pos, pos+1});\n        return merge(v[0], v[2]);\n\
    \    }\n    S get(int u, int pos) {\n        assert(~u && !~nodes_[u].parent);\n\
    \        assert(0 <= pos && pos < size(u));\n        while (~u) {\n          \
    \  push(u);\n            if (size(nodes_[u].children[0]) < pos) {\n          \
    \      pos -= size(nodes_[u].children[0]) + 1;\n                u = nodes_[u].children[1];\n\
    \            } else if (pos < size(nodes_[u].children[0])) {\n               \
    \ u = nodes_[u].children[0];\n            } else {\n                break;\n \
    \           }\n        }\n        assert(~u);\n        return nodes_[u].value;\n\
    \    }\n    int set(int u, int pos, S value) {\n        assert(0 <= pos && pos\
    \ < size(u));\n        auto v = split(u, {pos, pos + 1});\n        nodes_[v[1]].value\
    \ = value;\n        return merge({v[0], v[1], v[2]});\n    }\n    int apply(int\
    \ u, int pos, F f) { return apply(u, pos, pos + 1, f); }\n    int apply(int u,\
    \ int l, int r, F f) {\n        assert(0 <= l && l <= r && r <= size(u));\n  \
    \      auto v = split(u, {l, r});\n        all_apply(v[1], f);\n        return\
    \ merge({v[0], v[1], v[2]});\n    }\n    S all_prod(int u) const { return ~u ?\
    \ nodes_[u].subtree_sum : e(); }\n    std::pair<int, S> prod(int u, int l, int\
    \ r) {\n        auto v = split(u, {l, r});\n        auto result = all_prod(v[1]);\n\
    \        return {merge({v[0], v[1], v[2]}), result};\n    }\n    int reverse(int\
    \ u) {\n        if (~u) {\n            nodes_[u].reversed ^= true;\n        }\n\
    \        return u;\n    }\n    int reverse(int u, int l, int r) {\n        assert(0\
    \ <= l && l <= r && r <= size(u));\n        auto v = split(u, {l, r});\n     \
    \   reverse(v[1]);\n        return merge({v[0], v[1], v[2]});\n    }\n    void\
    \ reserve(std::vector<int>::size_type n) { nodes_.reserve(n); }\n    int size(int\
    \ u) const { return ~u ? nodes_[u].subtree_size : 0; }\n    template <typename\
    \ Function> void for_each(int u, Function f) {\n        if (~u) {\n          \
    \  push(u);\n            for_each(nodes_[u].children[0], f);\n            f(nodes_[u].value);\n\
    \            for_each(nodes_[u].children[1], f);\n        }\n    }\n\nprivate:\n\
    \    int update(int u) {\n        if (!~u) {\n            return u;\n        }\n\
    \        nodes_[u].parent = -1;\n        nodes_[u].subtree_size = 1;\n       \
    \ for (auto v : nodes_[u].children) {\n            if (~v) {\n               \
    \ nodes_[v].parent = u;\n                nodes_[u].subtree_size += nodes_[v].subtree_size;\n\
    \            }\n        }\n        nodes_[u].subtree_sum =\n                ~nodes_[u].children[0]\n\
    \                ? op(nodes_[nodes_[u].children[0]].subtree_sum, nodes_[u].value)\n\
    \                : nodes_[u].value;\n        nodes_[u].subtree_sum =\n       \
    \         ~nodes_[u].children[1]\n                ? op(nodes_[u].subtree_sum,\
    \ nodes_[nodes_[u].children[1]].subtree_sum)\n                : nodes_[u].subtree_sum;\n\
    \        return u;\n    }\n    void push(int u) {\n        if (!~u) {\n      \
    \      return;\n        }\n        all_apply(nodes_[u].children[0], nodes_[u].lazy);\n\
    \        all_apply(nodes_[u].children[1], nodes_[u].lazy);\n        nodes_[u].lazy\
    \ = id();\n        if (nodes_[u].reversed) {\n            for (auto v : nodes_[u].children)\
    \ {\n                if (~v) {\n                    nodes_[v].reversed ^= true;\n\
    \                }\n            }\n            std::swap(nodes_[u].children[0],\
    \ nodes_[u].children[1]);\n            nodes_[u].reversed = false;\n        }\n\
    \    }\n    void all_apply(int u, F f) {\n        if (~u) {\n            nodes_[u].value\
    \ = mapping(f, nodes_[u].value);\n            nodes_[u].subtree_sum = mapping(f,\
    \ nodes_[u].subtree_sum);\n            nodes_[u].lazy = composition(f, nodes_[u].lazy);\n\
    \        }\n    }\n    struct node {\n        node(const S &value_, typename Generator::result_type\
    \ priority_)\n            : value(value_), subtree_sum(value_), priority(priority_)\
    \ {}\n        S value;\n        S subtree_sum;\n        F lazy = id();\n     \
    \   typename Generator::result_type priority;\n        bool reversed = false;\n\
    \        int parent = -1;\n        int subtree_size = 1;\n        std::array<int,\
    \ 2> children{-1, -1};\n    };\n    Generator gen_;\n    std::vector<node> nodes_;\n\
    };\n\n#endif // LAZY_IMPLICIT_TREAP"
  dependsOn: []
  isVerificationFile: false
  path: treap/lazy_implicit_treap.hpp
  requiredBy: []
  timestamp: '2022-08-31 18:46:27+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: treap/lazy_implicit_treap.hpp
layout: document
redirect_from:
- /library/treap/lazy_implicit_treap.hpp
- /library/treap/lazy_implicit_treap.hpp.html
title: treap/lazy_implicit_treap.hpp
---
