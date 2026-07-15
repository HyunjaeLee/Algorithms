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
  bundledCode: "#line 1 \"transform/superset_mobius.hpp\"\n\n\n\n#include <bit>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename T> void superset_mobius_transform(std::vector<T>\
    \ &g) {\n    assert(std::has_single_bit(g.size()));\n    auto n = int(std::countr_zero(g.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto s = 0; s < (1 << n); ++s)\
    \ {\n            if (s & (1 << i)) {\n                g[s ^ (1 << i)] -= g[s];\n\
    \            }\n        }\n    }\n}\n\n\n"
  code: "#ifndef SUPERSET_MOBIUS_HPP\n#define SUPERSET_MOBIUS_HPP\n\n#include <bit>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename T> void superset_mobius_transform(std::vector<T>\
    \ &g) {\n    assert(std::has_single_bit(g.size()));\n    auto n = int(std::countr_zero(g.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto s = 0; s < (1 << n); ++s)\
    \ {\n            if (s & (1 << i)) {\n                g[s ^ (1 << i)] -= g[s];\n\
    \            }\n        }\n    }\n}\n\n#endif // SUPERSET_MOBIUS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: transform/superset_mobius.hpp
  requiredBy:
  - convolution/and.hpp
  timestamp: '2026-07-15 17:18:58+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/bitwise_and_convolution.test.cpp
documentation_of: transform/superset_mobius.hpp
layout: document
redirect_from:
- /library/transform/superset_mobius.hpp
- /library/transform/superset_mobius.hpp.html
title: transform/superset_mobius.hpp
---
