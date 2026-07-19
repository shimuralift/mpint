#pragma once

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include <gmp.h>

// MPint wrapping GMP mpz_t directly — no pimpl, all operators inline.

class MPint {
    mpz_t mVal;

    static void set_mpint_str(mpz_t dest, const char* const s) {
        if (!s) throw std::invalid_argument("MPint: null string pointer");
        const char* p = s;
        bool negative = false;
        if      (*p == '-') { negative = true; ++p; }
        else if (*p == '+') { ++p; }
        int base = 10;
        if (*p == '0') {
            const char* const q = p + 1;
            if      (*q == 'x' || *q == 'X') { base = 16; p += 2; }
            else if (*q == 'b' || *q == 'B') { base =  2; p += 2; }
            else                             { base =  8; }
        }
        std::string clean;
        clean.reserve(std::strlen(p) + 1);
        if (negative) clean += '-';
        for (; *p; ++p) {
            if (*p != '\'') clean += *p;
        }
        if (mpz_set_str(dest, clean.c_str(), base) != 0)
            throw std::invalid_argument(std::string("MPint: invalid integer string: ") + s);
    }

public:
    // --- construction -------------------------------------------------------
    MPint()                    noexcept { mpz_init(mVal); }
    MPint(signed long int   v) noexcept { mpz_init_set_si(mVal, v); }
    MPint(signed int        v) noexcept { mpz_init_set_si(mVal, static_cast<signed long int>(v)); }
    MPint(signed short      v) noexcept { mpz_init_set_si(mVal, static_cast<signed long int>(v)); }
    MPint(signed char       v) noexcept { mpz_init_set_si(mVal, static_cast<signed long int>(v)); }
    MPint(unsigned long int v) noexcept { mpz_init_set_ui(mVal, v); }
    MPint(unsigned int      v) noexcept { mpz_init_set_ui(mVal, static_cast<unsigned long int>(v)); }
    MPint(unsigned short    v) noexcept { mpz_init_set_ui(mVal, static_cast<unsigned long int>(v)); }
    MPint(unsigned char     v) noexcept { mpz_init_set_ui(mVal, static_cast<unsigned long int>(v)); }
    MPint(long long         v) noexcept { mpz_init_set_si(mVal, static_cast<signed long int>(v)); }
    explicit MPint(const char*        s) { mpz_init(mVal); set_mpint_str(mVal, s); }
    explicit MPint(const std::string& s) { mpz_init(mVal); set_mpint_str(mVal, s.c_str()); }

    MPint(const MPint& o)           { mpz_init_set(mVal, o.mVal); }
    MPint(MPint&&      o)  noexcept { mpz_init(mVal); mpz_swap(mVal, o.mVal); }
    MPint& operator=(const MPint& o) noexcept { if (this != &o) mpz_set(mVal, o.mVal); return *this; }
    MPint& operator=(MPint&&      o) noexcept { if (this != &o) mpz_swap(mVal, o.mVal); return *this; }
    ~MPint() { mpz_clear(mVal); }

    // --- conversion out -----------------------------------------------------
    [[nodiscard]] explicit operator signed long int()   const noexcept { return mpz_get_si(mVal); }
    [[nodiscard]] explicit operator signed int()        const noexcept { return static_cast<int>(mpz_get_si(mVal)); }
    [[nodiscard]] explicit operator signed short()      const noexcept { return static_cast<short>(mpz_get_si(mVal)); }
    [[nodiscard]] explicit operator signed char()       const noexcept { return static_cast<signed char>(mpz_get_si(mVal)); }
    [[nodiscard]] explicit operator unsigned long int() const noexcept { return mpz_get_ui(mVal); }
    [[nodiscard]] explicit operator unsigned int()      const noexcept { return static_cast<unsigned int>(mpz_get_ui(mVal)); }
    [[nodiscard]] explicit operator bool()              const noexcept { return mpz_sgn(mVal) != 0; }
    [[nodiscard]] explicit operator float() const {
        const float f = static_cast<float>(mpz_get_d(mVal));
        if (std::isinf(f)) throw std::overflow_error("MPint->float overflow");
        return f;
    }
    [[nodiscard]] explicit operator double() const {
        const double d = mpz_get_d(mVal);
        if (std::isinf(d)) throw std::overflow_error("MPint->double overflow");
        return d;
    }
    [[nodiscard]] explicit operator long double() const noexcept { return static_cast<long double>(mpz_get_d(mVal)); }

    // --- unary arithmetic ---------------------------------------------------
    [[nodiscard]] MPint operator+() const noexcept { return *this; }
    [[nodiscard]] MPint operator-() const noexcept { MPint r; mpz_neg(r.mVal, mVal); return r; }

    // --- unary logical ------------------------------------------------------
    [[nodiscard]] bool  operator!() const noexcept { return mpz_sgn(mVal) == 0; }

    // --- unary bitwise ------------------------------------------------------
    [[nodiscard]] MPint operator~() const noexcept { MPint r; mpz_com(r.mVal, mVal); return r; }

    // --- prefix increment / decrement ---------------------------------------
    MPint& operator++() noexcept { mpz_add_ui(mVal, mVal, 1); return *this; }
    MPint& operator--() noexcept { mpz_sub_ui(mVal, mVal, 1); return *this; }

    // --- postfix increment / decrement --------------------------------------
    MPint operator++(int) noexcept { MPint tmp(*this); mpz_add_ui(mVal, mVal, 1); return tmp; }
    MPint operator--(int) noexcept { MPint tmp(*this); mpz_sub_ui(mVal, mVal, 1); return tmp; }

    // --- compound assignment: arithmetic ------------------------------------
    MPint& operator+=(const MPint& rhs) noexcept { mpz_add(mVal, mVal, rhs.mVal);      return *this; }
    MPint& operator-=(const MPint& rhs) noexcept { mpz_sub(mVal, mVal, rhs.mVal);      return *this; }
    MPint& operator*=(const MPint& rhs) noexcept { mpz_mul(mVal, mVal, rhs.mVal);      return *this; }
    MPint& operator/=(const MPint& rhs)           { mpz_tdiv_q(mVal, mVal, rhs.mVal);  return *this; }
    MPint& operator%=(const MPint& rhs)           { mpz_tdiv_r(mVal, mVal, rhs.mVal);  return *this; }

    // --- compound assignment: bitwise ---------------------------------------
    MPint& operator&=(const MPint& rhs) noexcept { mpz_and(mVal, mVal, rhs.mVal); return *this; }
    MPint& operator|=(const MPint& rhs) noexcept { mpz_ior(mVal, mVal, rhs.mVal); return *this; }
    MPint& operator^=(const MPint& rhs) noexcept { mpz_xor(mVal, mVal, rhs.mVal); return *this; }

    // --- compound assignment: shift -----------------------------------------
    MPint& operator<<=(int n)            noexcept { mpz_mul_2exp(mVal, mVal, static_cast<mp_bitcnt_t>(n));              return *this; }
    MPint& operator>>=(int n)            noexcept { mpz_fdiv_q_2exp(mVal, mVal, static_cast<mp_bitcnt_t>(n));           return *this; }
    MPint& operator<<=(const MPint& rhs) noexcept { mpz_mul_2exp(mVal, mVal, static_cast<mp_bitcnt_t>(mpz_get_ui(rhs.mVal)));    return *this; }
    MPint& operator>>=(const MPint& rhs) noexcept { mpz_fdiv_q_2exp(mVal, mVal, static_cast<mp_bitcnt_t>(mpz_get_ui(rhs.mVal))); return *this; }

    // --- binary arithmetic (inline, delegate to compound assignment) --------
    [[nodiscard]] friend MPint operator+(MPint lhs, const MPint& rhs) noexcept { return lhs += rhs; }
    [[nodiscard]] friend MPint operator-(MPint lhs, const MPint& rhs) noexcept { return lhs -= rhs; }
    [[nodiscard]] friend MPint operator*(MPint lhs, const MPint& rhs) noexcept { return lhs *= rhs; }
    [[nodiscard]] friend MPint operator/(MPint lhs, const MPint& rhs)           { return lhs /= rhs; }
    [[nodiscard]] friend MPint operator%(MPint lhs, const MPint& rhs)           { return lhs %= rhs; }

    // --- binary bitwise -----------------------------------------------------
    [[nodiscard]] friend MPint operator&(MPint lhs, const MPint& rhs) noexcept { return lhs &= rhs; }
    [[nodiscard]] friend MPint operator|(MPint lhs, const MPint& rhs) noexcept { return lhs |= rhs; }
    [[nodiscard]] friend MPint operator^(MPint lhs, const MPint& rhs) noexcept { return lhs ^= rhs; }

    // --- shift --------------------------------------------------------------
    [[nodiscard]] friend MPint operator<<(MPint lhs, int n)            noexcept { return lhs <<= n; }
    [[nodiscard]] friend MPint operator>>(MPint lhs, int n)            noexcept { return lhs >>= n; }
    [[nodiscard]] friend MPint operator<<(MPint lhs, const MPint& rhs) noexcept { return lhs <<= rhs; }
    [[nodiscard]] friend MPint operator>>(MPint lhs, const MPint& rhs) noexcept { return lhs >>= rhs; }

    // --- comparison ---------------------------------------------------------
    [[nodiscard]] friend bool operator==(const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.mVal, b.mVal) == 0; }
    [[nodiscard]] friend bool operator!=(const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.mVal, b.mVal) != 0; }
    [[nodiscard]] friend bool operator< (const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.mVal, b.mVal) <  0; }
    [[nodiscard]] friend bool operator> (const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.mVal, b.mVal) >  0; }
    [[nodiscard]] friend bool operator<=(const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.mVal, b.mVal) <= 0; }
    [[nodiscard]] friend bool operator>=(const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.mVal, b.mVal) >= 0; }

    // --- stream I/O ---------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const MPint& v) {
        char* const s = mpz_get_str(nullptr, 10, v.mVal);
        os << s;
        std::free(s);
        return os;
    }
    friend std::istream& operator>>(std::istream& is, MPint& v) {
        std::string s;
        if (is >> s) {
            mpz_t tmp;
            mpz_init(tmp);
            if (mpz_set_str(tmp, s.c_str(), 10) == 0)
                mpz_set(v.mVal, tmp);
            else
                is.setstate(std::ios::failbit);
            mpz_clear(tmp);
        }
        return is;
    }
};
