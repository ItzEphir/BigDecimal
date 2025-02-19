//
// Created by ephir on 18.02.2025.
//

#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <string>

namespace ephir::bigdecimal {

    struct StringHelper {
        static bool containsOnlyDigit(const std::string_view &);
        static bool containsNotDigit(const std::string_view &);
    };

}

#endif //STRINGHELPER_H
