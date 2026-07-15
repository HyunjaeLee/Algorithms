---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: convolution/or.hpp
    title: convolution/or.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"transform/subset_mobius.hpp\"\n\n\n\n#include <bit>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename T> void subset_mobius_transform(std::vector<T>\
    \ &g) {\n    assert(std::has_single_bit(g.size()));\n    auto n = int(std::countr_zero(g.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto t = 0; t < (1 << n); ++t)\
    \ {\n            if (t & (1 << i)) {\n                g[t] -= g[t ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n\n"
  code: "#ifndef SUBSET_MOBIUS_HPP\n#define SUBSET_MOBIUS_HPP\n\n#include <bit>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename T> void subset_mobius_transform(std::vector<T>\
    \ &g) {\n    assert(std::has_single_bit(g.size()));\n    auto n = int(std::countr_zero(g.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto t = 0; t < (1 << n); ++t)\
    \ {\n            if (t & (1 << i)) {\n                g[t] -= g[t ^ (1 << i)];\n\
    \            }\n        }\n    }\n}\n\n#endif // SUBSET_MOBIUS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: transform/subset_mobius.hpp
  requiredBy:
  - convolution/or.hpp
  timestamp: '2026-07-15 17:03:35+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: transform/subset_mobius.hpp
layout: document
redirect_from:
- /library/transform/subset_mobius.hpp
- /library/transform/subset_mobius.hpp.html
title: transform/subset_mobius.hpp
---
