#pragma once

#include <iosfwd>

// MPint: a drop-in replacement for signed long int.
// All arithmetic, comparison, bitwise, increment/decrement, and stream
// operators are provided so legacy code needs no textual changes.
// The private mVal member will later be swapped out for a GMP/PARI/...
// multi-precision type without touching any call sites.

class MPint {
public:
    // --- construction -------------------------------------------------------
    MPint() noexcept : mVal(0) {}

    // Accept any built-in integral type without narrowing warnings.
    MPint(signed long int   v) noexcept : mVal(v) {}
    MPint(signed int        v) noexcept : mVal(v) {}
    MPint(signed short      v) noexcept : mVal(v) {}
    MPint(signed char       v) noexcept : mVal(v) {}
    MPint(unsigned long int v) noexcept : mVal(static_cast<signed long int>(v)) {}
    MPint(unsigned int      v) noexcept : mVal(static_cast<signed long int>(v)) {}
    MPint(unsigned short    v) noexcept : mVal(static_cast<signed long int>(v)) {}
    MPint(unsigned char     v) noexcept : mVal(static_cast<signed long int>(v)) {}
    MPint(long long         v) noexcept : mVal(static_cast<signed long int>(v)) {}

    // Copy / move (both trivial for a scalar wrapper)
    MPint(const MPint&)            = default;
    MPint& operator=(const MPint&) = default;

    // --- conversion out ------------------------------------------------------
    // explicit so code like "if (n)" still works (contextual bool conversion)
    // but silent implicit truncation to int, etc., is prevented.
    explicit operator signed long int()   const noexcept { return mVal; }
    explicit operator signed int()        const noexcept { return static_cast<int>(mVal); }
    explicit operator signed short()      const noexcept { return static_cast<short>(mVal); }
    explicit operator signed char()       const noexcept { return static_cast<signed char>(mVal); }
    explicit operator unsigned long int() const noexcept { return static_cast<unsigned long int>(mVal); }
    explicit operator unsigned int()      const noexcept { return static_cast<unsigned int>(mVal); }
    explicit operator bool()              const noexcept { return mVal != 0; }

    // --- unary arithmetic ---------------------------------------------------
    MPint  operator+()         const noexcept { return *this; }
    MPint  operator-()         const noexcept { return MPint(-mVal); }

    // --- unary logical ------------------------------------------------------
    bool   operator!()         const noexcept { return mVal == 0; }

    // --- unary bitwise ------------------------------------------------------
    MPint  operator~()         const noexcept { return MPint(~mVal); }

    // --- prefix increment / decrement ---------------------------------------
    MPint& operator++()    noexcept { ++mVal; return *this; }
    MPint& operator--()    noexcept { --mVal; return *this; }

    // --- postfix increment / decrement --------------------------------------
    MPint  operator++(int) noexcept { MPint tmp(*this); ++mVal; return tmp; }
    MPint  operator--(int) noexcept { MPint tmp(*this); --mVal; return tmp; }

    // --- compound assignment: arithmetic ------------------------------------
    MPint& operator+=(const MPint& rhs) noexcept { mVal += rhs.mVal; return *this; }
    MPint& operator-=(const MPint& rhs) noexcept { mVal -= rhs.mVal; return *this; }
    MPint& operator*=(const MPint& rhs) noexcept { mVal *= rhs.mVal; return *this; }
    MPint& operator/=(const MPint& rhs)          { mVal /= rhs.mVal; return *this; }
    MPint& operator%=(const MPint& rhs)          { mVal %= rhs.mVal; return *this; }

    // --- compound assignment: bitwise ---------------------------------------
    MPint& operator&=(const MPint& rhs) noexcept { mVal &= rhs.mVal; return *this; }
    MPint& operator|=(const MPint& rhs) noexcept { mVal |= rhs.mVal; return *this; }
    MPint& operator^=(const MPint& rhs) noexcept { mVal ^= rhs.mVal; return *this; }

    // --- compound assignment: shift -----------------------------------------
    MPint& operator<<=(int n) noexcept { mVal <<= n; return *this; }
    MPint& operator>>=(int n) noexcept { mVal >>= n; return *this; }
    MPint& operator<<=(const MPint& rhs) noexcept { mVal <<= rhs.mVal; return *this; }
    MPint& operator>>=(const MPint& rhs) noexcept { mVal >>= rhs.mVal; return *this; }

    // --- binary arithmetic (defined via compound assignment) ----------------
    friend MPint operator+(MPint lhs, const MPint& rhs) noexcept { return lhs += rhs; }
    friend MPint operator-(MPint lhs, const MPint& rhs) noexcept { return lhs -= rhs; }
    friend MPint operator*(MPint lhs, const MPint& rhs) noexcept { return lhs *= rhs; }
    friend MPint operator/(MPint lhs, const MPint& rhs)          { return lhs /= rhs; }
    friend MPint operator%(MPint lhs, const MPint& rhs)          { return lhs %= rhs; }

    // --- binary bitwise -----------------------------------------------------
    friend MPint operator&(MPint lhs, const MPint& rhs) noexcept { return lhs &= rhs; }
    friend MPint operator|(MPint lhs, const MPint& rhs) noexcept { return lhs |= rhs; }
    friend MPint operator^(MPint lhs, const MPint& rhs) noexcept { return lhs ^= rhs; }

    // --- shift --------------------------------------------------------------
    friend MPint operator<<(MPint lhs, int n)          noexcept { return lhs <<= n; }
    friend MPint operator>>(MPint lhs, int n)          noexcept { return lhs >>= n; }
    friend MPint operator<<(MPint lhs, const MPint& rhs) noexcept { return lhs <<= rhs; }
    friend MPint operator>>(MPint lhs, const MPint& rhs) noexcept { return lhs >>= rhs; }

    // --- comparison ---------------------------------------------------------
    friend bool operator==(const MPint& a, const MPint& b) noexcept { return a.mVal == b.mVal; }
    friend bool operator!=(const MPint& a, const MPint& b) noexcept { return a.mVal != b.mVal; }
    friend bool operator< (const MPint& a, const MPint& b) noexcept { return a.mVal <  b.mVal; }
    friend bool operator> (const MPint& a, const MPint& b) noexcept { return a.mVal >  b.mVal; }
    friend bool operator<=(const MPint& a, const MPint& b) noexcept { return a.mVal <= b.mVal; }
    friend bool operator>=(const MPint& a, const MPint& b) noexcept { return a.mVal >= b.mVal; }

    // --- stream I/O ---------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const MPint& v);
    friend std::istream& operator>>(std::istream& is,       MPint& v);

private:
    signed long int mVal;
};

// Stream definitions live in MPint.cpp to avoid pulling <iostream> into every
// translation unit that includes this header.
