//
// Created by ephir on 29.01.2025.
//

#ifndef BIGDECIMAL_H
#define BIGDECIMAL_H
#include <ostream>
#include <vector>


namespace ephir::bigdecimal {
    class BigDecimal final {
    public:
        static BigDecimal ZERO;

#pragma region Constructors / Destructors
        static BigDecimal create(const std::string_view&);

        BigDecimal() = default;

        BigDecimal(const BigDecimal& other) = default;

        BigDecimal(BigDecimal&& other) = default;

        // explicit BigDecimal(size_t accuracy);

        explicit BigDecimal(int8_t value);

        explicit BigDecimal(uint8_t value);

        explicit BigDecimal(int16_t value);

        explicit BigDecimal(uint16_t value);

        explicit BigDecimal(int32_t value);

        explicit BigDecimal(uint32_t value);

        explicit BigDecimal(int64_t value);

        explicit BigDecimal(uint64_t value);

        ~BigDecimal() = default;

#pragma endregion Constructors / Destructors

#pragma region Assignment operators

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

#pragma endregion Assignment operators

#pragma region String output

        [[nodiscard]] std::string to_bin_string() const;

        static std::ostream& binary_encode(std::ostream& out, const BigDecimal& obj);

        void print_binary() const;

#pragma endregion String output

#pragma region Getters / Setters

        void set_exp(const int64_t exp) { this->exponent = exp; }

#pragma endregion Getters / Setters

#pragma region Operators

        BigDecimal operator+() const;

        BigDecimal operator-() const;

        [[nodiscard]] int8_t compare(const BigDecimal& other) const;

        bool operator==(const BigDecimal& other) const;

        bool operator!=(const BigDecimal& other) const;

        bool operator>(const BigDecimal& other) const;

        bool operator>=(const BigDecimal& other) const;

        bool operator<(const BigDecimal& other) const;

        bool operator<=(const BigDecimal& other) const;

        BigDecimal operator+(const BigDecimal& other) const;

        BigDecimal operator-(const BigDecimal& other) const;

#pragma endregion Operators

    private:
#pragma region Fields

        std::vector<bool> value = {false};
        int64_t capacity = 0;
        int64_t exponent = 0;
        bool is_negative = false;

#pragma endregion Fields

#pragma region Useful private methods

        void optimize_number();

        void optimize_start();

        void optimize_exponent();

        void optimize_end();

        void process_integer(const std::string_view&);

        void process_fractional(const std::string_view&);

        void reverse_value();

        [[nodiscard]] int8_t compare_positive(const BigDecimal& other) const;
        [[nodiscard]] int8_t compare_negative(const BigDecimal& other) const;

#pragma endregion Useful private methods

        friend class BigDecimalTests;
    };
} // ephir::bigdecimal

#endif // BIGDECIMAL_H
