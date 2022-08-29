---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/scanner.test.cpp
    title: test/scanner.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"io/scanner.hpp\"\n\n#include <charconv>\n#include <sys/mman.h>\n\
    #include <sys/stat.h>\n#include <type_traits>\n\nstruct scanner {\npublic:\n \
    \   scanner() {\n        struct stat st;\n        fstat(0, &st);\n        data_\
    \ = p_ = static_cast<char *>(\n            mmap(nullptr, st.st_size, PROT_READ,\
    \ MAP_PRIVATE, 0, 0));\n        size_ = st.st_size;\n    }\n    template <typename...\
    \ Args> void operator()(Args &...args) {\n        (read(args), ...);\n    }\n\n\
    private:\n    template <typename T>\n    std::enable_if_t<std::is_integral_v<T>,\
    \ void> read(T &x) {\n        skip();\n        x = 0;\n        for (; *p_ > '\
    \ '; ++p_) {\n            x = (x << 1) + (x << 3) + (*p_ & 15);\n        }\n \
    \   }\n    template <typename T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ void> read(T &x) {\n        skip();\n        auto first = p_;\n        while\
    \ (*p_ > ' ') {\n            ++p_;\n        }\n        std::from_chars(first,\
    \ p_, x);\n    }\n    void read(char &x) {\n        skip();\n        x = *p_++;\n\
    \    }\n    void skip() {\n        while (*p_ <= ' ') {\n            ++p_;\n \
    \       }\n    }\n    char *data_;\n    char *p_;\n    size_t size_;\n};\n"
  code: "#pragma once\n\n#include <charconv>\n#include <sys/mman.h>\n#include <sys/stat.h>\n\
    #include <type_traits>\n\nstruct scanner {\npublic:\n    scanner() {\n       \
    \ struct stat st;\n        fstat(0, &st);\n        data_ = p_ = static_cast<char\
    \ *>(\n            mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0));\n\
    \        size_ = st.st_size;\n    }\n    template <typename... Args> void operator()(Args\
    \ &...args) {\n        (read(args), ...);\n    }\n\nprivate:\n    template <typename\
    \ T>\n    std::enable_if_t<std::is_integral_v<T>, void> read(T &x) {\n       \
    \ skip();\n        x = 0;\n        for (; *p_ > ' '; ++p_) {\n            x =\
    \ (x << 1) + (x << 3) + (*p_ & 15);\n        }\n    }\n    template <typename\
    \ T>\n    std::enable_if_t<std::is_floating_point_v<T>, void> read(T &x) {\n \
    \       skip();\n        auto first = p_;\n        while (*p_ > ' ') {\n     \
    \       ++p_;\n        }\n        std::from_chars(first, p_, x);\n    }\n    void\
    \ read(char &x) {\n        skip();\n        x = *p_++;\n    }\n    void skip()\
    \ {\n        while (*p_ <= ' ') {\n            ++p_;\n        }\n    }\n    char\
    \ *data_;\n    char *p_;\n    size_t size_;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: io/scanner.hpp
  requiredBy: []
  timestamp: '2022-08-29 12:37:26+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/scanner.test.cpp
documentation_of: io/scanner.hpp
layout: document
redirect_from:
- /library/io/scanner.hpp
- /library/io/scanner.hpp.html
title: io/scanner.hpp
---
