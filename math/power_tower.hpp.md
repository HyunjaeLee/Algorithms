---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/power_tower.test.cpp
    title: test/power_tower.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/tetration_mod.test.cpp
    title: test/tetration_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/power_tower.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <limits>\n#include <type_traits>\n#include <vector>\n\ntemplate <typename T>\
    \ T euler_phi(T n) {\n    T phi = n;\n    for (T i = 2; i * i <= n; i++) {\n \
    \       if (n % i == 0) {\n            phi -= phi / i;\n            while (n %\
    \ i == 0) {\n                n /= i;\n            }\n        }\n    }\n    if\
    \ (n != 1) {\n        phi -= phi / n;\n    }\n    return phi;\n}\n\ntemplate <typename\
    \ T, typename Promote = unsigned long long>\nT power_tower(const std::vector<T>\
    \ &a, T m) {\n    static_assert(std::is_integral_v<T>);\n    assert(m > 0);\n\
    \    std::vector<unsigned long long> mod_chain{\n        static_cast<unsigned\
    \ long long>(m)};\n    while (mod_chain.back() > 1) {\n        const auto phi\
    \ = euler_phi(mod_chain.back());\n        mod_chain.push_back(phi);\n    }\n \
    \   const auto f = [](Promote x, Promote n, Promote mod) {\n        Promote r\
    \ = 1;\n        if (x > mod) {\n            x = x % mod + mod;\n        }\n  \
    \      while (n) {\n            if (n & 1) {\n                r *= x;\n      \
    \          if (r > mod) {\n                    r = r % mod + mod;\n          \
    \      }\n            }\n            x *= x;\n            if (x > mod) {\n   \
    \             x = x % mod + mod;\n            }\n            n >>= 1;\n      \
    \  }\n        return r;\n    };\n    Promote r = 1;\n    const auto k = static_cast<int>(std::min(a.size(),\
    \ mod_chain.size()));\n    for (auto i = k - 1; i >= 0; --i) {\n        assert(a[i]\
    \ > 0);\n        r = f(static_cast<Promote>(a[i]), r, mod_chain[i]);\n    }\n\
    \    return static_cast<T>(r % static_cast<Promote>(m));\n}\n\n\n"
  code: "#ifndef POWER_TOWER_HPP\n#define POWER_TOWER_HPP\n\n#include <cassert>\n\
    #include <limits>\n#include <type_traits>\n#include <vector>\n\ntemplate <typename\
    \ T> T euler_phi(T n) {\n    T phi = n;\n    for (T i = 2; i * i <= n; i++) {\n\
    \        if (n % i == 0) {\n            phi -= phi / i;\n            while (n\
    \ % i == 0) {\n                n /= i;\n            }\n        }\n    }\n    if\
    \ (n != 1) {\n        phi -= phi / n;\n    }\n    return phi;\n}\n\ntemplate <typename\
    \ T, typename Promote = unsigned long long>\nT power_tower(const std::vector<T>\
    \ &a, T m) {\n    static_assert(std::is_integral_v<T>);\n    assert(m > 0);\n\
    \    std::vector<unsigned long long> mod_chain{\n        static_cast<unsigned\
    \ long long>(m)};\n    while (mod_chain.back() > 1) {\n        const auto phi\
    \ = euler_phi(mod_chain.back());\n        mod_chain.push_back(phi);\n    }\n \
    \   const auto f = [](Promote x, Promote n, Promote mod) {\n        Promote r\
    \ = 1;\n        if (x > mod) {\n            x = x % mod + mod;\n        }\n  \
    \      while (n) {\n            if (n & 1) {\n                r *= x;\n      \
    \          if (r > mod) {\n                    r = r % mod + mod;\n          \
    \      }\n            }\n            x *= x;\n            if (x > mod) {\n   \
    \             x = x % mod + mod;\n            }\n            n >>= 1;\n      \
    \  }\n        return r;\n    };\n    Promote r = 1;\n    const auto k = static_cast<int>(std::min(a.size(),\
    \ mod_chain.size()));\n    for (auto i = k - 1; i >= 0; --i) {\n        assert(a[i]\
    \ > 0);\n        r = f(static_cast<Promote>(a[i]), r, mod_chain[i]);\n    }\n\
    \    return static_cast<T>(r % static_cast<Promote>(m));\n}\n\n#endif // POWER_TOWER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/power_tower.hpp
  requiredBy: []
  timestamp: '2022-12-02 10:32:05+00:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/tetration_mod.test.cpp
  - test/power_tower.test.cpp
documentation_of: math/power_tower.hpp
layout: document
title: Power tower
---

Solves ${ a_0 }^{ { a_1 }^{ { \cdots }^{ a_{n-1} } } }\pmod m$ for positive integers $a_i$ and $m$.  
Algorithm implementation is based on [maspy's code](https://maspypy.github.io/library/mod/tetration.hpp).

power_tower
---
```cpp
template <typename T, typename Promote = unsigned long long>
T power_tower(const std::vector<T> &a, T m);
```

It returns ${ a_0 }^{ { a_1 }^{ { \cdots }^{ a_{ n-1 } } } }\pmod m$.

Providing first $\min(2\lfloor\lg{m}\rfloor, n)$ elements of $a$ is sufficient to calculate ${ a_0 }^{ { a_1 }^{ {\cdots }^{ a_{n-1} } } }\pmod m$. In other words ${a_0}^{ {a_1}^{ {\cdots}^{a_{n-1} } } } \equiv {a_0}^{ {a_1}^{ {\cdots}^{a_{k-1} } } } \pmod m$ where $k = \min(2\lfloor\lg{m}\rfloor, n)$. Notice that ${a_0}^{ {a_1}^{ {\cdots}^{a_{n-1} } } } \equiv {a_0}^{ {a_1}^{ {\cdots}^{a_{x-1} } } } \pmod m$ is true for any integer $x$ such that $\varphi^x(m) = 1$.

`T` is an integral type such as `int`, `unsigned int`, `long long`, and `unsigned long long`. `Promote` is an integral type that can express values between $0$ and $(2m-1)^2$, inclusive.

There are various methods to calculate Euler's phi function. Miller-Rabin and Pollard's rho and precalculated array are possible alternatives. It affects the complexity of `power_tower`.

### Constraints
+ $0 < a[i]$
+ $0 < m$

### Complexity
+ $\mathcal{O}\left(\sqrt{m}\right)$
