---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/dirichlet_series.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <numeric>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\ntemplate <typename T> struct dirichlet_series\
    \ {\n    dirichlet_series() : dirichlet_series(0) {}\n    explicit dirichlet_series(long\
    \ long n)\n        : dirichlet_series(n, opt_size_dense(n)) {}\n    template <typename\
    \ F, typename Prefix>\n    dirichlet_series(long long n, F f, Prefix prefix)\n\
    \        : dirichlet_series(n, opt_size_dense(n), f, prefix) {}\n    dirichlet_series(long\
    \ long n, long long size_dense)\n        : n_(n), size_dense_(size_dense), size_sparse_(n_\
    \ / (size_dense_ + 1)),\n          data_(size_dense_ + 1), sum_dense_(size_dense_\
    \ + 1),\n          sum_sparse_(size_sparse_ + 1) {\n        assert(static_cast<long\
    \ long>(std::sqrt(n_)) <= size_dense_);\n    }\n    template <typename F, typename\
    \ Prefix>\n    dirichlet_series(long long n, long long size_dense, F f, Prefix\
    \ prefix)\n        : n_(n), size_dense_(size_dense), size_sparse_(n_ / (size_dense_\
    \ + 1)),\n          data_(size_dense_ + 1), sum_dense_(size_dense_ + 1),\n   \
    \       sum_sparse_(size_sparse_ + 1) {\n        assert(static_cast<long long>(std::sqrt(n_))\
    \ <= size_dense_);\n        if constexpr (std::is_invocable_r_v<T, F, long long>)\
    \ {\n            for (auto i = 1LL; i <= size_dense_; ++i) {\n               \
    \ data_[i] = f(i);\n            }\n        } else {\n            f(data_);\n \
    \           assert(static_cast<long long>(data_.size()) == size_dense_ + 1);\n\
    \        }\n        std::partial_sum(data_.begin(), data_.end(), sum_dense_.begin());\n\
    \        for (auto i = 1LL; i <= size_sparse_; ++i) {\n            sum_sparse_[i]\
    \ = prefix(internal_div(n_, i));\n        }\n    };\n    const T &operator[](long\
    \ long pos) const {\n        assert(1 <= pos && pos <= size_dense_);\n       \
    \ return data_[pos];\n    }\n    T &operator[](long long pos) {\n        assert(1\
    \ <= pos && pos <= size_dense_);\n        return data_[pos];\n    }\n    T sum(long\
    \ long pos) const {\n        if (pos <= 0) {\n            return T(0);\n     \
    \   }\n        if (1 <= pos && pos <= size_dense_) {\n            return sum_dense_[pos];\n\
    \        } else {\n            const auto x = internal_div(n_, pos);\n       \
    \     assert(1 <= x && x <= size_sparse_ &&\n                   internal_div(n_,\
    \ (pos + 1)) + 1 == x);\n            return sum_sparse_[x];\n        }\n    }\n\
    \    dirichlet_series &operator+=(const dirichlet_series &other) {\n        assert_size(other);\n\
    \        for (auto i = 1LL; i <= size_dense_; ++i) {\n            data_[i] +=\
    \ other.data_[i];\n            sum_dense_[i] += other.sum_dense_[i];\n       \
    \ }\n        for (auto i = 1LL; i <= size_sparse_; ++i) {\n            sum_sparse_[i]\
    \ += other.sum_sparse_[i];\n        }\n        return *this;\n    }\n    dirichlet_series\
    \ &operator-=(const dirichlet_series &other) {\n        assert_size(other);\n\
    \        for (auto i = 1LL; i <= size_dense_; ++i) {\n            data_[i] -=\
    \ other.data_[i];\n            sum_dense_[i] -= other.sum_dense_[i];\n       \
    \ }\n        for (auto i = 1LL; i <= size_sparse_; ++i) {\n            sum_sparse_[i]\
    \ -= other.sum_sparse_[i];\n        }\n        return *this;\n    }\n    dirichlet_series\
    \ &operator*=(const dirichlet_series &other) {\n        assert_size(other);\n\
    \        dirichlet_series result(n_, size_dense_);\n        for (auto i = 1LL;\
    \ i <= size_dense_; ++i) {\n            for (auto j = 1LL; i * j <= size_dense_;\
    \ ++j) {\n                result.data_[i * j] += data_[i] * other.data_[j];\n\
    \            }\n        }\n        std::partial_sum(std::next(result.data_.begin()),\
    \ result.data_.end(),\n                         std::next(result.sum_dense_.begin()));\n\
    \        for (auto i = 1LL; i <= size_sparse_; ++i) {\n            const auto\
    \ x = internal_div(n_, i);\n            auto j = 1LL;\n            for (; j *\
    \ j <= x; ++j) {\n                result.sum_sparse_[i] +=\n                 \
    \   data_[j] * other.sum(internal_div(x, j)) +\n                    sum(internal_div(x,\
    \ j)) * other.data_[j];\n            }\n            result.sum_sparse_[i] -= sum(j\
    \ - 1) * other.sum(j - 1);\n        }\n        *this = std::move(result);\n  \
    \      return *this;\n    }\n    dirichlet_series &operator/=(const dirichlet_series\
    \ &other) {\n        assert_size(other);\n        assert(other[1] != T(0));\n\
    \        if (this == &other) {\n            *this = identity(n_, size_dense_);\n\
    \            return *this;\n        }\n        if constexpr (std::is_integral_v<T>)\
    \ {\n            assert(std::abs(other[1]) == T(1));\n        }\n        const\
    \ auto inv = T(1) / other[1];\n        for (auto i = 1LL; i <= size_dense_; ++i)\
    \ {\n            data_[i] *= inv;\n            for (auto j = 2LL; i * j <= size_dense_;\
    \ ++j) {\n                data_[i * j] -= data_[i] * other.data_[j];\n       \
    \     }\n        }\n        partial_sum(std::next(data_.begin()), data_.end(),\n\
    \                    std::next(sum_dense_.begin()));\n        for (auto i = size_sparse_;\
    \ 1 <= i; --i) {\n            const auto x = internal_div(n_, i);\n          \
    \  auto val = sum_sparse_[i];\n            sum_sparse_[i] = T(0);\n          \
    \  auto j = 1LL;\n            for (; j * j <= x; ++j) {\n                val -=\
    \ data_[j] * other.sum(internal_div(x, j)) +\n                       sum(internal_div(x,\
    \ j)) * other.data_[j];\n            }\n            val += sum(j - 1) * other.sum(j\
    \ - 1);\n            val *= inv;\n            sum_sparse_[i] = val;\n        }\n\
    \        return *this;\n    }\n    dirichlet_series &pow(long long k) {\n    \
    \    assert(k >= 0);\n        auto result(identity(n_, size_dense_));\n      \
    \  while (k) {\n            if (k & 1) {\n                result *= *this;\n \
    \           }\n            *this *= *this;\n            k >>= 1;\n        }\n\
    \        *this = std::move(result);\n        return *this;\n    }\n    friend\
    \ dirichlet_series operator+(const dirichlet_series &lhs,\n                  \
    \                    const dirichlet_series &rhs) {\n        auto result(lhs);\n\
    \        result += rhs;\n        return result;\n    };\n    friend dirichlet_series\
    \ operator-(const dirichlet_series &lhs,\n                                   \
    \   const dirichlet_series &rhs) {\n        auto result(lhs);\n        result\
    \ -= rhs;\n        return result;\n    };\n    friend dirichlet_series operator*(const\
    \ dirichlet_series &lhs,\n                                      const dirichlet_series\
    \ &rhs) {\n        auto result(lhs);\n        result *= rhs;\n        return result;\n\
    \    };\n    friend dirichlet_series operator/(const dirichlet_series &lhs,\n\
    \                                      const dirichlet_series &rhs) {\n      \
    \  auto result(lhs);\n        result /= rhs;\n        return result;\n    };\n\
    \    template <typename... Args>\n    static dirichlet_series identity(Args &&...args)\
    \ {\n        dirichlet_series result(std::forward<Args>(args)...);\n        result[1]\
    \ = T(1);\n        std::fill(std::next(result.sum_dense_.begin()), result.sum_dense_.end(),\n\
    \                  T(1));\n        std::fill(std::next(result.sum_sparse_.begin()),\n\
    \                  result.sum_sparse_.end(), T(1));\n        return result;\n\
    \    }\n    template <typename... Args> static dirichlet_series zeta(Args &&...args)\
    \ {\n        dirichlet_series result(std::forward<Args>(args)...);\n        std::fill(std::next(result.data_.begin()),\
    \ result.data_.end(), T(1));\n        std::iota(std::next(result.sum_dense_.begin()),\
    \ result.sum_dense_.end(),\n                  T(1));\n        for (auto i = 1LL;\
    \ i <= result.size_sparse_; ++i) {\n            const auto x = internal_div(result.n_,\
    \ i);\n            result.sum_sparse_[i] = T(x);\n        }\n        return result;\n\
    \    }\n    template <typename... Args>\n    static dirichlet_series zeta_shift_1(Args\
    \ &&...args) {\n        dirichlet_series result(std::forward<Args>(args)...);\n\
    \        std::iota(std::next(result.data_.begin()), result.data_.end(), T(1));\n\
    \        std::partial_sum(std::next(result.data_.begin()), result.data_.end(),\n\
    \                         std::next(result.sum_dense_.begin()));\n        for\
    \ (auto i = 1LL; i <= result.size_sparse_; ++i) {\n            const auto x =\
    \ internal_div(result.n_, i);\n            result.sum_sparse_[i] = T(x) * T(x\
    \ + 1) / T(2);\n        }\n        return result;\n    }\n    template <typename...\
    \ Args>\n    static dirichlet_series zeta_shift(long long k, Args &&...args) {\n\
    \        assert(0 <= k);\n        if (k == 0) {\n            return zeta(std::forward<Args>(args)...);\n\
    \        } else if (k == 1) {\n            return zeta_shift_1(std::forward<Args>(args)...);\n\
    \        }\n        dirichlet_series result(std::forward<Args>(args)...);\n  \
    \      for (auto i = 1LL; i <= result.size_dense_; ++i) {\n            result.data_[i]\
    \ = T(i).pow(k);\n        }\n        std::partial_sum(std::next(result.data_.begin()),\
    \ result.data_.end(),\n                         std::next(result.sum_dense_.begin()));\n\
    \        if (result.size_sparse_ == 0) {\n            return result;\n       \
    \ }\n        std::vector<T> y(k + 2);\n        for (auto i = 0LL; i < k + 2; ++i)\
    \ {\n            y[i] = T(i).pow(k);\n        }\n        std::partial_sum(y.begin(),\
    \ y.end(), y.begin());\n        for (auto i = 1LL; i <= result.size_sparse_; ++i)\
    \ {\n            const auto x = internal_div(result.n_, i);\n            result.sum_sparse_[i]\
    \ = interpolate(y, x);\n        }\n        return result;\n    }\n    template\
    \ <typename... Args> static dirichlet_series mu(Args &&...args) {\n        auto\
    \ result(identity(std::forward<Args>(args)...));\n        result /= zeta(std::forward<Args>(args)...);\n\
    \        return result;\n    }\n    template <typename... Args> static dirichlet_series\
    \ phi(Args &&...args) {\n        auto result(zeta_shift_1(std::forward<Args>(args)...));\n\
    \        result /= zeta(std::forward<Args>(args)...);\n        return result;\n\
    \    }\n\nprivate:\n    void assert_size(const dirichlet_series &other) {\n  \
    \      assert(n_ == other.n_ && size_dense_ == other.size_dense_ &&\n        \
    \       size_sparse_ == other.size_sparse_);\n    }\n    static long long opt_size_dense(long\
    \ long n) {\n        if (n <= 1) {\n            return n;\n        } else {\n\
    \            return static_cast<long long>(\n                std::max(std::sqrt(n),\
    \ std::pow(n, 2.0 / 3) / std::log(n)));\n        }\n    }\n    static long long\
    \ internal_div(long long x, long long y) {\n        return static_cast<long long>(static_cast<double>(x)\
    \ /\n                                      static_cast<double>(y));\n    }\n \
    \   static T interpolate(const std::vector<T> &y, T x) {\n        const auto n\
    \ = static_cast<long long>(y.size());\n        if (const auto i = static_cast<long\
    \ long>(x.val()); 0 <= i && i < n) {\n            return y[i];\n        }\n  \
    \      T f(1);\n        for (auto i = 1LL; i < n; ++i) {\n            f *= T(i);\n\
    \        }\n        std::vector<T> finv(n);\n        finv[n - 1] = f.inv();\n\
    \        for (auto i = n - 2; 0 <= i; --i) {\n            finv[i] = finv[i + 1]\
    \ * T(i + 1);\n        }\n        std::vector<T> prefix(n), suffix(n);\n     \
    \   prefix[0] = suffix[n - 1] = 1;\n        for (auto i = 1LL; i < n; ++i) {\n\
    \            prefix[i] = prefix[i - 1] * (i - 1 - x);\n        }\n        for\
    \ (auto i = n - 2; i >= 0; --i) {\n            suffix[i] = suffix[i + 1] * (i\
    \ + 1 - x);\n        }\n        auto sum = T(0);\n        for (auto i = 0LL; i\
    \ < n; ++i) {\n            const auto val =\n                y[i] * prefix[i]\
    \ * suffix[i] * finv[i] * finv[n - 1 - i];\n            sum += ((i & 1) ? -val\
    \ : val);\n        }\n        return sum;\n    }\n    long long n_, size_dense_,\
    \ size_sparse_;\n    std::vector<T> data_, sum_dense_, sum_sparse_;\n};\n\n\n"
  code: "#ifndef DIRICHLET_SERIES_HPP\n#define DIRICHLET_SERIES_HPP\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <numeric>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\ntemplate <typename T> struct dirichlet_series\
    \ {\n    dirichlet_series() : dirichlet_series(0) {}\n    explicit dirichlet_series(long\
    \ long n)\n        : dirichlet_series(n, opt_size_dense(n)) {}\n    template <typename\
    \ F, typename Prefix>\n    dirichlet_series(long long n, F f, Prefix prefix)\n\
    \        : dirichlet_series(n, opt_size_dense(n), f, prefix) {}\n    dirichlet_series(long\
    \ long n, long long size_dense)\n        : n_(n), size_dense_(size_dense), size_sparse_(n_\
    \ / (size_dense_ + 1)),\n          data_(size_dense_ + 1), sum_dense_(size_dense_\
    \ + 1),\n          sum_sparse_(size_sparse_ + 1) {\n        assert(static_cast<long\
    \ long>(std::sqrt(n_)) <= size_dense_);\n    }\n    template <typename F, typename\
    \ Prefix>\n    dirichlet_series(long long n, long long size_dense, F f, Prefix\
    \ prefix)\n        : n_(n), size_dense_(size_dense), size_sparse_(n_ / (size_dense_\
    \ + 1)),\n          data_(size_dense_ + 1), sum_dense_(size_dense_ + 1),\n   \
    \       sum_sparse_(size_sparse_ + 1) {\n        assert(static_cast<long long>(std::sqrt(n_))\
    \ <= size_dense_);\n        if constexpr (std::is_invocable_r_v<T, F, long long>)\
    \ {\n            for (auto i = 1LL; i <= size_dense_; ++i) {\n               \
    \ data_[i] = f(i);\n            }\n        } else {\n            f(data_);\n \
    \           assert(static_cast<long long>(data_.size()) == size_dense_ + 1);\n\
    \        }\n        std::partial_sum(data_.begin(), data_.end(), sum_dense_.begin());\n\
    \        for (auto i = 1LL; i <= size_sparse_; ++i) {\n            sum_sparse_[i]\
    \ = prefix(internal_div(n_, i));\n        }\n    };\n    const T &operator[](long\
    \ long pos) const {\n        assert(1 <= pos && pos <= size_dense_);\n       \
    \ return data_[pos];\n    }\n    T &operator[](long long pos) {\n        assert(1\
    \ <= pos && pos <= size_dense_);\n        return data_[pos];\n    }\n    T sum(long\
    \ long pos) const {\n        if (pos <= 0) {\n            return T(0);\n     \
    \   }\n        if (1 <= pos && pos <= size_dense_) {\n            return sum_dense_[pos];\n\
    \        } else {\n            const auto x = internal_div(n_, pos);\n       \
    \     assert(1 <= x && x <= size_sparse_ &&\n                   internal_div(n_,\
    \ (pos + 1)) + 1 == x);\n            return sum_sparse_[x];\n        }\n    }\n\
    \    dirichlet_series &operator+=(const dirichlet_series &other) {\n        assert_size(other);\n\
    \        for (auto i = 1LL; i <= size_dense_; ++i) {\n            data_[i] +=\
    \ other.data_[i];\n            sum_dense_[i] += other.sum_dense_[i];\n       \
    \ }\n        for (auto i = 1LL; i <= size_sparse_; ++i) {\n            sum_sparse_[i]\
    \ += other.sum_sparse_[i];\n        }\n        return *this;\n    }\n    dirichlet_series\
    \ &operator-=(const dirichlet_series &other) {\n        assert_size(other);\n\
    \        for (auto i = 1LL; i <= size_dense_; ++i) {\n            data_[i] -=\
    \ other.data_[i];\n            sum_dense_[i] -= other.sum_dense_[i];\n       \
    \ }\n        for (auto i = 1LL; i <= size_sparse_; ++i) {\n            sum_sparse_[i]\
    \ -= other.sum_sparse_[i];\n        }\n        return *this;\n    }\n    dirichlet_series\
    \ &operator*=(const dirichlet_series &other) {\n        assert_size(other);\n\
    \        dirichlet_series result(n_, size_dense_);\n        for (auto i = 1LL;\
    \ i <= size_dense_; ++i) {\n            for (auto j = 1LL; i * j <= size_dense_;\
    \ ++j) {\n                result.data_[i * j] += data_[i] * other.data_[j];\n\
    \            }\n        }\n        std::partial_sum(std::next(result.data_.begin()),\
    \ result.data_.end(),\n                         std::next(result.sum_dense_.begin()));\n\
    \        for (auto i = 1LL; i <= size_sparse_; ++i) {\n            const auto\
    \ x = internal_div(n_, i);\n            auto j = 1LL;\n            for (; j *\
    \ j <= x; ++j) {\n                result.sum_sparse_[i] +=\n                 \
    \   data_[j] * other.sum(internal_div(x, j)) +\n                    sum(internal_div(x,\
    \ j)) * other.data_[j];\n            }\n            result.sum_sparse_[i] -= sum(j\
    \ - 1) * other.sum(j - 1);\n        }\n        *this = std::move(result);\n  \
    \      return *this;\n    }\n    dirichlet_series &operator/=(const dirichlet_series\
    \ &other) {\n        assert_size(other);\n        assert(other[1] != T(0));\n\
    \        if (this == &other) {\n            *this = identity(n_, size_dense_);\n\
    \            return *this;\n        }\n        if constexpr (std::is_integral_v<T>)\
    \ {\n            assert(std::abs(other[1]) == T(1));\n        }\n        const\
    \ auto inv = T(1) / other[1];\n        for (auto i = 1LL; i <= size_dense_; ++i)\
    \ {\n            data_[i] *= inv;\n            for (auto j = 2LL; i * j <= size_dense_;\
    \ ++j) {\n                data_[i * j] -= data_[i] * other.data_[j];\n       \
    \     }\n        }\n        partial_sum(std::next(data_.begin()), data_.end(),\n\
    \                    std::next(sum_dense_.begin()));\n        for (auto i = size_sparse_;\
    \ 1 <= i; --i) {\n            const auto x = internal_div(n_, i);\n          \
    \  auto val = sum_sparse_[i];\n            sum_sparse_[i] = T(0);\n          \
    \  auto j = 1LL;\n            for (; j * j <= x; ++j) {\n                val -=\
    \ data_[j] * other.sum(internal_div(x, j)) +\n                       sum(internal_div(x,\
    \ j)) * other.data_[j];\n            }\n            val += sum(j - 1) * other.sum(j\
    \ - 1);\n            val *= inv;\n            sum_sparse_[i] = val;\n        }\n\
    \        return *this;\n    }\n    dirichlet_series &pow(long long k) {\n    \
    \    assert(k >= 0);\n        auto result(identity(n_, size_dense_));\n      \
    \  while (k) {\n            if (k & 1) {\n                result *= *this;\n \
    \           }\n            *this *= *this;\n            k >>= 1;\n        }\n\
    \        *this = std::move(result);\n        return *this;\n    }\n    friend\
    \ dirichlet_series operator+(const dirichlet_series &lhs,\n                  \
    \                    const dirichlet_series &rhs) {\n        auto result(lhs);\n\
    \        result += rhs;\n        return result;\n    };\n    friend dirichlet_series\
    \ operator-(const dirichlet_series &lhs,\n                                   \
    \   const dirichlet_series &rhs) {\n        auto result(lhs);\n        result\
    \ -= rhs;\n        return result;\n    };\n    friend dirichlet_series operator*(const\
    \ dirichlet_series &lhs,\n                                      const dirichlet_series\
    \ &rhs) {\n        auto result(lhs);\n        result *= rhs;\n        return result;\n\
    \    };\n    friend dirichlet_series operator/(const dirichlet_series &lhs,\n\
    \                                      const dirichlet_series &rhs) {\n      \
    \  auto result(lhs);\n        result /= rhs;\n        return result;\n    };\n\
    \    template <typename... Args>\n    static dirichlet_series identity(Args &&...args)\
    \ {\n        dirichlet_series result(std::forward<Args>(args)...);\n        result[1]\
    \ = T(1);\n        std::fill(std::next(result.sum_dense_.begin()), result.sum_dense_.end(),\n\
    \                  T(1));\n        std::fill(std::next(result.sum_sparse_.begin()),\n\
    \                  result.sum_sparse_.end(), T(1));\n        return result;\n\
    \    }\n    template <typename... Args> static dirichlet_series zeta(Args &&...args)\
    \ {\n        dirichlet_series result(std::forward<Args>(args)...);\n        std::fill(std::next(result.data_.begin()),\
    \ result.data_.end(), T(1));\n        std::iota(std::next(result.sum_dense_.begin()),\
    \ result.sum_dense_.end(),\n                  T(1));\n        for (auto i = 1LL;\
    \ i <= result.size_sparse_; ++i) {\n            const auto x = internal_div(result.n_,\
    \ i);\n            result.sum_sparse_[i] = T(x);\n        }\n        return result;\n\
    \    }\n    template <typename... Args>\n    static dirichlet_series zeta_shift_1(Args\
    \ &&...args) {\n        dirichlet_series result(std::forward<Args>(args)...);\n\
    \        std::iota(std::next(result.data_.begin()), result.data_.end(), T(1));\n\
    \        std::partial_sum(std::next(result.data_.begin()), result.data_.end(),\n\
    \                         std::next(result.sum_dense_.begin()));\n        for\
    \ (auto i = 1LL; i <= result.size_sparse_; ++i) {\n            const auto x =\
    \ internal_div(result.n_, i);\n            result.sum_sparse_[i] = T(x) * T(x\
    \ + 1) / T(2);\n        }\n        return result;\n    }\n    template <typename...\
    \ Args>\n    static dirichlet_series zeta_shift(long long k, Args &&...args) {\n\
    \        assert(0 <= k);\n        if (k == 0) {\n            return zeta(std::forward<Args>(args)...);\n\
    \        } else if (k == 1) {\n            return zeta_shift_1(std::forward<Args>(args)...);\n\
    \        }\n        dirichlet_series result(std::forward<Args>(args)...);\n  \
    \      for (auto i = 1LL; i <= result.size_dense_; ++i) {\n            result.data_[i]\
    \ = T(i).pow(k);\n        }\n        std::partial_sum(std::next(result.data_.begin()),\
    \ result.data_.end(),\n                         std::next(result.sum_dense_.begin()));\n\
    \        if (result.size_sparse_ == 0) {\n            return result;\n       \
    \ }\n        std::vector<T> y(k + 2);\n        for (auto i = 0LL; i < k + 2; ++i)\
    \ {\n            y[i] = T(i).pow(k);\n        }\n        std::partial_sum(y.begin(),\
    \ y.end(), y.begin());\n        for (auto i = 1LL; i <= result.size_sparse_; ++i)\
    \ {\n            const auto x = internal_div(result.n_, i);\n            result.sum_sparse_[i]\
    \ = interpolate(y, x);\n        }\n        return result;\n    }\n    template\
    \ <typename... Args> static dirichlet_series mu(Args &&...args) {\n        auto\
    \ result(identity(std::forward<Args>(args)...));\n        result /= zeta(std::forward<Args>(args)...);\n\
    \        return result;\n    }\n    template <typename... Args> static dirichlet_series\
    \ phi(Args &&...args) {\n        auto result(zeta_shift_1(std::forward<Args>(args)...));\n\
    \        result /= zeta(std::forward<Args>(args)...);\n        return result;\n\
    \    }\n\nprivate:\n    void assert_size(const dirichlet_series &other) {\n  \
    \      assert(n_ == other.n_ && size_dense_ == other.size_dense_ &&\n        \
    \       size_sparse_ == other.size_sparse_);\n    }\n    static long long opt_size_dense(long\
    \ long n) {\n        if (n <= 1) {\n            return n;\n        } else {\n\
    \            return static_cast<long long>(\n                std::max(std::sqrt(n),\
    \ std::pow(n, 2.0 / 3) / std::log(n)));\n        }\n    }\n    static long long\
    \ internal_div(long long x, long long y) {\n        return static_cast<long long>(static_cast<double>(x)\
    \ /\n                                      static_cast<double>(y));\n    }\n \
    \   static T interpolate(const std::vector<T> &y, T x) {\n        const auto n\
    \ = static_cast<long long>(y.size());\n        if (const auto i = static_cast<long\
    \ long>(x.val()); 0 <= i && i < n) {\n            return y[i];\n        }\n  \
    \      T f(1);\n        for (auto i = 1LL; i < n; ++i) {\n            f *= T(i);\n\
    \        }\n        std::vector<T> finv(n);\n        finv[n - 1] = f.inv();\n\
    \        for (auto i = n - 2; 0 <= i; --i) {\n            finv[i] = finv[i + 1]\
    \ * T(i + 1);\n        }\n        std::vector<T> prefix(n), suffix(n);\n     \
    \   prefix[0] = suffix[n - 1] = 1;\n        for (auto i = 1LL; i < n; ++i) {\n\
    \            prefix[i] = prefix[i - 1] * (i - 1 - x);\n        }\n        for\
    \ (auto i = n - 2; i >= 0; --i) {\n            suffix[i] = suffix[i + 1] * (i\
    \ + 1 - x);\n        }\n        auto sum = T(0);\n        for (auto i = 0LL; i\
    \ < n; ++i) {\n            const auto val =\n                y[i] * prefix[i]\
    \ * suffix[i] * finv[i] * finv[n - 1 - i];\n            sum += ((i & 1) ? -val\
    \ : val);\n        }\n        return sum;\n    }\n    long long n_, size_dense_,\
    \ size_sparse_;\n    std::vector<T> data_, sum_dense_, sum_sparse_;\n};\n\n#endif\
    \ // DIRICHLET_SERIES_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/dirichlet_series.hpp
  requiredBy: []
  timestamp: '2022-12-24 06:18:25+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/dirichlet_series.hpp
layout: document
redirect_from:
- /library/math/dirichlet_series.hpp
- /library/math/dirichlet_series.hpp.html
title: math/dirichlet_series.hpp
---
