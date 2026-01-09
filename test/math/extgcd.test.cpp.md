---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/extgcd.hpp
    title: Extended Euclidean Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E
  bundledCode: "#line 1 \"test/math/extgcd.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E\"\
    \n\n#line 1 \"math/extgcd.hpp\"\n\n\n\ntemplate <typename T> T extgcd(T a, T b,\
    \ T &x, T &y) {\n    if (b == 0) {\n        x = 1, y = 0;\n        return a;\n\
    \    }\n    T d = extgcd(b, a % b, y, x);\n    y -= a / b * x;\n    return d;\n\
    }\n\n\n#line 4 \"test/math/extgcd.test.cpp\"\n#include <bits/stdc++.h>\n\nint\
    \ main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int a, b;\n    std::cin\
    \ >> a >> b;\n    int x, y;\n    extgcd(a, b, x, y);\n    std::cout << x << \"\
    \ \" << y << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_E\"\n\n\
    #include \"math/extgcd.hpp\"\n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int a, b;\n    std::cin >> a >> b;\n    int x, y;\n    extgcd(a, b, x, y);\n\
    \    std::cout << x << \" \" << y << \"\\n\";\n}\n"
  dependsOn:
  - math/extgcd.hpp
  isVerificationFile: true
  path: test/math/extgcd.test.cpp
  requiredBy: []
  timestamp: '2026-01-09 14:45:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/math/extgcd.test.cpp
layout: document
redirect_from:
- /verify/test/math/extgcd.test.cpp
- /verify/test/math/extgcd.test.cpp.html
title: test/math/extgcd.test.cpp
---
