#pragma once

#include <iosfwd>
#include <string>

// MPint: a drop-in replacement for signed long int.
// All arithmetic, comparison, bitwise, increment/decrement, and stream
// operators are provided so legacy code needs no textual changes.
// The private Impl handle will later be swapped out for a multi-precision type
// without touching any call sites or this header.

class MPint {
public:
    // --- construction -------------------------------------------------------
    MPint();

    // Accept any built-in integral type without narrowing warnings.
    MPint(signed long int   v);
    MPint(signed int        v);
    MPint(signed short      v);
    MPint(signed char       v);
    MPint(unsigned long int v);
    MPint(unsigned int      v);
    MPint(unsigned short    v);
    MPint(unsigned char     v);
    MPint(long long         v);

    // String literals: decimal, octal (0-prefix), hex (0x), binary (0b).
    // Single-quote digit separators are ignored.  No type suffixes.
    explicit MPint(const char*        s);
    explicit MPint(const std::string& s);

    // Copy / move / destroy
    MPint(const MPint&);
    MPint& operator=(const MPint&) noexcept;
    MPint(MPint&&)                 noexcept;
    MPint& operator=(MPint&&)      noexcept;
    ~MPint();

    // --- conversion out -----------------------------------------------------
    // Integral: explicit, to prevent silent narrowing.
    [[nodiscard]] explicit operator signed long int()   const noexcept;
    [[nodiscard]] explicit operator signed int()        const noexcept;
    [[nodiscard]] explicit operator signed short()      const noexcept;
    [[nodiscard]] explicit operator signed char()       const noexcept;
    [[nodiscard]] explicit operator unsigned long int() const noexcept;
    [[nodiscard]] explicit operator unsigned int()      const noexcept;
    [[nodiscard]] explicit operator bool()              const noexcept;

    // Floating-point: explicit too — implicit operators cause overload
    // ambiguity when MPint is mixed with integral literals (e.g. a*3).
    [[nodiscard]] explicit operator float()             const;   // throws std::overflow_error on ±inf
    [[nodiscard]] explicit operator double()            const;   // throws std::overflow_error on ±inf
    [[nodiscard]] explicit operator long double()       const noexcept;

    // --- unary arithmetic ---------------------------------------------------
    [[nodiscard]] MPint  operator+()         const noexcept;
    [[nodiscard]] MPint  operator-()         const noexcept;

    // --- unary logical ------------------------------------------------------
    [[nodiscard]] bool   operator!()         const noexcept;

    // --- unary bitwise ------------------------------------------------------
    [[nodiscard]] MPint  operator~()         const noexcept;

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

    // --- binary arithmetic (inline: backend-agnostic, delegate to +=) -------
    [[nodiscard]] friend MPint operator+(MPint lhs, const MPint& rhs) noexcept { return lhs += rhs; }
    [[nodiscard]] friend MPint operator-(MPint lhs, const MPint& rhs) noexcept { return lhs -= rhs; }
    [[nodiscard]] friend MPint operator*(MPint lhs, const MPint& rhs) noexcept { return lhs *= rhs; }
    [[nodiscard]] friend MPint operator/(MPint lhs, const MPint& rhs)           { return lhs /= rhs; }
    [[nodiscard]] friend MPint operator%(MPint lhs, const MPint& rhs)           { return lhs %= rhs; }

    // --- binary bitwise (inline: backend-agnostic) --------------------------
    [[nodiscard]] friend MPint operator&(MPint lhs, const MPint& rhs) noexcept { return lhs &= rhs; }
    [[nodiscard]] friend MPint operator|(MPint lhs, const MPint& rhs) noexcept { return lhs |= rhs; }
    [[nodiscard]] friend MPint operator^(MPint lhs, const MPint& rhs) noexcept { return lhs ^= rhs; }

    // --- shift (inline: backend-agnostic) -----------------------------------
    [[nodiscard]] friend MPint operator<<(MPint lhs, int n)            noexcept { return lhs <<= n; }
    [[nodiscard]] friend MPint operator>>(MPint lhs, int n)            noexcept { return lhs >>= n; }
    [[nodiscard]] friend MPint operator<<(MPint lhs, const MPint& rhs) noexcept { return lhs <<= rhs; }
    [[nodiscard]] friend MPint operator>>(MPint lhs, const MPint& rhs) noexcept { return lhs >>= rhs; }

    // --- comparison (backend-specific, defined in .cpp) ---------------------
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
    struct MPintImpl;   // defined in MPint.cpp — no internals visible in this header
    MPintImpl*  pImpl;
};

// Comparison operators are backend-specific (defined in .cpp), so [[nodiscard]]
// cannot be placed on the non-definition friend declarations inside the class.
// Redeclaring them here makes the attribute visible at every call site.
[[nodiscard]] bool operator==(const MPint& a, const MPint& b) noexcept;
[[nodiscard]] bool operator!=(const MPint& a, const MPint& b) noexcept;
[[nodiscard]] bool operator< (const MPint& a, const MPint& b) noexcept;
[[nodiscard]] bool operator> (const MPint& a, const MPint& b) noexcept;
[[nodiscard]] bool operator<=(const MPint& a, const MPint& b) noexcept;
[[nodiscard]] bool operator>=(const MPint& a, const MPint& b) noexcept;
