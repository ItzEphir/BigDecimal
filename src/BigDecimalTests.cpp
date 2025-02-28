//
// Created by ephir on 20.02.2025.
//

#include <gtest/gtest.h>
#include "../include/BigDecimal.h"
#include <vector>

namespace ephir::bigdecimal {
    class BigDecimalTests : public testing::Test {
    public:
        static BigDecimal create_expected(const std::vector<bool>& data,
                                         const int64_t exponent,
                                         const bool is_negative = false,
                                         const int64_t capacity = 0) {
            BigDecimal result;
            result.value = data;
            result.exponent = exponent;
            result.is_negative = is_negative;
            result.capacity = capacity;
            return result;
        }
    };

    TEST_F(BigDecimalTests, CreateByString) {
        const auto given = "3";
        const auto expected = create_expected({true, true}, 0, false, 0);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringWithTrailingZeros) {
        const auto given = "12";
        const auto expected = create_expected({true, true}, 2);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringNegative) {
        const auto given = "-12";
        const auto expected = create_expected({false}, 2, true, 1);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringBase2FloatingPoint) {
        const auto given = "12.25";
        const auto expected = create_expected({true, true, false, false, false, true}, -2);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringBase10FloatingPoint) {
        const auto given = "12.33"; // 1100.010101
        const auto expected = create_expected({true, true, false, false, false, true, false, true, false, true}, -6);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringBase2NegativeFloatingPoint) {
        const auto given = "-12.25";
        const auto expected = create_expected({false, false}, -2, true, 4);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringBase2OnlyFloating) {
        const auto given = "0.25";
        const auto expected = create_expected({true}, -2);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByInt8) {
        constexpr int8_t given = 33;
        const auto expected = create_expected({true, false, false, false, false, true}, 0, false, 0);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByInt8Negative) {
        constexpr int8_t given = -33;
        const auto expected = create_expected({false}, 0, true, 5);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByUint8) {
        constexpr uint8_t given = 33;
        const auto expected = create_expected({true, false, false, false, false, true}, 0);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByInt16) {
        constexpr int16_t given = 33;
        const auto expected = create_expected({true, false, false, false, false, true}, 0);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByInt16Negative) {
        constexpr int16_t given = -33;
        const auto expected = create_expected({false}, 0, true, 5);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByUint16) {
        constexpr uint16_t given = 33;
        const auto expected = create_expected({true, false, false, false, false, true}, 0);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByInt32) {
        constexpr int32_t given = 33;
        const auto expected = create_expected({true, false, false, false, false, true}, 0);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByInt32Negative) {
        constexpr int32_t given = -33;
        const auto expected = create_expected({false}, 0, true, 5);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByUint32) {
        constexpr uint32_t given = 33;
        const auto expected = create_expected({true, false, false, false, false, true}, 0);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByInt64) {
        constexpr int64_t given = 33;
        const auto expected = create_expected({true, false, false, false, false, true}, 0);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByInt64Negative) {
        constexpr int64_t given = -33;
        const auto expected = create_expected({false}, 0, true, 5);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByUint64) {
        constexpr uint64_t given = 33;
        const auto expected = create_expected({true, false, false, false, false, true}, 0);
        const auto actual = BigDecimal(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestUnaryMinus) {
        const auto given = BigDecimal::create("12");
        const auto expected = BigDecimal::create("-12");
        const auto actual = -given;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestUnaryMinusWithNegative) {
        const auto given = BigDecimal::create("-12");
        const auto expected = BigDecimal::create("12");
        const auto actual = -given;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestCompare) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("12");
        constexpr auto expected = 0;
        const auto actual = given_a.compare(given_b);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestCompareWithDifferentSigns) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("-12");
        constexpr auto expected = 1;
        const auto actual = given_a.compare(given_b);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestCompareWithDifferentExponents) {
        const auto given_a = BigDecimal::create("12"); // 1100
        const auto given_b = BigDecimal::create("6"); // 110
        constexpr auto expected = 1;
        const auto actual = given_a.compare(given_b);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestEquals) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("12");
        constexpr auto expected = true;
        const auto actual = given_a == given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestEqualsFail) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("-12");
        constexpr auto expected = false;
        const auto actual = given_a == given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestNotEquals) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("12");
        constexpr auto expected = false;
        const auto actual = given_a != given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestGreater) {
        const auto given_a = BigDecimal::create("12.01");
        const auto given_b = BigDecimal::create("12");
        constexpr auto expected = true;
        const auto actual = given_a > given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestGreaterEqualsNotSame) {
        const auto given_a = BigDecimal::create("12.01");
        const auto given_b = BigDecimal::create("12");
        constexpr auto expected = true;
        const auto actual = given_a >= given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestGreaterEqualsSame) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("12");
        constexpr auto expected = true;
        const auto actual = given_a >= given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestLess) {
        const auto given_a = BigDecimal::create("-144");
        const auto given_b = BigDecimal::create("-12");
        constexpr auto expected = true;
        const auto actual = given_a < given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestLessEqualsNotSame) {
        const auto given_a = BigDecimal::create("-144");
        const auto given_b = BigDecimal::create("-12");
        constexpr auto expected = true;
        const auto actual = given_a <= given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestLessEqualsSame) {
        const auto given_a = BigDecimal::create("-144");
        const auto given_b = BigDecimal::create("-144");
        constexpr auto expected = true;
        const auto actual = given_a <= given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestGreaterDiffSigns) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("-12");
        constexpr auto expected = true;
        const auto actual = given_a > given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestPlus) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("15");
        const auto expected = BigDecimal::create("27");
        const auto actual = given_a + given_b;
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, TestMinus) {
        const auto given_a = BigDecimal::create("12");
        const auto given_b = BigDecimal::create("5");
        const auto expected = BigDecimal::create("7");
        const auto actual = given_a - given_b;
        ASSERT_EQ(expected, actual);
    }

} // ephir::bigdecimal
