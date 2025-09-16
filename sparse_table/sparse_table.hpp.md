---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/sparse_table/static_range_sum.test.cpp
    title: test/sparse_table/static_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/sparse_table/static_rmq.test.cpp
    title: test/sparse_table/static_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"sparse_table/sparse_table.hpp\"\n\n\n\n#include <bit>\n\
    #include <cassert>\n#include <type_traits>\n#include <vector>\n\ntemplate <typename\
    \ S, auto op, auto e> struct sparse_table {\n    static_assert(std::is_invocable_r_v<S,\
    \ decltype(op), S, S>,\n                  \"op must be a function of type S(S,\
    \ S)\");\n    static_assert(std::is_invocable_r_v<S, decltype(e)>,\n         \
    \         \"e must be a function of type S()\");\n    sparse_table(const std::vector<S>\
    \ &v)\n        : n_((int)v.size()), width_(std::bit_width(v.size())),\n      \
    \    table_(width_, std::vector<S>(v.size())) {\n        table_[0] = v;\n    \
    \    for (auto i = 1; i < width_; ++i) {\n            for (auto j = 0; j + (1\
    \ << i) <= n_; ++j) {\n                table_[i][j] =\n                    op(table_[i\
    \ - 1][j], table_[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n   \
    \ }\n    S prod(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n\
    \        auto sum = e();\n        for (auto i = width_ - 1; 0 <= i; --i) {\n \
    \           if ((1 << i) <= r - l) {\n                sum = op(sum, table_[i][l]);\n\
    \                l += (1 << i);\n            }\n        }\n        return sum;\n\
    \    }\n    S prod_idempotent(int l, int r) {\n        assert(0 <= l && l <= r\
    \ && r <= n_);\n        if (l == r) {\n            return e();\n        }\n  \
    \      auto i = std::bit_width(unsigned(r - l)) - 1;\n        return op(table_[i][l],\
    \ table_[i][r - (1 << i)]);\n    }\n\nprivate:\n    int n_, width_;\n    std::vector<std::vector<S>>\
    \ table_;\n};\n\n\n"
  code: "#ifndef SPARSE_TABLE_HPP\n#define SPARSE_TABLE_HPP\n\n#include <bit>\n#include\
    \ <cassert>\n#include <type_traits>\n#include <vector>\n\ntemplate <typename S,\
    \ auto op, auto e> struct sparse_table {\n    static_assert(std::is_invocable_r_v<S,\
    \ decltype(op), S, S>,\n                  \"op must be a function of type S(S,\
    \ S)\");\n    static_assert(std::is_invocable_r_v<S, decltype(e)>,\n         \
    \         \"e must be a function of type S()\");\n    sparse_table(const std::vector<S>\
    \ &v)\n        : n_((int)v.size()), width_(std::bit_width(v.size())),\n      \
    \    table_(width_, std::vector<S>(v.size())) {\n        table_[0] = v;\n    \
    \    for (auto i = 1; i < width_; ++i) {\n            for (auto j = 0; j + (1\
    \ << i) <= n_; ++j) {\n                table_[i][j] =\n                    op(table_[i\
    \ - 1][j], table_[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n   \
    \ }\n    S prod(int l, int r) {\n        assert(0 <= l && l <= r && r <= n_);\n\
    \        auto sum = e();\n        for (auto i = width_ - 1; 0 <= i; --i) {\n \
    \           if ((1 << i) <= r - l) {\n                sum = op(sum, table_[i][l]);\n\
    \                l += (1 << i);\n            }\n        }\n        return sum;\n\
    \    }\n    S prod_idempotent(int l, int r) {\n        assert(0 <= l && l <= r\
    \ && r <= n_);\n        if (l == r) {\n            return e();\n        }\n  \
    \      auto i = std::bit_width(unsigned(r - l)) - 1;\n        return op(table_[i][l],\
    \ table_[i][r - (1 << i)]);\n    }\n\nprivate:\n    int n_, width_;\n    std::vector<std::vector<S>>\
    \ table_;\n};\n\n#endif // SPARSE_TABLE_HPP"
  dependsOn: []
  isVerificationFile: false
  path: sparse_table/sparse_table.hpp
  requiredBy: []
  timestamp: '2025-09-16 22:59:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/sparse_table/static_range_sum.test.cpp
  - test/sparse_table/static_rmq.test.cpp
documentation_of: sparse_table/sparse_table.hpp
layout: document
title: Sparse Table
---

# Sparse Table

It is a data structure for [monoids](https://en.wikipedia.org/wiki/Monoid) $(S, \cdot: S \times S \to S, e \in S)$, i.e., an algebraic structure that satisfies the following properties:
- **Associativity**: $(a \cdot b) \cdot c = a \cdot (b \cdot c)$ for all $a, b, c \in S$.
- **Identity Element**: $a \cdot e = e \cdot a = a$ for all $a \in S$.

Given a static array `a` of length $N$, it can calculate the product of the elements in a given range `[l, r)`. Unlike a segment tree, it does not support updating elements of the array after construction.

- Range product query: $O(\log N)$
- Range product query (for idempotent operations): $O(1)$

For simplicity, in this document, we assume that the oracles `op` and `e` work in constant time.

## How to define S, op, e

The following should be defined to instantiate `sparse_table`.

- The type `S`.
- The binary operation `S op(S a, S b)`.
- The identity element `S e()`.

For example, for Range Minimum Query (which is an idempotent operation), the definitions are as follows.

```cpp
int op(int a, int b) {
    return std::min(a, b);
}

int e() {
    return std::numeric_limits<int>::max();
}

// std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
// sparse_table<int, op, e> st(v);
```

## Constructor

`sparse_table<S, op, e> st(const std::vector<S>& v)`

It creates a sparse table from the elements of vector `v`.

**Constraints**
- `v.size()` = $N$
- $0 \le N$

**Time Complexity**
- $O(N \log N)$

## Member Functions

### prod

`S st.prod(int l, int r)`

It returns `op(a[l], ..., a[r - 1])`. It returns `e()` if $l = r$.

**Constraints**
- $0 \le l \le r \le N$

**Time Complexity**
- $O(\log N)$

### prod_idempotent

`S st.prod_idempotent(int l, int r)`

It returns `op(a[l], ..., a[r - 1])`. It returns `e()` if $l = r$.

This is a faster version of `prod` that can only be used if the operation `op` is **idempotent**, meaning it satisfies `op(x, x) = x` for all `x` in `S`.

Common idempotent operations include:
- Minimum (`std::min`)
- Maximum (`std::max`)
- Greatest Common Divisor (GCD)
- Bitwise AND (`&`)
- Bitwise OR (`|`)

**Constraints**
- $0 \le l \le r \le N$
- `op` must be idempotent.

**Time Complexity**
- $O(1)$

**References**
- [https://cp-algorithms.com/data_structures/sparse-table.html](https://cp-algorithms.com/data_structures/sparse-table.html)
