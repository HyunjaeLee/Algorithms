---
title: Math Notes
layout: page
---

## 이항정리

$$
(1 + x)^n = \sum_{i = 0}^{n}{_nC_i \times x^i}
$$

## 음이항정리

$$
(1 - x)^{-n} = \sum_{i = 0}^{\infty}{_nH_i \times x^i}
$$

## 이항분포

$$
P(X = k) = \binom{n}{k} p^k (1 - p)^{n - k}
$$

## 음이항분포

$$
P(X = n) = \binom{n - 1}{r - 1} p^r (1 - p)^{n - r}
$$

## 항등식

$$
\sum_{i=n}^{m}\binom{m}{i}p^i(1-p)^{m-i}=\sum_{i=n}^{m}\binom{i-1}{n-1}p^n(1-p)^{i-n}
$$

## $1,2,\dots,N$의 subset sum

$1$ 이상 $\frac{(N+1)N}{2}$ 이하의 모든 정수 $x$를 $1,2,\dots,N$의 합으로 표현할 수 있다.\
$x$가 음수가 되지 않도록 $N$부터 $1$까지 차례대로 빼는 것으로 실제 해를 구성할 수 있다.

## $\lfloor\frac{n}{2}\rfloor\lceil\frac{n}{2}\rceil=\lfloor\frac{n^2}{4}\rfloor$
정수 $a,b,n$에 대해 $a,b \geq 0$ 이고 $a+b=n$이면 $ab\le\lfloor\frac{n^2}{4}\rfloor$이다.\
등호 성립 조건은 $\{a,b\}=\{\lfloor\frac{n}{2}\rfloor,\lceil\frac{n}{2}\rceil\}$ 이다.
