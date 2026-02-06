---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structures/ordered_set.hpp
    title: data_structures/ordered_set.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/ordered_set
    links:
    - https://judge.yosupo.jp/problem/ordered_set
  bundledCode: "#line 1 \"test/data_structures/ordered_set.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#line 1 \"data_structures/ordered_set.hpp\"\
    \n\n\n\n#include <ext/pb_ds/assoc_container.hpp>\n#include <ext/pb_ds/tree_policy.hpp>\n\
    #include <functional>\n\ntemplate <typename T>\nusing ordered_set =\n    __gnu_pbds::tree<T,\
    \ __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag,\n            \
    \         __gnu_pbds::tree_order_statistics_node_update>;\n\n\n#line 4 \"test/data_structures/ordered_set.test.cpp\"\
    \n#include <bits/stdc++.h>\n\nint main() {\n    std::cin.tie(0)->sync_with_stdio(0);\n\
    \    int N, Q;\n    std::cin >> N >> Q;\n    ordered_set<int> s;\n    for (auto\
    \ i = 0; i < N; ++i) {\n        int a;\n        std::cin >> a;\n        s.insert(a);\n\
    \    }\n    for (auto i = 0; i < Q; ++i) {\n        int t, x;\n        std::cin\
    \ >> t >> x;\n        if (t == 0) {\n            s.insert(x);\n        } else\
    \ if (t == 1) {\n            s.erase(x);\n        } else if (t == 2) {\n     \
    \       auto it = s.find_by_order(x - 1);\n            std::cout << (it != s.end()\
    \ ? *it : -1) << \"\\n\";\n        } else if (t == 3) {\n            std::cout\
    \ << s.order_of_key(x + 1) << \"\\n\";\n        } else if (t == 4) {\n       \
    \     auto it = s.upper_bound(x);\n            std::cout << (it != s.begin() ?\
    \ *std::prev(it) : -1) << \"\\n\";\n        } else if (t == 5) {\n           \
    \ auto it = s.lower_bound(x);\n            std::cout << (it != s.end() ? *it :\
    \ -1) << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#include\
    \ \"data_structures/ordered_set.hpp\"\n#include <bits/stdc++.h>\n\nint main()\
    \ {\n    std::cin.tie(0)->sync_with_stdio(0);\n    int N, Q;\n    std::cin >>\
    \ N >> Q;\n    ordered_set<int> s;\n    for (auto i = 0; i < N; ++i) {\n     \
    \   int a;\n        std::cin >> a;\n        s.insert(a);\n    }\n    for (auto\
    \ i = 0; i < Q; ++i) {\n        int t, x;\n        std::cin >> t >> x;\n     \
    \   if (t == 0) {\n            s.insert(x);\n        } else if (t == 1) {\n  \
    \          s.erase(x);\n        } else if (t == 2) {\n            auto it = s.find_by_order(x\
    \ - 1);\n            std::cout << (it != s.end() ? *it : -1) << \"\\n\";\n   \
    \     } else if (t == 3) {\n            std::cout << s.order_of_key(x + 1) <<\
    \ \"\\n\";\n        } else if (t == 4) {\n            auto it = s.upper_bound(x);\n\
    \            std::cout << (it != s.begin() ? *std::prev(it) : -1) << \"\\n\";\n\
    \        } else if (t == 5) {\n            auto it = s.lower_bound(x);\n     \
    \       std::cout << (it != s.end() ? *it : -1) << \"\\n\";\n        }\n    }\n\
    }\n"
  dependsOn:
  - data_structures/ordered_set.hpp
  isVerificationFile: true
  path: test/data_structures/ordered_set.test.cpp
  requiredBy: []
  timestamp: '2026-02-06 17:15:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structures/ordered_set.test.cpp
layout: document
redirect_from:
- /verify/test/data_structures/ordered_set.test.cpp
- /verify/test/data_structures/ordered_set.test.cpp.html
title: test/data_structures/ordered_set.test.cpp
---
