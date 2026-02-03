#ifndef XOR_HPP
#define XOR_HPP

// Xor Abelian Group
template <typename T> struct Xor {
    T val;
    static Xor op(Xor a, Xor b) { return {a.val ^ b.val}; }
    static Xor e() { return {0}; }
    static Xor inv(Xor x) { return x; }
    friend bool operator==(const Xor &a, const Xor &b) { return a.val == b.val; }
};

#endif // XOR_HPP