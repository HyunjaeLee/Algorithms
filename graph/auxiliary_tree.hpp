#ifndef AUXILIARY_TREE_HPP
#define AUXILIARY_TREE_HPP

#include "heavy_light_decomposition/heavy_light_decomposition.hpp"
#include <algorithm>
#include <utility>
#include <vector>

struct AuxiliaryTree {
    AuxiliaryTree(const std::vector<std::vector<int>> &graph, int root) : hld_(graph, root) {}
    std::vector<std::pair<int, int>> get(std::vector<int> x) const {
        if (x.empty()) {
            return {};
        }
        std::ranges::sort(x, {}, [&](int u) { return hld_.in(u); });
        const auto m = int(x.size());
        for (auto i = 1; i < m; i++) {
            x.push_back(hld_.lca(x[i - 1], x[i]));
        }
        std::ranges::sort(x, {}, [&](int u) { return hld_.in(u); });
        auto r = std::ranges::unique(x);
        x.erase(r.begin(), r.end());
        const auto n = int(x.size());
        std::vector<int> st;
        std::vector<std::pair<int, int>> dfs_order(n);
        st.push_back(x[0]);
        dfs_order[0] = {x[0], -1};
        for (auto i = 1; i < n; ++i) {
            auto v = x[i];
            while (!st.empty()) {
                auto u = st.back();
                if (hld_.in(u) <= hld_.in(v) && hld_.in(v) < hld_.out(u)) {
                    break;
                } else {
                    st.pop_back();
                }
            }
            auto parent = st.back();
            dfs_order[i] = {v, parent};
            st.push_back(v);
        }
        return dfs_order;
    }
    const heavy_light_decomposition &hld() const { return hld_; }

private:
    const heavy_light_decomposition hld_;
};

#endif // AUXILIARY_TREE_HPP