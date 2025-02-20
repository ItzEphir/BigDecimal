//
// Created by ephir on 29.01.2025.
//

#include "../include/BigDecimal.h"

#include <iostream>

using namespace ephir::bigdecimal;

#pragma region Constructors / Destructors

BigDecimal BigDecimal::create(const std::string_view& value) {
    if (StringHelper::containsNotDigit(value)) {
        throw std::invalid_argument("Invalid Decimal String");
    }
    auto result = BigDecimal();
    auto start_pos = 0;
    if (value[0] == '-') {
        result.is_negative = true;
        start_pos = 1;
    }
    auto rev_value = std::string(value.substr(start_pos));
    while (!rev_value.empty()) {
        uint8_t carry = 0;
        if (const auto first = rev_value[0] - '0'; first / 2 == 0
        ) {
            rev_value.erase(rev_value.begin());
            carry = first % 2;
        }
        for (auto& c : rev_value) {
            const auto num = c - '0' + carry * 10;
            c = static_cast<char>('0' + num / 2);
            carry = num % 2;
        }
        result.value.push_back(carry);
    }
    std::reverse(result.value.begin(), result.value.end());
    for (auto c : result.value) {
        std::cout << c;
    }
    std::cout << std::endl;
    result.optimize_end();
    return result;
}

BigDecimal::BigDecimal(const size_t size): value(size) {
    value[0] = false;
}

BigDecimal::BigDecimal(int8_t value) {
    if (value < 0) {
        this->is_negative = true;
        value = static_cast<int8_t>(-value);
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
        value = static_cast<int16_t>(-value);
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

BigDecimal& BigDecimal::operator=(const int8_t value) {
    return *this = BigDecimal(value);
}

BigDecimal& BigDecimal::operator=(const uint8_t value) {
    return *this = BigDecimal(value);
}

BigDecimal& BigDecimal::operator=(const int16_t value) {
    return *this = BigDecimal(value);
}

BigDecimal& BigDecimal::operator=(const uint16_t value) {
    return *this = BigDecimal(value);
}

BigDecimal& BigDecimal::operator=(const int32_t value) {
    return *this = BigDecimal(value);
}

BigDecimal& BigDecimal::operator=(const uint32_t value) {
    return *this = BigDecimal(value);
}

BigDecimal& BigDecimal::operator=(const int64_t value) {
    return *this = BigDecimal(value);
}

BigDecimal& BigDecimal::operator=(const uint64_t value) {
    return *this = BigDecimal(value);
}

#pragma endregion assignment operators

std::string BigDecimal::to_bin_string() const {
    std::string result;
    if (this->is_negative) {
        result += '-';
    }
    for (auto i : this->value) {
        result += std::to_string(i);
    }
    return result;
}

std::ostream& BigDecimal::binary_encode(std::ostream& out, const BigDecimal& obj) {
    if (obj.is_negative) {
        out << "-";
    }
    for (auto i : obj.value) {
        out << i;
    }
    return out;
}

void BigDecimal::print_binary() const {
    binary_encode(std::cout, *this);
}

bool BigDecimal::operator==(const BigDecimal& other) const {
    if (this->is_negative != other.is_negative) {
        return false;
    }
    if (this->exponent != other.exponent) {
        return false;
    }
    return this->value == other.value;
}

void BigDecimal::optimize_end() {
    size_t add_exponent = 0;
    while (value[value.size() - add_exponent - 1] == false) {
        add_exponent++;
    }
    if (add_exponent == 0) return;
    exponent += add_exponent;
    value.erase(value.end() - static_cast<long>(add_exponent), value.end());
}


size_t BigDecimal::fast_log2(size_t n) {
    static const int lookup[64] = {
        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
    };

    if (n == 0) return 0;

    size_t log = 0;
    if (n >= static_cast<size_t>(1) << 32) {
        n >>= 32;
        log += 32;
    }
    if (n >= static_cast<size_t>(1) << 16) {
        n >>= 16;
        log += 16;
    }
    if (n >= static_cast<size_t>(1) << 8) {
        n >>= 8;
        log += 8;
    }
    if (n >= static_cast<size_t>(1) << 4) {
        n >>= 4;
        log += 4;
    }
    log += lookup[n - 1];
    return log;
}
