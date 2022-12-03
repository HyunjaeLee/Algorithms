---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/stable_matching.stress.test.cpp
    title: test/stable_matching.stress.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matching/stable_matching.hpp\"\n\n\n\n#include <numeric>\n\
    #include <vector>\n\nstd::vector<int> stable_matching(const std::vector<std::vector<int>>\
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
    \    return a_match;\n}\n\n\n"
  code: "#ifndef STABLE_MATCHING_HPP\n#define STABLE_MATCHING_HPP\n\n#include <numeric>\n\
    #include <vector>\n\nstd::vector<int> stable_matching(const std::vector<std::vector<int>>\
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
    \    return a_match;\n}\n\n#endif // STABLE_MATCHING_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matching/stable_matching.hpp
  requiredBy: []
  timestamp: '2022-12-03 14:13:47+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/stable_matching.stress.test.cpp
documentation_of: matching/stable_matching.hpp
layout: document
title: Stable matching
---

It solves stable matching problem using the Gale-Shapley algorithm. The algorithm results in a perfect matching and a stable matching. For given sets $A$ and $B$ the result is $A$-optimal and $B$-pessimal. It assumes that $\lvert A \rvert = \lvert B \rvert = n$.

stable_matching
---
```cpp
std::vector<int> stable_matching(const std::vector<std::vector<int>> &a,
                                 const std::vector<std::vector<int>> &b);
```

### Parameters
__a, b__  
$a$ is an $n \times n$ 2D vector. $a[i]$ is a permutation of $0, 1, \cdots, n-1$. For $0 \le j \lt k \lt n$, $i$ prefers $a[i][j]$ over $a[i][k]$, where $i$ is in set $A$ and $a[i][j]$ and $a[i][k]$ are in set $B$. For $b$ it's vice versa.

### Return value
It returns a vector $r$ of length $n$, such that $i$ in set $A$ and $r[i]$ in set $B$ are matched.

### Complexity
$\mathcal{O}\left(n^2\right)$

### References
+ [Stable matching presentation - CMU](https://www.cs.cmu.edu/~arielpro/15896s16/slides/896s16-16.pdf)
+ [Gale-Shapley algorithm - Wikipedia](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm)
+ [Stable marriage problem - Wikipedia](https://en.wikipedia.org/wiki/Stable_marriage_problem)
