#ifndef STABLE_MATCHING_HPP
#define STABLE_MATCHING_HPP

#include <numeric>
#include <vector>

std::vector<int> stable_matching(const std::vector<std::vector<int>> &a,
                                 const std::vector<std::vector<int>> &b) {
    const auto n = static_cast<int>(a.size());
    std::vector<std::vector<int>> b_priority(n, std::vector<int>(n));
    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            b_priority[i][b[i][j]] = j;
        }
    }
    std::vector<int> a_propose(n), b_match(n, -1), unmatched(n);
    std::iota(unmatched.begin(), unmatched.end(), 0);
    while (!unmatched.empty()) {
        const auto l = unmatched.back();
        unmatched.pop_back();
        const auto r = a[l][a_propose[l]];
        if (b_match[r] == -1) {
            b_match[r] = l;
        } else if (b_priority[r][l] < b_priority[r][b_match[r]]) {
            ++a_propose[b_match[r]];
            unmatched.push_back(b_match[r]);
            b_match[r] = l;
        } else {
            ++a_propose[l];
            unmatched.push_back(l);
        }
    }
    std::vector<int> a_match(n);
    for (auto i = 0; i < n; ++i) {
        a_match[b_match[i]] = i;
    }
    return a_match;
}

#endif // STABLE_MATCHING_HPP
