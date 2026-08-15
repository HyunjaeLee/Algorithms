---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/optimization/aizu2069.test.cpp
    title: test/optimization/aizu2069.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/optimization/aizu2963.test.cpp
    title: test/optimization/aizu2963.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"optimization/canonical_coin_system.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <numeric>\n#include <tuple>\n#include <vector>\n\n// O(n^3),\
    \ requires distinct positive integers including 1\n// return (is canonical, smallest\
    \ counterexample w, M(w))\n// David Pearson, \"A Polynomial-time Algorithm for\
    \ the Change-Making Problem\"\ntemplate <typename T> std::tuple<bool, T, std::vector<T>>\
    \ greedy_optimality(std::vector<T> coins) {\n    auto n = int(coins.size());\n\
    \    std::sort(coins.rbegin(), coins.rend());\n    auto greedy = [&](T x) {\n\
    \        std::vector<T> v(n);\n        for (auto i = 0; i < n; ++i) {\n      \
    \      v[i] = x / coins[i];\n            x %= coins[i];\n        }\n        return\
    \ v;\n    };\n    auto count = [](const std::vector<T> &v) { return std::accumulate(v.begin(),\
    \ v.end(), T(0)); };\n    auto comp = [&](const auto &a, const auto &b) {\n  \
    \      const auto &[ca, wa, ma] = a;\n        const auto &[cb, wb, mb] = b;\n\
    \        if (ca != cb)\n            return ca < cb;\n        if (wa != wb)\n \
    \           return wa < wb;\n        auto sa = count(ma);\n        auto sb = count(mb);\n\
    \        if (sa != sb)\n            return sa < sb;\n        return ma > mb;\n\
    \    };\n    std::tuple<bool, T, std::vector<T>> ans{true, -1, {}};\n    for (auto\
    \ i = 1; i < n; ++i) {\n        auto v = greedy(coins[i - 1] - 1);\n        for\
    \ (auto j = i; j < n; ++j) {\n            std::vector<T> mw(n);\n            std::copy(v.begin(),\
    \ v.begin() + j, mw.begin());\n            mw[j] = v[j] + 1;\n            auto\
    \ w = std::inner_product(coins.begin(), coins.end(), mw.begin(), T(0));\n    \
    \        auto gw = greedy(w);\n            if (count(mw) < count(gw)) {\n    \
    \            ans = std::ranges::min(ans, {false, w, mw}, comp);\n            }\n\
    \        }\n    }\n    return ans;\n}\n\n\n"
  code: "#ifndef CANONICAL_COIN_SYSTEM_HPP\n#define CANONICAL_COIN_SYSTEM_HPP\n\n\
    #include <algorithm>\n#include <numeric>\n#include <tuple>\n#include <vector>\n\
    \n// O(n^3), requires distinct positive integers including 1\n// return (is canonical,\
    \ smallest counterexample w, M(w))\n// David Pearson, \"A Polynomial-time Algorithm\
    \ for the Change-Making Problem\"\ntemplate <typename T> std::tuple<bool, T, std::vector<T>>\
    \ greedy_optimality(std::vector<T> coins) {\n    auto n = int(coins.size());\n\
    \    std::sort(coins.rbegin(), coins.rend());\n    auto greedy = [&](T x) {\n\
    \        std::vector<T> v(n);\n        for (auto i = 0; i < n; ++i) {\n      \
    \      v[i] = x / coins[i];\n            x %= coins[i];\n        }\n        return\
    \ v;\n    };\n    auto count = [](const std::vector<T> &v) { return std::accumulate(v.begin(),\
    \ v.end(), T(0)); };\n    auto comp = [&](const auto &a, const auto &b) {\n  \
    \      const auto &[ca, wa, ma] = a;\n        const auto &[cb, wb, mb] = b;\n\
    \        if (ca != cb)\n            return ca < cb;\n        if (wa != wb)\n \
    \           return wa < wb;\n        auto sa = count(ma);\n        auto sb = count(mb);\n\
    \        if (sa != sb)\n            return sa < sb;\n        return ma > mb;\n\
    \    };\n    std::tuple<bool, T, std::vector<T>> ans{true, -1, {}};\n    for (auto\
    \ i = 1; i < n; ++i) {\n        auto v = greedy(coins[i - 1] - 1);\n        for\
    \ (auto j = i; j < n; ++j) {\n            std::vector<T> mw(n);\n            std::copy(v.begin(),\
    \ v.begin() + j, mw.begin());\n            mw[j] = v[j] + 1;\n            auto\
    \ w = std::inner_product(coins.begin(), coins.end(), mw.begin(), T(0));\n    \
    \        auto gw = greedy(w);\n            if (count(mw) < count(gw)) {\n    \
    \            ans = std::ranges::min(ans, {false, w, mw}, comp);\n            }\n\
    \        }\n    }\n    return ans;\n}\n\n#endif // CANONICAL_COIN_SYSTEM_HPP"
  dependsOn: []
  isVerificationFile: false
  path: optimization/canonical_coin_system.hpp
  requiredBy: []
  timestamp: '2026-08-15 04:52:31+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/optimization/aizu2069.test.cpp
  - test/optimization/aizu2963.test.cpp
documentation_of: optimization/canonical_coin_system.hpp
layout: document
title: A Polynomial-time Algorithm for the Change-Making Problem
---
