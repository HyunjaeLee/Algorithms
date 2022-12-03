---
title: Power tower
documentation_of: ./power_tower.hpp
---

Solves ${a_0}^{{a_1}^{{\cdots}^{a_{n-1}}}}\pmod m$ for positive integers $a_i$ and $m$.  
Algorithm implementation is based on [maspy's code](https://maspypy.github.io/library/mod/tetration.hpp).

power_tower
---
```cpp
template <typename T, typename Promote = unsigned long long>
T power_tower(const std::vector<T> &a, T m);
```

It returns ${a_0}^{{a_1}^{{\cdots}^{a_{n-1}}}}\pmod m$.

Providing first $\min(2\lfloor\lg{m}\rfloor, n)$ elements of $a$ is sufficient to calculate ${a_0}^{{a_1}^{{\cdots}^{a_{n-1}}}}\pmod m$. In other words ${a_0}^{{a_1}^{{\cdots}^{a_{n-1}}}} \equiv {a_0}^{{a_1}^{{\cdots}^{a_{k-1}}}} \pmod m$ where $k = \min(2\lfloor\lg{m}\rfloor, n)$. Notice that ${a_0}^{{a_1}^{{\cdots}^{a_{n-1}}}} \equiv {a_0}^{{a_1}^{{\cdots}^{a_{x-1}}}} \pmod m$ is true for any integer $x$ such that $\varphi^x(m) = 1$.

`T` is an integral type such as `int`, `unsigned int`, `long long`, and `unsigned long long`. `Promote` is an integral type that can express values between $0$ and $(2m-1)^2$, inclusive.

It's possible to use different Euler's phi function. Factorization using Miller-Rabin and Pollard's rho and precalcuated array are alternative implementations. It affects the complexity of `power_tower`.

### Constraints
+ $0 < a[i]$
+ $0 < m$

### Complexity
+ $\mathcal{O}\left(\sqrt{m}\right)$
