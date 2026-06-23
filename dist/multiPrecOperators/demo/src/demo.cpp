#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <streambuf>
#include <string>

#include "exprTest.hpp"


int main() {

  std::cout << "################ MPint: elementary operator expressions ################" << std::endl;
  expr();
  std::cout << std::endl << std::endl << std::endl << "################ MPint: more elementary operator expressions ################" << std::endl;
  basicexpr();
  std::cout << std::endl << std::endl << std::endl << "################ MPint: more operator expressions ################" << std::endl;
  moreexpr();
  std::cout << std::endl << std::endl << std::endl << "################ MPint: extra operator expressions ################" << std::endl;
  extraexpr();
  std::cout << std::endl << std::endl << std::endl << "################ MPint: string constructor tests ################" << std::endl;
  strconstr();
  std::cout << std::endl << std::endl << std::endl << "################ MPint: float/double conversion tests ################" << std::endl;
  floatconv();
  std::cout << std::endl << std::endl << std::endl << "################ MPint: missing coverage tests ################" << std::endl;
  missingexpr();

  return 0;
}
