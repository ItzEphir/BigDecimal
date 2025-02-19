//
// Created by ephir on 18.02.2025.
//

#include "../include/StringHelper.h"

using namespace ephir::bigdecimal;

bool StringHelper::containsOnlyDigit(const std::string_view& str) {
    auto start = 0;
    if (str.empty()) {
        return true;
    }
    if (str[0] == '-') {
        start = 1;
    }
    bool found_point = false;
    for (auto i = start; i < str.size(); i++) {
        if (!std::isdigit(str[i])) {
            if (str[i] == '.' && !found_point) {
                found_point = true;
                continue;
            }
            return false;
        }
    }
    return true;
}

bool StringHelper::containsNotDigit(const std::string_view& str) {
    return !containsOnlyDigit(str);
}
