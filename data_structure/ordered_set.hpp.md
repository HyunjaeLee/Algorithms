---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/ordered_set.test.cpp
    title: test/data_structure/ordered_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/ordered_set.hpp\"\n\n\n\n#include <ext/pb_ds/assoc_container.hpp>\n\
    #include <ext/pb_ds/tree_policy.hpp>\n#include <functional>\n\ntemplate <typename\
    \ T>\nusing ordered_set =\n    __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>,\
    \ __gnu_pbds::rb_tree_tag,\n                     __gnu_pbds::tree_order_statistics_node_update>;\n\
    \n\n"
  code: "#ifndef ORDERED_SET_HPP\n#define ORDERED_SET_HPP\n\n#include <ext/pb_ds/assoc_container.hpp>\n\
    #include <ext/pb_ds/tree_policy.hpp>\n#include <functional>\n\ntemplate <typename\
    \ T>\nusing ordered_set =\n    __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>,\
    \ __gnu_pbds::rb_tree_tag,\n                     __gnu_pbds::tree_order_statistics_node_update>;\n\
    \n#endif // ORDERED_SET_HPP"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/ordered_set.hpp
  requiredBy: []
  timestamp: '2026-01-15 02:55:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/ordered_set.test.cpp
documentation_of: data_structure/ordered_set.hpp
layout: document
redirect_from:
- /library/data_structure/ordered_set.hpp
- /library/data_structure/ordered_set.hpp.html
title: data_structure/ordered_set.hpp
---
