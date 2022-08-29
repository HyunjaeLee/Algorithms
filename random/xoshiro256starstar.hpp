#ifndef XOSHIRO256STARSTAR_HPP
#define XOSHIRO256STARSTAR_HPP

#include "splitmix64.hpp"
#include <array>
#include <cstdint>

struct xoshiro256starstar {
public:
    using result_type = std::uint64_t;
    xoshiro256starstar(std::uint64_t seed = 0) {
        splitmix64 g(seed);
        for (auto &x : s) {
            x = g();
        }
    }
    std::uint64_t operator()() { return next(); }

private:
    static std::uint64_t rotl(const std::uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }
    std::uint64_t next() {
        const std::uint64_t result = rotl(s[1] * 5, 7) * 9;
        const std::uint64_t t = s[1] << 17;
        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];
        s[2] ^= t;
        s[3] = rotl(s[3], 45);
        return result;
    }
    std::array<std::uint64_t, 4> s;
};

#endif // XOSHIRO256STARSTAR_HPP
