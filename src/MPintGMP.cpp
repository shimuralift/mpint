#include "MPint.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

#include <gmp.h>

// ---------------------------------------------------------------------------
// Impl wraps a GMP mpz_t.  All C++ resource management is handled here;
// the operator bodies below are unchanged in structure from the long-int
// variant — only the primitive operations differ.
// ---------------------------------------------------------------------------
struct MPint::Impl {
    mpz_t mVal;

    Impl()                             { mpz_init(mVal); }
    explicit Impl(signed long int   v) { mpz_init_set_si(mVal, v); }
    explicit Impl(unsigned long int v) { mpz_init_set_ui(mVal, v); }
    Impl(const Impl& o)                { mpz_init_set(mVal, o.mVal); }
    ~Impl()                            { mpz_clear(mVal); }
    Impl& operator=(const Impl&) = delete;
};

// --- construction -----------------------------------------------------------

MPint::MPint()                    noexcept : pImpl(new Impl()) {}
MPint::MPint(signed long int   v) noexcept : pImpl(new Impl(v)) {}
MPint::MPint(signed int        v) noexcept : pImpl(new Impl(static_cast<signed long int>(v))) {}
MPint::MPint(signed short      v) noexcept : pImpl(new Impl(static_cast<signed long int>(v))) {}
MPint::MPint(signed char       v) noexcept : pImpl(new Impl(static_cast<signed long int>(v))) {}
MPint::MPint(unsigned long int v) noexcept : pImpl(new Impl(static_cast<signed long int>(v))) {}
MPint::MPint(unsigned int      v) noexcept : pImpl(new Impl(static_cast<signed long int>(v))) {}
MPint::MPint(unsigned short    v) noexcept : pImpl(new Impl(static_cast<signed long int>(v))) {}
MPint::MPint(unsigned char     v) noexcept : pImpl(new Impl(static_cast<signed long int>(v))) {}
MPint::MPint(long long         v) noexcept : pImpl(new Impl(static_cast<signed long int>(v))) {}

MPint::MPint(const MPint& other)  noexcept : pImpl(new Impl(*other.pImpl)) {}
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
MPint::operator float()             const noexcept { return static_cast<float>(mpz_get_d(pImpl->mVal)); }
MPint::operator double()            const noexcept { return mpz_get_d(pImpl->mVal); }
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
