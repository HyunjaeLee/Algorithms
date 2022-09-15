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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dynamic_connectivity.test.cpp
    title: test/dynamic_connectivity.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/dynamic_connectivity.hpp\"\n\n\n\n#line 1 \"random/xoshiro256starstar.hpp\"\
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
    \ 4> s;\n};\n\n\n#line 6 \"graph/dynamic_connectivity.hpp\"\n#include <cassert>\n\
    #include <chrono>\n#line 9 \"graph/dynamic_connectivity.hpp\"\n#include <initializer_list>\n\
    #include <tuple>\n#include <unordered_map>\n#include <unordered_set>\n#include\
    \ <utility>\n#include <vector>\n\ntemplate <typename Generator = xoshiro256starstar>\
    \ struct treap {\n    treap()\n        : gen_(static_cast<typename Generator::result_type>(\n\
    \              std::chrono::steady_clock::now().time_since_epoch().count())) {}\n\
    \    std::array<int, 2> split(int u, int dir) {\n        assert(~u);\n       \
    \ std::array<int, 2> result{-1, -1};\n        result[dir] = update(nodes_[u].children[dir]);\n\
    \        while (true) {\n            auto p = nodes_[u].parent;\n            nodes_[u].children[dir]\
    \ = result[dir ^ 1];\n            result[dir ^ 1] = update(u);\n            if\
    \ (!~p) {\n                break;\n            }\n            dir = static_cast<int>(nodes_[p].children[1]\
    \ == u);\n            u = p;\n        }\n        return result;\n    }\n    int\
    \ merge(int u, int v) {\n        if (!~u || !~v) {\n            return ~u ? u\
    \ : v;\n        }\n        if (nodes_[u].priority < nodes_[v].priority) {\n  \
    \          nodes_[u].children[1] = merge(nodes_[u].children[1], v);\n        \
    \    return update(u);\n        } else {\n            nodes_[v].children[0] =\
    \ merge(u, nodes_[v].children[0]);\n            return update(v);\n        }\n\
    \    }\n    int merge(std::initializer_list<int> ilist) {\n        auto u = -1;\n\
    \        for (auto v : ilist) {\n            u = merge(u, v);\n        }\n   \
    \     return u;\n    }\n    bool same(int u, int v) const { return get_root(u)\
    \ == get_root(v); }\n    void mark(int u, int idx, bool val) {\n        assert(~u);\n\
    \        nodes_[u].mark[idx] = val;\n        while (~u) {\n            auto p\
    \ = nodes_[u].parent;\n            update(u);\n            u = p;\n        }\n\
    \    }\n    int get_marked(int u, int idx) const {\n        assert(~u);\n    \
    \    u = get_root(u);\n        if (!nodes_[u].subtree_mark[idx]) {\n         \
    \   return -1;\n        }\n        while (!nodes_[u].mark[idx]) {\n          \
    \  for (auto v : nodes_[u].children) {\n                if (~v && nodes_[v].subtree_mark[idx])\
    \ {\n                    u = v;\n                    break;\n                }\n\
    \            }\n        }\n        return u;\n    }\n    int new_node() {\n  \
    \      auto u = static_cast<int>(nodes_.size());\n        nodes_.emplace_back(gen_());\n\
    \        return u;\n    }\n    int get_root(int u) const {\n        assert(~u);\n\
    \        while (~nodes_[u].parent) {\n            u = nodes_[u].parent;\n    \
    \    }\n        return u;\n    }\n    int size(int u) const { return ~u ? nodes_[u].size\
    \ : 0; }\n    void reserve(int n) { nodes_.reserve(n); }\n\nprivate:\n    int\
    \ update(int u) {\n        if (~u) {\n            nodes_[u].parent = -1;\n   \
    \         nodes_[u].size = 1;\n            nodes_[u].subtree_mark = nodes_[u].mark;\n\
    \            for (auto v : nodes_[u].children) {\n                if (~v) {\n\
    \                    nodes_[v].parent = u;\n                    nodes_[u].size\
    \ += nodes_[v].size;\n                    for (auto i = 0; i < 2; ++i) {\n   \
    \                     nodes_[u].subtree_mark[i] |= nodes_[v].subtree_mark[i];\n\
    \                    }\n                }\n            }\n        }\n        return\
    \ u;\n    }\n    struct node {\n        node(typename Generator::result_type priority)\
    \ : priority(priority) {}\n        typename Generator::result_type priority;\n\
    \        int parent = -1, size = 1;\n        std::array<int, 2> children{-1, -1};\n\
    \        std::array<bool, 2> mark{}, subtree_mark{};\n    };\n    Generator gen_;\n\
    \    std::vector<node> nodes_;\n};\n\nstruct pair_hash {\n    std::size_t operator()(std::pair<int,\
    \ int> x) const {\n        static const std::uint64_t fixed_random =\n       \
    \     std::chrono::steady_clock::now().time_since_epoch().count();\n        return\
    \ splitmix64(x.first + fixed_random)() ^\n               (splitmix64(x.second\
    \ + fixed_random)() >> 1);\n    }\n};\n\nstruct int_hash {\n    std::size_t operator()(int\
    \ x) const {\n        static const std::uint64_t fixed_random =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + fixed_random)();\n    }\n};\n\nstruct euler_tour_tree\
    \ {\n    euler_tour_tree(int n) : n_(n) {\n        treap_.reserve(3 * n_);\n \
    \       edges_.reserve(2 * n_);\n        edge_data_.reserve(2 * n_);\n       \
    \ for (auto i = 0; i < n_; ++i) {\n            treap_.new_node();\n        }\n\
    \    }\n    bool connected(int u, int v) const { return treap_.same(u, v); }\n\
    \    void link(int u, int v) {\n        auto uv = treap_.new_node();\n       \
    \ edges_[{u, v}] = uv;\n        edge_data_.push_back({u, v});\n        auto vu\
    \ = treap_.new_node();\n        edges_[{v, u}] = vu;\n        edge_data_.push_back({v,\
    \ u});\n        auto [u1, u2] = treap_.split(u, 1);\n        auto [v1, v2] = treap_.split(v,\
    \ 1);\n        treap_.merge({u2, u1, uv, v2, v1, vu});\n    }\n    void cut(int\
    \ u, int v) {\n        auto uv_it = edges_.find({u, v});\n        auto vu_it =\
    \ edges_.find({v, u});\n        auto uv = uv_it->second;\n        auto vu = vu_it->second;\n\
    \        auto uv_left = treap_.split(uv, 0)[0];\n        bool is_uv_before_vu\
    \ = treap_.same(uv, vu);\n        auto uv_right = treap_.split(uv, 1)[1];\n  \
    \      auto vu_left = treap_.split(vu, 0)[0];\n        auto vu_right = treap_.split(vu,\
    \ 1)[1];\n        if (is_uv_before_vu) {\n            treap_.merge(uv_left, vu_right);\n\
    \        } else {\n            treap_.merge(vu_left, uv_right);\n        }\n \
    \       edges_.erase(uv_it);\n        edges_.erase(vu_it);\n    }\n    void mark_node(int\
    \ u, bool mark) { treap_.mark(u, 0, mark); }\n    void mark_edge(int u, int v,\
    \ bool mark) {\n        auto uv = edges_[{u, v}];\n        treap_.mark(uv, 1,\
    \ mark);\n        auto vu = edges_[{v, u}];\n        treap_.mark(vu, 1, mark);\n\
    \    }\n    int get_marked_node(int u) const { return treap_.get_marked(u, 0);\
    \ }\n    std::pair<int, int> get_marked_edge(int u) const {\n        auto edge\
    \ = treap_.get_marked(u, 1);\n        return ~edge ? edge_data_[edge - n_] : std::pair(-1,\
    \ -1);\n    }\n    int tree_size(int u) const {\n        u = treap_.get_root(u);\n\
    \        return treap_.size(u);\n    }\n\nprivate:\n    int n_;\n    treap<> treap_;\n\
    \    std::unordered_map<std::pair<int, int>, int, pair_hash> edges_;\n    std::vector<std::pair<int,\
    \ int>> edge_data_;\n};\n\nstruct dynamic_connectivity {\n    dynamic_connectivity(int\
    \ n)\n        : n_(n), log_(std::__lg(n_) + 1),\n          spanning_forest_(log_,\
    \ euler_tour_tree(n_)),\n          nontree_adj_(log_,\n                      \
    \ std::vector<std::unordered_set<int, int_hash>>(n_)) {\n        edge_level_.reserve(n_);\n\
    \        is_tree_edge_.reserve(n_);\n    }\n    bool connected(int u, int v) const\
    \ {\n        return spanning_forest_[0].connected(u, v);\n    }\n    void link(int\
    \ u, int v) {\n        edge_level(u, v) = 0;\n        if (connected(u, v)) {\n\
    \            is_tree_edge(u, v) = false;\n            add_edge_to_adj(u, v, 0);\n\
    \        } else {\n            is_tree_edge(u, v) = true;\n            spanning_forest_[0].link(u,\
    \ v);\n            spanning_forest_[0].mark_edge(u, v, true);\n        }\n   \
    \ }\n    void cut(int u, int v) {\n        auto level = edge_level(u, v);\n  \
    \      if (is_tree_edge(u, v)) {\n            for (auto i = level; i >= 0; --i)\
    \ {\n                spanning_forest_[i].cut(u, v);\n            }\n         \
    \   replace(u, v, level);\n        } else {\n            delete_edge_from_adj(u,\
    \ v, level);\n        }\n    }\n\nprivate:\n    void replace(int u, int v, int\
    \ level) {\n        if (spanning_forest_[level].tree_size(u) >\n            spanning_forest_[level].tree_size(v))\
    \ {\n            std::swap(u, v);\n        }\n        for (auto [x, y] = spanning_forest_[level].get_marked_edge(u);\
    \ ~x;\n             std::tie(x, y) = spanning_forest_[level].get_marked_edge(u))\
    \ {\n            ++edge_level(x, y);\n            spanning_forest_[level].mark_edge(x,\
    \ y, false);\n            spanning_forest_[level + 1].link(x, y);\n          \
    \  spanning_forest_[level + 1].mark_edge(x, y, true);\n        }\n        for\
    \ (auto x = spanning_forest_[level].get_marked_node(u); ~x;\n             x =\
    \ spanning_forest_[level].get_marked_node(u)) {\n            while (!nontree_adj_[level][x].empty())\
    \ {\n                auto y = *nontree_adj_[level][x].begin();\n             \
    \   if (spanning_forest_[level].connected(x, y)) {\n                    ++edge_level(x,\
    \ y);\n                    delete_edge_from_adj(x, y, level);\n              \
    \      add_edge_to_adj(x, y, level + 1);\n                } else {\n         \
    \           is_tree_edge(x, y) = true;\n                    delete_edge_from_adj(x,\
    \ y, level);\n                    for (auto i = level; i >= 0; --i) {\n      \
    \                  spanning_forest_[i].link(x, y);\n                    }\n  \
    \                  spanning_forest_[level].mark_edge(x, y, true);\n          \
    \          return;\n                }\n            }\n        }\n        if (level\
    \ > 0) {\n            replace(u, v, level - 1);\n        }\n    }\n    void add_edge_to_adj(int\
    \ u, int v, int level) {\n        if (nontree_adj_[level][u].empty()) {\n    \
    \        spanning_forest_[level].mark_node(u, true);\n        }\n        nontree_adj_[level][u].insert(v);\n\
    \        if (nontree_adj_[level][v].empty()) {\n            spanning_forest_[level].mark_node(v,\
    \ true);\n        }\n        nontree_adj_[level][v].insert(u);\n    }\n    void\
    \ delete_edge_from_adj(int u, int v, int level) {\n        nontree_adj_[level][u].erase(v);\n\
    \        if (nontree_adj_[level][u].empty()) {\n            spanning_forest_[level].mark_node(u,\
    \ false);\n        }\n        nontree_adj_[level][v].erase(u);\n        if (nontree_adj_[level][v].empty())\
    \ {\n            spanning_forest_[level].mark_node(v, false);\n        }\n   \
    \ }\n    int &edge_level(int u, int v) {\n        if (u > v) {\n            std::swap(u,\
    \ v);\n        }\n        return edge_level_[{u, v}];\n    }\n    bool &is_tree_edge(int\
    \ u, int v) {\n        if (u > v) {\n            std::swap(u, v);\n        }\n\
    \        return is_tree_edge_[{u, v}];\n    }\n    int n_, log_;\n    std::vector<euler_tour_tree>\
    \ spanning_forest_;\n    std::vector<std::vector<std::unordered_set<int, int_hash>>>\
    \ nontree_adj_;\n    std::unordered_map<std::pair<int, int>, int, pair_hash> edge_level_;\n\
    \    std::unordered_map<std::pair<int, int>, bool, pair_hash> is_tree_edge_;\n\
    };\n\n\n"
  code: "#ifndef DYNAMIC_CONNECTIVITY_HPP\n#define DYNAMIC_CONNECTIVITY_HPP\n\n#include\
    \ \"../random/xoshiro256starstar.hpp\"\n#include <array>\n#include <cassert>\n\
    #include <chrono>\n#include <cstdint>\n#include <initializer_list>\n#include <tuple>\n\
    #include <unordered_map>\n#include <unordered_set>\n#include <utility>\n#include\
    \ <vector>\n\ntemplate <typename Generator = xoshiro256starstar> struct treap\
    \ {\n    treap()\n        : gen_(static_cast<typename Generator::result_type>(\n\
    \              std::chrono::steady_clock::now().time_since_epoch().count())) {}\n\
    \    std::array<int, 2> split(int u, int dir) {\n        assert(~u);\n       \
    \ std::array<int, 2> result{-1, -1};\n        result[dir] = update(nodes_[u].children[dir]);\n\
    \        while (true) {\n            auto p = nodes_[u].parent;\n            nodes_[u].children[dir]\
    \ = result[dir ^ 1];\n            result[dir ^ 1] = update(u);\n            if\
    \ (!~p) {\n                break;\n            }\n            dir = static_cast<int>(nodes_[p].children[1]\
    \ == u);\n            u = p;\n        }\n        return result;\n    }\n    int\
    \ merge(int u, int v) {\n        if (!~u || !~v) {\n            return ~u ? u\
    \ : v;\n        }\n        if (nodes_[u].priority < nodes_[v].priority) {\n  \
    \          nodes_[u].children[1] = merge(nodes_[u].children[1], v);\n        \
    \    return update(u);\n        } else {\n            nodes_[v].children[0] =\
    \ merge(u, nodes_[v].children[0]);\n            return update(v);\n        }\n\
    \    }\n    int merge(std::initializer_list<int> ilist) {\n        auto u = -1;\n\
    \        for (auto v : ilist) {\n            u = merge(u, v);\n        }\n   \
    \     return u;\n    }\n    bool same(int u, int v) const { return get_root(u)\
    \ == get_root(v); }\n    void mark(int u, int idx, bool val) {\n        assert(~u);\n\
    \        nodes_[u].mark[idx] = val;\n        while (~u) {\n            auto p\
    \ = nodes_[u].parent;\n            update(u);\n            u = p;\n        }\n\
    \    }\n    int get_marked(int u, int idx) const {\n        assert(~u);\n    \
    \    u = get_root(u);\n        if (!nodes_[u].subtree_mark[idx]) {\n         \
    \   return -1;\n        }\n        while (!nodes_[u].mark[idx]) {\n          \
    \  for (auto v : nodes_[u].children) {\n                if (~v && nodes_[v].subtree_mark[idx])\
    \ {\n                    u = v;\n                    break;\n                }\n\
    \            }\n        }\n        return u;\n    }\n    int new_node() {\n  \
    \      auto u = static_cast<int>(nodes_.size());\n        nodes_.emplace_back(gen_());\n\
    \        return u;\n    }\n    int get_root(int u) const {\n        assert(~u);\n\
    \        while (~nodes_[u].parent) {\n            u = nodes_[u].parent;\n    \
    \    }\n        return u;\n    }\n    int size(int u) const { return ~u ? nodes_[u].size\
    \ : 0; }\n    void reserve(int n) { nodes_.reserve(n); }\n\nprivate:\n    int\
    \ update(int u) {\n        if (~u) {\n            nodes_[u].parent = -1;\n   \
    \         nodes_[u].size = 1;\n            nodes_[u].subtree_mark = nodes_[u].mark;\n\
    \            for (auto v : nodes_[u].children) {\n                if (~v) {\n\
    \                    nodes_[v].parent = u;\n                    nodes_[u].size\
    \ += nodes_[v].size;\n                    for (auto i = 0; i < 2; ++i) {\n   \
    \                     nodes_[u].subtree_mark[i] |= nodes_[v].subtree_mark[i];\n\
    \                    }\n                }\n            }\n        }\n        return\
    \ u;\n    }\n    struct node {\n        node(typename Generator::result_type priority)\
    \ : priority(priority) {}\n        typename Generator::result_type priority;\n\
    \        int parent = -1, size = 1;\n        std::array<int, 2> children{-1, -1};\n\
    \        std::array<bool, 2> mark{}, subtree_mark{};\n    };\n    Generator gen_;\n\
    \    std::vector<node> nodes_;\n};\n\nstruct pair_hash {\n    std::size_t operator()(std::pair<int,\
    \ int> x) const {\n        static const std::uint64_t fixed_random =\n       \
    \     std::chrono::steady_clock::now().time_since_epoch().count();\n        return\
    \ splitmix64(x.first + fixed_random)() ^\n               (splitmix64(x.second\
    \ + fixed_random)() >> 1);\n    }\n};\n\nstruct int_hash {\n    std::size_t operator()(int\
    \ x) const {\n        static const std::uint64_t fixed_random =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + fixed_random)();\n    }\n};\n\nstruct euler_tour_tree\
    \ {\n    euler_tour_tree(int n) : n_(n) {\n        treap_.reserve(3 * n_);\n \
    \       edges_.reserve(2 * n_);\n        edge_data_.reserve(2 * n_);\n       \
    \ for (auto i = 0; i < n_; ++i) {\n            treap_.new_node();\n        }\n\
    \    }\n    bool connected(int u, int v) const { return treap_.same(u, v); }\n\
    \    void link(int u, int v) {\n        auto uv = treap_.new_node();\n       \
    \ edges_[{u, v}] = uv;\n        edge_data_.push_back({u, v});\n        auto vu\
    \ = treap_.new_node();\n        edges_[{v, u}] = vu;\n        edge_data_.push_back({v,\
    \ u});\n        auto [u1, u2] = treap_.split(u, 1);\n        auto [v1, v2] = treap_.split(v,\
    \ 1);\n        treap_.merge({u2, u1, uv, v2, v1, vu});\n    }\n    void cut(int\
    \ u, int v) {\n        auto uv_it = edges_.find({u, v});\n        auto vu_it =\
    \ edges_.find({v, u});\n        auto uv = uv_it->second;\n        auto vu = vu_it->second;\n\
    \        auto uv_left = treap_.split(uv, 0)[0];\n        bool is_uv_before_vu\
    \ = treap_.same(uv, vu);\n        auto uv_right = treap_.split(uv, 1)[1];\n  \
    \      auto vu_left = treap_.split(vu, 0)[0];\n        auto vu_right = treap_.split(vu,\
    \ 1)[1];\n        if (is_uv_before_vu) {\n            treap_.merge(uv_left, vu_right);\n\
    \        } else {\n            treap_.merge(vu_left, uv_right);\n        }\n \
    \       edges_.erase(uv_it);\n        edges_.erase(vu_it);\n    }\n    void mark_node(int\
    \ u, bool mark) { treap_.mark(u, 0, mark); }\n    void mark_edge(int u, int v,\
    \ bool mark) {\n        auto uv = edges_[{u, v}];\n        treap_.mark(uv, 1,\
    \ mark);\n        auto vu = edges_[{v, u}];\n        treap_.mark(vu, 1, mark);\n\
    \    }\n    int get_marked_node(int u) const { return treap_.get_marked(u, 0);\
    \ }\n    std::pair<int, int> get_marked_edge(int u) const {\n        auto edge\
    \ = treap_.get_marked(u, 1);\n        return ~edge ? edge_data_[edge - n_] : std::pair(-1,\
    \ -1);\n    }\n    int tree_size(int u) const {\n        u = treap_.get_root(u);\n\
    \        return treap_.size(u);\n    }\n\nprivate:\n    int n_;\n    treap<> treap_;\n\
    \    std::unordered_map<std::pair<int, int>, int, pair_hash> edges_;\n    std::vector<std::pair<int,\
    \ int>> edge_data_;\n};\n\nstruct dynamic_connectivity {\n    dynamic_connectivity(int\
    \ n)\n        : n_(n), log_(std::__lg(n_) + 1),\n          spanning_forest_(log_,\
    \ euler_tour_tree(n_)),\n          nontree_adj_(log_,\n                      \
    \ std::vector<std::unordered_set<int, int_hash>>(n_)) {\n        edge_level_.reserve(n_);\n\
    \        is_tree_edge_.reserve(n_);\n    }\n    bool connected(int u, int v) const\
    \ {\n        return spanning_forest_[0].connected(u, v);\n    }\n    void link(int\
    \ u, int v) {\n        edge_level(u, v) = 0;\n        if (connected(u, v)) {\n\
    \            is_tree_edge(u, v) = false;\n            add_edge_to_adj(u, v, 0);\n\
    \        } else {\n            is_tree_edge(u, v) = true;\n            spanning_forest_[0].link(u,\
    \ v);\n            spanning_forest_[0].mark_edge(u, v, true);\n        }\n   \
    \ }\n    void cut(int u, int v) {\n        auto level = edge_level(u, v);\n  \
    \      if (is_tree_edge(u, v)) {\n            for (auto i = level; i >= 0; --i)\
    \ {\n                spanning_forest_[i].cut(u, v);\n            }\n         \
    \   replace(u, v, level);\n        } else {\n            delete_edge_from_adj(u,\
    \ v, level);\n        }\n    }\n\nprivate:\n    void replace(int u, int v, int\
    \ level) {\n        if (spanning_forest_[level].tree_size(u) >\n            spanning_forest_[level].tree_size(v))\
    \ {\n            std::swap(u, v);\n        }\n        for (auto [x, y] = spanning_forest_[level].get_marked_edge(u);\
    \ ~x;\n             std::tie(x, y) = spanning_forest_[level].get_marked_edge(u))\
    \ {\n            ++edge_level(x, y);\n            spanning_forest_[level].mark_edge(x,\
    \ y, false);\n            spanning_forest_[level + 1].link(x, y);\n          \
    \  spanning_forest_[level + 1].mark_edge(x, y, true);\n        }\n        for\
    \ (auto x = spanning_forest_[level].get_marked_node(u); ~x;\n             x =\
    \ spanning_forest_[level].get_marked_node(u)) {\n            while (!nontree_adj_[level][x].empty())\
    \ {\n                auto y = *nontree_adj_[level][x].begin();\n             \
    \   if (spanning_forest_[level].connected(x, y)) {\n                    ++edge_level(x,\
    \ y);\n                    delete_edge_from_adj(x, y, level);\n              \
    \      add_edge_to_adj(x, y, level + 1);\n                } else {\n         \
    \           is_tree_edge(x, y) = true;\n                    delete_edge_from_adj(x,\
    \ y, level);\n                    for (auto i = level; i >= 0; --i) {\n      \
    \                  spanning_forest_[i].link(x, y);\n                    }\n  \
    \                  spanning_forest_[level].mark_edge(x, y, true);\n          \
    \          return;\n                }\n            }\n        }\n        if (level\
    \ > 0) {\n            replace(u, v, level - 1);\n        }\n    }\n    void add_edge_to_adj(int\
    \ u, int v, int level) {\n        if (nontree_adj_[level][u].empty()) {\n    \
    \        spanning_forest_[level].mark_node(u, true);\n        }\n        nontree_adj_[level][u].insert(v);\n\
    \        if (nontree_adj_[level][v].empty()) {\n            spanning_forest_[level].mark_node(v,\
    \ true);\n        }\n        nontree_adj_[level][v].insert(u);\n    }\n    void\
    \ delete_edge_from_adj(int u, int v, int level) {\n        nontree_adj_[level][u].erase(v);\n\
    \        if (nontree_adj_[level][u].empty()) {\n            spanning_forest_[level].mark_node(u,\
    \ false);\n        }\n        nontree_adj_[level][v].erase(u);\n        if (nontree_adj_[level][v].empty())\
    \ {\n            spanning_forest_[level].mark_node(v, false);\n        }\n   \
    \ }\n    int &edge_level(int u, int v) {\n        if (u > v) {\n            std::swap(u,\
    \ v);\n        }\n        return edge_level_[{u, v}];\n    }\n    bool &is_tree_edge(int\
    \ u, int v) {\n        if (u > v) {\n            std::swap(u, v);\n        }\n\
    \        return is_tree_edge_[{u, v}];\n    }\n    int n_, log_;\n    std::vector<euler_tour_tree>\
    \ spanning_forest_;\n    std::vector<std::vector<std::unordered_set<int, int_hash>>>\
    \ nontree_adj_;\n    std::unordered_map<std::pair<int, int>, int, pair_hash> edge_level_;\n\
    \    std::unordered_map<std::pair<int, int>, bool, pair_hash> is_tree_edge_;\n\
    };\n\n#endif // DYNAMIC_CONNECTIVITY_HPP"
  dependsOn:
  - random/xoshiro256starstar.hpp
  - random/splitmix64.hpp
  isVerificationFile: false
  path: graph/dynamic_connectivity.hpp
  requiredBy: []
  timestamp: '2022-09-15 06:56:54+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dynamic_connectivity.test.cpp
documentation_of: graph/dynamic_connectivity.hpp
layout: document
redirect_from:
- /library/graph/dynamic_connectivity.hpp
- /library/graph/dynamic_connectivity.hpp.html
title: graph/dynamic_connectivity.hpp
---
