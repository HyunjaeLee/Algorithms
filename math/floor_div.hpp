#ifndef FLOOR_DIV_HPP
#define FLOOR_DIV_HPP

template <typename T> T floor_div(T a, T b) {
    return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0);
}

#endif // FLOOR_DIV_HPP