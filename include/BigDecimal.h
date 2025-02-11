//
// Created by Дмитрий Дворянников on 29.01.2025.
//

#ifndef BIGDECIMAL_H
#define BIGDECIMAL_H
#include <ostream>
#include <vector>


namespace ephir::bigdecimal {
    static bool containsNotDigit(const std::string_view &);

    class BigDecimal final {
    public:
#pragma region Constructors / Destructors
        static BigDecimal create(const std::string_view &);

        BigDecimal() = default;

        BigDecimal(const BigDecimal &other) = default;

        BigDecimal(BigDecimal &&other) = default;

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

        BigDecimal &operator=(const BigDecimal &other) = default;

        BigDecimal &operator=(BigDecimal &&other) = default;

        BigDecimal &operator=(int8_t);

        BigDecimal &operator=(uint8_t);

        BigDecimal &operator=(int16_t);

        BigDecimal &operator=(uint16_t);

        BigDecimal &operator=(int32_t);

        BigDecimal &operator=(uint32_t);

        BigDecimal &operator=(int64_t);

        BigDecimal &operator=(std::uint64_t);

        // inline BigDecimal &operator=(std::float_t) const;
        //
        // inline BigDecimal &operator=(std::double_t) const;
        //
        // inline BigDecimal &operator=(long double) const;

#pragma endregion assignment operators

        friend std::ostream &operator<<(std::ostream &out, const BigDecimal &obj) {
            if (obj.is_negative) {
                out << "-";
            }
            for (auto i: obj.value) {
                out << i;
            }
            return out;
        }

    private:
        bool is_negative = false;
        std::vector<bool> value;
        size_t exponent = 0;
    };
} // ephir::bigdecimal

#endif //BIGDECIMAL_H
