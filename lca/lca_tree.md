---
title: LCA Tree
documentation_of: ./lca_tree.hpp
---

# LCA Tree

## Overview

The `lca_tree` is a data structure designed to find the **Lowest Common Ancestor (LCA)** of any two nodes in a tree. This implementation utilizes the **Binary Lifting** technique.

Key functionalities include:
* Finding the $k$-th ancestor of a given node.
* Finding the Lowest Common Ancestor (LCA) of two nodes.
* Calculating the distance between two nodes.
* Finding a specific node on the path between two other nodes.

---

## Constructor

`lca_tree(const std::vector<std::vector<int>>& adj, int root)`

* **Description**: Constructs the `lca_tree` from an adjacency list `adj` and a specified `root` node.
* **Constraints**:
    * The graph given by `adj` must be a tree.
    * `adj.size()` = $N$.
    * $0 \le \text{root} < N$.
* **Time Complexity**: $O(N \log N)$, where $N$ is the number of nodes.

---

## Member Functions

#### `int kth_parent(int u, int k)`

* **Description**: Returns the $k$-th ancestor of node `u`.
* **Constraints**:
    * $0 \le u < N$
    * $0 \le k$
* **Time Complexity**: $O(\log N)$

#### `int lca(int u, int v)`

* **Description**: Returns the Lowest Common Ancestor of nodes `u` and `v`.
* **Constraints**:
    * $0 \le u < N$
    * $0 \le v < N$
* **Time Complexity**: $O(\log N)$

---

#### `int distance(int u, int v)`

* **Description**: Returns the distance between nodes `u` and `v`.
* **Constraints**:
    * $0 \le u < N$
    * $0 \le v < N$
* **Time Complexity**: $O(\log N)$

---

#### `int jump(int u, int v, int k)`

* **Description**: Returns the node that is $k$ steps away from `u` on the simple path to `v`. If the path length is less than `k`, it returns `-1`.
* **Constraints**:
    * $0 \le u < N$
    * $0 \le v < N$
    * $0 \le k$
* **Time Complexity**: $O(\log N)$
