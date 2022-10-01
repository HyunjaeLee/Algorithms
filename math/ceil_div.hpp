#ifndef CEIL_DIV_HPP
#define CEIL_DIV_HPP

template <typename T> T ceil_div(T a, T b) {
    return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0);
}

#endif // CEIL_DIV_HPP