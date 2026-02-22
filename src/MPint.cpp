#include "MPint.hpp"

#include <iostream>

// ---------------------------------------------------------------------------
// The only implementation detail: what an MPint actually stores.
// To switch to GMP, replace this struct and adjust the operator bodies below.
// Nothing outside this file needs to change.
// ---------------------------------------------------------------------------
struct MPint::Impl {
    signed long int mVal;
};

// --- construction -----------------------------------------------------------

MPint::MPint()                    noexcept : pImpl(new Impl{0L}) {}
MPint::MPint(signed long int   v) noexcept : pImpl(new Impl{v}) {}
MPint::MPint(signed int        v) noexcept : pImpl(new Impl{v}) {}
MPint::MPint(signed short      v) noexcept : pImpl(new Impl{v}) {}
MPint::MPint(signed char       v) noexcept : pImpl(new Impl{v}) {}
MPint::MPint(unsigned long int v) noexcept : pImpl(new Impl{static_cast<signed long int>(v)}) {}
MPint::MPint(unsigned int      v) noexcept : pImpl(new Impl{static_cast<signed long int>(v)}) {}
MPint::MPint(unsigned short    v) noexcept : pImpl(new Impl{static_cast<signed long int>(v)}) {}
MPint::MPint(unsigned char     v) noexcept : pImpl(new Impl{static_cast<signed long int>(v)}) {}
MPint::MPint(long long         v) noexcept : pImpl(new Impl{static_cast<signed long int>(v)}) {}

MPint::MPint(const MPint& other)  noexcept : pImpl(new Impl{other.pImpl->mVal}) {}
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
MPint::operator float()             const noexcept { return static_cast<float>(pImpl->mVal); }
MPint::operator double()            const noexcept { return static_cast<double>(pImpl->mVal); }
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

bool operator==(const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal == b.pImpl->mVal; }
bool operator!=(const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal != b.pImpl->mVal; }
bool operator< (const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal <  b.pImpl->mVal; }
bool operator> (const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal >  b.pImpl->mVal; }
bool operator<=(const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal <= b.pImpl->mVal; }
bool operator>=(const MPint& a, const MPint& b) noexcept { return a.pImpl->mVal >= b.pImpl->mVal; }

// --- stream I/O -------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const MPint& v) { return os << v.pImpl->mVal; }
std::istream& operator>>(std::istream& is,       MPint& v) { return is >> v.pImpl->mVal; }
