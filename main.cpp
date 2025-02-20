#include "include/BigDecimal.h"
#include <iostream>
using namespace ephir::bigdecimal;
using std::string_view_literals::operator ""sv;

int main() {
    const auto actual = BigDecimal::create("3");
    actual.print_binary();
}
