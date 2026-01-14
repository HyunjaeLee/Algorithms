#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <charconv>
#include <iostream>
#include <string_view>
#include <sys/mman.h>
#include <sys/stat.h>
#include <type_traits>
#include <unistd.h>

struct scanner {
    scanner() {
        struct stat st;
        fstat(0, &st);
        if (S_ISREG(st.st_mode)) {
            data_ = p_ = (char *)mmap(nullptr, st.st_size + 65536, PROT_READ,
                                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            if (st.st_size) {
                mmap(data_, st.st_size, PROT_READ, MAP_PRIVATE | MAP_FIXED, 0, 0);
            }
        } else {
            auto *s = new std::string(std::istreambuf_iterator<char>(std::cin), {});
            data_ = p_ = s->data();
        }
    }
    template <typename... Args> void operator()(Args &...args) { (scan(args), ...); }
    std::string_view getline() {
        skip();
        auto first = p_;
        while (*p_ >= ' ') {
            ++p_;
        }
        return std::string_view(first, p_ - first);
    }

private:
    void scan(std::integral auto &x) {
        skip();
        x = 0;
        auto is_negative = false;
        if (*p_ == '-') {
            ++p_;
            is_negative = true;
        }
        for (; *p_ > ' '; ++p_) {
            x = x * 10 + (*p_ & 15);
        }
        if (is_negative) {
            x = -x;
        }
    }
    void scan(std::floating_point auto &x) {
        skip();
        auto first = p_;
        while (*p_ > ' ') {
            ++p_;
        }
        std::from_chars(first, p_, x);
    }
    void scan(char &x) {
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
};

#endif // SCANNER_HPP
