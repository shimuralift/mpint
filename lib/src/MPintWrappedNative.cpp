#include "MPint.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

// ---------------------------------------------------------------------------
// The only implementation detail: what an MPint actually stores.
// To switch to an arbitrary precision backend, replace this struct
// and adjust the operator bodies below.
// Nothing outside this file needs to change.
// struct MPint::MPintImpl is an 'aggregate', i.e. it does not have a
// user defined ctor. On construction with 'new', an ordered list of
// member initializations may be provided, e.g. 'new MPintImpl{0L}', see below.
// ---------------------------------------------------------------------------
struct MPint::MPintImpl {
    signed long int mVal;
};

// --- string parsing helper --------------------------------------------------

static signed long int parse_str(const char* const s) {
    const char* p = s;
    bool negative = false;
    if (*p == '-')      { negative = true; ++p; }
    else if (*p == '+') { ++p; }

    int base = 10;
    if (*p == '0') {
        const char* const q = p + 1;
        if      (*q == 'x' || *q == 'X') { base = 16; p += 2; }
        else if (*q == 'b' || *q == 'B') { base =  2; p += 2; }
        else                             { base =  8; p += 1; }
    }

    unsigned long int result = 0;
    for (; *p; ++p) {
        if (*p == '\'') continue;
        unsigned int digit;
        const char c = *p;
        if      (c >= '0' && c <= '9') digit = static_cast<unsigned int>(c - '0');
        else if (c >= 'a' && c <= 'f') digit = static_cast<unsigned int>(c - 'a') + 10u;
        else if (c >= 'A' && c <= 'F') digit = static_cast<unsigned int>(c - 'A') + 10u;
        else break;
        result = result * static_cast<unsigned long int>(base) + digit;
    }
    return negative ? -static_cast<signed long int>(result)
                    :  static_cast<signed long int>(result);
}

// --- construction -----------------------------------------------------------

MPint::MPint()                    : pImpl(new MPintImpl{0L}) {}
MPint::MPint(signed long int   v) : pImpl(new MPintImpl{v}) {}
MPint::MPint(signed int        v) : pImpl(new MPintImpl{v}) {}
MPint::MPint(signed short      v) : pImpl(new MPintImpl{v}) {}
MPint::MPint(signed char       v) : pImpl(new MPintImpl{v}) {}
MPint::MPint(unsigned long int v) : pImpl(new MPintImpl{static_cast<signed long int>(v)}) {}
MPint::MPint(unsigned int      v) : pImpl(new MPintImpl{static_cast<signed long int>(v)}) {}
MPint::MPint(unsigned short    v) : pImpl(new MPintImpl{static_cast<signed long int>(v)}) {}
MPint::MPint(unsigned char     v) : pImpl(new MPintImpl{static_cast<signed long int>(v)}) {}
MPint::MPint(long long         v) : pImpl(new MPintImpl{static_cast<signed long int>(v)}) {}

MPint::MPint(const char*        s) : pImpl(new MPintImpl{parse_str(s)}) {}
MPint::MPint(const std::string& s) : pImpl(new MPintImpl{parse_str(s.c_str())}) {}

MPint::MPint(const MPint& other)  : pImpl(new MPintImpl{other.pImpl->mVal}) {}
MPint::MPint(MPint&&      other)  noexcept : pImpl(other.pImpl) { other.pImpl = nullptr; }

MPint& MPint::operator=(const MPint& other) noexcept {
    if (this != &other) pImpl->mVal = other.pImpl->mVal;
    return *this;
}

MPint& MPint::operator=(MPint&& other) noexcept {
    if (this != &other) { delete pImpl; pImpl = other.pImpl; other.pImpl = nullptr; }
    return *this;
}

MPint::~MPint() { delete pImpl; }

// --- conversion out ---------------------------------------------------------

MPint::operator signed long int()   const noexcept { return pImpl->mVal; }
MPint::operator signed int()        const noexcept { return static_cast<int>(pImpl->mVal); }
MPint::operator signed short()      const noexcept { return static_cast<short>(pImpl->mVal); }
MPint::operator signed char()       const noexcept { return static_cast<signed char>(pImpl->mVal); }
MPint::operator unsigned long int() const noexcept { return static_cast<unsigned long int>(pImpl->mVal); }
MPint::operator unsigned int()      const noexcept { return static_cast<unsigned int>(pImpl->mVal); }
MPint::operator bool()              const noexcept { return pImpl->mVal != 0; }
MPint::operator float() const {
    const float f = static_cast<float>(pImpl->mVal);
    if (std::isinf(f)) throw std::overflow_error("MPint->float overflow");
    return f;
}
MPint::operator double() const {
    const double d = static_cast<double>(pImpl->mVal);
    if (std::isinf(d)) throw std::overflow_error("MPint->double overflow");
    return d;
}
MPint::operator long double()       const noexcept { return static_cast<long double>(pImpl->mVal); }

// --- unary arithmetic -------------------------------------------------------

MPint MPint::operator+() const noexcept { return *this; }
MPint MPint::operator-() const noexcept { return MPint(-pImpl->mVal); }

// --- unary logical ----------------------------------------------------------

bool MPint::operator!() const noexcept { return pImpl->mVal == 0; }

// --- unary bitwise ----------------------------------------------------------

MPint MPint::operator~() const noexcept { return MPint(~pImpl->mVal); }

// --- prefix increment / decrement -------------------------------------------

MPint& MPint::operator++() noexcept { ++pImpl->mVal; return *this; }
MPint& MPint::operator--() noexcept { --pImpl->mVal; return *this; }

// --- postfix increment / decrement ------------------------------------------

MPint MPint::operator++(int) noexcept { MPint tmp(*this); ++pImpl->mVal; return tmp; }
MPint MPint::operator--(int) noexcept { MPint tmp(*this); --pImpl->mVal; return tmp; }

// --- compound assignment: arithmetic ----------------------------------------

MPint& MPint::operator+=(const MPint& rhs) noexcept { pImpl->mVal += rhs.pImpl->mVal; return *this; }
MPint& MPint::operator-=(const MPint& rhs) noexcept { pImpl->mVal -= rhs.pImpl->mVal; return *this; }
MPint& MPint::operator*=(const MPint& rhs) noexcept { pImpl->mVal *= rhs.pImpl->mVal; return *this; }
MPint& MPint::operator/=(const MPint& rhs)           { pImpl->mVal /= rhs.pImpl->mVal; return *this; }
MPint& MPint::operator%=(const MPint& rhs)           { pImpl->mVal %= rhs.pImpl->mVal; return *this; }

// --- compound assignment: bitwise -------------------------------------------

MPint& MPint::operator&=(const MPint& rhs) noexcept { pImpl->mVal &= rhs.pImpl->mVal; return *this; }
MPint& MPint::operator|=(const MPint& rhs) noexcept { pImpl->mVal |= rhs.pImpl->mVal; return *this; }
MPint& MPint::operator^=(const MPint& rhs) noexcept { pImpl->mVal ^= rhs.pImpl->mVal; return *this; }

// --- compound assignment: shift ---------------------------------------------

MPint& MPint::operator<<=(int n)            noexcept { pImpl->mVal <<= n;              return *this; }
MPint& MPint::operator>>=(int n)            noexcept { pImpl->mVal >>= n;              return *this; }
MPint& MPint::operator<<=(const MPint& rhs) noexcept { pImpl->mVal <<= rhs.pImpl->mVal; return *this; }
MPint& MPint::operator>>=(const MPint& rhs) noexcept { pImpl->mVal >>= rhs.pImpl->mVal; return *this; }

// --- comparison -------------------------------------------------------------

bool operator==(const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal == b.pImpl->mVal; }
bool operator!=(const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal != b.pImpl->mVal; }
bool operator< (const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal <  b.pImpl->mVal; }
bool operator> (const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal >  b.pImpl->mVal; }
bool operator<=(const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal <= b.pImpl->mVal; }
bool operator>=(const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal >= b.pImpl->mVal; }

// --- stream I/O -------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const MPint& v) { return os << v.pImpl->mVal; }
std::istream& operator>>(std::istream& is,       MPint& v) { return is >> v.pImpl->mVal; }
