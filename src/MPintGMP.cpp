#include "MPint.hpp"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include <gmp.h>

// ---------------------------------------------------------------------------
// Impl wraps a GMP mpz_t.  All C++ resource management is handled here;
// the operator bodies below are unchanged in structure from the long-int
// variant — only the primitive operations differ.
// ---------------------------------------------------------------------------
struct MPint::MPintImpl {
    mpz_t mVal;

    MPintImpl()                             { mpz_init(mVal); }
    explicit MPintImpl(signed long int   v) { mpz_init_set_si(mVal, v); }
    explicit MPintImpl(unsigned long int v) { mpz_init_set_ui(mVal, v); }
    MPintImpl(const MPintImpl& o)                { mpz_init_set(mVal, o.mVal); }
    ~MPintImpl()                            { mpz_clear(mVal); }
    MPintImpl& operator=(const MPintImpl&) = delete;
};

// --- string parsing helper --------------------------------------------------
// Strips single-quote separators and handles the 0b/0B binary prefix that
// GMP's mpz_set_str does not recognise natively.

static void mpz_set_mpint_str(mpz_t dest, const char* s) {
    const char* p = s;

    // Preserve leading sign for the clean buffer
    bool negative = false;
    if (*p == '-')      { negative = true; ++p; }
    else if (*p == '+') { ++p; }

    // Detect base and advance past any prefix
    int base = 0; // 0 → GMP auto-detects 0x (hex) and 0 (octal)
    if (*p == '0') {
        const char* q = p + 1;
        if (*q == 'b' || *q == 'B') { base = 2; p += 2; }
        // 0x and 0-prefix are left for GMP's base-0 auto-detection
    }

    // Build a clean copy without single-quote separators
    std::string clean;
    clean.reserve(std::strlen(p) + 1);
    if (negative) clean += '-';
    for (; *p; ++p) {
        if (*p != '\'') clean += *p;
    }

    mpz_set_str(dest, clean.c_str(), base);
}

// --- construction -----------------------------------------------------------

MPint::MPint()                    noexcept : pImpl(new MPintImpl()) {}
MPint::MPint(signed long int   v) noexcept : pImpl(new MPintImpl(v)) {}
MPint::MPint(signed int        v) noexcept : pImpl(new MPintImpl(static_cast<signed long int>(v))) {}
MPint::MPint(signed short      v) noexcept : pImpl(new MPintImpl(static_cast<signed long int>(v))) {}
MPint::MPint(signed char       v) noexcept : pImpl(new MPintImpl(static_cast<signed long int>(v))) {}
MPint::MPint(unsigned long int v) noexcept : pImpl(new MPintImpl(static_cast<signed long int>(v))) {}
MPint::MPint(unsigned int      v) noexcept : pImpl(new MPintImpl(static_cast<signed long int>(v))) {}
MPint::MPint(unsigned short    v) noexcept : pImpl(new MPintImpl(static_cast<signed long int>(v))) {}
MPint::MPint(unsigned char     v) noexcept : pImpl(new MPintImpl(static_cast<signed long int>(v))) {}
MPint::MPint(long long         v) noexcept : pImpl(new MPintImpl(static_cast<signed long int>(v))) {}

MPint::MPint(const char*        s) noexcept : pImpl(new MPintImpl()) { mpz_set_mpint_str(pImpl->mVal, s); }
MPint::MPint(const std::string& s) noexcept : pImpl(new MPintImpl()) { mpz_set_mpint_str(pImpl->mVal, s.c_str()); }

MPint::MPint(const MPint& other)  noexcept : pImpl(new MPintImpl(*other.pImpl)) {}
MPint::MPint(MPint&&      other)  noexcept : pImpl(other.pImpl) { other.pImpl = nullptr; }

MPint& MPint::operator=(const MPint& other) noexcept {
    if (this != &other) mpz_set(pImpl->mVal, other.pImpl->mVal);
    return *this;
}

MPint& MPint::operator=(MPint&& other) noexcept {
    if (this != &other) { delete pImpl; pImpl = other.pImpl; other.pImpl = nullptr; }
    return *this;
}

MPint::~MPint() { delete pImpl; }

// --- conversion out ---------------------------------------------------------

MPint::operator signed long int()   const noexcept { return mpz_get_si(pImpl->mVal); }
MPint::operator signed int()        const noexcept { return static_cast<int>(mpz_get_si(pImpl->mVal)); }
MPint::operator signed short()      const noexcept { return static_cast<short>(mpz_get_si(pImpl->mVal)); }
MPint::operator signed char()       const noexcept { return static_cast<signed char>(mpz_get_si(pImpl->mVal)); }
MPint::operator unsigned long int() const noexcept { return mpz_get_ui(pImpl->mVal); }
MPint::operator unsigned int()      const noexcept { return static_cast<unsigned int>(mpz_get_ui(pImpl->mVal)); }
MPint::operator bool()              const noexcept { return mpz_sgn(pImpl->mVal) != 0; }
MPint::operator float() const {
    float f = static_cast<float>(mpz_get_d(pImpl->mVal));
    if (std::isinf(f)) throw std::overflow_error("MPint->float overflow");
    return f;
}
MPint::operator double() const {
    double d = mpz_get_d(pImpl->mVal);
    if (std::isinf(d)) throw std::overflow_error("MPint->double overflow");
    return d;
}
MPint::operator long double()       const noexcept { return static_cast<long double>(mpz_get_d(pImpl->mVal)); }

// --- unary arithmetic -------------------------------------------------------

MPint MPint::operator+() const noexcept { return *this; }
MPint MPint::operator-() const noexcept {
    MPint r;
    mpz_neg(r.pImpl->mVal, pImpl->mVal);
    return r;
}

// --- unary logical ----------------------------------------------------------

bool MPint::operator!() const noexcept { return mpz_sgn(pImpl->mVal) == 0; }

// --- unary bitwise ----------------------------------------------------------

MPint MPint::operator~() const noexcept {
    MPint r;
    mpz_com(r.pImpl->mVal, pImpl->mVal);
    return r;
}

// --- prefix increment / decrement -------------------------------------------

MPint& MPint::operator++() noexcept { mpz_add_ui(pImpl->mVal, pImpl->mVal, 1); return *this; }
MPint& MPint::operator--() noexcept { mpz_sub_ui(pImpl->mVal, pImpl->mVal, 1); return *this; }

// --- postfix increment / decrement ------------------------------------------

MPint MPint::operator++(int) noexcept { MPint tmp(*this); mpz_add_ui(pImpl->mVal, pImpl->mVal, 1); return tmp; }
MPint MPint::operator--(int) noexcept { MPint tmp(*this); mpz_sub_ui(pImpl->mVal, pImpl->mVal, 1); return tmp; }

// --- compound assignment: arithmetic ----------------------------------------

MPint& MPint::operator+=(const MPint& rhs) noexcept { mpz_add(pImpl->mVal, pImpl->mVal, rhs.pImpl->mVal); return *this; }
MPint& MPint::operator-=(const MPint& rhs) noexcept { mpz_sub(pImpl->mVal, pImpl->mVal, rhs.pImpl->mVal); return *this; }
MPint& MPint::operator*=(const MPint& rhs) noexcept { mpz_mul(pImpl->mVal, pImpl->mVal, rhs.pImpl->mVal); return *this; }
MPint& MPint::operator/=(const MPint& rhs)           { mpz_tdiv_q(pImpl->mVal, pImpl->mVal, rhs.pImpl->mVal); return *this; }
MPint& MPint::operator%=(const MPint& rhs)           { mpz_tdiv_r(pImpl->mVal, pImpl->mVal, rhs.pImpl->mVal); return *this; }

// --- compound assignment: bitwise -------------------------------------------

MPint& MPint::operator&=(const MPint& rhs) noexcept { mpz_and(pImpl->mVal, pImpl->mVal, rhs.pImpl->mVal); return *this; }
MPint& MPint::operator|=(const MPint& rhs) noexcept { mpz_ior(pImpl->mVal, pImpl->mVal, rhs.pImpl->mVal); return *this; }
MPint& MPint::operator^=(const MPint& rhs) noexcept { mpz_xor(pImpl->mVal, pImpl->mVal, rhs.pImpl->mVal); return *this; }

// --- compound assignment: shift ---------------------------------------------

MPint& MPint::operator<<=(int n)            noexcept { mpz_mul_2exp(pImpl->mVal, pImpl->mVal, static_cast<mp_bitcnt_t>(n)); return *this; }
MPint& MPint::operator>>=(int n)            noexcept { mpz_fdiv_q_2exp(pImpl->mVal, pImpl->mVal, static_cast<mp_bitcnt_t>(n)); return *this; }
MPint& MPint::operator<<=(const MPint& rhs) noexcept { mpz_mul_2exp(pImpl->mVal, pImpl->mVal, static_cast<mp_bitcnt_t>(mpz_get_ui(rhs.pImpl->mVal))); return *this; }
MPint& MPint::operator>>=(const MPint& rhs) noexcept { mpz_fdiv_q_2exp(pImpl->mVal, pImpl->mVal, static_cast<mp_bitcnt_t>(mpz_get_ui(rhs.pImpl->mVal))); return *this; }

// --- binary arithmetic ------------------------------------------------------

MPint operator+(MPint lhs, const MPint& rhs) noexcept { return lhs += rhs; }
MPint operator-(MPint lhs, const MPint& rhs) noexcept { return lhs -= rhs; }
MPint operator*(MPint lhs, const MPint& rhs) noexcept { return lhs *= rhs; }
MPint operator/(MPint lhs, const MPint& rhs)           { return lhs /= rhs; }
MPint operator%(MPint lhs, const MPint& rhs)           { return lhs %= rhs; }

// --- binary bitwise ---------------------------------------------------------

MPint operator&(MPint lhs, const MPint& rhs) noexcept { return lhs &= rhs; }
MPint operator|(MPint lhs, const MPint& rhs) noexcept { return lhs |= rhs; }
MPint operator^(MPint lhs, const MPint& rhs) noexcept { return lhs ^= rhs; }

// --- shift ------------------------------------------------------------------

MPint operator<<(MPint lhs, int n)            noexcept { return lhs <<= n; }
MPint operator>>(MPint lhs, int n)            noexcept { return lhs >>= n; }
MPint operator<<(MPint lhs, const MPint& rhs) noexcept { return lhs <<= rhs; }
MPint operator>>(MPint lhs, const MPint& rhs) noexcept { return lhs >>= rhs; }

// --- comparison -------------------------------------------------------------

bool operator==(const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.pImpl->mVal, b.pImpl->mVal) == 0; }
bool operator!=(const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.pImpl->mVal, b.pImpl->mVal) != 0; }
bool operator< (const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.pImpl->mVal, b.pImpl->mVal) <  0; }
bool operator> (const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.pImpl->mVal, b.pImpl->mVal) >  0; }
bool operator<=(const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.pImpl->mVal, b.pImpl->mVal) <= 0; }
bool operator>=(const MPint& a, const MPint& b) noexcept { return mpz_cmp(a.pImpl->mVal, b.pImpl->mVal) >= 0; }

// --- stream I/O -------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const MPint& v) {
    char* s = mpz_get_str(nullptr, 10, v.pImpl->mVal);
    os << s;
    std::free(s);
    return os;
}

std::istream& operator>>(std::istream& is, MPint& v) {
    std::string s;
    if (is >> s) mpz_set_str(v.pImpl->mVal, s.c_str(), 10);
    return is;
}
