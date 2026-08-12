#ifndef AFFINE_MONOID_HPP
#define AFFINE_MONOID_HPP

template <typename Z> struct AffineMonoid {
    static AffineMonoid op(AffineMonoid f, AffineMonoid g) {
        auto [a, b] = f;
        auto [c, d] = g;
        return {c * a, c * b + d};
    }
    static AffineMonoid e() { return {1, 0}; }
    Z a, b;
};

#endif // AFFINE_MONOID_HPP