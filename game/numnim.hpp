#ifndef NUMNIM_HPP
#define NUMNIM_HPP

#include "mex.hpp"
#include "surreal.hpp"

// a + *b (number + nimber)
// a > 0: L wins
// a < 0: R wins
// a = 0 and b != 0: first wins
// a = 0 and b = 0: second wins
// https://codeforces.com/gym/105484/problem/D
// https://maspypy.github.io/library/game/number_and_star.hpp
struct NumNim {
    Surreal num;
    int nim;

    NumNim(Surreal num_ = 0, int nim_ = 0) : num(num_), nim(nim_) {}
    NumNim(const std::vector<NumNim> &l, const std::vector<NumNim> &r) {
        constexpr auto inf = std::numeric_limits<long long>::max() / 2;
        Surreal max_num_l = -inf;
        for (auto x : l) {
            max_num_l = std::max(max_num_l, x.num);
        }
        Surreal min_num_r = inf;
        for (auto x : r) {
            min_num_r = std::min(min_num_r, x.num);
        }
        std::vector<int> nim_l;
        for (auto x : l) {
            if (x.num == max_num_l) {
                nim_l.push_back(x.nim);
            }
        }
        auto mex_l = mex(nim_l);
        std::vector<int> nim_r;
        for (auto x : r) {
            if (x.num == min_num_r) {
                nim_r.push_back(x.nim);
            }
        }
        auto mex_r = mex(nim_r);
        assert(max_num_l <= min_num_r);
        if (max_num_l < min_num_r) {
            Surreal u = 0;
            while (!((mex_l ? max_num_l < u : max_num_l <= u) &&
                     (mex_r ? u < min_num_r : u <= min_num_r))) {
                u = (mex_l ? max_num_l < u : max_num_l <= u) ? u.left() : u.right();
            }
            num = u;
            nim = 0;
        } else {
            assert(mex_l == mex_r);
            num = max_num_l;
            nim = mex_l;
        }
    }

    NumNim &operator+=(NumNim o) {
        num += o.num;
        nim ^= o.nim;
        return *this;
    }
    NumNim &operator-=(NumNim o) {
        num -= o.num;
        nim ^= o.nim;
        return *this;
    }
    friend NumNim operator+(NumNim l, NumNim r) { return l += r; }
    friend NumNim operator-(NumNim l, NumNim r) { return l -= r; }

    friend std::ostream &operator<<(std::ostream &os, NumNim r) {
        os << r.num;
        if (r.nim) {
            os << " + *" << r.nim;
        }
        return os;
    }
};

#endif // NUMNIM_HPP