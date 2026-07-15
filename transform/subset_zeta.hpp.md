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
  bundledCode: "#line 1 \"transform/subset_zeta.hpp\"\n\n\n\n#include <bit>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename T> void subset_zeta_transform(std::vector<T>\
    \ &f) {\n    assert(std::has_single_bit(f.size()));\n    auto n = int(std::countr_zero(f.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto t = 0; t < (1 << n); ++t)\
    \ {\n            if (t & (1 << i)) {\n                f[t] += f[t ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n\n"
  code: "#ifndef SUBSET_ZETA_HPP\n#define SUBSET_ZETA_HPP\n\n#include <bit>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename T> void subset_zeta_transform(std::vector<T>\
    \ &f) {\n    assert(std::has_single_bit(f.size()));\n    auto n = int(std::countr_zero(f.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto t = 0; t < (1 << n); ++t)\
    \ {\n            if (t & (1 << i)) {\n                f[t] += f[t ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n#endif // SUBSET_ZETA_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: transform/subset_zeta.hpp
  requiredBy:
  - convolution/or.hpp
  timestamp: '2026-07-15 17:03:35+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/bitwise_or_convolution.test.cpp
documentation_of: transform/subset_zeta.hpp
layout: document
redirect_from:
- /library/transform/subset_zeta.hpp
- /library/transform/subset_zeta.hpp.html
title: transform/subset_zeta.hpp
---
