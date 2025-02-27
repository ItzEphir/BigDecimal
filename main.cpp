#include "include/BigDecimal.h"
#include <iostream>
using namespace ephir::bigdecimal;
using std::string_view_literals::operator ""sv;

int main() {
    size_t a = 0u;
    int64_t b = -1;
    std::cout << (a < b);
}