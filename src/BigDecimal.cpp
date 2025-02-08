//
// Created by Дмитрий Дворянников on 29.01.2025.
//

#include "../include/BigDecimal.h"

using namespace ephir::bigdecimal;

#pragma region Constructors / Destructors

BigDecimal::BigDecimal(const size_t capacity): value(capacity), capacity(capacity) {
}

BigDecimal::BigDecimal(const std::string_view &value): value(value.size()), capacity(value.size()) {

}

#pragma endregion Constructors / Destructors

#pragma region equals

inline BigDecimal BigDecimal::operator=(const std::string_view &value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::string &value) const {
    return BigDecimal(std::string_view(value));
}

inline BigDecimal BigDecimal::operator=(const char *value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::int8_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::uint8_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::int16_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::uint16_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::int32_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::uint32_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::int64_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::uint64_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::float_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const std::double_t value) const {
    return BigDecimal(value);
}

inline BigDecimal BigDecimal::operator=(const long double value) const {
    return BigDecimal(value);
}

#pragma endregion equals
