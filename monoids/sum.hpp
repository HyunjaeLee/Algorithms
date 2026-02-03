#ifndef SUM_HPP
#define SUM_HPP

// Additive Abelian Group
template <typename T> struct Sum {
    T val;
    static Sum op(Sum a, Sum b) { return {a.val + b.val}; }
    static Sum e() { return {0}; }
    static Sum inv(Sum x) { return {-x.val}; }
    friend bool operator==(const Sum &a, const Sum &b) { return a.val == b.val; }
};

#endif // SUM_HPP