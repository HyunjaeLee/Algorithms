#ifndef DIRICHLET_SERIES_HPP
#define DIRICHLET_SERIES_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T> struct dirichlet_series {
    dirichlet_series() : dirichlet_series(0) {}
    explicit dirichlet_series(long long n)
        : dirichlet_series(n, opt_size_dense(n)) {}
    template <typename F, typename Prefix>
    dirichlet_series(long long n, F f, Prefix prefix)
        : dirichlet_series(n, opt_size_dense(n), f, prefix) {}
    dirichlet_series(long long n, long long size_dense)
        : n_(n), size_dense_(size_dense), size_sparse_(n_ / (size_dense_ + 1)),
          data_(size_dense_ + 1), sum_dense_(size_dense_ + 1),
          sum_sparse_(size_sparse_ + 1) {
        assert(static_cast<long long>(std::sqrt(n_)) <= size_dense_);
    }
    template <typename F, typename Prefix>
    dirichlet_series(long long n, long long size_dense, F f, Prefix prefix)
        : n_(n), size_dense_(size_dense), size_sparse_(n_ / (size_dense_ + 1)),
          data_(size_dense_ + 1), sum_dense_(size_dense_ + 1),
          sum_sparse_(size_sparse_ + 1) {
        assert(static_cast<long long>(std::sqrt(n_)) <= size_dense_);
        if constexpr (std::is_invocable_r_v<T, F, long long>) {
            for (auto i = 1LL; i <= size_dense_; ++i) {
                data_[i] = f(i);
            }
        } else {
            f(data_);
            assert(static_cast<long long>(data_.size()) == size_dense_ + 1);
        }
        std::partial_sum(data_.begin(), data_.end(), sum_dense_.begin());
        for (auto i = 1LL; i <= size_sparse_; ++i) {
            sum_sparse_[i] = prefix(internal_div(n_, i));
        }
    };
    const T &operator[](long long pos) const {
        assert(1 <= pos && pos <= size_dense_);
        return data_[pos];
    }
    T &operator[](long long pos) {
        assert(1 <= pos && pos <= size_dense_);
        return data_[pos];
    }
    T sum(long long pos) const {
        if (pos <= 0) {
            return T(0);
        }
        if (1 <= pos && pos <= size_dense_) {
            return sum_dense_[pos];
        } else {
            const auto x = internal_div(n_, pos);
            assert(1 <= x && x <= size_sparse_ &&
                   internal_div(n_, (pos + 1)) + 1 == x);
            return sum_sparse_[x];
        }
    }
    dirichlet_series &operator+=(const dirichlet_series &other) {
        assert_size(other);
        for (auto i = 1LL; i <= size_dense_; ++i) {
            data_[i] += other.data_[i];
            sum_dense_[i] += other.sum_dense_[i];
        }
        for (auto i = 1LL; i <= size_sparse_; ++i) {
            sum_sparse_[i] += other.sum_sparse_[i];
        }
        return *this;
    }
    dirichlet_series &operator-=(const dirichlet_series &other) {
        assert_size(other);
        for (auto i = 1LL; i <= size_dense_; ++i) {
            data_[i] -= other.data_[i];
            sum_dense_[i] -= other.sum_dense_[i];
        }
        for (auto i = 1LL; i <= size_sparse_; ++i) {
            sum_sparse_[i] -= other.sum_sparse_[i];
        }
        return *this;
    }
    dirichlet_series &operator*=(const dirichlet_series &other) {
        assert_size(other);
        dirichlet_series result(n_, size_dense_);
        for (auto i = 1LL; i <= size_dense_; ++i) {
            for (auto j = 1LL; i * j <= size_dense_; ++j) {
                result.data_[i * j] += data_[i] * other.data_[j];
            }
        }
        std::partial_sum(std::next(result.data_.begin()), result.data_.end(),
                         std::next(result.sum_dense_.begin()));
        for (auto i = 1LL; i <= size_sparse_; ++i) {
            const auto x = internal_div(n_, i);
            auto j = 1LL;
            for (; j * j <= x; ++j) {
                result.sum_sparse_[i] +=
                    data_[j] * other.sum(internal_div(x, j)) +
                    sum(internal_div(x, j)) * other.data_[j];
            }
            result.sum_sparse_[i] -= sum(j - 1) * other.sum(j - 1);
        }
        *this = std::move(result);
        return *this;
    }
    dirichlet_series &operator/=(const dirichlet_series &other) {
        assert_size(other);
        assert(other[1] != T(0));
        if (this == &other) {
            *this = identity(n_, size_dense_);
            return *this;
        }
        if constexpr (std::is_integral_v<T>) {
            assert(std::abs(other[1]) == T(1));
        }
        const auto inv = T(1) / other[1];
        for (auto i = 1LL; i <= size_dense_; ++i) {
            data_[i] *= inv;
            for (auto j = 2LL; i * j <= size_dense_; ++j) {
                data_[i * j] -= data_[i] * other.data_[j];
            }
        }
        partial_sum(std::next(data_.begin()), data_.end(),
                    std::next(sum_dense_.begin()));
        for (auto i = size_sparse_; 1 <= i; --i) {
            const auto x = internal_div(n_, i);
            auto val = sum_sparse_[i];
            sum_sparse_[i] = T(0);
            auto j = 1LL;
            for (; j * j <= x; ++j) {
                val -= data_[j] * other.sum(internal_div(x, j)) +
                       sum(internal_div(x, j)) * other.data_[j];
            }
            val += sum(j - 1) * other.sum(j - 1);
            val *= inv;
            sum_sparse_[i] = val;
        }
        return *this;
    }
    dirichlet_series &pow(long long k) {
        assert(k >= 0);
        auto result(identity(n_, size_dense_));
        while (k) {
            if (k & 1) {
                result *= *this;
            }
            *this *= *this;
            k >>= 1;
        }
        *this = std::move(result);
        return *this;
    }
    friend dirichlet_series operator+(const dirichlet_series &lhs,
                                      const dirichlet_series &rhs) {
        auto result(lhs);
        result += rhs;
        return result;
    };
    friend dirichlet_series operator-(const dirichlet_series &lhs,
                                      const dirichlet_series &rhs) {
        auto result(lhs);
        result -= rhs;
        return result;
    };
    friend dirichlet_series operator*(const dirichlet_series &lhs,
                                      const dirichlet_series &rhs) {
        auto result(lhs);
        result *= rhs;
        return result;
    };
    friend dirichlet_series operator/(const dirichlet_series &lhs,
                                      const dirichlet_series &rhs) {
        auto result(lhs);
        result /= rhs;
        return result;
    };
    template <typename... Args>
    static dirichlet_series identity(Args &&...args) {
        dirichlet_series result(std::forward<Args>(args)...);
        result[1] = T(1);
        std::fill(std::next(result.sum_dense_.begin()), result.sum_dense_.end(),
                  T(1));
        std::fill(std::next(result.sum_sparse_.begin()),
                  result.sum_sparse_.end(), T(1));
        return result;
    }
    template <typename... Args> static dirichlet_series zeta(Args &&...args) {
        dirichlet_series result(std::forward<Args>(args)...);
        std::fill(std::next(result.data_.begin()), result.data_.end(), T(1));
        std::iota(std::next(result.sum_dense_.begin()), result.sum_dense_.end(),
                  T(1));
        for (auto i = 1LL; i <= result.size_sparse_; ++i) {
            const auto x = internal_div(result.n_, i);
            result.sum_sparse_[i] = T(x);
        }
        return result;
    }
    template <typename... Args>
    static dirichlet_series zeta_shift_1(Args &&...args) {
        dirichlet_series result(std::forward<Args>(args)...);
        std::iota(std::next(result.data_.begin()), result.data_.end(), T(1));
        std::partial_sum(std::next(result.data_.begin()), result.data_.end(),
                         std::next(result.sum_dense_.begin()));
        for (auto i = 1LL; i <= result.size_sparse_; ++i) {
            const auto x = internal_div(result.n_, i);
            result.sum_sparse_[i] = T(x) * T(x + 1) / T(2);
        }
        return result;
    }
    template <typename... Args>
    static dirichlet_series zeta_shift(long long k, Args &&...args) {
        assert(0 <= k);
        if (k == 0) {
            return zeta(std::forward<Args>(args)...);
        } else if (k == 1) {
            return zeta_shift_1(std::forward<Args>(args)...);
        }
        dirichlet_series result(std::forward<Args>(args)...);
        for (auto i = 1LL; i <= result.size_dense_; ++i) {
            result.data_[i] = T(i).pow(k);
        }
        std::partial_sum(std::next(result.data_.begin()), result.data_.end(),
                         std::next(result.sum_dense_.begin()));
        if (result.size_sparse_ == 0) {
            return result;
        }
        std::vector<T> y(k + 2);
        for (auto i = 0LL; i < k + 2; ++i) {
            y[i] = T(i).pow(k);
        }
        std::partial_sum(y.begin(), y.end(), y.begin());
        for (auto i = 1LL; i <= result.size_sparse_; ++i) {
            const auto x = internal_div(result.n_, i);
            result.sum_sparse_[i] = interpolate(y, x);
        }
        return result;
    }
    template <typename... Args> static dirichlet_series mu(Args &&...args) {
        auto result(identity(std::forward<Args>(args)...));
        result /= zeta(std::forward<Args>(args)...);
        return result;
    }
    template <typename... Args> static dirichlet_series phi(Args &&...args) {
        auto result(zeta_shift_1(std::forward<Args>(args)...));
        result /= zeta(std::forward<Args>(args)...);
        return result;
    }

private:
    void assert_size(const dirichlet_series &other) {
        assert(n_ == other.n_ && size_dense_ == other.size_dense_ &&
               size_sparse_ == other.size_sparse_);
    }
    static long long opt_size_dense(long long n) {
        if (n <= 1) {
            return n;
        } else {
            return static_cast<long long>(
                std::max(std::sqrt(n), std::pow(n, 2.0 / 3) / std::log(n)));
        }
    }
    static long long internal_div(long long x, long long y) {
        return static_cast<long long>(static_cast<double>(x) /
                                      static_cast<double>(y));
    }
    static T interpolate(const std::vector<T> &y, T x) {
        const auto n = static_cast<long long>(y.size());
        if (const auto i = static_cast<long long>(x.val()); 0 <= i && i < n) {
            return y[i];
        }
        T f(1);
        for (auto i = 1LL; i < n; ++i) {
            f *= T(i);
        }
        std::vector<T> finv(n);
        finv[n - 1] = f.inv();
        for (auto i = n - 2; 0 <= i; --i) {
            finv[i] = finv[i + 1] * T(i + 1);
        }
        std::vector<T> prefix(n), suffix(n);
        prefix[0] = suffix[n - 1] = 1;
        for (auto i = 1LL; i < n; ++i) {
            prefix[i] = prefix[i - 1] * (i - 1 - x);
        }
        for (auto i = n - 2; i >= 0; --i) {
            suffix[i] = suffix[i + 1] * (i + 1 - x);
        }
        auto sum = T(0);
        for (auto i = 0LL; i < n; ++i) {
            const auto val =
                y[i] * prefix[i] * suffix[i] * finv[i] * finv[n - 1 - i];
            sum += ((i & 1) ? -val : val);
        }
        return sum;
    }
    long long n_, size_dense_, size_sparse_;
    std::vector<T> data_, sum_dense_, sum_sparse_;
};

#endif // DIRICHLET_SERIES_HPP
