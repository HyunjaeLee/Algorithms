#ifndef REVERSIBLE_MONOID_HPP
#define REVERSIBLE_MONOID_HPP

template <typename M> struct ReversibleMonoid {
    ReversibleMonoid(M x) : val(x), rev(x) {}
    ReversibleMonoid(M x, M y) : val(x), rev(y) {}
    static ReversibleMonoid op(ReversibleMonoid l, ReversibleMonoid r) {
        return {M::op(l.val, r.val), M::op(r.rev, l.rev)};
    }
    static ReversibleMonoid e() { return {M::e(), M::e()}; }
    static ReversibleMonoid toggle(ReversibleMonoid x) { return {x.rev, x.val}; }
    M val, rev;
};

#endif // REVERSIBLE_MONOID_HPP