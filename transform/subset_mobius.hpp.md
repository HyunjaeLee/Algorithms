---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: convolution/or.hpp
    title: convolution/or.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_or_convolution.test.cpp
    title: test/convolution/bitwise_or_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"transform/subset_mobius.hpp\"\n\n\n\n#include <bit>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename T> void subset_mobius_transform(std::vector<T>\
    \ &g) {\n    assert(std::has_single_bit(g.size()));\n    auto n = int(std::countr_zero(g.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto s = 0; s < (1 << n); ++s)\
    \ {\n            if (s & (1 << i)) {\n                g[s] -= g[s ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n\n"
  code: "#ifndef SUBSET_MOBIUS_HPP\n#define SUBSET_MOBIUS_HPP\n\n#include <bit>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename T> void subset_mobius_transform(std::vector<T>\
    \ &g) {\n    assert(std::has_single_bit(g.size()));\n    auto n = int(std::countr_zero(g.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto s = 0; s < (1 << n); ++s)\
    \ {\n            if (s & (1 << i)) {\n                g[s] -= g[s ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n#endif // SUBSET_MOBIUS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: transform/subset_mobius.hpp
  requiredBy:
  - convolution/or.hpp
  timestamp: '2026-07-15 17:18:58+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/bitwise_or_convolution.test.cpp
documentation_of: transform/subset_mobius.hpp
layout: document
redirect_from:
- /library/transform/subset_mobius.hpp
- /library/transform/subset_mobius.hpp.html
title: transform/subset_mobius.hpp
---
