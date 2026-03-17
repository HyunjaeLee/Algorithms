#ifndef CARTESIAN_TREE_HPP
#define CARTESIAN_TREE_HPP

#include <vector>

std::vector<int> cartesian_tree(const std::vector<int> &a) {
    const auto n = int(a.size());
    std::vector<int> parent(n, -1), st;
    for (auto i = 0; i < n; ++i) {
        auto v = -1;
        while (!st.empty() && a[i] < a[st.back()]) {
            v = st.back();
            st.pop_back();
        }
        if (!st.empty()) {
            parent[i] = st.back();
        }
        if (~v) {
            parent[v] = i;
        }
        st.push_back(i);
    }
    return parent;
}

#endif // CARTESIAN_TREE_HPP