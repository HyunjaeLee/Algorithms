#ifndef SPLITMIX64_HPP
#define SPLITMIX64_HPP

#include <cstdint>
#include <limits>

struct splitmix64 {
public:
    using result_type = std::uint64_t;
    splitmix64(std::uint64_t seed = 0) : x(seed) {}
    std::uint64_t operator()() {
        std::uint64_t z = (x += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
    static constexpr std::uint64_t min() {
        return std::numeric_limits<std::uint64_t>::min();
    }
    static constexpr std::uint64_t max() {
        return std::numeric_limits<std::uint64_t>::max();
    }

private:
    std::uint64_t x; // The state can be seeded with any value.
};

#endif // SPLITMIX64_HPP
