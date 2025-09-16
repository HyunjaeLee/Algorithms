---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/io/scanner.test.cpp
    title: test/io/scanner.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"io/scanner.hpp\"\n\n\n\n#include <charconv>\n#include <string_view>\n\
    #include <sys/mman.h>\n#include <sys/stat.h>\n#include <type_traits>\n\nstruct\
    \ scanner {\n    scanner() {\n        struct stat st;\n        fstat(0, &st);\n\
    \        data_ = p_ = static_cast<char *>(\n            mmap(nullptr, st.st_size,\
    \ PROT_READ, MAP_PRIVATE, 0, 0));\n        size_ = st.st_size;\n    }\n    template\
    \ <typename... Args> void operator()(Args &...args) {\n        (read(args), ...);\n\
    \    }\n    std::string_view getline() {\n        skip();\n        auto first\
    \ = p_;\n        while (*p_ >= ' ') {\n            ++p_;\n        }\n        return\
    \ std::string_view(first, p_ - first);\n    }\n\nprivate:\n    template <typename\
    \ T>\n    std::enable_if_t<std::is_integral_v<T>, void> read(T &x) {\n       \
    \ skip();\n        x = 0;\n        auto is_negative = false;\n        if (*p_\
    \ == '-') {\n            ++p_;\n            is_negative = true;\n        }\n \
    \       for (; *p_ > ' '; ++p_) {\n            x = (x << 1) + (x << 3) + (*p_\
    \ & 15);\n        }\n        if (is_negative) {\n            x = -x;\n       \
    \ }\n    }\n    template <typename T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ void> read(T &x) {\n        skip();\n        auto first = p_;\n        while\
    \ (*p_ > ' ') {\n            ++p_;\n        }\n        std::from_chars(first,\
    \ p_, x);\n    }\n    void read(char &x) {\n        skip();\n        x = *p_++;\n\
    \    }\n    void skip() {\n        while (*p_ <= ' ') {\n            ++p_;\n \
    \       }\n    }\n    char *data_;\n    char *p_;\n    size_t size_;\n};\n\n\n"
  code: "#ifndef SCANNER_HPP\n#define SCANNER_HPP\n\n#include <charconv>\n#include\
    \ <string_view>\n#include <sys/mman.h>\n#include <sys/stat.h>\n#include <type_traits>\n\
    \nstruct scanner {\n    scanner() {\n        struct stat st;\n        fstat(0,\
    \ &st);\n        data_ = p_ = static_cast<char *>(\n            mmap(nullptr,\
    \ st.st_size, PROT_READ, MAP_PRIVATE, 0, 0));\n        size_ = st.st_size;\n \
    \   }\n    template <typename... Args> void operator()(Args &...args) {\n    \
    \    (read(args), ...);\n    }\n    std::string_view getline() {\n        skip();\n\
    \        auto first = p_;\n        while (*p_ >= ' ') {\n            ++p_;\n \
    \       }\n        return std::string_view(first, p_ - first);\n    }\n\nprivate:\n\
    \    template <typename T>\n    std::enable_if_t<std::is_integral_v<T>, void>\
    \ read(T &x) {\n        skip();\n        x = 0;\n        auto is_negative = false;\n\
    \        if (*p_ == '-') {\n            ++p_;\n            is_negative = true;\n\
    \        }\n        for (; *p_ > ' '; ++p_) {\n            x = (x << 1) + (x <<\
    \ 3) + (*p_ & 15);\n        }\n        if (is_negative) {\n            x = -x;\n\
    \        }\n    }\n    template <typename T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ void> read(T &x) {\n        skip();\n        auto first = p_;\n        while\
    \ (*p_ > ' ') {\n            ++p_;\n        }\n        std::from_chars(first,\
    \ p_, x);\n    }\n    void read(char &x) {\n        skip();\n        x = *p_++;\n\
    \    }\n    void skip() {\n        while (*p_ <= ' ') {\n            ++p_;\n \
    \       }\n    }\n    char *data_;\n    char *p_;\n    size_t size_;\n};\n\n#endif\
    \ // SCANNER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: io/scanner.hpp
  requiredBy: []
  timestamp: '2022-09-01 14:58:55+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/io/scanner.test.cpp
documentation_of: io/scanner.hpp
layout: document
redirect_from:
- /library/io/scanner.hpp
- /library/io/scanner.hpp.html
title: io/scanner.hpp
---
