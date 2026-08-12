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
  bundledCode: "#line 1 \"data_structures/tensor.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <concepts>\n#include <type_traits>\n\
    #include <utility>\n\ntemplate <typename T, int NDIMS> struct tensor_view {\n\
    \    static_assert(0 < NDIMS);\n\n    tensor_view() : shape_{}, strides_{}, data_(nullptr)\
    \ {}\n\n    T &operator[](std::array<int, NDIMS> idx) const {\n#ifdef _GLIBCXX_DEBUG\n\
    \        return data_[flatten_index_checked(idx)];\n#else\n        return data_[flatten_index(idx)];\n\
    #endif\n    }\n#ifdef __cpp_multidimensional_subscript\n    template <typename...\
    \ I>\n        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>>\
    \ && ...))\n    T &operator[](I... idx) const {\n        return (*this)[std::array<int,\
    \ NDIMS>{static_cast<int>(idx)...}];\n    }\n#endif\n    decltype(auto) operator[](int\
    \ idx) const {\n#ifdef _GLIBCXX_DEBUG\n        assert(0 <= idx && idx < shape_[0]);\n\
    #endif\n        if constexpr (NDIMS == 1) {\n            return (data_[strides_[0]\
    \ * idx]);\n        } else {\n            std::array<int, NDIMS - 1> nshape;\n\
    \            std::copy(shape_.begin() + 1, shape_.end(), nshape.begin());\n  \
    \          std::array<int, NDIMS - 1> nstrides;\n            std::copy(strides_.begin()\
    \ + 1, strides_.end(), nstrides.begin());\n            T *ndata = data_ + (strides_[0]\
    \ * idx);\n            return tensor_view<T, NDIMS - 1>(nshape, nstrides, ndata);\n\
    \        }\n    }\n\n    T &at(std::array<int, NDIMS> idx) const { return data_[flatten_index_checked(idx)];\
    \ }\n    template <typename... I>\n        requires(1 < NDIMS && sizeof...(I)\
    \ == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))\n    T &at(I...\
    \ idx) const {\n        return at(std::array<int, NDIMS>{static_cast<int>(idx)...});\n\
    \    }\n    decltype(auto) at(int idx) const {\n        assert(0 <= idx && idx\
    \ < shape_[0]);\n        return operator[](idx);\n    }\n\nprivate:\n    tensor_view(std::array<int,\
    \ NDIMS> shape, std::array<int, NDIMS> strides, T *data)\n        : shape_(shape),\
    \ strides_(strides), data_(data) {}\n    int flatten_index(std::array<int, NDIMS>\
    \ idx) const {\n        int res = 0;\n        for (int i = 0; i < NDIMS; ++i)\
    \ {\n            res += idx[i] * strides_[i];\n        }\n        return res;\n\
    \    }\n    int flatten_index_checked(std::array<int, NDIMS> idx) const {\n  \
    \      int res = 0;\n        for (int i = 0; i < NDIMS; ++i) {\n            assert(0\
    \ <= idx[i] && idx[i] < shape_[i]);\n            res += idx[i] * strides_[i];\n\
    \        }\n        return res;\n    }\n    template <typename U, int D> friend\
    \ struct tensor_view;\n    template <typename U, int D> friend struct tensor;\n\
    \    std::array<int, NDIMS> shape_;\n    std::array<int, NDIMS> strides_;\n  \
    \  T *data_;\n};\n\ntemplate <typename T, int NDIMS> struct tensor {\n    static_assert(0\
    \ < NDIMS);\n\n    tensor() : shape_{}, strides_{}, len_(0), data_(nullptr) {}\n\
    \    explicit tensor(std::array<int, NDIMS> shape, const T &val = T()) : shape_(shape),\
    \ len_(1) {\n        for (int i = NDIMS - 1; 0 <= i; --i) {\n            strides_[i]\
    \ = len_;\n            len_ *= shape_[i];\n        }\n        data_ = new T[len_];\n\
    \        std::fill(data_, data_ + len_, val);\n    }\n    tensor(const tensor\
    \ &o) : shape_(o.shape_), strides_(o.strides_), len_(o.len_), data_(new T[len_])\
    \ {\n        for (int i = 0; i < len_; ++i) {\n            data_[i] = o.data_[i];\n\
    \        }\n    }\n    tensor(tensor &&o) noexcept\n        : shape_(std::exchange(o.shape_,\
    \ std::array<int, NDIMS>{})),\n          strides_(std::exchange(o.strides_, std::array<int,\
    \ NDIMS>{})), len_(std::exchange(o.len_, 0)),\n          data_(std::exchange(o.data_,\
    \ nullptr)) {}\n\n    void swap(tensor &o) noexcept {\n        std::swap(shape_,\
    \ o.shape_);\n        std::swap(strides_, o.strides_);\n        std::swap(len_,\
    \ o.len_);\n        std::swap(data_, o.data_);\n    }\n    tensor &operator=(tensor\
    \ &&o) noexcept {\n        tensor tmp(std::move(o));\n        swap(tmp);\n   \
    \     return *this;\n    }\n    tensor &operator=(const tensor &o) { return *this\
    \ = tensor(o); }\n    ~tensor() { delete[] data_; }\n\n    using view_t = tensor_view<T,\
    \ NDIMS>;\n    view_t view() { return tensor_view<T, NDIMS>(shape_, strides_,\
    \ data_); }\n    operator view_t() { return view(); }\n\n    using const_view_t\
    \ = tensor_view<const T, NDIMS>;\n    const_view_t view() const { return tensor_view<const\
    \ T, NDIMS>(shape_, strides_, data_); }\n    operator const_view_t() const { return\
    \ view(); }\n\n    T &operator[](std::array<int, NDIMS> idx) { return view()[idx];\
    \ }\n    const T &operator[](std::array<int, NDIMS> idx) const { return view()[idx];\
    \ }\n\n#ifdef __cpp_multidimensional_subscript\n    template <typename... I>\n\
    \        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>>\
    \ && ...))\n    T &operator[](I... idx) {\n        return (*this)[std::array<int,\
    \ NDIMS>{static_cast<int>(idx)...}];\n    }\n    template <typename... I>\n  \
    \      requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>>\
    \ && ...))\n    const T &operator[](I... idx) const {\n        return (*this)[std::array<int,\
    \ NDIMS>{static_cast<int>(idx)...}];\n    }\n#endif\n\n    decltype(auto) operator[](int\
    \ idx) { return view()[idx]; }\n    decltype(auto) operator[](int idx) const {\
    \ return view()[idx]; }\n\n    T &at(std::array<int, NDIMS> idx) { return view().at(idx);\
    \ }\n    const T &at(std::array<int, NDIMS> idx) const { return view().at(idx);\
    \ }\n\n    template <typename... I>\n        requires(1 < NDIMS && sizeof...(I)\
    \ == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))\n    T &at(I...\
    \ idx) {\n        return view().at(idx...);\n    }\n    template <typename...\
    \ I>\n        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>>\
    \ && ...))\n    const T &at(I... idx) const {\n        return view().at(idx...);\n\
    \    }\n\n    decltype(auto) at(int idx) { return view().at(idx); }\n    decltype(auto)\
    \ at(int idx) const { return view().at(idx); }\n\nprivate:\n    std::array<int,\
    \ NDIMS> shape_;\n    std::array<int, NDIMS> strides_;\n    int len_;\n    T *data_;\n\
    };\n\n\n"
  code: "#ifndef TENSOR_HPP\n#define TENSOR_HPP\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#include <concepts>\n#include <type_traits>\n#include\
    \ <utility>\n\ntemplate <typename T, int NDIMS> struct tensor_view {\n    static_assert(0\
    \ < NDIMS);\n\n    tensor_view() : shape_{}, strides_{}, data_(nullptr) {}\n\n\
    \    T &operator[](std::array<int, NDIMS> idx) const {\n#ifdef _GLIBCXX_DEBUG\n\
    \        return data_[flatten_index_checked(idx)];\n#else\n        return data_[flatten_index(idx)];\n\
    #endif\n    }\n#ifdef __cpp_multidimensional_subscript\n    template <typename...\
    \ I>\n        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>>\
    \ && ...))\n    T &operator[](I... idx) const {\n        return (*this)[std::array<int,\
    \ NDIMS>{static_cast<int>(idx)...}];\n    }\n#endif\n    decltype(auto) operator[](int\
    \ idx) const {\n#ifdef _GLIBCXX_DEBUG\n        assert(0 <= idx && idx < shape_[0]);\n\
    #endif\n        if constexpr (NDIMS == 1) {\n            return (data_[strides_[0]\
    \ * idx]);\n        } else {\n            std::array<int, NDIMS - 1> nshape;\n\
    \            std::copy(shape_.begin() + 1, shape_.end(), nshape.begin());\n  \
    \          std::array<int, NDIMS - 1> nstrides;\n            std::copy(strides_.begin()\
    \ + 1, strides_.end(), nstrides.begin());\n            T *ndata = data_ + (strides_[0]\
    \ * idx);\n            return tensor_view<T, NDIMS - 1>(nshape, nstrides, ndata);\n\
    \        }\n    }\n\n    T &at(std::array<int, NDIMS> idx) const { return data_[flatten_index_checked(idx)];\
    \ }\n    template <typename... I>\n        requires(1 < NDIMS && sizeof...(I)\
    \ == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))\n    T &at(I...\
    \ idx) const {\n        return at(std::array<int, NDIMS>{static_cast<int>(idx)...});\n\
    \    }\n    decltype(auto) at(int idx) const {\n        assert(0 <= idx && idx\
    \ < shape_[0]);\n        return operator[](idx);\n    }\n\nprivate:\n    tensor_view(std::array<int,\
    \ NDIMS> shape, std::array<int, NDIMS> strides, T *data)\n        : shape_(shape),\
    \ strides_(strides), data_(data) {}\n    int flatten_index(std::array<int, NDIMS>\
    \ idx) const {\n        int res = 0;\n        for (int i = 0; i < NDIMS; ++i)\
    \ {\n            res += idx[i] * strides_[i];\n        }\n        return res;\n\
    \    }\n    int flatten_index_checked(std::array<int, NDIMS> idx) const {\n  \
    \      int res = 0;\n        for (int i = 0; i < NDIMS; ++i) {\n            assert(0\
    \ <= idx[i] && idx[i] < shape_[i]);\n            res += idx[i] * strides_[i];\n\
    \        }\n        return res;\n    }\n    template <typename U, int D> friend\
    \ struct tensor_view;\n    template <typename U, int D> friend struct tensor;\n\
    \    std::array<int, NDIMS> shape_;\n    std::array<int, NDIMS> strides_;\n  \
    \  T *data_;\n};\n\ntemplate <typename T, int NDIMS> struct tensor {\n    static_assert(0\
    \ < NDIMS);\n\n    tensor() : shape_{}, strides_{}, len_(0), data_(nullptr) {}\n\
    \    explicit tensor(std::array<int, NDIMS> shape, const T &val = T()) : shape_(shape),\
    \ len_(1) {\n        for (int i = NDIMS - 1; 0 <= i; --i) {\n            strides_[i]\
    \ = len_;\n            len_ *= shape_[i];\n        }\n        data_ = new T[len_];\n\
    \        std::fill(data_, data_ + len_, val);\n    }\n    tensor(const tensor\
    \ &o) : shape_(o.shape_), strides_(o.strides_), len_(o.len_), data_(new T[len_])\
    \ {\n        for (int i = 0; i < len_; ++i) {\n            data_[i] = o.data_[i];\n\
    \        }\n    }\n    tensor(tensor &&o) noexcept\n        : shape_(std::exchange(o.shape_,\
    \ std::array<int, NDIMS>{})),\n          strides_(std::exchange(o.strides_, std::array<int,\
    \ NDIMS>{})), len_(std::exchange(o.len_, 0)),\n          data_(std::exchange(o.data_,\
    \ nullptr)) {}\n\n    void swap(tensor &o) noexcept {\n        std::swap(shape_,\
    \ o.shape_);\n        std::swap(strides_, o.strides_);\n        std::swap(len_,\
    \ o.len_);\n        std::swap(data_, o.data_);\n    }\n    tensor &operator=(tensor\
    \ &&o) noexcept {\n        tensor tmp(std::move(o));\n        swap(tmp);\n   \
    \     return *this;\n    }\n    tensor &operator=(const tensor &o) { return *this\
    \ = tensor(o); }\n    ~tensor() { delete[] data_; }\n\n    using view_t = tensor_view<T,\
    \ NDIMS>;\n    view_t view() { return tensor_view<T, NDIMS>(shape_, strides_,\
    \ data_); }\n    operator view_t() { return view(); }\n\n    using const_view_t\
    \ = tensor_view<const T, NDIMS>;\n    const_view_t view() const { return tensor_view<const\
    \ T, NDIMS>(shape_, strides_, data_); }\n    operator const_view_t() const { return\
    \ view(); }\n\n    T &operator[](std::array<int, NDIMS> idx) { return view()[idx];\
    \ }\n    const T &operator[](std::array<int, NDIMS> idx) const { return view()[idx];\
    \ }\n\n#ifdef __cpp_multidimensional_subscript\n    template <typename... I>\n\
    \        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>>\
    \ && ...))\n    T &operator[](I... idx) {\n        return (*this)[std::array<int,\
    \ NDIMS>{static_cast<int>(idx)...}];\n    }\n    template <typename... I>\n  \
    \      requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>>\
    \ && ...))\n    const T &operator[](I... idx) const {\n        return (*this)[std::array<int,\
    \ NDIMS>{static_cast<int>(idx)...}];\n    }\n#endif\n\n    decltype(auto) operator[](int\
    \ idx) { return view()[idx]; }\n    decltype(auto) operator[](int idx) const {\
    \ return view()[idx]; }\n\n    T &at(std::array<int, NDIMS> idx) { return view().at(idx);\
    \ }\n    const T &at(std::array<int, NDIMS> idx) const { return view().at(idx);\
    \ }\n\n    template <typename... I>\n        requires(1 < NDIMS && sizeof...(I)\
    \ == NDIMS && (std::integral<std::remove_cvref_t<I>> && ...))\n    T &at(I...\
    \ idx) {\n        return view().at(idx...);\n    }\n    template <typename...\
    \ I>\n        requires(1 < NDIMS && sizeof...(I) == NDIMS && (std::integral<std::remove_cvref_t<I>>\
    \ && ...))\n    const T &at(I... idx) const {\n        return view().at(idx...);\n\
    \    }\n\n    decltype(auto) at(int idx) { return view().at(idx); }\n    decltype(auto)\
    \ at(int idx) const { return view().at(idx); }\n\nprivate:\n    std::array<int,\
    \ NDIMS> shape_;\n    std::array<int, NDIMS> strides_;\n    int len_;\n    T *data_;\n\
    };\n\n#endif // TENSOR_HPP"
  dependsOn: []
  isVerificationFile: false
  path: data_structures/tensor.hpp
  requiredBy: []
  timestamp: '2026-08-12 07:43:22+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structures/tensor.hpp
layout: document
redirect_from:
- /library/data_structures/tensor.hpp
- /library/data_structures/tensor.hpp.html
title: data_structures/tensor.hpp
---
