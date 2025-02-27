#include "include/BigDecimal.h"
#include <iostream>
using namespace ephir::bigdecimal;
using std::string_view_literals::operator ""sv;

int main() {
    std::cout << std::hex << -12.25;
}