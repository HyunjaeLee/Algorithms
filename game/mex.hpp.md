---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: game/numnim.hpp
    title: game/numnim.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"game/mex.hpp\"\n\n\n\n#include <vector>\n\nint mex(const\
    \ auto &a) {\n    auto n = int(a.size());\n    std::vector<bool> f(n);\n    for\
    \ (auto x : a) {\n        if (x < n) {\n            f[x] = true;\n        }\n\
    \    }\n    for (auto i = 0; i < n; ++i) {\n        if (!f[i]) {\n           \
    \ return i;\n        }\n    }\n    return n;\n}\n\n\n"
  code: "#ifndef MEX_HPP\n#define MEX_HPP\n\n#include <vector>\n\nint mex(const auto\
    \ &a) {\n    auto n = int(a.size());\n    std::vector<bool> f(n);\n    for (auto\
    \ x : a) {\n        if (x < n) {\n            f[x] = true;\n        }\n    }\n\
    \    for (auto i = 0; i < n; ++i) {\n        if (!f[i]) {\n            return\
    \ i;\n        }\n    }\n    return n;\n}\n\n#endif // MEX_HPP"
  dependsOn: []
  isVerificationFile: false
  path: game/mex.hpp
  requiredBy:
  - game/numnim.hpp
  timestamp: '2026-11-05 13:44:03+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: game/mex.hpp
layout: document
redirect_from:
- /library/game/mex.hpp
- /library/game/mex.hpp.html
title: game/mex.hpp
---
