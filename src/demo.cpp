#include "MPint.hpp"
#include "det.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <streambuf>
#include <string>

int claude_main() {
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

int basicexpr() {
  const                int  c_____i = -11;
  const          short int  c___s_i = -12;
  const          long  int  c___l_i = 13;
  const unsigned       int  c_u___i = 21;
  const unsigned short int  c_u_s_i = static_cast<unsigned short>(-22);
  const unsigned long  int  c_u_l_i = static_cast<unsigned long>(-23);
                       int nc_____i = 31;
                 short int nc___s_i = 32;
                 long  int nc___l_i = -33;
        unsigned       int nc_u___i = static_cast<unsigned int>(-41);
        unsigned short int nc_u_s_i = 42;
        unsigned long  int nc_u_l_i = 43;

  const MPint cMP_________;
  const MPint cMP__c______ = MPint(1);
  const MPint cMP__c_____i = MPint( c_____i);  (void)cMP__c_____i;
  const MPint cMP__c___s_i = MPint( c___s_i);
  const MPint cMP__c___l_i = MPint( c___l_i);  (void)cMP__c___l_i;
  const MPint cMP__c_u___i = MPint( c_u___i);
  const MPint cMP__c_u_s_i = MPint( c_u_s_i);
  const MPint cMP__c_u_l_i = MPint( c_u_l_i);
  const MPint cMP_nc_____i = MPint(nc_____i);  (void)cMP_nc_____i;
  const MPint cMP_nc___s_i = MPint(nc___s_i);
  const MPint cMP_nc___l_i = MPint(nc___l_i);  (void)cMP_nc___l_i;
  const MPint cMP_nc_u___i = MPint(nc_u___i);
  const MPint cMP_nc_u_s_i = MPint(nc_u_s_i);  (void)cMP_nc_u_s_i;
  const MPint cMP_nc_u_l_i = MPint(nc_u_l_i);
  MPint ncMP_________;
  MPint ncMP__c______ = MPint(1);
  MPint ncMP__c_____i = MPint( c_____i);
  MPint ncMP__c___s_i = MPint( c___s_i);
  MPint ncMP__c___l_i = MPint( c___l_i);
  MPint ncMP__c_u___i = MPint( c_u___i);
  MPint ncMP__c_u_s_i = MPint( c_u_s_i);
  MPint ncMP__c_u_l_i = MPint( c_u_l_i);
  MPint ncMP_nc_____i = MPint(nc_____i);
  MPint ncMP_nc___s_i = MPint(nc___s_i);  (void)ncMP_nc___s_i;
  MPint ncMP_nc___l_i = MPint(nc___l_i);
  MPint ncMP_nc_u___i = MPint(nc_u___i);
  MPint ncMP_nc_u_s_i = MPint(nc_u_s_i);
  MPint ncMP_nc_u_l_i = MPint(nc_u_l_i);  (void)ncMP_nc_u_l_i;


  const MPint cMPnul = MPint();
  const MPint cMPsix = 6;
  const MPint cMPelf = 11;
  const MPint cMP733 = MPint(-733);

  std::cout << "    +() const :: " << cMP_________ << "::" <<  +cMP_________   << std::endl;
  std::cout << "    -() const :: " << cMP__c______ << "::" <<  -cMP__c______   << std::endl;
  std::cout << "2nc +() const :: " << ncMP_________ << "::" <<  +ncMP_________   << std::endl;
  std::cout << "2nc -() const :: " << ncMP__c______ << "::" <<  -ncMP__c______   << std::endl;
  std::cout << "!() const :: " << cMP__c_u_s_i << "::" <<  !cMP__c_u_s_i   << std::endl;
  std::cout << "~() const :: " << cMP__c_u_l_i << "::" <<  ~cMP__c_u_l_i   << std::endl;
  
  std::cout << "+()       :: " << ncMP_________ << "::" <<  +ncMP_________   << std::endl;
  std::cout << "-()       :: " << ncMP__c______ << "::" <<  -ncMP__c______   << std::endl;
  std::cout << "++()      :: " << ncMP__c_____i << "::" << ++ncMP__c_____i   << "::" << ncMP__c_____i << std::endl;
  std::cout << "++(int)   :: " << ncMP__c___s_i << "::" <<   ncMP__c___s_i++ << "::" << ncMP__c___s_i << std::endl;
  std::cout << "--()      :: " << ncMP__c___l_i << "::" << --ncMP__c___l_i   << "::" << ncMP__c___l_i << std::endl;
  std::cout << "--(int)   :: " << ncMP__c_u___i << "::" <<   ncMP__c_u___i-- << "::" << ncMP__c_u___i << std::endl;
  std::cout << "!()       :: " << ncMP__c_u_s_i << "::" <<  !ncMP__c_u_s_i   << std::endl;
  std::cout << "~()       :: " << ncMP__c_u_l_i << "::" <<  ~ncMP__c_u_l_i   << std::endl;
  std::cout << std::endl;

  std::cout << "=(MPint&, MPint) :: " << ncMP__c_u_l_i << " = " << cMP733 << " :: " << (ncMP__c_u_l_i = cMP733) << " :: " << ncMP__c_u_l_i << std::endl;
  std::cout << std::endl;

  std::cout << " +=(MPint&)  :: " << ncMP__c_____i << " +=  " << cMPsix << " :: " << (ncMP__c_____i +=  cMPsix) << " :: " << ncMP__c_____i << std::endl;
  std::cout << "  +(MPint&)  :: " <<  cMP__c___s_i << "  +  " << cMPsix << " :: " << ( cMP__c___s_i  +  cMPsix) << " :: " <<  cMP__c___s_i << std::endl;
  std::cout << " -=(MPint&)  :: " << ncMP__c___l_i << " -=  " << cMPsix << " :: " << (ncMP__c___l_i -=  cMPsix) << " :: " << ncMP__c___l_i << std::endl;
  std::cout << "  -(MPint&)  :: " <<  cMP__c_u___i << "  -  " << cMPsix << " :: " << ( cMP__c_u___i  -  cMPsix) << " :: " <<  cMP__c_u___i << std::endl;
  std::cout << " *=(MPint&)  :: " << ncMP__c_u_s_i << " *=  " << cMPsix << " :: " << (ncMP__c_u_s_i *=  cMPsix) << " :: " << ncMP__c_u_s_i << std::endl;
  std::cout << "  *(MPint&)  :: " <<  cMP__c_u_l_i << "  *  " << cMPsix << " :: " << ( cMP__c_u_l_i  *  cMPsix) << " :: " <<  cMP__c_u_l_i << std::endl;
  std::cout << " /=(MPint&)  :: " << ncMP_nc_____i << " /=  " << cMPsix << " :: " << (ncMP_nc_____i /=  cMPsix) << " :: " << ncMP_nc_____i << std::endl;
  std::cout << "  /(MPint&)  :: " <<  cMP_nc___s_i << "  /  " << cMPsix << " :: " << ( cMP_nc___s_i  /  cMPsix) << " :: " <<  cMP_nc___s_i << std::endl;
  std::cout << " %=(MPint&)  :: " << ncMP_nc___l_i << " %=  " << cMPsix << " :: " << (ncMP_nc___l_i %=  cMPsix) << " :: " << ncMP_nc___l_i << std::endl;
  std::cout << "  %(MPint&)  :: " <<  cMP_nc_u___i << "  %  " << cMPsix << " :: " << ( cMP_nc_u___i  %  cMPsix) << " :: " <<  cMP_nc_u___i << std::endl;
  std::cout << " &=(MPint&)  :: " << ncMP_nc_u_s_i << " &=  " << cMPelf << " :: " << (ncMP_nc_u_s_i &=  cMPelf) << " :: " << ncMP_nc_u_s_i << std::endl;
  std::cout << "  &(MPint&)  :: " <<  cMP_nc_u_l_i << "  &  " << cMPelf << " :: " << ( cMP_nc_u_l_i  &  cMPelf) << " :: " <<  cMP_nc_u_l_i << std::endl;
  std::cout << " |=(MPint&)  :: " << ncMP__c___l_i << " |=  " << cMPelf << " :: " << (ncMP__c___l_i |=  cMPelf) << " :: " << ncMP__c___l_i << std::endl;
  std::cout << "  |(MPint&)  :: " <<  cMP__c_u___i << "  |  " << cMPelf << " :: " << ( cMP__c_u___i  |  cMPelf) << " :: " <<  cMP__c_u___i << std::endl;
  std::cout << " ^=(MPint&)  :: " << ncMP__c_u_s_i << " ^=  " << cMPelf << " :: " << (ncMP__c_u_s_i ^=  cMPelf) << " :: " << ncMP__c_u_s_i << std::endl;
  std::cout << "  ^(MPint&)  :: " <<  cMP__c_u_l_i << "  ^  " << cMPelf << " :: " << ( cMP__c_u_l_i  ^  cMPelf) << " :: " <<  cMP__c_u_l_i << std::endl;
  std::cout << "<<=(MPint&)  :: " << ncMP_nc_____i << " <<= " << cMPelf << " :: " << (ncMP_nc_____i <<= cMPelf) << " :: " << ncMP_nc_____i << std::endl;
  std::cout << " <<(MPint&)  :: " <<  cMP_nc___s_i << " <<  " << cMPelf << " :: " << ( cMP_nc___s_i <<  cMPelf) << " :: " <<  cMP_nc___s_i << std::endl;
  std::cout << ">>=(MPint&)  :: " << ncMP_nc___l_i << " >>= " << cMPelf << " :: " << (ncMP_nc___l_i >>= cMPelf) << " :: " << ncMP_nc___l_i << std::endl;
  std::cout << " >>(MPint&)  :: " <<  cMP_nc_u___i << " >>  " << cMPelf << " :: " << ( cMP_nc_u___i >>  cMPelf) << " :: " <<  cMP_nc_u___i << std::endl;
  std::cout << std::endl;


  std::cout << "==(MPint&, MPint&   )  :: "  << ncMP_nc___l_i << " == " << cMPelf        << " :: " << (ncMP_nc___l_i == cMPelf        ) << std::endl;
  std::cout << "==(MPint&, int      )  :: "  << ncMP_nc___l_i << " == " << c_____i       << " :: " << (ncMP_nc___l_i == c_____i       ) << std::endl;
  std::cout << "==(MPint&, short int)  :: "  << ncMP_nc___l_i << " == " << c___s_i       << " :: " << (ncMP_nc___l_i == c___s_i       ) << std::endl;
  std::cout << "==(MPint&, long int )  :: "  << ncMP_nc___l_i << " == " << c___l_i       << " :: " << (ncMP_nc___l_i == c___l_i       ) << std::endl;
  std::cout << "==(int,       MPint&)  :: "  << c_____i << " == " << ncMP_nc___l_i       << " :: " << (c_____i == ncMP_nc___l_i       ) << std::endl;
  std::cout << "==(short int, MPint&)  :: "  << c___s_i << " == " << ncMP_nc___l_i       << " :: " << (c___s_i == ncMP_nc___l_i       ) << std::endl;
  std::cout << "==(long int,  MPint&)  :: "  << c___l_i << " == " << ncMP_nc___l_i       << " :: " << (c___l_i == ncMP_nc___l_i       ) << std::endl;

  std::cout << "!=(MPint&, MPint&   )  :: "  << ncMP_nc_u___i << " != " << cMPelf        << " :: " << (ncMP_nc_u___i != cMPelf        ) << std::endl;
  std::cout << "!=(MPint&, int      )  :: "  << ncMP_nc_u___i << " != " << c_____i       << " :: " << (ncMP_nc_u___i != c_____i       ) << std::endl;
  std::cout << "!=(MPint&, short int)  :: "  << ncMP_nc_u___i << " != " << c___s_i       << " :: " << (ncMP_nc_u___i != c___s_i       ) << std::endl;
  std::cout << "!=(MPint&, long int )  :: "  << ncMP_nc_u___i << " != " << c___l_i       << " :: " << (ncMP_nc_u___i != c___l_i       ) << std::endl;
  std::cout << "!=(int,       MPint&)  :: "  << c_____i << " != " << ncMP_nc_u___i       << " :: " << (c_____i != ncMP_nc_u___i       ) << std::endl;
  std::cout << "!=(short int, MPint&)  :: "  << c___s_i << " != " << ncMP_nc_u___i       << " :: " << (c___s_i != ncMP_nc_u___i       ) << std::endl;
  std::cout << "!=(long int,  MPint&)  :: "  << c___l_i << " != " << ncMP_nc_u___i       << " :: " << (c___l_i != ncMP_nc_u___i       ) << std::endl;

  std::cout << " <(MPint&, MPint&   )  :: "  << ncMP_nc___l_i << " <  " << cMPnul        << " :: " << (ncMP_nc___l_i  <  cMPnul       ) << std::endl;
  std::cout << " <(MPint&, int      )  :: "  << ncMP_nc___l_i << " <  " << c_____i       << " :: " << (ncMP_nc___l_i  <  c_____i      ) << std::endl;
  std::cout << " <(MPint&, short int)  :: "  << ncMP_nc___l_i << " <  " << c___s_i       << " :: " << (ncMP_nc___l_i  <  c___s_i      ) << std::endl;
  std::cout << " <(MPint&, long int )  :: "  << ncMP_nc___l_i << " <  " << c___l_i       << " :: " << (ncMP_nc___l_i  <  c___l_i      ) << std::endl;
  std::cout << " <(int,       MPint&)  :: "  << c_____i << " <  " << ncMP_nc___l_i       << " :: " << (c_____i  <  ncMP_nc___l_i      ) << std::endl;
  std::cout << " <(short int, MPint&)  :: "  << c___s_i << " <  " << ncMP_nc___l_i       << " :: " << (c___s_i  <  ncMP_nc___l_i      ) << std::endl;
  std::cout << " <(long int,  MPint&)  :: "  << c___l_i << " <  " << ncMP_nc___l_i       << " :: " << (c___l_i  <  ncMP_nc___l_i      ) << std::endl;

  std::cout << " >(MPint&, MPint&   )  :: "  << ncMP_nc_u___i << " >  " << cMPnul        << " :: " << (ncMP_nc_u___i  >  cMPnul       ) << std::endl;
  std::cout << " >(MPint&, int      )  :: "  << ncMP_nc_u___i << " >  " << c_____i       << " :: " << (ncMP_nc_u___i  >  c_____i      ) << std::endl;
  std::cout << " >(MPint&, short int)  :: "  << ncMP_nc_u___i << " >  " << c___s_i       << " :: " << (ncMP_nc_u___i  >  c___s_i      ) << std::endl;
  std::cout << " >(MPint&, long int )  :: "  << ncMP_nc_u___i << " >  " << c___l_i       << " :: " << (ncMP_nc_u___i  >  c___l_i      ) << std::endl;
  std::cout << " >(int,       MPint&)  :: "  << c_____i << " >  " << ncMP_nc_u___i       << " :: " << (c_____i  >  ncMP_nc_u___i      ) << std::endl;
  std::cout << " >(short int, MPint&)  :: "  << c___s_i << " >  " << ncMP_nc_u___i       << " :: " << (c___s_i  >  ncMP_nc_u___i      ) << std::endl;
  std::cout << " >(long int,  MPint&)  :: "  << c___l_i << " >  " << ncMP_nc_u___i       << " :: " << (c___l_i  >  ncMP_nc_u___i      ) << std::endl;

  std::cout << "<=(MPint&, MPint&   )  :: "  << cMPelf        << " <= " << ncMP_nc___l_i << " :: " << (cMPelf         <= ncMP_nc___l_i) << std::endl;
  std::cout << "<=(MPint&, int      )  :: "  << cMPelf        << " <= " << c_____i       << " :: " << (cMPelf         <= c_____i      ) << std::endl;
  std::cout << "<=(MPint&, short int)  :: "  << cMPelf        << " <= " << c___s_i       << " :: " << (cMPelf         <= c___s_i      ) << std::endl;
  std::cout << "<=(MPint&, long int )  :: "  << cMPelf        << " <= " << c___l_i       << " :: " << (cMPelf         <= c___l_i      ) << std::endl;
  std::cout << "<=(int,       MPint&)  :: "  << c_____i        << " <= " << cMPelf       << " :: " << (c_____i         <= cMPelf      ) << std::endl;
  std::cout << "<=(short int, MPint&)  :: "  << c___s_i        << " <= " << cMPelf       << " :: " << (c___s_i         <= cMPelf      ) << std::endl;
  std::cout << "<=(long int,  MPint&)  :: "  << c___l_i        << " <= " << cMPelf       << " :: " << (c___l_i         <= cMPelf      ) << std::endl;

  std::cout << ">=(MPint&, MPint&   )  :: "  << cMPelf        << " >= " << ncMP_nc_u___i << " :: " << (cMPelf         >= ncMP_nc_u___i) << std::endl;
  std::cout << ">=(MPint&, int      )  :: "  << cMPelf        << " >= " << c_____i       << " :: " << (cMPelf         >= c_____i      ) << std::endl;
  std::cout << ">=(MPint&, short int)  :: "  << cMPelf        << " >= " << c___s_i       << " :: " << (cMPelf         >= c___s_i      ) << std::endl;
  std::cout << ">=(MPint&, long int )  :: "  << cMPelf        << " >= " << c___l_i       << " :: " << (cMPelf         >= c___l_i      ) << std::endl;
  std::cout << ">=(int,       MPint&)  :: "  << c_____i        << " >= " << cMPelf       << " :: " << (c_____i         >= cMPelf      ) << std::endl;
  std::cout << ">=(short int, MPint&)  :: "  << c___s_i        << " >= " << cMPelf       << " :: " << (c___s_i         >= cMPelf      ) << std::endl;
  std::cout << ">=(long int,  MPint&)  :: "  << c___l_i        << " >= " << cMPelf       << " :: " << (c___l_i         >= cMPelf      ) << std::endl;

  return 0;
}

int moreexpr() {
  std::cout << "--- copy construction & assignment from int ---" << std::endl;
  MPint orig = 42;
  MPint copy(orig);
  MPint assigned;
  assigned = orig;
  std::cout << "orig     = " << orig     << std::endl;  // 42
  std::cout << "copy     = " << copy     << std::endl;  // 42
  std::cout << "assigned = " << assigned << std::endl;  // 42

  std::cout << std::endl << "--- assign from plain int types ---" << std::endl;
  MPint m;
  m = 100;
  std::cout << "m = 100  :: " << m << std::endl;        // 100
  m = static_cast<short>(7);
  std::cout << "m = (short)7 :: " << m << std::endl;    // 7
  m = 99L;
  std::cout << "m = 99L  :: " << m << std::endl;        // 99

  std::cout << std::endl << "--- long long construction ---" << std::endl;
  long long big = 1234567890LL;
  MPint fromLL(big);
  std::cout << "from long long :: " << fromLL << std::endl;  // 1234567890

  std::cout << std::endl << "--- explicit conversion operators ---" << std::endl;
  MPint v = 257;
  std::cout << "v                         = " << v << std::endl;
  std::cout << "static_cast<long>(v)      = " << static_cast<long>(v)           << std::endl;  // 257
  std::cout << "static_cast<int>(v)       = " << static_cast<int>(v)            << std::endl;  // 257
  std::cout << "static_cast<short>(v)     = " << static_cast<short>(v)          << std::endl;  // 257
  std::cout << "static_cast<signed char>  = " << static_cast<int>(static_cast<signed char>(v))  << std::endl;  // 1 (truncated)
  std::cout << "static_cast<unsigned long>= " << static_cast<unsigned long>(v)  << std::endl;  // 257
  std::cout << "static_cast<unsigned int> = " << static_cast<unsigned int>(v)   << std::endl;  // 257
  std::cout << "static_cast<bool>(v)      = " << static_cast<bool>(v)           << std::endl;  // 1
  std::cout << "static_cast<bool>(MPint())= " << static_cast<bool>(MPint())     << std::endl;  // 0

  std::cout << std::endl << "--- int on left side (implicit MPint construction) ---" << std::endl;
  MPint rhs = 5;
  std::cout << "10 + MPint(5) = " << (10 + rhs)  << std::endl;  // 15
  std::cout << "10 - MPint(5) = " << (10 - rhs)  << std::endl;  // 5
  std::cout << "10 * MPint(5) = " << (10 * rhs)  << std::endl;  // 50
  std::cout << "10 / MPint(5) = " << (10 / rhs)  << std::endl;  // 2
  std::cout << "10 % MPint(5) = " << (10 % rhs)  << std::endl;  // 0
  std::cout << "12 & MPint(5) = " << (12 & rhs)  << std::endl;  // 4
  std::cout << "12 | MPint(5) = " << (12 | rhs)  << std::endl;  // 13
  std::cout << "12 ^ MPint(5) = " << (12 ^ rhs)  << std::endl;  // 9

  std::cout << std::endl << "--- chained expressions ---" << std::endl;
  MPint a = 2, b = 3, c = 4;
  std::cout << "2 + 3 + 4     = " << (a + b + c)     << std::endl;  // 9
  std::cout << "2 * 3 + 4     = " << (a * b + c)     << std::endl;  // 10
  std::cout << "2 + 3 * 4     = " << (a + b * c)     << std::endl;  // 14
  std::cout << "(2+3) * 4     = " << ((a + b) * c)   << std::endl;  // 20
  std::cout << "2 * 3 * 4     = " << (a * b * c)     << std::endl;  // 24
  MPint chain = 1;
  chain += 2;
  chain *= 3;
  chain -= 1;
  std::cout << "((1+2)*3)-1   = " << chain << std::endl;  // 8

  std::cout << std::endl << "--- comparison edge cases ---" << std::endl;
  MPint z1 = 0, z2 = 0;
  std::cout << "0 == 0 :: " << (z1 == z2) << std::endl;  // 1
  std::cout << "0 != 0 :: " << (z1 != z2) << std::endl;  // 0
  std::cout << "0 <  0 :: " << (z1 <  z2) << std::endl;  // 0
  std::cout << "0 <= 0 :: " << (z1 <= z2) << std::endl;  // 1
  std::cout << "0 >  0 :: " << (z1 >  z2) << std::endl;  // 0
  std::cout << "0 >= 0 :: " << (z1 >= z2) << std::endl;  // 1
  MPint neg = -1, pos = 1;
  std::cout << "-1 < 1  :: " << (neg < pos)  << std::endl;  // 1
  std::cout << "-1 > 1  :: " << (neg > pos)  << std::endl;  // 0
  std::cout << "-1 == 1 :: " << (neg == pos) << std::endl;  // 0
  std::cout << "-1 != 1 :: " << (neg != pos) << std::endl;  // 1

  std::cout << std::endl << "--- bool / logical contexts ---" << std::endl;
  MPint t = 1, f = 0;
  std::cout << "bool(1)  = " << (t ? "true" : "false") << std::endl;   // true
  std::cout << "bool(0)  = " << (f ? "true" : "false") << std::endl;   // false
  std::cout << "!1       = " << !t << std::endl;  // 0
  std::cout << "!0       = " << !f << std::endl;  // 1
  std::cout << "!!42     = " << !!MPint(42) << std::endl;  // 1

  std::cout << std::endl << "--- negation and double negation ---" << std::endl;
  MPint p = 77;
  std::cout << "-77      = " << -p      << std::endl;   // -77
  std::cout << "-(-77)   = " << -(-p)   << std::endl;   // 77
  std::cout << "~~77     = " << ~~p     << std::endl;   // 77
  std::cout << "+(-77)   = " << +(-p)   << std::endl;   // -77

  std::cout << std::endl << "--- self-operations ---" << std::endl;
  MPint s = 10;
  std::cout << "s + s    = " << (s + s) << std::endl;  // 20
  std::cout << "s - s    = " << (s - s) << std::endl;  // 0
  std::cout << "s * s    = " << (s * s) << std::endl;  // 100
  std::cout << "s / s    = " << (s / s) << std::endl;  // 1
  std::cout << "s % s    = " << (s % s) << std::endl;  // 0
  s += s;
  std::cout << "s += s (10) :: " << s   << std::endl;  // 20

  return 0;
}

int extraexpr() {
  std::cout << "--- construction from signed/unsigned char ---" << std::endl;
  signed char   sc = -5;
  unsigned char uc = 200;
  MPint fromSC(sc);
  MPint fromUC(uc);
  std::cout << "from signed char(-5)    = " << fromSC << std::endl;   // -5
  std::cout << "from unsigned char(200) = " << fromUC << std::endl;   // 200

  std::cout << std::endl << "--- compound assignment with plain ints ---" << std::endl;
  MPint m = 100;
  m += 10;
  std::cout << "100 += 10  :: " << m << std::endl;   // 110
  m -= 20;
  std::cout << "110 -= 20  :: " << m << std::endl;   // 90
  m *= 3;
  std::cout << "90  *= 3   :: " << m << std::endl;   // 270
  m /= 9;
  std::cout << "270 /= 9   :: " << m << std::endl;   // 30
  m %= 7;
  std::cout << "30  %= 7   :: " << m << std::endl;   // 2
  m = 0xFF;
  m &= 0x0F;
  std::cout << "0xFF &= 0x0F :: " << m << std::endl; // 15
  m |= 0xF0;
  std::cout << "15   |= 0xF0 :: " << m << std::endl; // 255
  m ^= 0xAA;
  std::cout << "255  ^= 0xAA :: " << m << std::endl; // 85
  m = 1;
  m <<= 8;
  std::cout << "1  <<= 8   :: " << m << std::endl;   // 256
  m >>= 4;
  std::cout << "256 >>= 4  :: " << m << std::endl;   // 16

  std::cout << std::endl << "--- arithmetic identities ---" << std::endl;
  MPint x = 42;
  assert(x + 0 == x);       std::cout << "x + 0 == x      ok" << std::endl;
  assert(x - 0 == x);       std::cout << "x - 0 == x      ok" << std::endl;
  assert(x * 1 == x);       std::cout << "x * 1 == x      ok" << std::endl;
  assert(x / 1 == x);       std::cout << "x / 1 == x      ok" << std::endl;
  assert(x * 0 == MPint(0)); std::cout << "x * 0 == 0      ok" << std::endl;
  assert(x - x == MPint(0)); std::cout << "x - x == 0      ok" << std::endl;
  assert(x / x == MPint(1)); std::cout << "x / x == 1      ok" << std::endl;
  assert(x % x == MPint(0)); std::cout << "x %% x == 0     ok" << std::endl;

  std::cout << std::endl << "--- commutativity ---" << std::endl;
  MPint a = 7, b = 13;
  assert(a + b == b + a);   std::cout << "a + b == b + a   ok" << std::endl;
  assert(a * b == b * a);   std::cout << "a * b == b * a   ok" << std::endl;
  assert((a & b) == (b & a)); std::cout << "a & b == b & a   ok" << std::endl;
  assert((a | b) == (b | a)); std::cout << "a | b == b | a   ok" << std::endl;
  assert((a ^ b) == (b ^ a)); std::cout << "a ^ b == b ^ a   ok" << std::endl;

  std::cout << std::endl << "--- associativity ---" << std::endl;
  MPint c = 5;
  assert((a + b) + c == a + (b + c)); std::cout << "(a+b)+c == a+(b+c)  ok" << std::endl;
  assert((a * b) * c == a * (b * c)); std::cout << "(a*b)*c == a*(b*c)  ok" << std::endl;

  std::cout << std::endl << "--- distributivity ---" << std::endl;
  assert(a * (b + c) == a * b + a * c); std::cout << "a*(b+c) == a*b+a*c  ok" << std::endl;
  assert(a * (b - c) == a * b - a * c); std::cout << "a*(b-c) == a*b-a*c  ok" << std::endl;

  std::cout << std::endl << "--- negative arithmetic ---" << std::endl;
  MPint n1 = -10, n2 = -3;
  std::cout << "-10 + -3   = " << (n1 + n2) << std::endl;   // -13
  std::cout << "-10 - -3   = " << (n1 - n2) << std::endl;   // -7
  std::cout << "-10 * -3   = " << (n1 * n2) << std::endl;   // 30
  std::cout << "-10 / -3   = " << (n1 / n2) << std::endl;   // 3
  std::cout << "-10 % -3   = " << (n1 % n2) << std::endl;   // -1
  std::cout << "-10 / 3    = " << (n1 / MPint(3)) << std::endl;   // -3
  std::cout << "-10 % 3    = " << (n1 % MPint(3)) << std::endl;   // -1
  std::cout << "10 / -3    = " << (MPint(10) / n2) << std::endl;  // -3
  std::cout << "10 % -3    = " << (MPint(10) % n2) << std::endl;  // 1

  std::cout << std::endl << "--- MPint in a loop ---" << std::endl;
  MPint sum = 0;
  for (MPint i = 1; i <= 10; ++i) {
    sum += i;
  }
  std::cout << "sum(1..10) = " << sum << std::endl;  // 55
  assert(sum == MPint(55));

  MPint factorial = 1;
  for (MPint i = 2; i <= 10; ++i) {
    factorial *= i;
  }
  std::cout << "10!        = " << factorial << std::endl;  // 3628800
  assert(factorial == MPint(3628800));

  std::cout << std::endl << "--- MPint as array index (explicit cast) ---" << std::endl;
  int arr[] = {10, 20, 30, 40, 50};
  MPint idx = 3;
  std::cout << "arr[MPint(3)] = " << arr[static_cast<int>(idx)] << std::endl;  // 40

  std::cout << std::endl << "--- bitwise shift patterns ---" << std::endl;
  MPint one = 1;
  std::cout << "1 << 0  = " << (one << 0) << std::endl;   // 1
  std::cout << "1 << 1  = " << (one << 1) << std::endl;   // 2
  std::cout << "1 << 4  = " << (one << 4) << std::endl;   // 16
  std::cout << "1 << 10 = " << (one << 10) << std::endl;  // 1024
  MPint big = 1024;
  std::cout << "1024 >> 10 = " << (big >> 10) << std::endl;  // 1
  std::cout << "1024 >> 5  = " << (big >> 5) << std::endl;   // 32
  assert((one << 10) == big);
  std::cout << "(1<<10) == 1024  ok" << std::endl;

  std::cout << std::endl << "--- bitwise identity properties ---" << std::endl;
  MPint val = 0xABCD;
  assert((val & val) == val);        std::cout << "x & x == x       ok" << std::endl;
  assert((val | val) == val);        std::cout << "x | x == x       ok" << std::endl;
  assert((val ^ val) == MPint(0));   std::cout << "x ^ x == 0       ok" << std::endl;
  assert((val & MPint(0)) == MPint(0)); std::cout << "x & 0 == 0       ok" << std::endl;
  assert((val | MPint(0)) == val);     std::cout << "x | 0 == x       ok" << std::endl;
  assert((val ^ MPint(0)) == val);     std::cout << "x ^ 0 == x       ok" << std::endl;

  std::cout << std::endl << "--- swap via XOR ---" << std::endl;
  MPint sa = 123, sb = 456;
  std::cout << "before: sa=" << sa << " sb=" << sb << std::endl;
  sa ^= sb;
  sb ^= sa;
  sa ^= sb;
  std::cout << "after:  sa=" << sa << " sb=" << sb << std::endl;
  assert(sa == MPint(456));
  assert(sb == MPint(123));

  std::cout << std::endl << "--- compound assignment chaining ---" << std::endl;
  MPint ch = 2;
  (ch += 3) *= 4;
  std::cout << "(2 += 3) *= 4  = " << ch << std::endl;  // 20
  (ch -= 5) /= 3;
  std::cout << "(20 -= 5) /= 3 = " << ch << std::endl;  // 5

  std::cout << std::endl << "--- comparison with implicit construction ---" << std::endl;
  MPint v = 42;
  assert(v == 42);     std::cout << "MPint(42) == 42     ok" << std::endl;
  assert(42 == v);     std::cout << "42 == MPint(42)     ok" << std::endl;
  assert(v != 99);     std::cout << "MPint(42) != 99     ok" << std::endl;
  assert(v < 100);     std::cout << "MPint(42) < 100     ok" << std::endl;
  assert(v > 0);       std::cout << "MPint(42) > 0       ok" << std::endl;
  assert(v <= 42);     std::cout << "MPint(42) <= 42     ok" << std::endl;
  assert(v >= 42);     std::cout << "MPint(42) >= 42     ok" << std::endl;
  assert(0 < v);       std::cout << "0 < MPint(42)       ok" << std::endl;
  assert(100 > v);     std::cout << "100 > MPint(42)     ok" << std::endl;

  std::cout << std::endl << "--- GCD (Euclidean algorithm) ---" << std::endl;
  MPint ga = 48, gb = 18;
  MPint ta = ga, tb = gb;
  while (tb != 0) {
    MPint tmp = tb;
    tb = ta % tb;
    ta = tmp;
  }
  std::cout << "gcd(48, 18) = " << ta << std::endl;  // 6
  assert(ta == MPint(6));

  std::cout << std::endl << "--- power by repeated squaring ---" << std::endl;
  MPint base = 3, exp = 7, result = 1;
  MPint b2 = base;
  MPint e2 = exp;
  while (e2 > 0) {
    if (e2 % 2 != 0)
      result *= b2;
    b2 *= b2;
    e2 /= 2;
  }
  std::cout << "3^7 = " << result << std::endl;  // 2187
  assert(result == MPint(2187));

  return 0;
}

static std::string format_cycles(uint64_t n) {
    std::string s = std::to_string(n);
    for (int pos = static_cast<int>(s.size()) - 3; pos > 0; pos -= 3)
        s.insert(static_cast<std::string::size_type>(pos), 1, ' ');
    return s;
}

struct NullBuf : std::streambuf {
    int overflow(int c) override { return c; }
};

static inline uint64_t rdtsc_read() {
#if defined(__x86_64__) || defined(__i386__)
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return (static_cast<uint64_t>(hi) << 32) | lo;
#else
    return 0;
#endif
}

int main(int argc, char* argv[]) {
  bool prof = false;
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "-prof") == 0) { prof = true; break; }
  }

  uint64_t ts[5], te[5];

  NullBuf nullbuf;
  std::streambuf* orig = prof ? std::cout.rdbuf(&nullbuf) : nullptr;

  std::cout << "MPint: claude's elementary operator expressions" << std::endl << std::endl;
  ts[0] = rdtsc_read(); claude_main();  te[0] = rdtsc_read();
  std::cout << "MPint: my elementary operator expressions" << std::endl << std::endl;
  ts[1] = rdtsc_read(); basicexpr();    te[1] = rdtsc_read();
  std::cout << std::endl << "MPint: more operator expressions" << std::endl << std::endl;
  ts[2] = rdtsc_read(); moreexpr();     te[2] = rdtsc_read();
  std::cout << std::endl << "MPint: extra operator expressions" << std::endl << std::endl;
  ts[3] = rdtsc_read(); extraexpr();    te[3] = rdtsc_read();
  std::cout << std::endl << "MPint: determinant example" << std::endl << std::endl;
  ts[4] = rdtsc_read(); detTest();      te[4] = rdtsc_read();

  if (prof) {
    std::cout.rdbuf(orig);
    static const char* const names[5] = {
      "claude_main", "basicexpr", "moreexpr", "extraexpr", "detTest"
    };
    std::string formatted[5];
    std::string::size_type maxlen = 0;
    for (int i = 0; i < 5; ++i) {
      formatted[i] = format_cycles(te[i] - ts[i]);
      if (formatted[i].size() > maxlen) maxlen = formatted[i].size();
    }
    std::cout << "=== profiling report (rdtsc cpu cycles) ===" << std::endl;
    for (int i = 0; i < 5; ++i) {
      std::cout << "  " << names[i] << ": "
                << std::setw(static_cast<int>(maxlen)) << std::right << formatted[i]
                << " cycles" << std::endl;
    }
  }

  return 0;
}
