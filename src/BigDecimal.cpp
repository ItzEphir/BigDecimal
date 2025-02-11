//
// Created by Дмитрий Дворянников on 29.01.2025.
//

#include "../include/BigDecimal.h"

using namespace ephir::bigdecimal;

static bool ephir::bigdecimal::containsNotDigit(const std::string_view &value) {
    auto start = 0;
    if (value[0] == '-') {
        start = 1;
    }
    for (auto i = start; i < value.size(); i++) {
        if (!isdigit(value[i])) {
            return true;
        }
    }
    return false;
}

#pragma region Constructors / Destructors

BigDecimal BigDecimal::create(const std::string_view &value) {
    if (containsNotDigit(value)) {
        throw std::invalid_argument("Invalid Decimal String");
    }
    auto result = BigDecimal();
    auto start_pos = 0;
    if (value[0] == '-') {
        result.is_negative = true;
        start_pos = 1;
    }
    auto rev_value = std::string(value.substr(start_pos));
    while (rev_value.size() > 0) {
        uint8_t carry = 0;
        if (const auto first = rev_value[0] - '0'; first / 2 == 0) {
            rev_value.erase(rev_value.begin());
            carry = first % 2;
        }
        for (auto &c: rev_value) {
            const auto num = c - '0' + carry * 10;
            c = num / 2 + '0';
            carry = num % 2;
        }
        result.value.push_back(carry);
    }
    std::reverse(result.value.begin(), result.value.end());
    return result;
}

BigDecimal::BigDecimal(const size_t size): value(size) {
    value[0] = false;
}

BigDecimal::BigDecimal(int8_t value) {
    if (value < 0) {
        this->is_negative = true;
        value = -value;
    }
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
}

BigDecimal::BigDecimal(uint8_t value) {
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
}

BigDecimal::BigDecimal(int16_t value) {
    if (value < 0) {
        this->is_negative = true;
        value = -value;
    }
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
}

BigDecimal::BigDecimal(uint16_t value) {
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
}

BigDecimal::BigDecimal(int32_t value) {
    if (value < 0) {
        this->is_negative = true;
        value = -value;
    }
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
}

BigDecimal::BigDecimal(uint32_t value) {
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
}

BigDecimal::BigDecimal(int64_t value) {
    if (value < 0) {
        this->is_negative = true;
        value = -value;
    }
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
}

BigDecimal::BigDecimal(uint64_t value) {
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
}

#pragma endregion Constructors / Destructors

#pragma region assignment operators

BigDecimal &BigDecimal::operator=(const int8_t value) {
    return *this = BigDecimal(value);
}

BigDecimal &BigDecimal::operator=(const uint8_t value) {
    return *this = BigDecimal(value);
}

BigDecimal &BigDecimal::operator=(const int16_t value) {
    return *this = BigDecimal(value);
}

BigDecimal &BigDecimal::operator=(const uint16_t value) {
    return *this = BigDecimal(value);
}

BigDecimal &BigDecimal::operator=(const int32_t value) {
    return *this = BigDecimal(value);
}

BigDecimal &BigDecimal::operator=(const uint32_t value) {
    return *this = BigDecimal(value);
}

BigDecimal &BigDecimal::operator=(const int64_t value) {
    return *this = BigDecimal(value);
}

BigDecimal &BigDecimal::operator=(const uint64_t value) {
    return *this = BigDecimal(value);
}

#pragma endregion assignment operators
