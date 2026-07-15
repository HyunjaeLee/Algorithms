---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: convolution/and.hpp
    title: convolution/and.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_and_convolution.test.cpp
    title: test/convolution/bitwise_and_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"transform/superset_zeta.hpp\"\n\n\n\n#include <bit>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename T> void superset_zeta_transform(std::vector<T>\
    \ &f) {\n    assert(std::has_single_bit(f.size()));\n    auto n = int(std::countr_zero(f.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto t = 0; t < (1 << n); ++t)\
    \ {\n            if (t & (1 << i)) {\n                f[t ^ (1 << i)] += f[t];\n\
    \            }\n        }\n    }\n}\n\n\n"
  code: "#ifndef SUPERSET_ZETA_HPP\n#define SUPERSET_ZETA_HPP\n\n#include <bit>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename T> void superset_zeta_transform(std::vector<T>\
    \ &f) {\n    assert(std::has_single_bit(f.size()));\n    auto n = int(std::countr_zero(f.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto t = 0; t < (1 << n); ++t)\
    \ {\n            if (t & (1 << i)) {\n                f[t ^ (1 << i)] += f[t];\n\
    \            }\n        }\n    }\n}\n\n#endif // SUPERSET_ZETA_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: transform/superset_zeta.hpp
  requiredBy:
  - convolution/and.hpp
  timestamp: '2026-07-15 17:03:35+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/bitwise_and_convolution.test.cpp
documentation_of: transform/superset_zeta.hpp
layout: document
redirect_from:
- /library/transform/superset_zeta.hpp
- /library/transform/superset_zeta.hpp.html
title: transform/superset_zeta.hpp
---
