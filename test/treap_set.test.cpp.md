---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: random/splitmix64.hpp
    title: splitmix64
  - icon: ':heavy_check_mark:'
    path: random/xoshiro256starstar.hpp
    title: xoshiro256**
  - icon: ':heavy_check_mark:'
    path: treap/treap_set.hpp
    title: treap/treap_set.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_A
  bundledCode: "#line 1 \"test/treap_set.test.cpp\"\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_A\"\
    \n\n#line 1 \"random/xoshiro256starstar.hpp\"\n\n\n\n#line 1 \"random/splitmix64.hpp\"\
    \n\n\n\n#include <cstdint>\n#include <limits>\n\nstruct splitmix64 {\npublic:\n\
    \    using result_type = std::uint64_t;\n    splitmix64(std::uint64_t seed = 0)\
    \ : x(seed) {}\n    std::uint64_t operator()() {\n        std::uint64_t z = (x\
    \ += 0x9e3779b97f4a7c15);\n        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n        return z ^ (z >> 31);\n\
    \    }\n    static constexpr std::uint64_t min() {\n        return std::numeric_limits<std::uint64_t>::min();\n\
    \    }\n    static constexpr std::uint64_t max() {\n        return std::numeric_limits<std::uint64_t>::max();\n\
    \    }\n\nprivate:\n    std::uint64_t x; // The state can be seeded with any value.\n\
    };\n\n\n#line 5 \"random/xoshiro256starstar.hpp\"\n#include <array>\n#line 8 \"\
    random/xoshiro256starstar.hpp\"\n\nstruct xoshiro256starstar {\npublic:\n    using\
    \ result_type = std::uint64_t;\n    xoshiro256starstar(std::uint64_t seed = 0)\
    \ {\n        splitmix64 g(seed);\n        for (auto &x : s) {\n            x =\
    \ g();\n        }\n    }\n    std::uint64_t operator()() {\n        const std::uint64_t\
    \ result = rotl(s[1] * 5, 7) * 9;\n        const std::uint64_t t = s[1] << 17;\n\
    \        s[2] ^= s[0];\n        s[3] ^= s[1];\n        s[1] ^= s[2];\n       \
    \ s[0] ^= s[3];\n        s[2] ^= t;\n        s[3] = rotl(s[3], 45);\n        return\
    \ result;\n    }\n    static constexpr std::uint64_t min() {\n        return std::numeric_limits<std::uint64_t>::min();\n\
    \    }\n    static constexpr std::uint64_t max() {\n        return std::numeric_limits<std::uint64_t>::max();\n\
    \    }\n\nprivate:\n    static std::uint64_t rotl(const std::uint64_t x, int k)\
    \ {\n        return (x << k) | (x >> (64 - k));\n    }\n    std::array<std::uint64_t,\
    \ 4> s;\n};\n\n\n#line 1 \"treap/treap_set.hpp\"\n\n\n\n#line 5 \"treap/treap_set.hpp\"\
    \n#include <cassert>\n#include <vector>\n\ntemplate <typename Key, typename Generator>\
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
    };\n\n\n#line 5 \"test/treap_set.test.cpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int q;\n    std::cin >> q;\n\
    \    treap_set<int, xoshiro256starstar> s;\n    while (q--) {\n        int t,\
    \ x;\n        std::cin >> t >> x;\n        if (t == 0) {\n            s.insert(x);\n\
    \            std::cout << s.size() << '\\n';\n        } else {\n            std::cout\
    \ << (s.contains(x) ? 1 : 0) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_A\"\
    \n\n#include \"../random/xoshiro256starstar.hpp\"\n#include \"../treap/treap_set.hpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int q;\n    std::cin >> q;\n    treap_set<int, xoshiro256starstar> s;\n \
    \   while (q--) {\n        int t, x;\n        std::cin >> t >> x;\n        if\
    \ (t == 0) {\n            s.insert(x);\n            std::cout << s.size() << '\\\
    n';\n        } else {\n            std::cout << (s.contains(x) ? 1 : 0) << '\\\
    n';\n        }\n    }\n}\n"
  dependsOn:
  - random/xoshiro256starstar.hpp
  - random/splitmix64.hpp
  - treap/treap_set.hpp
  isVerificationFile: true
  path: test/treap_set.test.cpp
  requiredBy: []
  timestamp: '2022-08-31 18:46:27+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/treap_set.test.cpp
layout: document
redirect_from:
- /verify/test/treap_set.test.cpp
- /verify/test/treap_set.test.cpp.html
title: test/treap_set.test.cpp
---
