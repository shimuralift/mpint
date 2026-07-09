#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

// MPint wrapping signed long int directly — no pimpl, all operators inline.

class MPint {
    signed long int mVal;

    static signed long int parse_str(const char* const s) {
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
        unsigned long int result = 0;
        bool got_digit = false;
        for (; *p; ++p) {
            if (*p == '\'') continue;
            unsigned int digit;
            const char c = *p;
            if      (c >= '0' && c <= '9') digit = static_cast<unsigned int>(c - '0');
            else if (c >= 'a' && c <= 'f') digit = static_cast<unsigned int>(c - 'a') + 10u;
            else if (c >= 'A' && c <= 'F') digit = static_cast<unsigned int>(c - 'A') + 10u;
            else throw std::invalid_argument(std::string("MPint: invalid integer string: ") + s);
            if (digit >= static_cast<unsigned int>(base))
                throw std::invalid_argument(std::string("MPint: invalid integer string: ") + s);
            result = result * static_cast<unsigned long int>(base) + digit;
            got_digit = true;
        }
        if (!got_digit)
            throw std::invalid_argument(std::string("MPint: invalid integer string: ") + s);
        return negative ? -static_cast<signed long int>(result)
                        :  static_cast<signed long int>(result);
    }

public:
    // --- construction -------------------------------------------------------
    MPint()                    noexcept : mVal(0) {}
    MPint(signed long int   v) noexcept : mVal(v) {}
    MPint(signed int        v) noexcept : mVal(v) {}
    MPint(signed short      v) noexcept : mVal(v) {}
    MPint(signed char       v) noexcept : mVal(v) {}
    MPint(unsigned long int v) noexcept : mVal(static_cast<signed long int>(v)) {}
    MPint(unsigned int      v) noexcept : mVal(static_cast<signed long int>(v)) {}
    MPint(unsigned short    v) noexcept : mVal(static_cast<signed long int>(v)) {}
    MPint(unsigned char     v) noexcept : mVal(static_cast<signed long int>(v)) {}
    MPint(long long         v) noexcept : mVal(static_cast<signed long int>(v)) {}
    explicit MPint(const char*        s) : mVal(parse_str(s)) {}
    explicit MPint(const std::string& s) : mVal(parse_str(s.c_str())) {}

    // Copy / move / destroy — trivial for a scalar member
    MPint(const MPint&)            noexcept = default;
    MPint& operator=(const MPint&) noexcept = default;
    MPint(MPint&&)                 noexcept = default;
    MPint& operator=(MPint&&)      noexcept = default;
    ~MPint()                                = default;

    // --- conversion out -----------------------------------------------------
    [[nodiscard]] explicit operator signed long int()   const noexcept { return mVal; }
    [[nodiscard]] explicit operator signed int()        const noexcept { return static_cast<int>(mVal); }
    [[nodiscard]] explicit operator signed short()      const noexcept { return static_cast<short>(mVal); }
    [[nodiscard]] explicit operator signed char()       const noexcept { return static_cast<signed char>(mVal); }
    [[nodiscard]] explicit operator unsigned long int() const noexcept { return static_cast<unsigned long int>(mVal); }
    [[nodiscard]] explicit operator unsigned int()      const noexcept { return static_cast<unsigned int>(mVal); }
    [[nodiscard]] explicit operator bool()              const noexcept { return mVal != 0; }
    [[nodiscard]] explicit operator float() const {
        const float f = static_cast<float>(mVal);
        if (std::isinf(f)) throw std::overflow_error("MPint->float overflow");
        return f;
    }
    [[nodiscard]] explicit operator double() const {
        const double d = static_cast<double>(mVal);
        if (std::isinf(d)) throw std::overflow_error("MPint->double overflow");
        return d;
    }
    [[nodiscard]] explicit operator long double() const noexcept { return static_cast<long double>(mVal); }

    // --- unary arithmetic ---------------------------------------------------
    [[nodiscard]] MPint operator+() const noexcept { return *this; }
    [[nodiscard]] MPint operator-() const noexcept { return MPint(-mVal); }

    // --- unary logical ------------------------------------------------------
    [[nodiscard]] bool  operator!() const noexcept { return mVal == 0; }

    // --- unary bitwise ------------------------------------------------------
    [[nodiscard]] MPint operator~() const noexcept { return MPint(~mVal); }

    // --- prefix increment / decrement ---------------------------------------
    MPint& operator++() noexcept { ++mVal; return *this; }
    MPint& operator--() noexcept { --mVal; return *this; }

    // --- postfix increment / decrement --------------------------------------
    MPint operator++(int) noexcept { MPint tmp(*this); ++mVal; return tmp; }
    MPint operator--(int) noexcept { MPint tmp(*this); --mVal; return tmp; }

    // --- compound assignment: arithmetic ------------------------------------
    MPint& operator+=(const MPint& rhs) noexcept { mVal += rhs.mVal; return *this; }
    MPint& operator-=(const MPint& rhs) noexcept { mVal -= rhs.mVal; return *this; }
    MPint& operator*=(const MPint& rhs) noexcept { mVal *= rhs.mVal; return *this; }
    MPint& operator/=(const MPint& rhs)           { mVal /= rhs.mVal; return *this; }
    MPint& operator%=(const MPint& rhs)           { mVal %= rhs.mVal; return *this; }

    // --- compound assignment: bitwise ---------------------------------------
    MPint& operator&=(const MPint& rhs) noexcept { mVal &= rhs.mVal; return *this; }
    MPint& operator|=(const MPint& rhs) noexcept { mVal |= rhs.mVal; return *this; }
    MPint& operator^=(const MPint& rhs) noexcept { mVal ^= rhs.mVal; return *this; }

    // --- compound assignment: shift -----------------------------------------
    MPint& operator<<=(int n)            noexcept { mVal <<= n;        return *this; }
    MPint& operator>>=(int n)            noexcept { mVal >>= n;        return *this; }
    MPint& operator<<=(const MPint& rhs) noexcept { mVal <<= rhs.mVal; return *this; }
    MPint& operator>>=(const MPint& rhs) noexcept { mVal >>= rhs.mVal; return *this; }

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
    [[nodiscard]] friend bool operator==(const MPint& a, const MPint& b) noexcept { return a.mVal == b.mVal; }
    [[nodiscard]] friend bool operator!=(const MPint& a, const MPint& b) noexcept { return a.mVal != b.mVal; }
    [[nodiscard]] friend bool operator< (const MPint& a, const MPint& b) noexcept { return a.mVal <  b.mVal; }
    [[nodiscard]] friend bool operator> (const MPint& a, const MPint& b) noexcept { return a.mVal >  b.mVal; }
    [[nodiscard]] friend bool operator<=(const MPint& a, const MPint& b) noexcept { return a.mVal <= b.mVal; }
    [[nodiscard]] friend bool operator>=(const MPint& a, const MPint& b) noexcept { return a.mVal >= b.mVal; }

    // --- stream I/O ---------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const MPint& v) {
        return os << v.mVal;
    }
    friend std::istream& operator>>(std::istream& is, MPint& v) {
        std::string s;
        if (is >> s) {
            try        { v.mVal = parse_str(s.c_str()); }
            catch(const std::invalid_argument&) { is.setstate(std::ios::failbit); }
        }
        return is;
    }
};
