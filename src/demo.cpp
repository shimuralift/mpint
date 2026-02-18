#include "MPint.hpp"

#include <cassert>
#include <iostream>

int main() {
    // --- construction from literals -----------------------------------------
    MPint a = 6;
    MPint b = 4;
    MPint c;          // default: 0

    // --- arithmetic ---------------------------------------------------------
    std::cout << "a        = " << a       << "\n";   // 6
    std::cout << "b        = " << b       << "\n";   // 4
    std::cout << "a + b    = " << a + b   << "\n";   // 10
    std::cout << "a - b    = " << a - b   << "\n";   // 2
    std::cout << "a * b    = " << a * b   << "\n";   // 24
    std::cout << "a / b    = " << a / b   << "\n";   // 1
    std::cout << "a % b    = " << a % b   << "\n";   // 2

    // --- unary --------------------------------------------------------------
    std::cout << "-a       = " << -a      << "\n";   // -6
    std::cout << "~b       = " << ~b      << "\n";   // -5

    // --- compound assignment ------------------------------------------------
    c = a;
    c += b;
    std::cout << "c=a; c+=b => " << c << "\n";       // 10

    // --- increment / decrement ----------------------------------------------
    MPint n = 0;
    std::cout << "n++      = " << n++ << "\n";       // 0
    std::cout << "n (after)= " << n   << "\n";       // 1
    std::cout << "++n      = " << ++n << "\n";       // 2

    // --- comparison ---------------------------------------------------------
    assert(a > b);
    assert(b < a);
    assert(a != b);
    assert(a == MPint(6));

    // --- bitwise ------------------------------------------------------------
    MPint x = 0b1010;
    MPint y = 0b1100;
    std::cout << "x & y    = " << (x & y) << "\n";  // 8  (0b1000)
    std::cout << "x | y    = " << (x | y) << "\n";  // 14 (0b1110)
    std::cout << "x ^ y    = " << (x ^ y) << "\n";  // 6  (0b0110)
    std::cout << "x << 1   = " << (x << 1) << "\n"; // 20
    std::cout << "y >> 1   = " << (y >> 1) << "\n"; // 6

    // --- mixed with plain int literals (implicit construction) --------------
    MPint r = a * 3 + 1;
    std::cout << "a*3+1    = " << r << "\n";         // 19

    // --- bool context -------------------------------------------------------
    if (a) std::cout << "a is nonzero (ok)\n";
    MPint zero = 0;
    if (!zero) std::cout << "zero is zero (ok)\n";

    std::cout << "all checks passed.\n";
    return 0;
}
