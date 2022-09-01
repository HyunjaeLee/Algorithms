#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <charconv>
#include <string_view>
#include <sys/mman.h>
#include <sys/stat.h>
#include <type_traits>

struct scanner {
    scanner() {
        struct stat st;
        fstat(0, &st);
        data_ = p_ = static_cast<char *>(
            mmap(nullptr, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0));
        size_ = st.st_size;
    }
    template <typename... Args> void operator()(Args &...args) {
        (read(args), ...);
    }
    std::string_view getline() {
        skip();
        auto first = p_;
        while (*p_ >= ' ') {
            ++p_;
        }
        return std::string_view(first, p_ - first);
    }

private:
    template <typename T>
    std::enable_if_t<std::is_integral_v<T>, void> read(T &x) {
        skip();
        x = 0;
        auto is_negative = false;
        if (*p_ == '-') {
            ++p_;
            is_negative = true;
        }
        for (; *p_ > ' '; ++p_) {
            x = (x << 1) + (x << 3) + (*p_ & 15);
        }
        if (is_negative) {
            x = -x;
        }
    }
    template <typename T>
    std::enable_if_t<std::is_floating_point_v<T>, void> read(T &x) {
        skip();
        auto first = p_;
        while (*p_ > ' ') {
            ++p_;
        }
        std::from_chars(first, p_, x);
    }
    void read(char &x) {
        skip();
        x = *p_++;
    }
    void skip() {
        while (*p_ <= ' ') {
            ++p_;
        }
    }
    char *data_;
    char *p_;
    size_t size_;
};

#endif // SCANNER_HPP
