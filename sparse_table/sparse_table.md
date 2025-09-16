---
title: Sparse Table
documentation_of: ./sparse_table.hpp
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

## References
- [https://cp-algorithms.com/data_structures/sparse-table.html](https://cp-algorithms.com/data_structures/sparse-table.html)
