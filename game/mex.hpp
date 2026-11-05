#ifndef MEX_HPP
#define MEX_HPP

#include <vector>

int mex(const auto &a) {
    auto n = int(a.size());
    std::vector<bool> f(n);
    for (auto x : a) {
        if (x < n) {
            f[x] = true;
        }
    }
    for (auto i = 0; i < n; ++i) {
        if (!f[i]) {
            return i;
        }
    }
    return n;
}

#endif // MEX_HPP