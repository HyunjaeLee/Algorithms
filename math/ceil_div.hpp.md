---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structures/line_container.hpp
    title: data_structures/line_container.hpp
  - icon: ':heavy_check_mark:'
    path: data_structures/line_container_2d.hpp
    title: data_structures/line_container_2d.hpp
  - icon: ':heavy_check_mark:'
    path: math/rational.hpp
    title: math/rational.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structures/line_container.test.cpp
    title: test/data_structures/line_container.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structures/yuki2012.test.cpp
    title: test/data_structures/yuki2012.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/ceil_div.hpp\"\n\n\n\ntemplate <typename T> T ceil_div(T\
    \ a, T b) {\n    return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0);\n}\n\
    \n\n"
  code: "#ifndef CEIL_DIV_HPP\n#define CEIL_DIV_HPP\n\ntemplate <typename T> T ceil_div(T\
    \ a, T b) {\n    return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0);\n}\n\
    \n#endif // CEIL_DIV_HPP"
  dependsOn: []
  isVerificationFile: false
  path: math/ceil_div.hpp
  requiredBy:
  - math/rational.hpp
  - data_structures/line_container.hpp
  - data_structures/line_container_2d.hpp
  timestamp: '2022-10-01 07:25:57+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structures/yuki2012.test.cpp
  - test/data_structures/line_container.test.cpp
documentation_of: math/ceil_div.hpp
layout: document
redirect_from:
- /library/math/ceil_div.hpp
- /library/math/ceil_div.hpp.html
title: math/ceil_div.hpp
---
