---
title: Graph Notes
layout: page
---

## Prüfer Code

트리에서 번호가 가장 작은 리프를 제거하고 해당 리프와 연결되어 있던 정점의 번호를 기록한다. 이를 $N-2$ 번 반복한다.

Prüfer code를 구축하고 나면 $2$ 개의 정점이 남는다. 그 중 하나는 번호가 가장 큰 정점 $N$ 이다.

$N$ 개의 정점을 가지는 labeled tree와 $1$ 이상 $N$ 이하의 정수로 이루어진 길이 $N-2$ 의 수열은 일대일 대응이다.

Cayley's formula: $N$ 개의 정점을 가진 labeled tree의 개수는 $N^{N-2}$ 이다.

각 정점은 Prüfer code에 $\text{degree} - 1$ 번 등장한다.

정점 $i$의 차수가 $d_i$인 트리의 개수는 $\frac{(N-2)!}{\prod_{i=1}^{N}{(d_i-1)!}}$이다.

## Lovász’s Decomposition Lemma

그래프 $G=(V,E)$와 정수 $r_1, r_2, \dots, r_k \ge 0$에 대해

$$
\Delta(G) + 1 \le \sum_{i=1}^k(r_i+1)
$$

이면 $V$를 $\Delta(G[V_i]) \le r_i$인 $k$개의 집합으로 분할할 수 있다.

모든 정점을 $k$가지의 색으로 임의로 색칠한다. $d_{i}(u) > r_i$이고 색이 $i$인 정점 $u\in V$를 골라 $d_{j}(u) \le r_j$를 만족하는 색 $j$로 다시 색칠하는 과정을 반복한다. 조건을 만족하는 색 $j$는 항상 존재하고 재색칠 횟수는 $O(\lvert E \rvert)$이다.

**용어**
+ $\Delta(G)$: 그래프 $G$의 최대 차수
+ $G[S]$: 집합 $S \subset V$에 대한 그래프 $G$의 induced subgraph
+ $d_i(u)$: 그래프 $G$에서 $u$와 인접한 정점 중 색이 $i$인 정점의 개수

**문제**
+ [CERC 2025 - Joyful Guided Tour](https://qoj.ac/contest/2814/problem/16009)
