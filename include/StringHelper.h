//
// Created by ephir on 18.02.2025.
//

#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <vector>

namespace ephir::bigdecimal {

    struct StringHelper {
        static bool contains_only_digit(const std::string_view &);
        static bool contains_not_digit(const std::string_view &);
        static std::vector<std::string_view> split(const std::string_view&, char);
    };

}

#endif //STRINGHELPER_H
