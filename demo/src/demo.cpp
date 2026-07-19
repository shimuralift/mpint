#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <streambuf>
#include <string>

#include "det.hpp"
#include "exprTest.hpp"
#include "redu.hpp"


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

  const int PROF_RUNS = 100000;
  uint64_t total[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint64_t t0, t1;

  NullBuf nullbuf;
  std::streambuf* orig = prof ? std::cout.rdbuf(&nullbuf) : nullptr;

  std::cout << "MPint: elementary operator expressions" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); expr();        t1 = rdtsc_read(); total[0] += t1 - t0; }

  std::cout << "MPint: my elementary operator expressions" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); basicexpr();   t1 = rdtsc_read(); total[1] += t1 - t0; }

  std::cout << std::endl << "MPint: more operator expressions" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); moreexpr();    t1 = rdtsc_read(); total[2] += t1 - t0; }

  std::cout << std::endl << "MPint: extra operator expressions" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); extraexpr();   t1 = rdtsc_read(); total[3] += t1 - t0; }

  std::cout << std::endl << "MPint: string constructor tests" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); strconstr();   t1 = rdtsc_read(); total[4] += t1 - t0; }

  std::cout << std::endl << "MPint: float/double conversion tests" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); floatconv();    t1 = rdtsc_read(); total[5] += t1 - t0; }

  std::cout << std::endl << "MPint: missing coverage tests" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); missingexpr();  t1 = rdtsc_read(); total[6] += t1 - t0; }

  std::cout << std::endl << "MPint: input safety tests" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); injTest();      t1 = rdtsc_read(); total[7] += t1 - t0; }

  std::cout << std::endl << "MPint: operator optimisation tests" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); operatorOpt();  t1 = rdtsc_read(); total[8] += t1 - t0; }

  std::cout << std::endl << "MPint: determinant example" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); detTest();     t1 = rdtsc_read(); total[9] += t1 - t0; }

  std::cout << std::endl << "MPint: integral lattice example" << std::endl << std::endl;
  for (int r = 0; r < (prof ? PROF_RUNS : 1); ++r)
    { t0 = rdtsc_read(); reduTest();     t1 = rdtsc_read(); total[10] += t1 - t0; }

  if (prof) {
    std::cout.rdbuf(orig);
    static const char* const names[11] = {
      "expr", "basicexpr", "moreexpr", "extraexpr", "strconstr", "floatconv", "missingexpr", "injTest", "operatorOpt", "detTest", "reduTest"
    };
    std::string formatted[11];
    std::string::size_type maxcycles = 0, maxname = 0;
    for (int i = 0; i < 11; ++i) {
      formatted[i] = format_cycles(total[i] / PROF_RUNS);
      if (formatted[i].size() > maxcycles) maxcycles = formatted[i].size();
      if (std::strlen(names[i]) > maxname) maxname = std::strlen(names[i]);
    }
    std::cout << "=== profiling report (rdtsc cpu cycles, avg of " << PROF_RUNS << " runs) ===" << std::endl;
    for (int i = 0; i < 11; ++i) {
      std::cout << "  " << std::setw(static_cast<int>(maxname)) << std::left  << names[i]
                << ": " << std::setw(static_cast<int>(maxcycles)) << std::right << formatted[i]
                << " cycles" << std::endl;
    }
  }

  return 0;
}
