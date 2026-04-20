#pragma once

#include <cstring>
#include <string>
#include <gmpxx.h>

// MPint is a thin subclass of mpz_class that adds the few pieces missing from
// the gmpxx.h "drop-in replacement" claim:
//   • explicit narrowing conversion operators (mpz_class has none)
//   • right-shift using floor division (mpz_class uses truncating)
//   • shift-by-MPint operators (mpz_class only shifts by unsigned long)
//   • unambiguous long long constructor
//   • string constructor with 0b/0B prefix and single-quote separator support

class MPint : public mpz_class {
public:
    // --- construction -------------------------------------------------------
    MPint()                          : mpz_class()                     {}
    MPint(int            v)          : mpz_class(v)                    {}
    MPint(long           v)          : mpz_class(v)                    {}
    MPint(long long      v)          : mpz_class(static_cast<long>(v)) {}
    MPint(short          v)          : mpz_class(static_cast<int>(v))  {}
    MPint(signed char    v)          : mpz_class(static_cast<int>(v))  {}
    MPint(unsigned int   v)          : mpz_class(static_cast<long>(v)) {}
    MPint(unsigned long  v)          : mpz_class(static_cast<long>(v)) {}
    MPint(unsigned short v)          : mpz_class(static_cast<int>(static_cast<unsigned short>(v))) {}
    MPint(unsigned char  v)          : mpz_class(static_cast<int>(static_cast<unsigned char>(v)))  {}
    MPint(double         v)          : mpz_class(v)                    {}
    MPint(const mpz_class& v)        : mpz_class(v)                    {}
    MPint(mpz_class&&    v) noexcept : mpz_class(std::move(v))         {}
    MPint(const MPint&   v)          : mpz_class(v)                    {}
    MPint(MPint&&        v) noexcept : mpz_class(std::move(v))         {}

    using mpz_class::operator=;
    MPint& operator=(const MPint& v)    { mpz_class::operator=(v);                            return *this; }
    MPint& operator=(MPint&& v) noexcept{ mpz_class::operator=(std::move(v));                  return *this; }
    // Treat unsigned assignments as signed (matching MPintGMP constructor behaviour):
    MPint& operator=(unsigned long  v)  { mpz_class::operator=(static_cast<long>(v));          return *this; }
    MPint& operator=(unsigned int   v)  { mpz_class::operator=(static_cast<long>(v));          return *this; }
    MPint& operator=(unsigned short v)  { mpz_class::operator=(static_cast<long>(v));          return *this; }
    MPint& operator=(unsigned char  v)  { mpz_class::operator=(static_cast<long>(v));          return *this; }

    // Accept results of GMP expression templates (e.g. a*3+1) which return
    // __gmp_expr<T,U> rather than mpz_class or MPint directly.
    template<class T, class U>
    MPint(const __gmp_expr<T, U>& v) : mpz_class(v) {}

    explicit MPint(const char* s) noexcept : mpz_class() {
        const char* p = s;
        bool neg = (*p == '-'); if (neg || *p == '+') ++p;
        int base = 0; // 0 = GMP auto-detects 0x/octal; we handle 0b ourselves
        if (p[0] == '0' && (p[1] == 'b' || p[1] == 'B')) { base = 2; p += 2; }
        std::string clean; clean.reserve(std::strlen(p) + 1u);
        if (neg) clean += '-';
        for (; *p; ++p) if (*p != '\'') clean += *p;
        set_str(clean.c_str(), base);
    }
    explicit MPint(const std::string& s) noexcept : MPint(s.c_str()) {}

    // --- explicit conversion operators missing from mpz_class ---------------
    explicit operator signed long int()   const noexcept { return get_si(); }
    explicit operator signed int()        const noexcept { return static_cast<int>(get_si()); }
    explicit operator signed short()      const noexcept { return static_cast<short>(get_si()); }
    explicit operator signed char()       const noexcept { return static_cast<signed char>(get_si()); }
    explicit operator unsigned long int() const noexcept { return get_ui(); }
    explicit operator unsigned int()      const noexcept { return static_cast<unsigned int>(get_ui()); }
    explicit operator bool()              const noexcept { return mpz_sgn(get_mpz_t()) != 0; }
    explicit operator float()             const noexcept { return static_cast<float>(get_d()); }
    explicit operator double()            const noexcept { return get_d(); }
    explicit operator long double()       const noexcept { return static_cast<long double>(get_d()); }

    // --- right shift: floor division; mpz_class uses truncating -------------
    MPint& operator>>=(mp_bitcnt_t n) noexcept {
        mpz_fdiv_q_2exp(get_mpz_t(), get_mpz_t(), n);
        return *this;
    }
    MPint& operator>>=(const MPint& rhs) noexcept { return *this >>= rhs.get_ui(); }

    // --- shift by MPint: mpz_class only shifts by unsigned long -------------
    MPint& operator<<=(const MPint& rhs) noexcept {
        mpz_class::operator<<=(rhs.get_ui());
        return *this;
    }

    friend MPint operator>>(MPint lhs, mp_bitcnt_t n)    noexcept { return lhs >>= n; }
    friend MPint operator>>(MPint lhs, int n)            noexcept { return lhs >>= static_cast<mp_bitcnt_t>(n); }
    friend MPint operator>>(MPint lhs, const MPint& rhs) noexcept { return lhs >>= rhs; }
    friend MPint operator<<(MPint lhs, int n)            noexcept { return lhs <<= static_cast<mp_bitcnt_t>(n); }
    friend MPint operator<<(MPint lhs, const MPint& rhs) noexcept { return lhs <<= rhs; }
};
