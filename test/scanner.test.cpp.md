---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: io/scanner.hpp
    title: io/scanner.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/scanner.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\
    \n\n#line 1 \"io/scanner.hpp\"\n\n\n\n#include <charconv>\n#include <sys/mman.h>\n\
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
    \       }\n    }\n    char *data_;\n    char *p_;\n    size_t size_;\n};\n\n\n\
    #line 4 \"test/scanner.test.cpp\"\n#include <iostream>\n\nscanner scan;\n\nint\
    \ main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int T;\n    scan(T);\n\
    \    while (T--) {\n        long long A, B;\n        scan(A, B);\n        std::cout\
    \ << A + B << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ \"../io/scanner.hpp\"\n#include <iostream>\n\nscanner scan;\n\nint main() {\n\
    \    std::cin.tie(0)->sync_with_stdio(0);\n    int T;\n    scan(T);\n    while\
    \ (T--) {\n        long long A, B;\n        scan(A, B);\n        std::cout <<\
    \ A + B << '\\n';\n    }\n}\n"
  dependsOn:
  - io/scanner.hpp
  isVerificationFile: true
  path: test/scanner.test.cpp
  requiredBy: []
  timestamp: '2022-08-29 15:08:35+00:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/scanner.test.cpp
layout: document
redirect_from:
- /verify/test/scanner.test.cpp
- /verify/test/scanner.test.cpp.html
title: test/scanner.test.cpp
---
