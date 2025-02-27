//
// Created by ephir on 18.02.2025.
//

#include "../include/StringHelper.h"

#include <sstream>

using namespace ephir::bigdecimal;

bool StringHelper::contains_only_digit(const std::string_view& str) {
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

bool StringHelper::contains_not_digit(const std::string_view& str) {
    return !contains_only_digit(str);
}

std::vector<std::string_view> StringHelper::split(const std::string_view& str, char delimiter) {
    std::vector<std::string_view> result;
    size_t start = 0;
    size_t end;

    while ((end = str.find(delimiter, start)) != std::string_view::npos) {
        result.emplace_back(str.substr(start, end - start));
        start = end + 1;
    }

    // Add the last part
    result.emplace_back(str.substr(start));
    return result;
}
