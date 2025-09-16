---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: matching/stable_matching.hpp
    title: Stable matching
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"test/matching/stable_matching.stress.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#line 1 \"matching/stable_matching.hpp\"\n\n\n\n#include <numeric>\n#include\
    \ <vector>\n\nstd::vector<int> stable_matching(const std::vector<std::vector<int>>\
    \ &a,\n                                 const std::vector<std::vector<int>> &b)\
    \ {\n    const auto n = static_cast<int>(a.size());\n    std::vector<std::vector<int>>\
    \ b_priority(n, std::vector<int>(n));\n    for (auto i = 0; i < n; ++i) {\n  \
    \      for (auto j = 0; j < n; ++j) {\n            b_priority[i][b[i][j]] = j;\n\
    \        }\n    }\n    std::vector<int> a_propose(n), b_match(n, -1), unmatched(n);\n\
    \    std::iota(unmatched.begin(), unmatched.end(), 0);\n    while (!unmatched.empty())\
    \ {\n        const auto l = unmatched.back();\n        unmatched.pop_back();\n\
    \        const auto r = a[l][a_propose[l]];\n        if (b_match[r] == -1) {\n\
    \            b_match[r] = l;\n        } else if (b_priority[r][l] < b_priority[r][b_match[r]])\
    \ {\n            ++a_propose[b_match[r]];\n            unmatched.push_back(b_match[r]);\n\
    \            b_match[r] = l;\n        } else {\n            ++a_propose[l];\n\
    \            unmatched.push_back(l);\n        }\n    }\n    std::vector<int> a_match(n);\n\
    \    for (auto i = 0; i < n; ++i) {\n        a_match[b_match[i]] = i;\n    }\n\
    \    return a_match;\n}\n\n\n#line 4 \"test/matching/stable_matching.stress.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nvoid assert_unique(std::vector<int> v, int n) {\n\
    \    assert(static_cast<int>(v.size()) == n);\n    std::sort(v.begin(), v.end());\n\
    \    for (auto i = 0; i < n; ++i) {\n        assert(v[i] == i);\n    }\n}\n\n\
    void test() {\n    for (auto n = 1; n <= 100; ++n) {\n        std::vector<std::vector<int>>\
    \ a(n, std::vector<int>(n)),\n            b(n, std::vector<int>(n));\n       \
    \ std::mt19937 g(0);\n        for (auto i = 0; i < n; ++i) {\n            std::iota(a[i].begin(),\
    \ a[i].end(), 0);\n            std::shuffle(a[i].begin(), a[i].end(), g);\n  \
    \      }\n        for (auto i = 0; i < n; ++i) {\n            std::iota(b[i].begin(),\
    \ b[i].end(), 0);\n            std::shuffle(b[i].begin(), b[i].end(), g);\n  \
    \      }\n        std::vector<std::vector<int>> a_priority(n, std::vector<int>(n)),\n\
    \            b_priority(n, std::vector<int>(n));\n        for (auto i = 0; i <\
    \ n; ++i) {\n            for (auto j = 0; j < n; ++j) {\n                a_priority[i][a[i][j]]\
    \ = j;\n            }\n        }\n        for (auto i = 0; i < n; ++i) {\n   \
    \         for (auto j = 0; j < n; ++j) {\n                b_priority[i][b[i][j]]\
    \ = j;\n            }\n        }\n        auto a_match = stable_matching(a, b);\n\
    \        assert_unique(a_match, n);\n        std::vector<int> b_match(n);\n  \
    \      for (auto i = 0; i < n; ++i) {\n            b_match[a_match[i]] = i;\n\
    \        }\n        for (auto i = 0; i < n; ++i) {\n            for (auto j =\
    \ 0; j < n; ++j) {\n                assert(!(a_priority[i][j] < a_priority[i][a_match[i]]\
    \ &&\n                         b_priority[j][i] < b_priority[j][b_match[j]]));\n\
    \            }\n        }\n    }\n}\n\nint main() {\n    test();\n    std::cout\
    \ << \"Hello World\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \n\n#include \"matching/stable_matching.hpp\"\n#include <bits/stdc++.h>\n\nvoid\
    \ assert_unique(std::vector<int> v, int n) {\n    assert(static_cast<int>(v.size())\
    \ == n);\n    std::sort(v.begin(), v.end());\n    for (auto i = 0; i < n; ++i)\
    \ {\n        assert(v[i] == i);\n    }\n}\n\nvoid test() {\n    for (auto n =\
    \ 1; n <= 100; ++n) {\n        std::vector<std::vector<int>> a(n, std::vector<int>(n)),\n\
    \            b(n, std::vector<int>(n));\n        std::mt19937 g(0);\n        for\
    \ (auto i = 0; i < n; ++i) {\n            std::iota(a[i].begin(), a[i].end(),\
    \ 0);\n            std::shuffle(a[i].begin(), a[i].end(), g);\n        }\n   \
    \     for (auto i = 0; i < n; ++i) {\n            std::iota(b[i].begin(), b[i].end(),\
    \ 0);\n            std::shuffle(b[i].begin(), b[i].end(), g);\n        }\n   \
    \     std::vector<std::vector<int>> a_priority(n, std::vector<int>(n)),\n    \
    \        b_priority(n, std::vector<int>(n));\n        for (auto i = 0; i < n;\
    \ ++i) {\n            for (auto j = 0; j < n; ++j) {\n                a_priority[i][a[i][j]]\
    \ = j;\n            }\n        }\n        for (auto i = 0; i < n; ++i) {\n   \
    \         for (auto j = 0; j < n; ++j) {\n                b_priority[i][b[i][j]]\
    \ = j;\n            }\n        }\n        auto a_match = stable_matching(a, b);\n\
    \        assert_unique(a_match, n);\n        std::vector<int> b_match(n);\n  \
    \      for (auto i = 0; i < n; ++i) {\n            b_match[a_match[i]] = i;\n\
    \        }\n        for (auto i = 0; i < n; ++i) {\n            for (auto j =\
    \ 0; j < n; ++j) {\n                assert(!(a_priority[i][j] < a_priority[i][a_match[i]]\
    \ &&\n                         b_priority[j][i] < b_priority[j][b_match[j]]));\n\
    \            }\n        }\n    }\n}\n\nint main() {\n    test();\n    std::cout\
    \ << \"Hello World\\n\";\n}\n"
  dependsOn:
  - matching/stable_matching.hpp
  isVerificationFile: true
  path: test/matching/stable_matching.stress.test.cpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/matching/stable_matching.stress.test.cpp
layout: document
redirect_from:
- /verify/test/matching/stable_matching.stress.test.cpp
- /verify/test/matching/stable_matching.stress.test.cpp.html
title: test/matching/stable_matching.stress.test.cpp
---
