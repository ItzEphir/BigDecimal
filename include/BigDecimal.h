//
// Created by Дмитрий Дворянников on 29.01.2025.
//

#ifndef BIGDECIMAL_H
#define BIGDECIMAL_H
#include <vector>


namespace ephir::bigdecimal {
    class BigDecimal final {
    public:
        BigDecimal() = default;

        BigDecimal(const BigDecimal &other) = default;

        explicit BigDecimal(size_t capacity);

        explicit BigDecimal(const std::string_view &value);

        explicit BigDecimal(const char *value);

        explicit BigDecimal(std::int8_t value);

        explicit BigDecimal(std::uint8_t value);

        explicit BigDecimal(std::int16_t value);

        explicit BigDecimal(std::uint16_t value);

        explicit BigDecimal(std::int32_t value);

        explicit BigDecimal(std::uint32_t value);

        explicit BigDecimal(std::int64_t value);

        explicit BigDecimal(std::uint64_t value);

        explicit BigDecimal(std::float_t value);

        explicit BigDecimal(std::double_t value);

        explicit BigDecimal(long double value);

        ~BigDecimal() = default;

        inline BigDecimal operator=(const std::string_view &) const;

        inline BigDecimal operator=(const std::string &) const;;

        inline BigDecimal operator=(const char *) const;

        inline BigDecimal operator=(std::int8_t) const;

        inline BigDecimal operator=(std::uint8_t) const;

        inline BigDecimal operator=(std::int16_t) const;

        inline BigDecimal operator=(std::uint16_t) const;

        inline BigDecimal operator=(std::int32_t) const;

        inline BigDecimal operator=(std::uint32_t) const;

        inline BigDecimal operator=(std::int64_t) const;

        inline BigDecimal operator=(std::uint64_t) const;

        inline BigDecimal operator=(std::float_t) const;

        inline BigDecimal operator=(std::double_t) const;

        inline BigDecimal operator=(long double) const;

    private:
        std::vector<bool> value = {false};
        size_t exponent = 0;
        size_t size_decimal = 1;
        size_t capacity = 1;
    };
} // ephir::bigdecimal

#endif //BIGDECIMAL_H
