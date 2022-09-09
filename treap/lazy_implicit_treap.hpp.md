---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: random/splitmix64.hpp
    title: splitmix64
  - icon: ':heavy_check_mark:'
    path: random/xoshiro256starstar.hpp
    title: xoshiro256**
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"treap/lazy_implicit_treap.hpp\"\n\n\n\n#line 1 \"random/xoshiro256starstar.hpp\"\
    \n\n\n\n#line 1 \"random/splitmix64.hpp\"\n\n\n\n#include <cstdint>\n#include\
    \ <limits>\n\nstruct splitmix64 {\npublic:\n    using result_type = std::uint64_t;\n\
    \    splitmix64(std::uint64_t seed = 0) : x(seed) {}\n    std::uint64_t operator()()\
    \ {\n        std::uint64_t z = (x += 0x9e3779b97f4a7c15);\n        z = (z ^ (z\
    \ >> 30)) * 0xbf58476d1ce4e5b9;\n        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n\
    \        return z ^ (z >> 31);\n    }\n    static constexpr std::uint64_t min()\
    \ {\n        return std::numeric_limits<std::uint64_t>::min();\n    }\n    static\
    \ constexpr std::uint64_t max() {\n        return std::numeric_limits<std::uint64_t>::max();\n\
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
    \ 4> s;\n};\n\n\n#line 6 \"treap/lazy_implicit_treap.hpp\"\n#include <cassert>\n\
    #include <chrono>\n#include <initializer_list>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\nusing null_type = struct {};\n\ntemplate <typename\
    \ S = null_type, S (*op)(S, S) = nullptr, S (*e)() = nullptr,\n          typename\
    \ F = null_type, S (*mapping)(F, S) = nullptr,\n          F (*composition)(F,\
    \ F) = nullptr, F (*id)() = nullptr,\n          typename Generator = xoshiro256starstar>\n\
    struct lazy_implicit_treap {\n    lazy_implicit_treap()\n        : gen_(static_cast<typename\
    \ Generator::result_type>(\n              std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {}\n    explicit lazy_implicit_treap(typename Generator::result_type seed)\n\
    \        : gen_(seed) {}\n    // Construct a trep on values {data[0], data[1],\
    \ ..., data[n - 1]}\n    template <typename Data> int build(const Data &data)\
    \ {\n        auto n = static_cast<int>(std::size(data));\n        reserve(n);\n\
    \        return build(data, 0, n);\n    }\n    // Split into [0, pos), [pos, inf)\n\
    \    std::array<int, 2> split(int u, int pos) {\n        if (!~u) {\n        \
    \    return {-1, -1};\n        }\n        push(u);\n        if (size(nodes_[u].children[0])\
    \ < pos) {\n            auto [left, right] = split(nodes_[u].children[1],\n  \
    \                                     pos - size(nodes_[u].children[0]) - 1);\n\
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
    \ < nodes_[v].priority) {\n            push(v);\n            nodes_[v].children[0]\
    \ = merge(u, nodes_[v].children[0]);\n            return update(v);\n        }\
    \ else {\n            push(u);\n            nodes_[u].children[1] = merge(nodes_[u].children[1],\
    \ v);\n            return update(u);\n        }\n    }\n    int merge(std::initializer_list<int>\
    \ ilist) {\n        auto u = -1;\n        for (auto v : ilist) {\n           \
    \ u = merge(u, v);\n        }\n        return u;\n    }\n    // Inserts value\
    \ before pos\n    int insert(int u, int pos, const S &value) {\n        assert(0\
    \ <= pos && pos <= size(u));\n        auto v = new_node(value);\n        auto\
    \ [left, right] = split(u, pos);\n        return merge({left, v, right});\n  \
    \  }\n    int push_back(int u, const S &value) {\n        auto v = new_node(value);\n\
    \        return merge(u, v);\n    }\n    int new_node(const S &value) {\n    \
    \    auto u = static_cast<int>(nodes_.size());\n        nodes_.emplace_back(value,\
    \ gen_());\n        return u;\n    }\n    int erase(int u, int pos) {\n      \
    \  assert(0 <= pos && pos < size(u));\n        auto v = split(u, {pos, pos + 1});\n\
    \        return merge(v[0], v[2]);\n    }\n    S get(int u, int pos) {\n     \
    \   assert(~u && !~nodes_[u].parent);\n        assert(0 <= pos && pos < size(u));\n\
    \        while (~u) {\n            push(u);\n            if (size(nodes_[u].children[0])\
    \ < pos) {\n                pos -= size(nodes_[u].children[0]) + 1;\n        \
    \        u = nodes_[u].children[1];\n            } else if (pos < size(nodes_[u].children[0]))\
    \ {\n                u = nodes_[u].children[0];\n            } else {\n      \
    \          break;\n            }\n        }\n        assert(~u);\n        return\
    \ nodes_[u].value;\n    }\n    int set(int u, int pos, S value) {\n        assert(0\
    \ <= pos && pos < size(u));\n        auto v = split(u, {pos, pos + 1});\n    \
    \    nodes_[v[1]].value = value;\n        if constexpr (op != nullptr && e !=\
    \ nullptr) {\n            nodes_[v[1]].subtree_sum = value;\n        }\n     \
    \   return merge({v[0], v[1], v[2]});\n    }\n    int apply(int u, int pos, F\
    \ f) {\n        static_assert(!std::is_empty_v<F> && mapping != nullptr &&\n \
    \                     composition != nullptr && id != nullptr);\n        return\
    \ apply(u, pos, pos + 1, f);\n    }\n    int apply(int u, int l, int r, F f) {\n\
    \        static_assert(!std::is_empty_v<F> && mapping != nullptr &&\n        \
    \              composition != nullptr && id != nullptr);\n        assert(0 <=\
    \ l && l <= r && r <= size(u));\n        auto v = split(u, {l, r});\n        all_apply(v[1],\
    \ f);\n        return merge({v[0], v[1], v[2]});\n    }\n    S all_prod(int u)\
    \ const {\n        static_assert(!std::is_empty_v<S> && op != nullptr && e !=\
    \ nullptr);\n        return ~u ? nodes_[u].subtree_sum : e();\n    }\n    std::pair<int,\
    \ S> prod(int u, int l, int r) {\n        static_assert(!std::is_empty_v<S> &&\
    \ op != nullptr && e != nullptr);\n        auto v = split(u, {l, r});\n      \
    \  auto result = all_prod(v[1]);\n        return {merge({v[0], v[1], v[2]}), result};\n\
    \    }\n    int reverse(int u) {\n        if (~u) {\n            nodes_[u].reversed\
    \ ^= true;\n        }\n        return u;\n    }\n    int reverse(int u, int l,\
    \ int r) {\n        assert(0 <= l && l <= r && r <= size(u));\n        auto v\
    \ = split(u, {l, r});\n        reverse(v[1]);\n        return merge({v[0], v[1],\
    \ v[2]});\n    }\n    int order_of_node(int u) {\n        assert(0 <= u && u <\
    \ static_cast<int>(nodes_.size()));\n        auto propagate = [&](auto self, int\
    \ x) -> void {\n            if (~x) {\n                self(self, nodes_[x].parent);\n\
    \                push(x);\n            }\n        };\n        propagate(propagate,\
    \ u);\n        auto order = size(nodes_[u].children[0]);\n        for (; ~nodes_[u].parent;\
    \ u = nodes_[u].parent) {\n            if (auto p = nodes_[u].parent; nodes_[p].children[1]\
    \ == u) {\n                order += size(p) - size(u);\n            }\n      \
    \  }\n        return order;\n    }\n    void reserve(std::vector<int>::size_type\
    \ n) { nodes_.reserve(n); }\n    int size(int u) const { return ~u ? nodes_[u].subtree_size\
    \ : 0; }\n    template <typename Function> void for_each(int u, Function f) {\n\
    \        if (~u) {\n            push(u);\n            for_each(nodes_[u].children[0],\
    \ f);\n            f(nodes_[u].value);\n            for_each(nodes_[u].children[1],\
    \ f);\n        }\n    }\n\nprivate:\n    int update(int u) {\n        if (!~u)\
    \ {\n            return u;\n        }\n        nodes_[u].parent = -1;\n      \
    \  nodes_[u].subtree_size = 1;\n        for (auto v : nodes_[u].children) {\n\
    \            if (~v) {\n                nodes_[v].parent = u;\n              \
    \  nodes_[u].subtree_size += nodes_[v].subtree_size;\n            }\n        }\n\
    \        if constexpr (!std::is_empty_v<S> && op != nullptr && e != nullptr) {\n\
    \            nodes_[u].subtree_sum =\n                ~nodes_[u].children[0]\n\
    \                    ? op(nodes_[nodes_[u].children[0]].subtree_sum,\n       \
    \                  nodes_[u].value)\n                    : nodes_[u].value;\n\
    \            nodes_[u].subtree_sum =\n                ~nodes_[u].children[1]\n\
    \                    ? op(nodes_[u].subtree_sum,\n                         nodes_[nodes_[u].children[1]].subtree_sum)\n\
    \                    : nodes_[u].subtree_sum;\n        }\n        return u;\n\
    \    }\n    void push(int u) {\n        if (!~u) {\n            return;\n    \
    \    }\n        if constexpr (!std::is_empty_v<F> && mapping != nullptr &&\n \
    \                     composition != nullptr && id != nullptr) {\n           \
    \ all_apply(nodes_[u].children[0], nodes_[u].lazy);\n            all_apply(nodes_[u].children[1],\
    \ nodes_[u].lazy);\n            nodes_[u].lazy = id();\n        }\n        if\
    \ (nodes_[u].reversed) {\n            for (auto v : nodes_[u].children) {\n  \
    \              if (~v) {\n                    nodes_[v].reversed ^= true;\n  \
    \              }\n            }\n            std::swap(nodes_[u].children[0],\
    \ nodes_[u].children[1]);\n            nodes_[u].reversed = false;\n        }\n\
    \    }\n    void all_apply(int u, F f) {\n        static_assert(!std::is_empty_v<F>\
    \ && mapping != nullptr &&\n                      composition != nullptr && id\
    \ != nullptr);\n        if (~u) {\n            nodes_[u].value = mapping(f, nodes_[u].value);\n\
    \            nodes_[u].subtree_sum = mapping(f, nodes_[u].subtree_sum);\n    \
    \        nodes_[u].lazy = composition(f, nodes_[u].lazy);\n        }\n    }\n\
    \    void heapify(int u) {\n        if (!~u) {\n            return;\n        }\n\
    \        auto max = u;\n        for (auto v : nodes_[u].children) {\n        \
    \    if (~v && nodes_[v].priority > nodes_[max].priority) {\n                max\
    \ = v;\n            }\n        }\n        if (max != u) {\n            std::swap(nodes_[u].priority,\
    \ nodes_[max].priority);\n            heapify(max);\n        }\n    }\n    template\
    \ <typename Data> int build(const Data &data, int left, int right) {\n       \
    \ if (left >= right)\n            return -1;\n        auto mid = (left + right)\
    \ / 2;\n        auto u = new_node(data[mid]);\n        nodes_[u].children[0] =\
    \ build(data, left, mid);\n        nodes_[u].children[1] = build(data, mid + 1,\
    \ right);\n        heapify(u);\n        return update(u);\n    }\n    struct node\
    \ {\n        node(const S &value_, typename Generator::result_type priority_)\n\
    \            : value(value_), priority(priority_) {\n            if constexpr\
    \ (op != nullptr && e != nullptr) {\n                subtree_sum = value;\n  \
    \          }\n            if constexpr (id != nullptr) {\n                lazy\
    \ = id();\n            }\n        }\n        S value;\n        std::conditional_t<op\
    \ != nullptr && e != nullptr, S, null_type>\n            subtree_sum;\n      \
    \  F lazy;\n        typename Generator::result_type priority;\n        bool reversed\
    \ = false;\n        int parent = -1;\n        int subtree_size = 1;\n        std::array<int,\
    \ 2> children{-1, -1};\n    };\n    Generator gen_;\n    std::vector<node> nodes_;\n\
    };\n\n\n"
  code: "#ifndef LAZY_IMPLICIT_TREAP_HPP\n#define LAZY_IMPLICIT_TREAP_HPP\n\n#include\
    \ \"../random/xoshiro256starstar.hpp\"\n#include <array>\n#include <cassert>\n\
    #include <chrono>\n#include <initializer_list>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\nusing null_type = struct {};\n\ntemplate <typename\
    \ S = null_type, S (*op)(S, S) = nullptr, S (*e)() = nullptr,\n          typename\
    \ F = null_type, S (*mapping)(F, S) = nullptr,\n          F (*composition)(F,\
    \ F) = nullptr, F (*id)() = nullptr,\n          typename Generator = xoshiro256starstar>\n\
    struct lazy_implicit_treap {\n    lazy_implicit_treap()\n        : gen_(static_cast<typename\
    \ Generator::result_type>(\n              std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {}\n    explicit lazy_implicit_treap(typename Generator::result_type seed)\n\
    \        : gen_(seed) {}\n    // Construct a trep on values {data[0], data[1],\
    \ ..., data[n - 1]}\n    template <typename Data> int build(const Data &data)\
    \ {\n        auto n = static_cast<int>(std::size(data));\n        reserve(n);\n\
    \        return build(data, 0, n);\n    }\n    // Split into [0, pos), [pos, inf)\n\
    \    std::array<int, 2> split(int u, int pos) {\n        if (!~u) {\n        \
    \    return {-1, -1};\n        }\n        push(u);\n        if (size(nodes_[u].children[0])\
    \ < pos) {\n            auto [left, right] = split(nodes_[u].children[1],\n  \
    \                                     pos - size(nodes_[u].children[0]) - 1);\n\
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
    \ < nodes_[v].priority) {\n            push(v);\n            nodes_[v].children[0]\
    \ = merge(u, nodes_[v].children[0]);\n            return update(v);\n        }\
    \ else {\n            push(u);\n            nodes_[u].children[1] = merge(nodes_[u].children[1],\
    \ v);\n            return update(u);\n        }\n    }\n    int merge(std::initializer_list<int>\
    \ ilist) {\n        auto u = -1;\n        for (auto v : ilist) {\n           \
    \ u = merge(u, v);\n        }\n        return u;\n    }\n    // Inserts value\
    \ before pos\n    int insert(int u, int pos, const S &value) {\n        assert(0\
    \ <= pos && pos <= size(u));\n        auto v = new_node(value);\n        auto\
    \ [left, right] = split(u, pos);\n        return merge({left, v, right});\n  \
    \  }\n    int push_back(int u, const S &value) {\n        auto v = new_node(value);\n\
    \        return merge(u, v);\n    }\n    int new_node(const S &value) {\n    \
    \    auto u = static_cast<int>(nodes_.size());\n        nodes_.emplace_back(value,\
    \ gen_());\n        return u;\n    }\n    int erase(int u, int pos) {\n      \
    \  assert(0 <= pos && pos < size(u));\n        auto v = split(u, {pos, pos + 1});\n\
    \        return merge(v[0], v[2]);\n    }\n    S get(int u, int pos) {\n     \
    \   assert(~u && !~nodes_[u].parent);\n        assert(0 <= pos && pos < size(u));\n\
    \        while (~u) {\n            push(u);\n            if (size(nodes_[u].children[0])\
    \ < pos) {\n                pos -= size(nodes_[u].children[0]) + 1;\n        \
    \        u = nodes_[u].children[1];\n            } else if (pos < size(nodes_[u].children[0]))\
    \ {\n                u = nodes_[u].children[0];\n            } else {\n      \
    \          break;\n            }\n        }\n        assert(~u);\n        return\
    \ nodes_[u].value;\n    }\n    int set(int u, int pos, S value) {\n        assert(0\
    \ <= pos && pos < size(u));\n        auto v = split(u, {pos, pos + 1});\n    \
    \    nodes_[v[1]].value = value;\n        if constexpr (op != nullptr && e !=\
    \ nullptr) {\n            nodes_[v[1]].subtree_sum = value;\n        }\n     \
    \   return merge({v[0], v[1], v[2]});\n    }\n    int apply(int u, int pos, F\
    \ f) {\n        static_assert(!std::is_empty_v<F> && mapping != nullptr &&\n \
    \                     composition != nullptr && id != nullptr);\n        return\
    \ apply(u, pos, pos + 1, f);\n    }\n    int apply(int u, int l, int r, F f) {\n\
    \        static_assert(!std::is_empty_v<F> && mapping != nullptr &&\n        \
    \              composition != nullptr && id != nullptr);\n        assert(0 <=\
    \ l && l <= r && r <= size(u));\n        auto v = split(u, {l, r});\n        all_apply(v[1],\
    \ f);\n        return merge({v[0], v[1], v[2]});\n    }\n    S all_prod(int u)\
    \ const {\n        static_assert(!std::is_empty_v<S> && op != nullptr && e !=\
    \ nullptr);\n        return ~u ? nodes_[u].subtree_sum : e();\n    }\n    std::pair<int,\
    \ S> prod(int u, int l, int r) {\n        static_assert(!std::is_empty_v<S> &&\
    \ op != nullptr && e != nullptr);\n        auto v = split(u, {l, r});\n      \
    \  auto result = all_prod(v[1]);\n        return {merge({v[0], v[1], v[2]}), result};\n\
    \    }\n    int reverse(int u) {\n        if (~u) {\n            nodes_[u].reversed\
    \ ^= true;\n        }\n        return u;\n    }\n    int reverse(int u, int l,\
    \ int r) {\n        assert(0 <= l && l <= r && r <= size(u));\n        auto v\
    \ = split(u, {l, r});\n        reverse(v[1]);\n        return merge({v[0], v[1],\
    \ v[2]});\n    }\n    int order_of_node(int u) {\n        assert(0 <= u && u <\
    \ static_cast<int>(nodes_.size()));\n        auto propagate = [&](auto self, int\
    \ x) -> void {\n            if (~x) {\n                self(self, nodes_[x].parent);\n\
    \                push(x);\n            }\n        };\n        propagate(propagate,\
    \ u);\n        auto order = size(nodes_[u].children[0]);\n        for (; ~nodes_[u].parent;\
    \ u = nodes_[u].parent) {\n            if (auto p = nodes_[u].parent; nodes_[p].children[1]\
    \ == u) {\n                order += size(p) - size(u);\n            }\n      \
    \  }\n        return order;\n    }\n    void reserve(std::vector<int>::size_type\
    \ n) { nodes_.reserve(n); }\n    int size(int u) const { return ~u ? nodes_[u].subtree_size\
    \ : 0; }\n    template <typename Function> void for_each(int u, Function f) {\n\
    \        if (~u) {\n            push(u);\n            for_each(nodes_[u].children[0],\
    \ f);\n            f(nodes_[u].value);\n            for_each(nodes_[u].children[1],\
    \ f);\n        }\n    }\n\nprivate:\n    int update(int u) {\n        if (!~u)\
    \ {\n            return u;\n        }\n        nodes_[u].parent = -1;\n      \
    \  nodes_[u].subtree_size = 1;\n        for (auto v : nodes_[u].children) {\n\
    \            if (~v) {\n                nodes_[v].parent = u;\n              \
    \  nodes_[u].subtree_size += nodes_[v].subtree_size;\n            }\n        }\n\
    \        if constexpr (!std::is_empty_v<S> && op != nullptr && e != nullptr) {\n\
    \            nodes_[u].subtree_sum =\n                ~nodes_[u].children[0]\n\
    \                    ? op(nodes_[nodes_[u].children[0]].subtree_sum,\n       \
    \                  nodes_[u].value)\n                    : nodes_[u].value;\n\
    \            nodes_[u].subtree_sum =\n                ~nodes_[u].children[1]\n\
    \                    ? op(nodes_[u].subtree_sum,\n                         nodes_[nodes_[u].children[1]].subtree_sum)\n\
    \                    : nodes_[u].subtree_sum;\n        }\n        return u;\n\
    \    }\n    void push(int u) {\n        if (!~u) {\n            return;\n    \
    \    }\n        if constexpr (!std::is_empty_v<F> && mapping != nullptr &&\n \
    \                     composition != nullptr && id != nullptr) {\n           \
    \ all_apply(nodes_[u].children[0], nodes_[u].lazy);\n            all_apply(nodes_[u].children[1],\
    \ nodes_[u].lazy);\n            nodes_[u].lazy = id();\n        }\n        if\
    \ (nodes_[u].reversed) {\n            for (auto v : nodes_[u].children) {\n  \
    \              if (~v) {\n                    nodes_[v].reversed ^= true;\n  \
    \              }\n            }\n            std::swap(nodes_[u].children[0],\
    \ nodes_[u].children[1]);\n            nodes_[u].reversed = false;\n        }\n\
    \    }\n    void all_apply(int u, F f) {\n        static_assert(!std::is_empty_v<F>\
    \ && mapping != nullptr &&\n                      composition != nullptr && id\
    \ != nullptr);\n        if (~u) {\n            nodes_[u].value = mapping(f, nodes_[u].value);\n\
    \            nodes_[u].subtree_sum = mapping(f, nodes_[u].subtree_sum);\n    \
    \        nodes_[u].lazy = composition(f, nodes_[u].lazy);\n        }\n    }\n\
    \    void heapify(int u) {\n        if (!~u) {\n            return;\n        }\n\
    \        auto max = u;\n        for (auto v : nodes_[u].children) {\n        \
    \    if (~v && nodes_[v].priority > nodes_[max].priority) {\n                max\
    \ = v;\n            }\n        }\n        if (max != u) {\n            std::swap(nodes_[u].priority,\
    \ nodes_[max].priority);\n            heapify(max);\n        }\n    }\n    template\
    \ <typename Data> int build(const Data &data, int left, int right) {\n       \
    \ if (left >= right)\n            return -1;\n        auto mid = (left + right)\
    \ / 2;\n        auto u = new_node(data[mid]);\n        nodes_[u].children[0] =\
    \ build(data, left, mid);\n        nodes_[u].children[1] = build(data, mid + 1,\
    \ right);\n        heapify(u);\n        return update(u);\n    }\n    struct node\
    \ {\n        node(const S &value_, typename Generator::result_type priority_)\n\
    \            : value(value_), priority(priority_) {\n            if constexpr\
    \ (op != nullptr && e != nullptr) {\n                subtree_sum = value;\n  \
    \          }\n            if constexpr (id != nullptr) {\n                lazy\
    \ = id();\n            }\n        }\n        S value;\n        std::conditional_t<op\
    \ != nullptr && e != nullptr, S, null_type>\n            subtree_sum;\n      \
    \  F lazy;\n        typename Generator::result_type priority;\n        bool reversed\
    \ = false;\n        int parent = -1;\n        int subtree_size = 1;\n        std::array<int,\
    \ 2> children{-1, -1};\n    };\n    Generator gen_;\n    std::vector<node> nodes_;\n\
    };\n\n#endif // LAZY_IMPLICIT_TREAP_HPP"
  dependsOn:
  - random/xoshiro256starstar.hpp
  - random/splitmix64.hpp
  isVerificationFile: false
  path: treap/lazy_implicit_treap.hpp
  requiredBy: []
  timestamp: '2022-09-09 09:09:24+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: treap/lazy_implicit_treap.hpp
layout: document
redirect_from:
- /library/treap/lazy_implicit_treap.hpp
- /library/treap/lazy_implicit_treap.hpp.html
title: treap/lazy_implicit_treap.hpp
---
