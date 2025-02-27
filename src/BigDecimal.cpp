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
    if (StringHelper::contains_not_digit(value)) {
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
    const auto part_before = parts[0];
    const auto part_after = parts.size() > 1 ? parts[1] : "";
    result.process_integer(part_before);
    result.process_fractional(part_after);
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

// BigDecimal::BigDecimal(const size_t accuracy) {
//     value[0] = false;
//     capacity = accuracy;
//     exponent = -accuracy;
// }

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

#pragma region Assignment operators

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

#pragma endregion Assignment operators

#pragma region String output

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

#pragma endregion String output

#pragma region Operators

static bool get_at(const std::vector<bool>& data, const size_t at) {
    if (at >= data.size()) {
        return false;
    }
    return data[at];
}

static bool get_fractional(const std::vector<bool>& data, int64_t exp, size_t at) {
    if (data.size() + exp + at >= data.size()) {
        return false;
    }
    return data[data.size() + exp + at];
}

BigDecimal BigDecimal::operator+() const {
    return *this;
}

BigDecimal BigDecimal::operator-() const {
    BigDecimal result = *this;
    result.is_negative = !result.is_negative;
    result.reverse_value();
    result.value[result.value.size() - 1] = true;
    result.optimize_end();
    if (result.value.empty()) {
        result.value = {false};
    }
    return result;
}

int8_t BigDecimal::compare_positive(const BigDecimal& other) const {
    std::vector<bool> first_data = this->value;
    std::vector<bool> second_data = other.value;

    for (int64_t i = 0; i < this->capacity; i++) {
        first_data.push_back(false);
    }
    for (int64_t i = 0; i < other.capacity; i++) {
        second_data.push_back(false);
    }

    const int64_t integer1 = first_data.size() + this->exponent;

    if (const int64_t integer2 = second_data.size() + other.exponent; integer1 != integer2) {
        return integer1 > integer2 ? 1 : -1;
    }

    const int64_t integer = integer1;

    for (int64_t i = 0; i < integer; i++) {
        if (get_at(first_data, i) != get_at(second_data, i)) {
            return get_at(first_data, i) ? 1 : -1;
        }
    }

    const int64_t fractional1 = -this->exponent;
    const int64_t fractional2 = -other.exponent;

    if (fractional1 < 0 ^ fractional2 < 0) {
        return fractional1 < 0 ? -1 : 1;
    }

    const int64_t fractional = std::min(fractional1, fractional2);

    for (int64_t i = 0; i < fractional; i++) {
        if (get_fractional(first_data, this->exponent, i) != get_fractional(second_data, other.exponent, i)) {
            return get_fractional(first_data, this->exponent, i) ? 1 : -1;
        }
    }
    if (fractional1 != fractional2) {
        return fractional1 > fractional2 ? 1 : -1;
    }
    return 0;
}

int8_t BigDecimal::compare_negative(const BigDecimal& other) const {
    return static_cast<int8_t>(-(-*this).compare_positive(-other)); // todo: rewrite for faster speed
}

int8_t BigDecimal::compare(const BigDecimal& other) const {
    if (this->is_negative ^ other.is_negative) {
        return this->is_negative ? -1 : 1;
    }
    return this->is_negative ? this->compare_negative(other) : this->compare_positive(other);
}

bool BigDecimal::operator==(const BigDecimal& other) const {
    return this->compare(other) == 0;
}

bool BigDecimal::operator!=(const BigDecimal& other) const {
    return this->compare(other) != 0;
}

bool BigDecimal::operator>(const BigDecimal& other) const {
    return this->compare(other) > 0;
}

bool BigDecimal::operator>=(const BigDecimal& other) const {
    return this->compare(other) >= 0;
}

bool BigDecimal::operator<(const BigDecimal& other) const {
    return this->compare(other) < 0;
}

bool BigDecimal::operator<=(const BigDecimal& other) const {
    return this->compare(other) <= 0;
}

BigDecimal BigDecimal::operator+(const BigDecimal& other) const {
    // todo
}


BigDecimal BigDecimal::operator-(const BigDecimal& other) const {
    return *this + -other;
}

#pragma endregion Operators

static bool contains_only_zeros(const std::vector<bool>& value) {
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
    if (contains_only_zeros(value) && is_negative == false) {
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
    if (contains_only_zeros(value)) {
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
    if (contains_only_zeros(value)) {
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
    for (auto i = 0; i < size; i++) {
        auto to_add = dec_value[0] - '0' >= 5;
        mult2(dec_value);
        this->value.push_back(to_add);
    }
}

void BigDecimal::reverse_value() {
    for (auto i = 0; i < this->capacity; i++) {
        value.push_back(is_negative);
    }
    this->capacity = 0;
    for (auto&& i : value) {
        i = !i;
    }
}
