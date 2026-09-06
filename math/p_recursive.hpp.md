---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/math/aizu3614.test.cpp
    title: test/math/aizu3614.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://min-25.hatenablog.com/entry/2018/05/10/212805
  bundledCode: "#line 1 \"math/p_recursive.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdio>\n#include <utility>\n#include <vector>\n\n// https://min-25.hatenablog.com/entry/2018/05/10/212805\n\
    \ntemplate <typename Z>\nstd::vector<Z> extended(int n, const std::vector<std::vector<Z>>\
    \ &coeffs,\n                        const std::vector<Z> &terms) {\n    std::vector<Z>\
    \ ret(std::max(n + 1, int(terms.size())));\n    std::copy(terms.begin(), terms.end(),\
    \ ret.begin());\n    auto order = int(coeffs.size()) - 1;\n    auto deg = int(coeffs[0].size())\
    \ - 1;\n    assert(order <= int(terms.size()));\n    for (auto m = int(terms.size());\
    \ m <= n; ++m) {\n        Z s = 0;\n        for (auto i = 1; i <= order; ++i)\
    \ {\n            auto k = m - i;\n            auto t = ret[k];\n            for\
    \ (auto d = 0; d <= deg; ++d) {\n                s += t * coeffs[i][d];\n    \
    \            t *= k;\n            }\n        }\n        Z denom = 0, mpow = 1;\n\
    \        for (auto d = 0; d <= deg; ++d) {\n            denom += mpow * coeffs[0][d];\n\
    \            mpow *= m;\n        }\n        ret[m] = -s / denom;\n    }\n    return\
    \ ret;\n}\n\ntemplate <typename Z>\nstd::vector<std::vector<Z>> find_recurrence_relation(const\
    \ std::vector<Z> &terms, int deg,\n                                          \
    \           bool verify = true, bool verbose = true) {\n    auto n = int(terms.size());\n\
    \    auto B = (n + 2) / (deg + 2); // number of blocks\n    auto C = B * (deg\
    \ + 1);       // number of columns\n    auto R = n - (B - 1);         // number\
    \ of rows\n    assert(2 <= B);\n    assert(C - 1 <= R);\n    auto error = [](int\
    \ order, int d) {\n        std::fprintf(stderr,\n                     \"Error:\
    \ Could not find a recurrence relation \"\n                     \"of order <=\
    \ %d and degree <= %d.\\n\\n\",\n                     order, d);\n        assert(0);\n\
    \    };\n    std::vector<std::vector<Z>> mat(R, std::vector<Z>(C));\n    for (auto\
    \ y = 0; y < R; ++y) {\n        for (auto b = 0; b < B; ++b) {\n            auto\
    \ v = terms[y + b];\n            for (auto d = 0; d <= deg; ++d) {\n         \
    \       mat[y][b * (deg + 1) + d] = v;\n                v *= y + b;\n        \
    \    }\n        }\n    }\n    auto rank = 0;\n    for (auto x = 0; x < C; ++x)\
    \ {\n        auto pivot = -1;\n        for (auto y = rank; y < R; ++y) {\n   \
    \         if (mat[y][x] != 0) {\n                pivot = y;\n                break;\n\
    \            }\n        }\n        if (pivot < 0) {\n            break;\n    \
    \    }\n        if (pivot != rank) {\n            std::swap(mat[rank], mat[pivot]);\n\
    \        }\n        auto inv = mat[rank][x].inv();\n        for (auto x2 = x;\
    \ x2 < C; ++x2) {\n            mat[rank][x2] *= inv;\n        }\n        for (auto\
    \ y = rank + 1; y < R; ++y) {\n            if (mat[y][x] != 0) {\n           \
    \     auto c = -mat[y][x];\n                for (auto x2 = x; x2 < C; ++x2) {\n\
    \                    mat[y][x2] += c * mat[rank][x2];\n                }\n   \
    \         }\n        }\n        ++rank;\n    }\n    if (rank == C) {\n       \
    \ error(B - 1, deg);\n    }\n    for (auto y = rank - 1; 0 <= y; --y) {\n    \
    \    if (mat[y][rank] != 0) {\n            assert(mat[y][y] == 1);\n         \
    \   auto c = -mat[y][rank];\n            for (int y2 = 0; y2 < y; ++y2) {\n  \
    \              mat[y2][rank] += c * mat[y2][y];\n            }\n        }\n  \
    \  }\n    auto order = rank / (deg + 1);\n    std::vector<std::vector<Z>> ret(order\
    \ + 1, std::vector<Z>(deg + 1));\n    ret[0][rank % (deg + 1)] = 1;\n    for (auto\
    \ y = rank - 1; 0 <= y; --y) {\n        auto k = order - y / (deg + 1);\n    \
    \    auto d = y % (deg + 1);\n        ret[k][d] = -mat[y][rank];\n    }\n    if\
    \ (verify) {\n        auto extended_terms =\n            extended(n - 1, ret,\
    \ std::vector<Z>(terms.begin(), terms.begin() + order));\n        for (auto i\
    \ = 0; i < int(terms.size()); ++i) {\n            if (terms[i] != extended_terms[i])\
    \ {\n                error(B - 1, deg);\n            }\n        }\n    }\n   \
    \ if (verbose) {\n        auto mod = Z::mod();\n        auto last = verify ? n\
    \ - 1 : order + R - 1;\n        std::fprintf(stderr,\n                     \"\
    [ Found a recurrence relation ]\\n\"\n                     \"- order %d\\n\"\n\
    \                     \"- degree %d\\n\"\n                     \"- verified up\
    \ to a(%d) (number of non-trivial terms: %d)\\n\",\n                     order,\
    \ deg, last, (last + 1) - ((deg + 2) * (order + 1) - 2));\n        std::fprintf(stderr,\
    \ \"{\\n\");\n        for (auto k = 0; k <= order; ++k) {\n            std::fprintf(stderr,\
    \ \"  {\");\n            for (auto d = 0; d <= deg; ++d) {\n                if\
    \ (d) {\n                    std::fprintf(stderr, \", \");\n                }\n\
    \                auto v = ret[k][d].val();\n                std::fprintf(stderr,\
    \ \"%d\", v <= mod / 2 ? v : v - mod);\n            }\n            std::fprintf(stderr,\
    \ \"}%s\\n\", k == order ? \"\" : \",\");\n        }\n        std::fprintf(stderr,\
    \ \"}\\n\\n\");\n    }\n    return ret;\n}\n\n\n"
  code: "#ifndef P_RECURSIVE_HPP\n#define P_RECURSIVE_HPP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdio>\n#include <utility>\n#include <vector>\n\
    \n// https://min-25.hatenablog.com/entry/2018/05/10/212805\n\ntemplate <typename\
    \ Z>\nstd::vector<Z> extended(int n, const std::vector<std::vector<Z>> &coeffs,\n\
    \                        const std::vector<Z> &terms) {\n    std::vector<Z> ret(std::max(n\
    \ + 1, int(terms.size())));\n    std::copy(terms.begin(), terms.end(), ret.begin());\n\
    \    auto order = int(coeffs.size()) - 1;\n    auto deg = int(coeffs[0].size())\
    \ - 1;\n    assert(order <= int(terms.size()));\n    for (auto m = int(terms.size());\
    \ m <= n; ++m) {\n        Z s = 0;\n        for (auto i = 1; i <= order; ++i)\
    \ {\n            auto k = m - i;\n            auto t = ret[k];\n            for\
    \ (auto d = 0; d <= deg; ++d) {\n                s += t * coeffs[i][d];\n    \
    \            t *= k;\n            }\n        }\n        Z denom = 0, mpow = 1;\n\
    \        for (auto d = 0; d <= deg; ++d) {\n            denom += mpow * coeffs[0][d];\n\
    \            mpow *= m;\n        }\n        ret[m] = -s / denom;\n    }\n    return\
    \ ret;\n}\n\ntemplate <typename Z>\nstd::vector<std::vector<Z>> find_recurrence_relation(const\
    \ std::vector<Z> &terms, int deg,\n                                          \
    \           bool verify = true, bool verbose = true) {\n    auto n = int(terms.size());\n\
    \    auto B = (n + 2) / (deg + 2); // number of blocks\n    auto C = B * (deg\
    \ + 1);       // number of columns\n    auto R = n - (B - 1);         // number\
    \ of rows\n    assert(2 <= B);\n    assert(C - 1 <= R);\n    auto error = [](int\
    \ order, int d) {\n        std::fprintf(stderr,\n                     \"Error:\
    \ Could not find a recurrence relation \"\n                     \"of order <=\
    \ %d and degree <= %d.\\n\\n\",\n                     order, d);\n        assert(0);\n\
    \    };\n    std::vector<std::vector<Z>> mat(R, std::vector<Z>(C));\n    for (auto\
    \ y = 0; y < R; ++y) {\n        for (auto b = 0; b < B; ++b) {\n            auto\
    \ v = terms[y + b];\n            for (auto d = 0; d <= deg; ++d) {\n         \
    \       mat[y][b * (deg + 1) + d] = v;\n                v *= y + b;\n        \
    \    }\n        }\n    }\n    auto rank = 0;\n    for (auto x = 0; x < C; ++x)\
    \ {\n        auto pivot = -1;\n        for (auto y = rank; y < R; ++y) {\n   \
    \         if (mat[y][x] != 0) {\n                pivot = y;\n                break;\n\
    \            }\n        }\n        if (pivot < 0) {\n            break;\n    \
    \    }\n        if (pivot != rank) {\n            std::swap(mat[rank], mat[pivot]);\n\
    \        }\n        auto inv = mat[rank][x].inv();\n        for (auto x2 = x;\
    \ x2 < C; ++x2) {\n            mat[rank][x2] *= inv;\n        }\n        for (auto\
    \ y = rank + 1; y < R; ++y) {\n            if (mat[y][x] != 0) {\n           \
    \     auto c = -mat[y][x];\n                for (auto x2 = x; x2 < C; ++x2) {\n\
    \                    mat[y][x2] += c * mat[rank][x2];\n                }\n   \
    \         }\n        }\n        ++rank;\n    }\n    if (rank == C) {\n       \
    \ error(B - 1, deg);\n    }\n    for (auto y = rank - 1; 0 <= y; --y) {\n    \
    \    if (mat[y][rank] != 0) {\n            assert(mat[y][y] == 1);\n         \
    \   auto c = -mat[y][rank];\n            for (int y2 = 0; y2 < y; ++y2) {\n  \
    \              mat[y2][rank] += c * mat[y2][y];\n            }\n        }\n  \
    \  }\n    auto order = rank / (deg + 1);\n    std::vector<std::vector<Z>> ret(order\
    \ + 1, std::vector<Z>(deg + 1));\n    ret[0][rank % (deg + 1)] = 1;\n    for (auto\
    \ y = rank - 1; 0 <= y; --y) {\n        auto k = order - y / (deg + 1);\n    \
    \    auto d = y % (deg + 1);\n        ret[k][d] = -mat[y][rank];\n    }\n    if\
    \ (verify) {\n        auto extended_terms =\n            extended(n - 1, ret,\
    \ std::vector<Z>(terms.begin(), terms.begin() + order));\n        for (auto i\
    \ = 0; i < int(terms.size()); ++i) {\n            if (terms[i] != extended_terms[i])\
    \ {\n                error(B - 1, deg);\n            }\n        }\n    }\n   \
    \ if (verbose) {\n        auto mod = Z::mod();\n        auto last = verify ? n\
    \ - 1 : order + R - 1;\n        std::fprintf(stderr,\n                     \"\
    [ Found a recurrence relation ]\\n\"\n                     \"- order %d\\n\"\n\
    \                     \"- degree %d\\n\"\n                     \"- verified up\
    \ to a(%d) (number of non-trivial terms: %d)\\n\",\n                     order,\
    \ deg, last, (last + 1) - ((deg + 2) * (order + 1) - 2));\n        std::fprintf(stderr,\
    \ \"{\\n\");\n        for (auto k = 0; k <= order; ++k) {\n            std::fprintf(stderr,\
    \ \"  {\");\n            for (auto d = 0; d <= deg; ++d) {\n                if\
    \ (d) {\n                    std::fprintf(stderr, \", \");\n                }\n\
    \                auto v = ret[k][d].val();\n                std::fprintf(stderr,\
    \ \"%d\", v <= mod / 2 ? v : v - mod);\n            }\n            std::fprintf(stderr,\
    \ \"}%s\\n\", k == order ? \"\" : \",\");\n        }\n        std::fprintf(stderr,\
    \ \"}\\n\\n\");\n    }\n    return ret;\n}\n\n#endif // P_RECURSIVE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: math/p_recursive.hpp
  requiredBy: []
  timestamp: '2026-09-06 18:51:02+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/math/aizu3614.test.cpp
documentation_of: math/p_recursive.hpp
layout: document
redirect_from:
- /library/math/p_recursive.hpp
- /library/math/p_recursive.hpp.html
title: math/p_recursive.hpp
---
