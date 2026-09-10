---
layout: page
title: Math Notes
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

## 코시-슈바르츠 부등식

$$
(a_1^2 + a_2^2 + \cdots + a_n^2)(b_1^2 + b_2^2 + \cdots + b_n^2) \ge (a_1 b_1 + a_2 b_2 + \cdots + a_n b _n)^2
$$

등호 성립 조건은 $\frac{a_1}{b_1} = \frac{a_2}{b_2} = \cdots = \frac{a_n}{b_n}$ 이다.

## 합동식

+ $ab \equiv ac \pmod{m}$이고, $d = \gcd(a, m)$이면, $b \equiv c \pmod{\frac{m}{d}}$이다.
+ $a \equiv b \pmod{m}$이고, $n$이 $m$의 약수이면, $a \equiv b \pmod{n}$이다.
+ $a \equiv b \pmod{m}$이고, $d \gt 0$이 $a, b, m$의 공약수이면, $\frac{a}{d} \equiv \frac{b}{d} \pmod{\frac{m}{d}}$이다.