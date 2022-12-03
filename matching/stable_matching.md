---
title: Stable matching
documentation_of: ./stable_matching.hpp
---

It solves stable matching problem using the Gale-Shapley algorithm. The algorithm results in a perfect matching and a stable matching. For given sets $A$ and $B$ the result is $A$-optimal and $B$-pessimal. It assumes that $\lvert A \rvert = \lvert B \rvert = n$.

stable_matching
---
```cpp
std::vector<int> stable_matching(const std::vector<std::vector<int>> &a,
                                 const std::vector<std::vector<int>> &b);
```

### Parameters
__a, b__  
$a$ is an $n \times n$ 2D vector. $a[i]$ is a permutation of $0, 1, \cdots, n-1$. For $0 \le j \lt k \lt n$, $i$ prefers $a[i][j]$ over $a[i][k]$, where $i$ is in set $A$ and $a[i][j]$ and $a[i][k]$ are in set $B$. For $b$ it's vice versa.

### Return value
It returns a vector $r$ of length $n$, such that $i$ in set $A$ and $r[i]$ in set $B$ are matched.

### Complexity
$\mathcal{O}\left(n^2\right)$

### References
+ [Stable matching presentation - CMU](https://www.cs.cmu.edu/~arielpro/15896s16/slides/896s16-16.pdf)
+ [Gale-Shapley algorithm - Wikipedia](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm)
+ [Stable marriage problem - Wikipedia](https://en.wikipedia.org/wiki/Stable_marriage_problem)
