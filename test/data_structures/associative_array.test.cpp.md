---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structures/hash_map.hpp
    title: data_structures/hash_map.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/associative_array
    links:
    - https://judge.yosupo.jp/problem/associative_array
  bundledCode: "#line 1 \"test/data_structures/associative_array.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n\n#line 1 \"\
    data_structures/hash_map.hpp\"\n\n\n\n#include <array>\n#include <bit>\n#include\
    \ <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <optional>\n#include <random>\n\n// https://hitonanode.github.io/cplib-cpp/data_structure/fast_hash_map.hpp\n\
    // Fixed-capacity hash map for integer keys.\n// N must be a power of two. At\
    \ most N distinct keys can be stored.\ntemplate <std::integral K, typename V,\
    \ std::size_t N> struct hash_map {\n    static_assert(sizeof(K) <= sizeof(std::uint64_t));\n\
    \    static_assert(std::has_single_bit(N));\n\n    hash_map() : multiplier(make_multiplier())\
    \ {}\n    void set(K key, V value) {\n        std::size_t pos = hash(key);\n \
    \       for (std::size_t step = 0; step < N; ++step) {\n            if (versions[pos]\
    \ != version) {\n                keys[pos] = key;\n                values[pos]\
    \ = value;\n                versions[pos] = version;\n                assert(count\
    \ < N);\n                ++count;\n                return;\n            }\n  \
    \          if (keys[pos] == key) {\n                values[pos] = value;\n   \
    \             return;\n            }\n            pos = (pos + 1) & (N - 1);\n\
    \        }\n        assert(false && \"hash map capacity exceeded\");\n    }\n\
    \    std::optional<V> get(K key) const {\n        std::size_t pos = hash(key);\n\
    \        for (std::size_t step = 0; step < N; ++step) {\n            if (versions[pos]\
    \ != version) {\n                return std::nullopt;\n            }\n       \
    \     if (keys[pos] == key) {\n                return values[pos];\n         \
    \   }\n            pos = (pos + 1) & (N - 1);\n        }\n        return std::nullopt;\n\
    \    }\n    std::size_t size() const { return count; }\n    bool empty() const\
    \ { return count == 0; }\n    void clear() {\n        ++version;\n        count\
    \ = 0;\n    }\n    void reset() { clear(); }\n\nprivate:\n    std::size_t hash(K\
    \ key) const {\n        if constexpr (N == 1) {\n            return 0;\n     \
    \   } else {\n            constexpr int shift = 64 - std::countr_zero(N);\n  \
    \          return (static_cast<std::uint64_t>(key) * multiplier) >> shift;\n \
    \       }\n    }\n    static std::uint64_t make_multiplier() {\n        std::mt19937_64\
    \ mt(std::chrono::steady_clock::now().time_since_epoch().count());\n        return\
    \ mt() | 1;\n    }\n\n    std::array<K, N> keys;\n    std::array<V, N> values;\n\
    \    std::array<std::uint32_t, N> versions{};\n    std::uint32_t version = 1;\n\
    \    std::size_t count = 0;\n    std::uint64_t multiplier;\n};\n\n\n#line 4 \"\
    test/data_structures/associative_array.test.cpp\"\n#include <bits/stdc++.h>\n\n\
    hash_map<long long, long long, 1 << 20> mp;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int Q;\n    std::cin >> Q;\n    while (Q--) {\n        int t;\n        std::cin\
    \ >> t;\n        if (t == 0) {\n            long long k, v;\n            std::cin\
    \ >> k >> v;\n            mp.set(k, v);\n        } else {\n            long long\
    \ k;\n            std::cin >> k;\n            std::cout << mp.get(k).value_or(0)\
    \ << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n\n\
    #include \"data_structures/hash_map.hpp\"\n#include <bits/stdc++.h>\n\nhash_map<long\
    \ long, long long, 1 << 20> mp;\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int Q;\n    std::cin >> Q;\n    while (Q--) {\n        int t;\n        std::cin\
    \ >> t;\n        if (t == 0) {\n            long long k, v;\n            std::cin\
    \ >> k >> v;\n            mp.set(k, v);\n        } else {\n            long long\
    \ k;\n            std::cin >> k;\n            std::cout << mp.get(k).value_or(0)\
    \ << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - data_structures/hash_map.hpp
  isVerificationFile: true
  path: test/data_structures/associative_array.test.cpp
  requiredBy: []
  timestamp: '2026-10-15 08:44:01+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structures/associative_array.test.cpp
layout: document
redirect_from:
- /verify/test/data_structures/associative_array.test.cpp
- /verify/test/data_structures/associative_array.test.cpp.html
title: test/data_structures/associative_array.test.cpp
---
