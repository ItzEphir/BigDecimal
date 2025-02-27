//
// Created by ephir on 29.01.2025.
//

#include "../include/BigDecimal.h"
#include "../include/Maths.h"
#include "../include/StringHelper.h"

#include <iostream>

using namespace ephir::bigdecimal;

BigDecimal BigDecimal::ZERO = create("0");

#pragma region Constructors / Destructors

BigDecimal BigDecimal::create(const std::string_view& value) {
    if (StringHelper::containsNotDigit(value)) {
        throw std::invalid_argument("Invalid Decimal String");
    }
    BigDecimal result;
    if (value == "0" || value == "-0") {
        result.value = {false};
        result.capacity = 0;
        return result;
    }
    result.value.clear();
    const auto val = std::string(value);
    const auto parts = StringHelper::split(val, '.');
    const auto partBefore = parts[0];
    const auto partAfter = parts.size() > 1 ? parts[1] : "";
    result.process_integer(partBefore);
    result.process_fractional(partAfter);
    result.optimize_start();
    result.optimize_exponent();
    if (value[0] == '-') {
        result.is_negative = true;
        result.reverse_value();
        result.value[result.value.size() - 1] = true;
        result.optimize_end();
    }
    return result;
}

BigDecimal::BigDecimal(const size_t size): value(size) {
    value[0] = false;
}

BigDecimal::BigDecimal(int8_t value) {
    this->value.clear();
    if (value < 0) {
        this->is_negative = true;
        value = static_cast<int8_t>(-value);
    }
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
    optimize_number();
}

BigDecimal::BigDecimal(uint8_t value) {
    this->value.clear();
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
    optimize_number();
}

BigDecimal::BigDecimal(int16_t value) {
    this->value.clear();
    if (value < 0) {
        this->is_negative = true;
        value = static_cast<int16_t>(-value);
    }
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
    optimize_number();
}

BigDecimal::BigDecimal(uint16_t value) {
    this->value.clear();
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
    optimize_number();
}

BigDecimal::BigDecimal(int32_t value) {
    this->value.clear();
    if (value < 0) {
        this->is_negative = true;
        value = -value;
    }
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
    optimize_number();
}

BigDecimal::BigDecimal(uint32_t value) {
    this->value.clear();
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
    optimize_number();
}

BigDecimal::BigDecimal(int64_t value) {
    this->value.clear();
    if (value < 0) {
        this->is_negative = true;
        value = -value;
    }
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
    optimize_number();
}

BigDecimal::BigDecimal(uint64_t value) {
    this->value.clear();
    while (value > 0) {
        this->value.push_back(value % 2);
        value /= 2;
    }
    std::reverse(this->value.begin(), this->value.end());
    optimize_number();
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

static bool containsOnlyZeros(const std::vector<bool>& value) {
    return !std::any_of(value.begin(), value.end(), [](const bool x) { return x; });
}

void BigDecimal::optimize_number() {
    this->optimize_start();
    this->optimize_exponent();
    if (is_negative) {
        this->reverse_value();
        this->value[this->value.size() - 1] = true;
        this->optimize_end();
    }
    if (this->value.empty()) {
        this->value = {false};
    }
}

void BigDecimal::optimize_start() {
    if (value.empty()) return;
    if (containsOnlyZeros(value) && is_negative == false) {
        value = {false};
        exponent = 0;
        capacity = 0;
        return;
    }

    size_t to_delete;
    for (to_delete = 0; value[to_delete] == is_negative; to_delete++) {}
    if (to_delete == 0) return;
    value.erase(value.begin(), value.begin() + static_cast<long>(to_delete));
    if (value.empty()) {
        value = {false};
    }
}

void BigDecimal::optimize_exponent() {
    size_t add_exponent = 0;
    if (value.empty()) return;
    if (containsOnlyZeros(value)) {
        value = {false};
        exponent = 0;
        capacity = 0;
        return;
    }
    while (value[value.size() - add_exponent - 1] == false) {
        add_exponent++;
    }
    if (add_exponent == 0) return;
    exponent += static_cast<int64_t>(add_exponent);
    value.erase(value.end() - static_cast<long>(add_exponent), value.end());
    if (value.empty()) {
        value = {false};
    }
}

void BigDecimal::optimize_end() {
    size_t add_capacity = 0;
    if (value.empty()) return;
    if (containsOnlyZeros(value)) {
        value = {false};
        exponent = 0;
        capacity = 0;
        return;
    }
    while (value[value.size() - add_capacity - 1] == is_negative) {
        add_capacity++;
    }
    if (add_capacity == 0) return;
    capacity += static_cast<int64_t>(add_capacity);
    value.erase(value.end() - static_cast<long>(add_capacity), value.end());
}

void BigDecimal::process_integer(const std::string_view& str) {
    if (str.empty()) return;
    auto start_pos = 0;
    if (str[0] == '-') {
        start_pos = 1;
    }
    auto rev_value = std::string(str.substr(start_pos));
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
        value.push_back(carry);
    }
    std::reverse(this->value.begin(), this->value.end());
}

static void mult2(std::string& str) {
    int64_t carry = 0;
    for (int64_t i = static_cast<int64_t>(str.size()) - 1; i >= 0; i--) {
        const auto num = str[i] - '0';
        const auto result = num * 2 + carry;
        carry = result / 10;
        str[i] = static_cast<char>('0' + result % 10);
    }
}

void BigDecimal::process_fractional(const std::string_view& str) {
    if (str.empty()) return;
    const size_t size = str.size() * maths::fast_log2(10) + 1;
    auto dec_value = std::string(str);
    exponent = -static_cast<int64_t>(size);
    capacity = exponent;
    for (auto i = 0; i < size; i++) {
        auto to_add = dec_value[0] - '0' >= 5;
        mult2(dec_value);
        this->value.push_back(to_add);
    }
}

void BigDecimal::reverse_value() {
    for (auto&& i : value) {
        i = !i;
    }
}
