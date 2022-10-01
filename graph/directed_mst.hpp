#ifndef DIRECTED_MST_HPP
#define DIRECTED_MST_HPP

#include "disjoint_set/rollback_disjoint_set.hpp"
#include <cassert>
#include <utility>
#include <vector>

template <typename Cost> struct directed_mst {
    explicit directed_mst(int n) : n_(n), heap_(n_, -1) {}

    void add_edge(int from, int to, Cost cost) {
        assert(0 <= from && from < n_ && 0 <= to && to < n_);
        auto edge_id = static_cast<int>(from_.size());
        from_.push_back(from);
        to_.push_back(to);
        cost_.push_back(cost);
        auto node_id = static_cast<int>(key_.size());
        key_.push_back(edge_id);
        left_.push_back(-1);
        right_.push_back(-1);
        lazy_.push_back(Cost{});
        heap_[to] = merge(heap_[to], node_id);
    }

    std::pair<Cost, std::vector<int>> run(int root) {
        rollback_disjoint_set dsu(n_);
        Cost result{};
        std::vector<int> seen(n_, -1), path(n_), queue(n_), in(n_, -1);
        seen[root] = root;
        std::vector<std::pair<int, std::vector<int>>> cycles;
        for (auto s = 0; s < n_; ++s) {
            auto u = s, pos = 0, w = -1;
            while (!~seen[u]) {
                if (!~heap_[u]) {
                    return {-1, {}};
                }
                auto e = top(heap_[u]);
                result += cost_[e];
                lazy_[heap_[u]] -= cost_[e];
                heap_[u] = pop(heap_[u]);
                queue[pos] = e;
                path[pos++] = u;
                seen[u] = s;
                u = dsu.find(from_[e]);
                if (seen[u] == s) {
                    auto cycle = -1;
                    auto end = pos;
                    do {
                        w = path[--pos];
                        cycle = merge(cycle, heap_[w]);
                    } while (dsu.merge(u, w));
                    u = dsu.find(u);
                    heap_[u] = cycle;
                    seen[u] = -1;
                    cycles.emplace_back(u,
                                        std::vector<int>(queue.begin() + pos,
                                                         queue.begin() + end));
                }
            }
            for (auto i = 0; i < pos; ++i) {
                in[dsu.find(to_[queue[i]])] = queue[i];
            }
        }
        for (auto it = cycles.rbegin(); it != cycles.rend(); ++it) {
            auto &[u, comp] = *it;
            auto count = static_cast<int>(comp.size()) - 1;
            dsu.rollback(count);
            auto in_edge = in[u];
            for (auto e : comp) {
                in[dsu.find(to_[e])] = e;
            }
            in[dsu.find(to_[in_edge])] = in_edge;
        }
        std::vector<int> parent;
        parent.reserve(n_);
        for (auto i : in) {
            parent.push_back(~i ? from_[i] : -1);
        }
        return {result, parent};
    }

private:
    void push(int u) {
        cost_[key_[u]] += lazy_[u];
        if (auto l = left_[u]; ~l) {
            lazy_[l] += lazy_[u];
        }
        if (auto r = right_[u]; ~r) {
            lazy_[r] += lazy_[u];
        }
        lazy_[u] = 0;
    }
    int top(int u) {
        push(u);
        return key_[u];
    }
    int merge(int u, int v) {
        if (!~u || !~v) {
            return ~u ? u : v;
        }
        push(u);
        push(v);
        if (cost_[key_[u]] > cost_[key_[v]]) {
            std::swap(u, v);
        }
        right_[u] = merge(v, right_[u]);
        std::swap(left_[u], right_[u]);
        return u;
    }
    int pop(int u) {
        push(u);
        return merge(left_[u], right_[u]);
    }
    const int n_;
    std::vector<int> from_, to_;
    std::vector<Cost> cost_;
    std::vector<int> key_, left_, right_, heap_;
    std::vector<Cost> lazy_;
};

#endif // DIRECTED_MST_HPP