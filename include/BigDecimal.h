//
// Created by ephir on 29.01.2025.
//

#ifndef BIGDECIMAL_H
#define BIGDECIMAL_H
#include <ostream>
#include <vector>
#include "StringHelper.h"


namespace ephir::bigdecimal {
    class BigDecimal final {
    public:
        static BigDecimal ZERO;
#pragma region Constructors / Destructors
        static BigDecimal create(const std::string_view&);

        BigDecimal() = default;

        BigDecimal(const BigDecimal& other) = default;

        BigDecimal(BigDecimal&& other) = default;

        explicit BigDecimal(size_t size);

        explicit BigDecimal(int8_t value);

        explicit BigDecimal(uint8_t value);

        explicit BigDecimal(int16_t value);

        explicit BigDecimal(uint16_t value);

        explicit BigDecimal(int32_t value);

        explicit BigDecimal(uint32_t value);

        explicit BigDecimal(int64_t value);

        explicit BigDecimal(uint64_t value);

        // explicit BigDecimal(std::float_t value);
        //
        // explicit BigDecimal(std::double_t value);
        //
        // explicit BigDecimal(long double value);

        ~BigDecimal() = default;

#pragma endregion Constructors / Destructors

#pragma region assignment operators

        BigDecimal& operator=(const BigDecimal& other) = default;

        BigDecimal& operator=(BigDecimal&& other) = default;

        BigDecimal& operator=(int8_t);

        BigDecimal& operator=(uint8_t);

        BigDecimal& operator=(int16_t);

        BigDecimal& operator=(uint16_t);

        BigDecimal& operator=(int32_t);

        BigDecimal& operator=(uint32_t);

        BigDecimal& operator=(int64_t);

        BigDecimal& operator=(std::uint64_t);

        // inline BigDecimal &operator=(std::float_t) const;
        //
        // inline BigDecimal &operator=(std::double_t) const;
        //
        // inline BigDecimal &operator=(long double) const;

#pragma endregion assignment operators

        [[nodiscard]] std::string to_bin_string() const;

        static std::ostream& binary_encode(std::ostream& out, const BigDecimal& obj);

        void print_binary() const;

        std::vector<bool>& get_raw() { return value; }

        void set_exp(const int64_t exp) { this->exponent = exp; }

        bool operator==(const BigDecimal& other) const;

        bool is_negative = false;
    private:
        std::vector<bool> value;
        int64_t exponent = 0;

        void optimize_start();

        void optimize_end();

        void process_integer(const std::string_view&);

        void process_fractional(const std::string_view&);

        void reverse_value();
    };
} // ephir::bigdecimal

#endif // BIGDECIMAL_H
