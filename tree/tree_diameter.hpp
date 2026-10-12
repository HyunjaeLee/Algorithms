#ifndef TREE_DIAMETER_HPP
#define TREE_DIAMETER_HPP

#include <algorithm>
#include <cassert>
#include <vector>

// requires non-negative edge weights
// return (diameter, path)
// for an unweighted tree, centers are path[d / 2] and path[(d + 1) / 2]
template <typename T> auto tree_diameter(const auto &g) {
    assert(0 < g.size());
    auto n = int(g.size());
    std::vector<int> parent(n, -1);
    std::vector<T> depth(n);
    auto dfs = [&](int x) {
        std::vector<int> st;
        st.push_back(x);
        parent[x] = -1;
        depth[x] = 0;
        while (!st.empty()) {
            auto u = st.back();
            st.pop_back();
            for (auto [v, w]: g[u]) {
                if (v != parent[u]) {
                    st.push_back(v);
                    parent[v] = u;
                    depth[v] = depth[u] + w;
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