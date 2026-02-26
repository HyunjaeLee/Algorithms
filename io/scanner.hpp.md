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
  bundledCode: "#line 1 \"io/scanner.hpp\"\n\n\n\n#include <charconv>\n#include <concepts>\n\
    #include <iostream>\n#include <iterator>\n#include <string>\n#include <string_view>\n\
    #include <sys/mman.h>\n#include <sys/stat.h>\n\nstruct scanner {\n    scanner()\
    \ {\n        struct stat st;\n        fstat(0, &st);\n        if (S_ISREG(st.st_mode))\
    \ {\n            data_ = p_ = (char *)mmap(nullptr, st.st_size + 65536, PROT_READ,\n\
    \                                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);\n\
    \            if (st.st_size) {\n                mmap(data_, st.st_size, PROT_READ,\
    \ MAP_PRIVATE | MAP_FIXED, 0, 0);\n            }\n        } else {\n         \
    \   auto *s = new std::string(std::istreambuf_iterator<char>(std::cin), {});\n\
    \            data_ = p_ = s->data();\n        }\n    }\n    template <typename...\
    \ Args> void operator()(Args &...args) { (scan(args), ...); }\n    std::string_view\
    \ getline() {\n        skip();\n        auto first = p_;\n        while (*p_ >=\
    \ ' ') {\n            ++p_;\n        }\n        return std::string_view(first,\
    \ p_ - first);\n    }\n    auto &operator>>(auto &x) {\n        scan(x);\n   \
    \     return *this;\n    }\n\nprivate:\n    void scan(std::integral auto &x) {\n\
    \        skip();\n        x = 0;\n        auto is_negative = false;\n        if\
    \ (*p_ == '-') {\n            ++p_;\n            is_negative = true;\n       \
    \ }\n        for (; *p_ > ' '; ++p_) {\n            x = x * 10 + (*p_ & 15);\n\
    \        }\n        if (is_negative) {\n            x = -x;\n        }\n    }\n\
    \    void scan(std::floating_point auto &x) {\n        skip();\n        auto first\
    \ = p_;\n        while (*p_ > ' ') {\n            ++p_;\n        }\n        std::from_chars(first,\
    \ p_, x);\n    }\n    void scan(char &x) {\n        skip();\n        x = *p_++;\n\
    \    }\n    void skip() {\n        while (*p_ <= ' ') {\n            ++p_;\n \
    \       }\n    }\n    char *data_;\n    char *p_;\n};\n\n\n"
  code: "#ifndef SCANNER_HPP\n#define SCANNER_HPP\n\n#include <charconv>\n#include\
    \ <concepts>\n#include <iostream>\n#include <iterator>\n#include <string>\n#include\
    \ <string_view>\n#include <sys/mman.h>\n#include <sys/stat.h>\n\nstruct scanner\
    \ {\n    scanner() {\n        struct stat st;\n        fstat(0, &st);\n      \
    \  if (S_ISREG(st.st_mode)) {\n            data_ = p_ = (char *)mmap(nullptr,\
    \ st.st_size + 65536, PROT_READ,\n                                      MAP_PRIVATE\
    \ | MAP_ANONYMOUS, -1, 0);\n            if (st.st_size) {\n                mmap(data_,\
    \ st.st_size, PROT_READ, MAP_PRIVATE | MAP_FIXED, 0, 0);\n            }\n    \
    \    } else {\n            auto *s = new std::string(std::istreambuf_iterator<char>(std::cin),\
    \ {});\n            data_ = p_ = s->data();\n        }\n    }\n    template <typename...\
    \ Args> void operator()(Args &...args) { (scan(args), ...); }\n    std::string_view\
    \ getline() {\n        skip();\n        auto first = p_;\n        while (*p_ >=\
    \ ' ') {\n            ++p_;\n        }\n        return std::string_view(first,\
    \ p_ - first);\n    }\n    auto &operator>>(auto &x) {\n        scan(x);\n   \
    \     return *this;\n    }\n\nprivate:\n    void scan(std::integral auto &x) {\n\
    \        skip();\n        x = 0;\n        auto is_negative = false;\n        if\
    \ (*p_ == '-') {\n            ++p_;\n            is_negative = true;\n       \
    \ }\n        for (; *p_ > ' '; ++p_) {\n            x = x * 10 + (*p_ & 15);\n\
    \        }\n        if (is_negative) {\n            x = -x;\n        }\n    }\n\
    \    void scan(std::floating_point auto &x) {\n        skip();\n        auto first\
    \ = p_;\n        while (*p_ > ' ') {\n            ++p_;\n        }\n        std::from_chars(first,\
    \ p_, x);\n    }\n    void scan(char &x) {\n        skip();\n        x = *p_++;\n\
    \    }\n    void skip() {\n        while (*p_ <= ' ') {\n            ++p_;\n \
    \       }\n    }\n    char *data_;\n    char *p_;\n};\n\n#endif // SCANNER_HPP"
  dependsOn: []
  isVerificationFile: false
  path: io/scanner.hpp
  requiredBy: []
  timestamp: '2026-02-26 17:14:58+09:00'
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
