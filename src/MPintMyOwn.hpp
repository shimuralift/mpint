#pragma once

#include <iosfwd>

// MPint: a drop-in replacement for signed long int.
// All arithmetic, comparison, bitwise, increment/decrement, and stream
// operators are provided so legacy code needs no textual changes.
// The private Impl handle will later be swapped out for a GMP/PARI/...
// multi-precision type without touching any call sites or this header.

class MPint {
public:
    // --- construction -------------------------------------------------------
    MPint() noexcept;

    // Accept any built-in integral type without narrowing warnings.
    MPint(signed long int   v) noexcept;
    MPint(signed int        v) noexcept;
    MPint(signed short      v) noexcept;
    MPint(signed char       v) noexcept;
    MPint(unsigned long int v) noexcept;
    MPint(unsigned int      v) noexcept;
    MPint(unsigned short    v) noexcept;
    MPint(unsigned char     v) noexcept;
    MPint(long long         v) noexcept;

    // Copy / move / destroy
    MPint(const MPint&)            noexcept;
    MPint& operator=(const MPint&) noexcept;
    MPint(MPint&&)                 noexcept;
    MPint& operator=(MPint&&)      noexcept;
    ~MPint();

    // --- conversion out -----------------------------------------------------
    // Integral: explicit, to prevent silent narrowing.
    explicit operator signed long int()   const noexcept;
    explicit operator signed int()        const noexcept;
    explicit operator signed short()      const noexcept;
    explicit operator signed char()       const noexcept;
    explicit operator unsigned long int() const noexcept;
    explicit operator unsigned int()      const noexcept;
    explicit operator bool()              const noexcept;

    // Floating-point: explicit too — implicit operators cause overload
    // ambiguity when MPint is mixed with integral literals (e.g. a*3).
    explicit operator float()             const noexcept;
    explicit operator double()            const noexcept;
    explicit operator long double()       const noexcept;

    // --- unary arithmetic ---------------------------------------------------
    MPint  operator+()         const noexcept;
    MPint  operator-()         const noexcept;

    // --- unary logical ------------------------------------------------------
    bool   operator!()         const noexcept;

    // --- unary bitwise ------------------------------------------------------
    MPint  operator~()         const noexcept;

    // --- prefix increment / decrement ---------------------------------------
    MPint& operator++()    noexcept;
    MPint& operator--()    noexcept;

    // --- postfix increment / decrement --------------------------------------
    MPint  operator++(int) noexcept;
    MPint  operator--(int) noexcept;

    // --- compound assignment: arithmetic ------------------------------------
    MPint& operator+=(const MPint& rhs) noexcept;
    MPint& operator-=(const MPint& rhs) noexcept;
    MPint& operator*=(const MPint& rhs) noexcept;
    MPint& operator/=(const MPint& rhs);
    MPint& operator%=(const MPint& rhs);

    // --- compound assignment: bitwise ---------------------------------------
    MPint& operator&=(const MPint& rhs) noexcept;
    MPint& operator|=(const MPint& rhs) noexcept;
    MPint& operator^=(const MPint& rhs) noexcept;

    // --- compound assignment: shift -----------------------------------------
    MPint& operator<<=(int n)            noexcept;
    MPint& operator>>=(int n)            noexcept;
    MPint& operator<<=(const MPint& rhs) noexcept;
    MPint& operator>>=(const MPint& rhs) noexcept;

    // --- binary arithmetic (defined via compound assignment) ----------------
    friend MPint operator+(MPint lhs, const MPint& rhs) noexcept;
    friend MPint operator-(MPint lhs, const MPint& rhs) noexcept;
    friend MPint operator*(MPint lhs, const MPint& rhs) noexcept;
    friend MPint operator/(MPint lhs, const MPint& rhs);
    friend MPint operator%(MPint lhs, const MPint& rhs);

    // --- binary bitwise -----------------------------------------------------
    friend MPint operator&(MPint lhs, const MPint& rhs) noexcept;
    friend MPint operator|(MPint lhs, const MPint& rhs) noexcept;
    friend MPint operator^(MPint lhs, const MPint& rhs) noexcept;

    // --- shift --------------------------------------------------------------
    friend MPint operator<<(MPint lhs, int n)            noexcept;
    friend MPint operator>>(MPint lhs, int n)            noexcept;
    friend MPint operator<<(MPint lhs, const MPint& rhs) noexcept;
    friend MPint operator>>(MPint lhs, const MPint& rhs) noexcept;

    // --- comparison ---------------------------------------------------------
    friend bool operator==(const MPint& a, const MPint& b) noexcept;
    friend bool operator!=(const MPint& a, const MPint& b) noexcept;
    friend bool operator< (const MPint& a, const MPint& b) noexcept;
    friend bool operator> (const MPint& a, const MPint& b) noexcept;
    friend bool operator<=(const MPint& a, const MPint& b) noexcept;
    friend bool operator>=(const MPint& a, const MPint& b) noexcept;

    // --- stream I/O ---------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const MPint& v);
    friend std::istream& operator>>(std::istream& is,       MPint& v);

private:
    struct Impl;   // defined in MPint.cpp — no internals visible in this header
    Impl*  pImpl;
};
