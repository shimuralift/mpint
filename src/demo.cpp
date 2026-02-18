#include "MPint.hpp"

#include <cassert>
#include <iostream>

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
  const unsigned short int  c_u_s_i = -22;
  const unsigned long  int  c_u_l_i = -23;
                       int nc_____i = 31;
                 short int nc___s_i = 32;
                 long  int nc___l_i = -33;
        unsigned       int nc_u___i = -41;
        unsigned short int nc_u_s_i = 42;
        unsigned long  int nc_u_l_i = 43;

  const MPint cMP_________;
  const MPint cMP__c______ = MPint(1);
  const MPint cMP__c_____i = MPint( c_____i);
  const MPint cMP__c___s_i = MPint( c___s_i);
  const MPint cMP__c___l_i = MPint( c___l_i);
  const MPint cMP__c_u___i = MPint( c_u___i);
  const MPint cMP__c_u_s_i = MPint( c_u_s_i);
  const MPint cMP__c_u_l_i = MPint( c_u_l_i);
  const MPint cMP_nc_____i = MPint(nc_____i);
  const MPint cMP_nc___s_i = MPint(nc___s_i);
  const MPint cMP_nc___l_i = MPint(nc___l_i);
  const MPint cMP_nc_u___i = MPint(nc_u___i);
  const MPint cMP_nc_u_s_i = MPint(nc_u_s_i);
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
  MPint ncMP_nc___s_i = MPint(nc___s_i);
  MPint ncMP_nc___l_i = MPint(nc___l_i);
  MPint ncMP_nc_u___i = MPint(nc_u___i);
  MPint ncMP_nc_u_s_i = MPint(nc_u_s_i);
  MPint ncMP_nc_u_l_i = MPint(nc_u_l_i);


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

int main() {
  std::cout << "MPint: claude's elementary operator expressions" << std::endl << std::endl;
  claude_main();
  std::cout << "MPint: my elementary operator expressions" << std::endl << std::endl;
  basicexpr();
  return 0;
}
