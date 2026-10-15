#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <array>
#include <bit>
#include <cassert>
#include <chrono>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <random>

// https://hitonanode.github.io/cplib-cpp/data_structure/fast_hash_map.hpp
// Fixed-capacity hash map for integer keys.
// N must be a power of two. At most N distinct keys can be stored.
template <std::integral K, typename V, std::size_t N> struct hash_map {
    static_assert(sizeof(K) <= sizeof(std::uint64_t));
    static_assert(std::has_single_bit(N));

    hash_map() : multiplier(make_multiplier()) {}
    void set(K key, V value) {
        std::size_t pos = hash(key);
        for (std::size_t step = 0; step < N; ++step) {
            if (versions[pos] != version) {
                keys[pos] = key;
                values[pos] = value;
                versions[pos] = version;
                assert(count < N);
                ++count;
                return;
            }
            if (keys[pos] == key) {
                values[pos] = value;
                return;
            }
            pos = (pos + 1) & (N - 1);
        }
        assert(false && "hash map capacity exceeded");
    }
    std::optional<V> get(K key) const {
        std::size_t pos = hash(key);
        for (std::size_t step = 0; step < N; ++step) {
            if (versions[pos] != version) {
                return std::nullopt;
            }
            if (keys[pos] == key) {
                return values[pos];
            }
            pos = (pos + 1) & (N - 1);
        }
        return std::nullopt;
    }
    std::size_t size() const { return count; }
    bool empty() const { return count == 0; }
    void clear() {
        ++version;
        count = 0;
    }
    void reset() { clear(); }

private:
    std::size_t hash(K key) const {
        if constexpr (N == 1) {
            return 0;
        } else {
            constexpr int shift = 64 - std::countr_zero(N);
            return (static_cast<std::uint64_t>(key) * multiplier) >> shift;
        }
    }
    static std::uint64_t make_multiplier() {
        std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());
        return mt() | 1;
    }

    std::array<K, N> keys;
    std::array<V, N> values;
    std::array<std::uint32_t, N> versions{};
    std::uint32_t version = 1;
    std::size_t count = 0;
    std::uint64_t multiplier;
};

#endif // HASH_MAP_HPP