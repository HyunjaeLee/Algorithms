#ifndef TREE_DIAMETER_HPP
#define TREE_DIAMETER_HPP

#include "graph/csr_graph.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// requires non-negative edge weights
// return (diameter, path)
// for an unweighted tree, centers are path[d / 2] and path[(d + 1) / 2]
template <typename EdgeWeight> auto tree_diameter(const CSRGraph<EdgeWeight> &g) {
    assert(0 < g.size());
    auto n = int(g.size());
    std::vector<int> parent(n, -1);
    std::vector<EdgeWeight> depth(n);
    auto dfs = [&](int x) {
        std::vector<int> st;
        st.push_back(x);
        parent[x] = -1;
        depth[x] = 0;
        while (!st.empty()) {
            auto u = st.back();
            st.pop_back();
            for (const auto &e : g[u]) {
                if (e.v != parent[u]) {
                    st.push_back(e.v);
                    parent[e.v] = u;
                    depth[e.v] = depth[u] + e.w;
                }
            }
        }
        auto it = std::ranges::max_element(depth);
        auto r = int(it - depth.begin());
        return std::pair(r, *it);
    };
    auto x = dfs(0).first;
    auto [y, d] = dfs(x);
    std::vector<int> path;
    for (auto u = y; ~u; u = parent[u]) {
        path.push_back(u);
    }
    return std::pair(d, path);
}

#endif // TREE_DIAMETER_HPP