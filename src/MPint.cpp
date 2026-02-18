#include "MPint.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const MPint& v) {
    return os << v.mVal;
}

std::istream& operator>>(std::istream& is, MPint& v) {
    return is >> v.mVal;
}
