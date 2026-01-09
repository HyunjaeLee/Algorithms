---
title: Extended Euclidean Algorithm
documentation_of: ./extgcd.hpp
---

Computes $g = \gcd(a,b)$ and find integers $x$ and $y$ such that $ax+by=g$.
+ $g$ may be negative.
+ $|x| \le \left\lvert \frac{b}{g} \right\rvert$
+ $|y| \le \left\lvert \frac{a}{g} \right\rvert$

> **Bézout's identity**—Let $a$ and $b$ be integers with greatest common divisor $g$. Then there exist integers $x$ and $y$ such that $ax + by = g$. Moreover, the integers of the form $az + bt$ are exactly the multiples of $g$.

### Complexity

+ $ \mathcal{O(\log(\min(a, b)))} $

### References
+ [euclid.h - KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/euclid.h)
+ [Extended Euclidean Algorithm - CP Algorithms](https://cp-algorithms.com/algebra/extended-euclid-algorithm.html)
+ [Extended Euclidean algorithm - Wikipedia](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)
+ [Bézout's identity - Wikipedia](https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity)
+ [Proof of Bounds for the Extended Euclidean Algorithm - Jeffrey Hurchalla](https://jeffhurchalla.com/2018/10/09/analysis-of-bounds-in-the-extended-euclidean-algorithm/)
