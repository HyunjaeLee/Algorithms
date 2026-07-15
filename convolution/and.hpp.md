---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: transform/superset_mobius.hpp
    title: transform/superset_mobius.hpp
  - icon: ':heavy_check_mark:'
    path: transform/superset_zeta.hpp
    title: transform/superset_zeta.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_and_convolution.test.cpp
    title: test/convolution/bitwise_and_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convolution/and.hpp\"\n\n\n\n#line 1 \"transform/superset_mobius.hpp\"\
    \n\n\n\n#include <bit>\n#include <cassert>\n#include <vector>\n\ntemplate <typename\
    \ T> void superset_mobius_transform(std::vector<T> &g) {\n    assert(std::has_single_bit(g.size()));\n\
    \    auto n = int(std::countr_zero(g.size()));\n    for (auto i = 0; i < n; ++i)\
    \ {\n        for (auto s = 0; s < (1 << n); ++s) {\n            if (s & (1 <<\
    \ i)) {\n                g[s ^ (1 << i)] -= g[s];\n            }\n        }\n\
    \    }\n}\n\n\n#line 1 \"transform/superset_zeta.hpp\"\n\n\n\n#line 7 \"transform/superset_zeta.hpp\"\
    \n\ntemplate <typename T> void superset_zeta_transform(std::vector<T> &f) {\n\
    \    assert(std::has_single_bit(f.size()));\n    auto n = int(std::countr_zero(f.size()));\n\
    \    for (auto i = 0; i < n; ++i) {\n        for (auto s = 0; s < (1 << n); ++s)\
    \ {\n            if (s & (1 << i)) {\n                f[s ^ (1 << i)] += f[s];\n\
    \            }\n        }\n    }\n}\n\n\n#line 8 \"convolution/and.hpp\"\n\ntemplate\
    \ <typename T> std::vector<T> and_convolution(std::vector<T> a, std::vector<T>\
    \ b) {\n    assert(a.size() == b.size());\n    superset_zeta_transform(a);\n \
    \   superset_zeta_transform(b);\n    for (auto i = 0; i < int(a.size()); ++i)\
    \ {\n        a[i] *= b[i];\n    }\n    superset_mobius_transform(a);\n    return\
    \ a;\n}\n\n\n"
  code: "#ifndef AND_HPP\n#define AND_HPP\n\n#include \"transform/superset_mobius.hpp\"\
    \n#include \"transform/superset_zeta.hpp\"\n#include <cassert>\n#include <vector>\n\
    \ntemplate <typename T> std::vector<T> and_convolution(std::vector<T> a, std::vector<T>\
    \ b) {\n    assert(a.size() == b.size());\n    superset_zeta_transform(a);\n \
    \   superset_zeta_transform(b);\n    for (auto i = 0; i < int(a.size()); ++i)\
    \ {\n        a[i] *= b[i];\n    }\n    superset_mobius_transform(a);\n    return\
    \ a;\n}\n\n#endif // AND_HPP\n"
  dependsOn:
  - transform/superset_mobius.hpp
  - transform/superset_zeta.hpp
  isVerificationFile: false
  path: convolution/and.hpp
  requiredBy: []
  timestamp: '2026-07-15 17:18:58+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/bitwise_and_convolution.test.cpp
documentation_of: convolution/and.hpp
layout: document
redirect_from:
- /library/convolution/and.hpp
- /library/convolution/and.hpp.html
title: convolution/and.hpp
---
