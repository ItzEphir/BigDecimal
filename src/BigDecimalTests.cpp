//
// Created by ephir on 20.02.2025.
//

#include <gtest/gtest.h>
#include "../include/BigDecimal.h"
#include <vector>

namespace ephir::bigdecimal {
    class BigDecimalTests : public testing::Test {};

    TEST_F(BigDecimalTests, CreateByString) {
        const auto given = "3";
        auto expected = BigDecimal();
        expected.get_raw() = {true, true};
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringWithTrailingZeros) {
        const auto given = "12";
        auto expected = BigDecimal();
        expected.get_raw() = {true, true};
        expected.set_exp(2);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringNegative) {
        const auto given = "-12"; // 0011
        auto expected = BigDecimal();
        expected.get_raw() = {false, false};
        expected.is_negative = true;
        expected.set_exp(2);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringBase2FloatingPoint) {
        const auto given = "12.25";
        auto expected = BigDecimal();
        expected.get_raw() = {true, true, false, false, false, true};
        expected.set_exp(-2);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringBase10FloatingPoint) {
        const auto given = "12.33"; // 1100.010101
        auto expected = BigDecimal();
        expected.get_raw() = {true, true, false, false, false, true, false, true, false, true};
        expected.set_exp(-6);
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }

    TEST_F(BigDecimalTests, CreateByStringBase2NegativeFloatingPoint) {
        const auto given = "-12.25";
        auto expected = BigDecimal();
        expected.get_raw() = {false, false, true, true, true, false};
        expected.set_exp(-2);
        expected.is_negative = true;
        const auto actual = BigDecimal::create(given);
        ASSERT_EQ(expected, actual);
    }
} // ephir::bigdecimal
