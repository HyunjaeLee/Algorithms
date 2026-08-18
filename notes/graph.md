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
