#include "include/BigDecimal.h"
#include <iostream>
using namespace ephir::bigdecimal;

int main() {
    auto b = BigDecimal(static_cast<uint32_t>(12));
    std::cout << b << std::endl;
}
