---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structures/associative_array.test.cpp
    title: test/data_structures/associative_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://hitonanode.github.io/cplib-cpp/data_structure/fast_hash_map.hpp
  bundledCode: "#line 1 \"data_structures/hash_map.hpp\"\n\n\n\n#include <array>\n\
    #include <bit>\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <cstdint>\n#include <optional>\n#include <random>\n\n//\
    \ https://hitonanode.github.io/cplib-cpp/data_structure/fast_hash_map.hpp\n//\
    \ Fixed-capacity hash map for integer keys.\n// N must be a power of two. At most\
    \ N distinct keys can be stored.\ntemplate <std::integral K, typename V, std::size_t\
    \ N> struct hash_map {\n    static_assert(sizeof(K) <= sizeof(std::uint64_t));\n\
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
    \    std::size_t count = 0;\n    std::uint64_t multiplier;\n};\n\n\n"
  code: "#ifndef HASH_MAP_HPP\n#define HASH_MAP_HPP\n\n#include <array>\n#include\
    \ <bit>\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <cstdint>\n#include <optional>\n#include <random>\n\n//\
    \ https://hitonanode.github.io/cplib-cpp/data_structure/fast_hash_map.hpp\n//\
    \ Fixed-capacity hash map for integer keys.\n// N must be a power of two. At most\
    \ N distinct keys can be stored.\ntemplate <std::integral K, typename V, std::size_t\
    \ N> struct hash_map {\n    static_assert(sizeof(K) <= sizeof(std::uint64_t));\n\
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
    \    std::size_t count = 0;\n    std::uint64_t multiplier;\n};\n\n#endif // HASH_MAP_HPP"
  dependsOn: []
  isVerificationFile: false
  path: data_structures/hash_map.hpp
  requiredBy: []
  timestamp: '2026-10-15 08:44:01+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structures/associative_array.test.cpp
documentation_of: data_structures/hash_map.hpp
layout: document
redirect_from:
- /library/data_structures/hash_map.hpp
- /library/data_structures/hash_map.hpp.html
title: data_structures/hash_map.hpp
---
