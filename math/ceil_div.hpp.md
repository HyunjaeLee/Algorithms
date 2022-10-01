---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
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
  requiredBy: []
  timestamp: '2022-10-01 07:25:57+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/ceil_div.hpp
layout: document
redirect_from:
- /library/math/ceil_div.hpp
- /library/math/ceil_div.hpp.html
title: math/ceil_div.hpp
---
