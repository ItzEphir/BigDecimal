//
// Created by ephir on 18.02.2025.
//

#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <vector>

namespace ephir::bigdecimal {

    struct StringHelper {
        static bool containsOnlyDigit(const std::string_view &);
        static bool containsNotDigit(const std::string_view &);
        static std::vector<std::string_view> split(const std::string_view&, char);
    };

}

#endif //STRINGHELPER_H
